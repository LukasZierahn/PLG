//
//  GeneticTrainer.cpp
//  PLG
//
//  Created by Lukas Zierahn on 14.08.19.
//  Copyright © 2019 Lukas Zierahn. All rights reserved.
//

#include "NeuralNetwork.hpp"
#include "NeuralNetworkScenario.hpp"
#include "HelperFunction.h"

#include "GeneticTrainer.hpp"


GeneticTrainer::GeneticTrainer(int population, vector<int> layerSetup, NeuralNetworkScenario* scenario): population(population), scenario(scenario) {
    for (int i = 0; i < population; i++) {
        networks.push_back(new NeuralNetwork(layerSetup));
        networks[i]->RandomizeValues();
    }
    
    scenario->setNeuralNetworks(networks);
}

bool isBigger(NeuralNetwork* A, NeuralNetwork* B) {
    return A->getScore() > B->getScore();
}

void GeneticTrainer::Mainloop() {
    while(true) {
        iteration++;
        
        if (scenario->Compute()) {
            break;
        }
        
        vector<NeuralNetwork*> results = scenario->getNeuralNetworks();
        sort(results.begin(), results.end(), isBigger);
        
        if (results[0]->getScore() > highscore) {
            highscore = results[0]->getScore();
            lastImprovement = iteration;
        }
        
        averageScore = 0;
        for (int i = 0; i < results.size(); i++) {
            averageScore += results[i]->getScore();
        }
        averageScore /= results.size();

        for (int i = 0; i < results.size(); i++) {
            printf("Car %d, result: %f\n", i, results[i]->getScore());
        }
        printf("Iteration %d, Score %f/%f, Last Improvement %d\n", iteration, highscore, averageScore, lastImprovement);

        
        for (int i = 5; i < 10; i++) {
            MutateNetwork(results[i], results[i - 5]);
        }
        
        for (int i = 10; i < 20; i++) {
            MutateNetwork(results[i], results[i - 10]);
        }

//        for (int i = 10; i < results.size(); i++) {
//            MutateNetwork(results[i], results[i - 10]);
//        }

        scenario->Reset();
    }
}

void GeneticTrainer::CombineNetworks(NeuralNetwork* target, NeuralNetwork* source1, NeuralNetwork* source2) {
    vector<double>* connectionsTarget = target->getConnections();
    vector<double>* connectionsSource1 = source1->getConnections();
    vector<double>* connectionsSource2 = source2->getConnections();
    
    for (long i = 0; i < connectionsTarget->size(); i++) {
        (*connectionsTarget)[i] = rand()/(double)(RAND_MAX + 1u) < 0.5 ? (*connectionsSource1)[i] : (*connectionsSource2)[i];
    }
    
    vector<double>* biasesTarget = target->getBiases();
    vector<double>* biasesSource1 = source1->getBiases();
    vector<double>* biasesSource2 = source2->getBiases();
    for (long i = 0; i < biasesTarget->size(); i++) {
        (*biasesTarget)[i] = rand()/(double)(RAND_MAX + 1u) < 0.5 ? (*biasesSource1)[i] : (*biasesSource2)[i];
    }
}

void GeneticTrainer::MutateNetwork(NeuralNetwork* target, NeuralNetwork* source) {
    vector<double>* connectionsTarget = target->getConnections();
    vector<double>* connectionsSource = source->getConnections();

    for (long i = 0; i < connectionsTarget->size(); i++) {
        if (rand()/(double)(RAND_MAX + 1u) < CONNECTION_MUTATION_CHANCE) {
            (*connectionsTarget)[i] = (*connectionsSource)[i] + (2 * (rand()/(double)(RAND_MAX + 1u)) - 1);
        } else {
            (*connectionsTarget)[i] = (*connectionsSource)[i];
        }
    }
    
    vector<double>* biasesTarget = target->getBiases();
    vector<double>* biasesSource = source->getBiases();
    for (long i = 0; i < biasesTarget->size(); i++) {
        if (rand()/(double)(RAND_MAX + 1u) < BIASIS_MUTATION_CHANCE) {
            (*biasesTarget)[i] = (*biasesSource)[i] + (2 * (rand()/(double)(RAND_MAX + 1u)) - 1);
        } else {
            (*biasesTarget)[i] = (*biasesSource)[i];
        }
    }
}

GeneticTrainer::~GeneticTrainer() {
    for (int i = 0; i < population; i++) {
        delete networks[i];
    }
}
