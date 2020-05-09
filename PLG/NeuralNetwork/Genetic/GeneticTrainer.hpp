//
//  GeneticTrainer.hpp
//  PLG
//
//  Created by Lukas Zierahn on 14.08.19.
//  Copyright © 2019 Lukas Zierahn. All rights reserved.
//

#ifndef GeneticTrainer_hpp
#define GeneticTrainer_hpp

#include <stdio.h>

#include <vector>
using namespace std;

class NeuralNetwork;
class NeuralNetworkScenario;
class Branch;
class NetworkMerger;

#define INITIAL_BRANCHES 3

#define BRANCH_CREATION_THRESHOLD 0.3

class GeneticTrainer {
private:
    vector<int> layerSetup;
    
    int population;
    int iteration = 0;
        
    const int keptPopulation = 5;
    
    NetworkMerger* networkMerger = nullptr;
    
    NeuralNetworkScenario* scenario;
    
    vector<Branch*> branches;

public:
    
    GeneticTrainer(int population, vector<int> layerSetup, NeuralNetworkScenario* scenario);
    
    void addBranch(NeuralNetwork* initialNetwork);
    
    void Mainloop();
                
    NeuralNetwork* CombineNetworks(NeuralNetwork* source1, NeuralNetwork* source2);

    ~GeneticTrainer();
};

#endif /* GeneticTrainer_hpp */
