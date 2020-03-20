//
//  Branch.hpp
//  PLG
//
//  Created by Lukas Zierahn on 16.12.19.
//  Copyright © 2019 Lukas Zierahn. All rights reserved.
//

#ifndef Branch_hpp
#define Branch_hpp

#include <stdio.h>
#include "NeuralNetwork.hpp"

#include <vector>
using namespace::std;

class GeneticTrainer;

#define CONNECTION_MUTATION_CHANCE 0.1
#define BIASIS_MUTATION_CHANCE 0.05

#define LOOKBACK_LENGTH 50

class Branch {
    GeneticTrainer* geneticTrainer;
    
    int populationSize;
    vector<NeuralNetwork*> population;
    vector<int> layerSetup;
    
    vector<float> pastImprovements;
    
    void MutateNetwork(NeuralNetwork* target, NeuralNetwork* source, double connectionChance, double BasisChance);
    
    float r;
    float g;
    float b;

public:
    Branch(GeneticTrainer* geneticTrainer, vector<int> layerSetup, NeuralNetwork* initialNetwork);
    
    void MutatePopulation(int newSize);
    double Distance(Branch* branch) { return getNetwork(0)->Distance(branch->getNetwork(0)); }
    double Distance(NeuralNetwork* network) { return getNetwork(0)->Distance(network); }

    void Post();
    int DemandPopulation(double averageScore);
    
    NeuralNetwork* getNetwork(int index);
    vector<NeuralNetwork*> getNetworks() { return population; }
    int getPopulationSize() { return populationSize; }
    float getScore() { return population[0]->getScore(); }
    
    ~Branch();
};

#endif /* Branch_hpp */
