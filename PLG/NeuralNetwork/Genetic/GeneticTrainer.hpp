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

class GeneticTrainer {
private:
    int population;
    vector<NeuralNetwork*> networks;
    
public:
    
    GeneticTrainer(int population, vector<int> layerSetup);
    
    
    
    ~GeneticTrainer();
};

#endif /* GeneticTrainer_hpp */
