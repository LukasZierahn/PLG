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

float GeneticTrainer::RequiredChange() {
    
    float result = improvementDelta * 0.3f < 1 ? 1: pow(improvementDelta * 0.3f, 2);
    result = result > 25 ? 25 : result;
    
    return result;
}

bool isBigger(NeuralNetwork* A, NeuralNetwork* B) {
    return A->getScore() > B->getScore();
}

void GeneticTrainer::Mainloop() {
    while(true) {
        iteration++;
        improvementDelta = iteration - lastImprovement;
        
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

        printf("Iteration %d, Score %f/%f, Last Improvement %d/%d, Required Difference: %f\n", iteration, highscore, averageScore, lastImprovement, improvementDelta, RequiredChange());
        for (int i = 0; i < results.size(); i++) {
            printf("Car %d, result: %f, distance: %f\n", i, results[i]->getScore(), results[i]->DistanceSquared(results[0]));
        }
        printf("\n");
        
        
        int offset = keptPopulation;
        for (int i = offset; i < offset + 15; i++) {
            int repeatIterations = 1;
            repeat:;
            
            //            MutateNetwork(results[i], results[i - 5], repeatIterations * improvementDelta * 0.1f, repeatIterations * improvementDelta * 0.05);
            MutateNetwork(results[i], results[(i - offset) % keptPopulation], CONNECTION_MUTATION_CHANCE, BIASIS_MUTATION_CHANCE);

            for (int j = 0; j < keptPopulation; j++) {
                if (results[i]->DistanceSquared(results[j]) < RequiredChange() && repeatIterations < 1000) {
                    repeatIterations++;
                    goto repeat;
                }
            }
        }
        offset += 15;
        
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

void GeneticTrainer::MutateNetwork(NeuralNetwork* target, NeuralNetwork* source, double connectionChance, double BasisChance) {
    vector<double>* connectionsTarget = target->getConnections();
    vector<double>* connectionsSource = source->getConnections();

    for (long i = 0; i < connectionsTarget->size(); i++) {
        if (rand()/(double)(RAND_MAX + 1u) < connectionChance) {
            (*connectionsTarget)[i] = (*connectionsSource)[i] + 2 * (2 * (rand()/(double)(RAND_MAX + 1u)) - 1);
        } else {
            (*connectionsTarget)[i] = (*connectionsSource)[i];
        }
    }
    
    vector<double>* biasesTarget = target->getBiases();
    vector<double>* biasesSource = source->getBiases();
    for (long i = 0; i < biasesTarget->size(); i++) {
        if (rand()/(double)(RAND_MAX + 1u) < BasisChance) {
            (*biasesTarget)[i] = (*biasesSource)[i] + 2 * (2 * (rand()/(double)(RAND_MAX + 1u)) - 1);
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
