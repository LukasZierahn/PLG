//
//  NeuralNetwork.cpp
//  PLG
//
//  Created by Lukas Zierahn on 07.07.19.
//  Copyright © 2019 Lukas Zierahn. All rights reserved.
//

#include "NeuralNetwork.hpp"

#include <cmath>
#include <cstdlib>

NeuralNetwork::NeuralNetwork(vector<int> layerSetup) {
    this->nodeCount = layerSetup;
    
    this->nodeCountSums.push_back(0);
    
    for (int i = 0; i < layerSetup.size(); i++) {
        this->totalNodeCount += layerSetup[i];
        if (i != layerSetup.size() - 1) {
            this->nodeCountSums.push_back(this->totalNodeCount);
            this->totalConnectionCount += layerSetup[i] * layerSetup[i + 1];
        }
    }
    
    this->nodes.reserve(this->totalNodeCount);
    this->biases.reserve(this->totalNodeCount);
    this->connections.reserve(this->totalConnectionCount);

    srand(time(nullptr));
}

void NeuralNetwork::Compute() {
    int connectionPos = 0;
    int biasPos = 0;
    double sum = 0;
    
    for (int i = 0; i < this->nodeCount.size(); i++) {
        if (i == 0) {
            continue;
        }
        
        for (int j = 0; j < this->nodeCount[i]; j++) {
            sum = -this->biases[biasPos];
            biasPos++;
            
            for (int k = 0; k < this->nodeCount[i - 1]; k++) {
                sum -= this->nodes[this->nodeCountSums[i - 1] + k] * this->connections[connectionPos];
                connectionPos++;
            }
            
            this->nodes[this->nodeCountSums[i] + j] = 1.0f / (1.0f + exp(sum));
        }
    }

}

void NeuralNetwork::RandomizeValues() {
    for (int i = 0; i < this->totalNodeCount; i++) {
        this->nodes[i] = rand()/(RAND_MAX + 1u);
        this->biases[i] = rand()/(RAND_MAX + 1u);
    }
        
    for (int i = 0; i < this->totalConnectionCount; i++) {
        this->connections[i] = rand()/(RAND_MAX + 1u);
    }
}


NeuralNetwork::~NeuralNetwork() {
}

void NeuralNetwork::setNode(int layer, int position, double value) {
    int absolutePosition = this->nodeCountSums[layer] + position;
    
    this->nodes[absolutePosition] = value;
}

void NeuralNetwork::setConnection(int absolutePosition, double value) {
    this->connections[absolutePosition] = value;
}

void NeuralNetwork::setBiases(int absolutePosition, double value) {
    this->biases[absolutePosition] = value;
}

double NeuralNetwork::getNode(int layer, int position) { 
    int absolutePosition = this->nodeCountSums[layer] + position;
    
    return this->nodes[absolutePosition];
}

