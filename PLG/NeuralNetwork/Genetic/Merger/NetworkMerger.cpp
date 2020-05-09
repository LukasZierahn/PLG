//
//  NetworkMerger.cpp
//  PLG
//
//  Created by Lukas on 29.04.20.
//  Copyright © 2020 Lukas. All rights reserved.
//

#include "NetworkMerger.hpp"

#include "NeuralNetwork.hpp"
#include "NeuralDistance.h"
#include "MergeNode.hpp"

void NetworkMerger::GenerateMergeMap(NeuralNetwork* inp1, NeuralNetwork* inp2) {
    Cleanup();
    
    layerSetup = inp1->nodeCount;
    
    mergeMap.push_back(new NetworkModel(inp1));
    mergeMap.push_back(new NetworkModel(inp2));

    for (auto model : mergeMap) {
        for (int layer = 0; layer < layerSetup.size(); layer++) {
            for (int node = 0; node < layerSetup[layer]; node++) {
                model->nodes[layer][node] = new MergeNode(model, layer, node);
            }
        }
        
        vector<int> currentConfig(inp1->nodeCount[0], 0);
        
        //evil evil do while loop, sue me
        int i = 0;
        do {
            model->network->EvaluateNetwork(currentConfig, METRIC_DISTANCE);
            
            for (int layer = 0; layer < layerSetup.size(); layer++) {
                for (int node = 0; node < layerSetup[layer]; node++) {
                    MergeNode* mergeNode = model->nodes[layer][node];
                    NeuralNetwork* network = model->network;
                                    
                    mergeNode->values.push_back(network->getNode(layer, node));
                }
            }
                        
            i++;
            
        } while (IncreaseConfig(&currentConfig));
    }
    printf("test");
}

void NetworkMerger::Cleanup() {
    for (auto merge : mergeMap) {
        for (auto list : merge->nodes) {
            for (auto node : list) {
                delete node;
            }
        }
    }
    
    mergeMap.clear();
}


//NeuralNetwork* NetworkMerger::MergeNetworks(NeuralNetwork* inp1, NeuralNetwork* inp2) {
//}
