//
//  NetworkMerger.hpp
//  PLG
//
//  Created by Lukas on 29.04.20.
//  Copyright © 2020 Lukas. All rights reserved.
//

#ifndef NetworkMerger_hpp
#define NetworkMerger_hpp

#include <stdio.h>
#include <vector>
using namespace std;

class NeuralNetwork;

struct MergeNode {
    int layer = 0;
    int node = 0;
    
    NeuralNetwork* network = nullptr;
};

class NetworkMerger {
    vector<int> layerSetup;
    vector<vector<MergeNode>> mergeMap;
    
    void GenerateMergeMap(NeuralNetwork inp1, NeuralNetwork inp2);
    
public:
    NeuralNetwork* MergeNetworks(NeuralNetwork inp1, NeuralNetwork inp2);
};

#endif /* NetworkMerger_hpp */
