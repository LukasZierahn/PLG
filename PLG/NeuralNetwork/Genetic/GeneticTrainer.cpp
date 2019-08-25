//
//  GeneticTrainer.cpp
//  PLG
//
//  Created by Lukas Zierahn on 14.08.19.
//  Copyright © 2019 Lukas Zierahn. All rights reserved.
//

#include "NeuralNetwork.hpp"
#include "NeuralNetworkScenario.hpp"

#include "GeneticTrainer.hpp"


GeneticTrainer::GeneticTrainer(int population, vector<int> layerSetup, NeuralNetworkScenario* scenario): population(population), scenario(scenario) {
    for (int i = 0; i < population; i++) {
        networks.push_back(new NeuralNetwork(layerSetup));
        networks[i]->RandomizeValues();
    }
    
    scenario->setNeuralNetworks(networks);
}

void GeneticTrainer::Mainloop() {
    while(true) {
        iteration++;
        printf("Starting iteration %d\n", iteration);
        if (scenario->Compute()) {
            break;
        }
        
        scenario->Reset();
    }
}

GeneticTrainer::~GeneticTrainer() {
    for (int i = 0; i < population; i++) {
        delete networks[i];
    }
}
