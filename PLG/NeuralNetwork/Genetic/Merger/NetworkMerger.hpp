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
#include <cmath>
#include <vector>
using namespace std;

#include "NeuralNetwork.hpp"

struct MergeNode;

struct NetworkModel {
    NeuralNetwork* network = nullptr;
    vector<vector<MergeNode*>> nodes;
    
    NetworkModel(NeuralNetwork* network): network(network) {
        vector<int> layerSetup = *network->getNodeCount();
        
        for (int count : *network->getNodeCount()) {
            nodes.push_back(vector<MergeNode*>(count, nullptr));
        }
    }
};

class NetworkMerger {
    vector<int> layerSetup;
    vector<NetworkModel*> mergeMap;
        
public:    
    void GenerateMergeMap(NeuralNetwork* inp1, NeuralNetwork* inp2);

    void Cleanup();
    
    NeuralNetwork* MergeNetworks(NeuralNetwork* inp1, NeuralNetwork* inp2);
    
    ~NetworkMerger() {
        Cleanup();
    }
    
};

#endif /* NetworkMerger_hpp */
