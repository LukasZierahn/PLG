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

class GeneticTrainer {
private:
    int population;
    int iteration = 0;
    
    NeuralNetworkScenario* scenario;
    
    vector<NeuralNetwork*> networks;
    
public:
    
    GeneticTrainer(int population, vector<int> layerSetup, NeuralNetworkScenario* scenario);
    
    void Mainloop();
    
    ~GeneticTrainer();
};

#endif /* GeneticTrainer_hpp */
