//
//  Branch.cpp
//  PLG
//
//  Created by Lukas Zierahn on 16.12.19.
//  Copyright © 2019 Lukas Zierahn. All rights reserved.
//
#include "HelperFunction.h"
#include "GeneticTrainer.hpp"

#include "Branch.hpp"

Branch::Branch(GeneticTrainer* geneticTrainer, vector<int> layerSetup, NeuralNetwork* initialNetwork): geneticTrainer(geneticTrainer), layerSetup(layerSetup) {
    population.push_back(initialNetwork);
    populationSize = 1;
    
    r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX + 1u);
    g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX + 1u);
    b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX + 1u);
    initialNetwork->setColor(r, g, b);
    
    pastImprovements.resize(LOOKBACK_LENGTH, 0.001);
}


void Branch::MutateNetwork(NeuralNetwork* target, NeuralNetwork* source, double connectionChance, double BasisChance) {
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

void Branch::MutatePopulation(int newSize) {
    while(newSize < populationSize) {
        delete population[populationSize - 1];
        populationSize -= 1;
    }
    
    population.resize(newSize, nullptr);
    
    while(newSize > populationSize) {
        population[populationSize] = new NeuralNetwork(layerSetup);
        population[populationSize]->setColor(r, g, b);
        populationSize += 1;
    }
    
    for (int i = 1; i < populationSize; i++) {
        MutateNetwork(population[i], population[0], CONNECTION_MUTATION_CHANCE, BIASIS_MUTATION_CHANCE);
    }
}

NeuralNetwork* Branch::getNetwork(int index) {
    if (index >= populationSize || index < 0) {
        throw new runtime_error("Index Error");
    }
    
    return population[index];
}

void Branch::Post() {
    pastImprovements.insert(pastImprovements.begin(), 0);
    
    NeuralNetwork* lastBest = population[0];
    NeuralNetwork* newBest = population[0];
    int newBestIndex = 0;
    for (int i = 0; i < population.size(); i++) {
        if (population[i]->getScore() > newBest->getScore()) {
            if (lastBest->Distance(population[i]) > BRANCH_CREATION_THRESHOLD) {
                geneticTrainer->addBranch(population[i]);
                population[i] = new NeuralNetwork(layerSetup);
            } else {
                newBest = population[i];
                newBestIndex = i;
            }
        }
    }
    population[newBestIndex] = lastBest;
    population[0] = newBest;
    
    pastImprovements[0] += newBest->getScore() - lastBest->getScore();
    pastImprovements[0] /= float(population.size());
        
    
    if (pastImprovements.size() > LOOKBACK_LENGTH) {
        pastImprovements.pop_back();
    }
}

int Branch::DemandPopulation(double averageScore) {
    if (pastImprovements.size() < 2) {
        return 10;
    }
    
    float demandedPopulation = pastImprovements[pastImprovements.size() - 1];
    const float alpha = 0.3;
    
    for (int i = pastImprovements.size() - 2; i >= 0; i--) {
        demandedPopulation = alpha * 20000 * pastImprovements[i] + (1 - alpha) * demandedPopulation;
    }
    
    printf("%f\n", demandedPopulation);
    
    return demandedPopulation < 20 ? 20 : demandedPopulation;
}

Branch::~Branch() {
    for (int i = 0; i < populationSize; i++) {
        delete population[i];
    }
}
