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
    NeuralNetwork* network = nullptr;
    int layer = 0;
    int node = 0;

    vector<float> forwardImportance; //Importance for the nodes in the next layer
    vector<float> backwardsImportance; //Importance of the nodes in the previous layer for this node
    float aggregatedImportance = 0.0f;
    
    bool include = false;
};

class NetworkMerger {
    vector<int> layerSetup;
    vector<vector<MergeNode>> mergeMap;
    
    
    
    void GenerateMergeMap(NeuralNetwork* inp1, NeuralNetwork* inp2);
    
public:
    NeuralNetwork* MergeNetworks(NeuralNetwork* inp1, NeuralNetwork* inp2);
};

#endif /* NetworkMerger_hpp */
