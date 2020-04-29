//
//  GeneticTrainer.cpp
//  PLG
//
//  Created by Lukas Zierahn on 14.08.19.
//  Copyright © 2019 Lukas Zierahn. All rights reserved.
//

#include "NeuralNetwork.hpp"
#include "NeuralNetworkScenario.hpp"
#include "Branch.hpp"

#include "GeneticTrainer.hpp"


GeneticTrainer::GeneticTrainer(int population, vector<int> layerSetup, NeuralNetworkScenario* scenario): population(population), scenario(scenario), layerSetup(layerSetup) {
    while(branches.size() < INITIAL_BRANCHES) {
        NeuralNetwork* newNeuralNet = new NeuralNetwork(layerSetup);
        newNeuralNet->RandomizeValues();
        addBranch(newNeuralNet);
    }
}

void GeneticTrainer::addBranch(NeuralNetwork* initialNetwork) {
    
    for (auto branch : branches) {
        if (branch->Distance(initialNetwork) < BRANCH_CREATION_THRESHOLD) {
            delete initialNetwork;
            return;
        }
    }
    
    branches.push_back(new Branch(this, layerSetup, initialNetwork));
}

void GeneticTrainer::Mainloop() {
    while(true) {
        iteration++;
        
        scenario->removeAllNetworks();
        for (int i = 0; i < branches.size(); i++) {
            scenario->addNetworks(branches[i]->getNetworks());
        }
        
        if (scenario->Compute()) {
            break;
        }
        
        double averageScore = 0.0f;
        int totalPopulation = 0;
        for (int i = 0; i < branches.size(); i++) {
            branches[i]->Post();
            totalPopulation += branches[i]->getPopulationSize();
            averageScore += branches[i]->getScore();
        }
        averageScore /= double(totalPopulation);
                
        for (int i = 0; i < branches.size(); i++) {
            branches[i]->MutatePopulation(branches[i]->DemandPopulation(averageScore));
        }
        
        scenario->Reset();
    }
}

NeuralNetwork* GeneticTrainer::CombineNetworks(NeuralNetwork* source1, NeuralNetwork* source2) {
    
    NeuralNetwork* output = new NeuralNetwork(layerSetup);
    
    return output;
}

GeneticTrainer::~GeneticTrainer() {
    for (int i = 0; i < branches.size(); i++) {
        delete branches[i];
    }
}
