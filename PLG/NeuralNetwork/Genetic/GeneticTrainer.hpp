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

#define CONNECTION_MUTATION_CHANCE 0.1
#define BIASIS_MUTATION_CHANCE 0.05

class NeuralNetwork;
class NeuralNetworkScenario;

class GeneticTrainer {
private:
    int population;
    int iteration = 0;
    
    double highscore = 0;
    double averageScore = 0;
    int lastImprovement = 0;
    
    NeuralNetworkScenario* scenario;
    
    vector<NeuralNetwork*> networks;
    
public:
    
    GeneticTrainer(int population, vector<int> layerSetup, NeuralNetworkScenario* scenario);
    
    void Mainloop();
    
    void MutateNetwork(NeuralNetwork* target, NeuralNetwork* source);
    void CombineNetworks(NeuralNetwork* target, NeuralNetwork* source1, NeuralNetwork* source2);
    
    ~GeneticTrainer();
};

#endif /* GeneticTrainer_hpp */
