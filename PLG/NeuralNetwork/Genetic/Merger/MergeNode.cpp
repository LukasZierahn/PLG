//
//  MergeNode.cpp
//  PLG
//
//  Created by Lukas on 01.05.20.
//  Copyright © 2020 Lukas. All rights reserved.
//

#include "MergeNode.hpp"

#include "NeuralNetwork.hpp"
#include "NetworkMerger.hpp"

MergeNode::MergeNode(NetworkModel *networkModel, int layer, int node): networkModel(networkModel), layer(layer), node(node) {
    network = networkModel->network;
    layerSetup = *network->getNodeCount();
    
    if (layer == 0) {
        backwardsImportance = vector<double>(1, 0.0f);
    } else {
        backwardsImportance = vector<double>(layerSetup[layer - 1], 0.0f);
    }

    if (layer == layerSetup.size() - 1) {
        forwardImportance = vector<double>(1, 0.0f);
    } else {
        forwardImportance = vector<double>(layerSetup[layer + 1], 0.0f);
    }
}

void MergeNode::ComputeImportance() {
    if (layer != 0) {
        double totalInfluence = 0;
        for (int i = 0; i < values.size(); i++) {
            totalInfluence = fabs(network->getBias(layer, node));
            for (int j = 0; j < layerSetup[layer - 1]; j++) {
                totalInfluence += fabs(networkModel->nodes[layer - 1][j]->values[i] * network->getConnection(layer, j, node));
            }
        
            for (int j = 0; j < layerSetup[layer - 1]; j++) {
                double relativeImportance = fabs(networkModel->nodes[layer - 1][j]->values[i] * network->getConnection(layer, j, node) / totalInfluence);
                backwardsImportance[j] += relativeImportance;
                networkModel->nodes[layer - 1][j]->forwardImportance[node] += relativeImportance;
            }
        }
    }
}

double MergeNode::getImportance() {
    return 0.0;
}

