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

#include "NeuralDistance.h"

NeuralNetwork::NeuralNetwork(vector<int> layerSetup) {
    nodeCount = layerSetup;
    
    nodeCountSums.push_back(0);
    connectionCountSums.push_back(0);
    
    for (int i = 0; i < layerSetup.size(); i++) {
        totalNodeCount += layerSetup[i];
        if (i != layerSetup.size() - 1) {
            nodeCountSums.push_back(totalNodeCount);
            totalConnectionCount += layerSetup[i] * layerSetup[i + 1];
            if (i != layerSetup.size() - 2) {
                connectionCountSums.push_back(totalConnectionCount);
            }
        }
    }
    
    nodes = vector<double>(totalNodeCount, 0);
    biases = vector<double>(totalNodeCount, 0);
    connections = vector<double>(totalConnectionCount, 0);
}

void NeuralNetwork::Compute() {
    int connectionPos = 0;
    int biasPos = 0;
    double sum = 0;
    
    for (int i = 0; i < nodeCount.size(); i++) {
        if (i == 0) {
            continue;
        }
        
        for (int j = 0; j < nodeCount[i]; j++) {
            sum = -biases[biasPos];
            biasPos++;
            
            for (int k = 0; k < nodeCount[i - 1]; k++) {
                sum -= nodes[nodeCountSums[i - 1] + k] * connections[connectionPos];
                connectionPos++;
            }
            
            nodes[nodeCountSums[i] + j] = 1.0f / (1.0f + exp(sum));
        }
    }

}

void NeuralNetwork::RandomizeValues() {
    for (int i = 0; i < totalNodeCount; i++) {
        nodes[i] = rand()/(double)(RAND_MAX + 1u);
        biases[i] = (2 * (rand()/(double)(RAND_MAX + 1u)) - 1);
    }
        
    for (int i = 0; i < totalConnectionCount; i++) {
        connections[i] = (2 * (rand()/(double)(RAND_MAX + 1u)) - 1);
    }
}

void NeuralNetwork::setNextInputNode(double value) {
    if (currentInputNode > nodeCount[0]) {
        throw new runtime_error("Tried to set input node after all input nodes have been set");
    }
    
    setNode(currentInputNode, value);
    currentInputNode++;
}

double NeuralNetwork::getNextOutputNode(bool stretch) {
    if (currentOutputNode > nodeCount[nodeCount.size() - 1]) {
        throw new runtime_error("Tried to get output node after all output nodes have been gotten");
    }
    
    currentOutputNode++;
    if (stretch) {
        return 2 * (nodes[nodeCountSums[nodeCountSums.size() - 1] + currentOutputNode - 1]) - 1;
    } else {
        return nodes[nodeCountSums[nodeCountSums.size() - 1] + currentOutputNode - 1];
    }
}

void NeuralNetwork::EvaluateNetwork(vector<int> config, float stepSize) {
    resetCurrentInputNode();
    for (auto configValue : config) {
        setNextInputNode((METRIC_STEPS_START + configValue) * stepSize);
    }
    
    Compute();
}

double NeuralNetwork::Distance(NeuralNetwork* neuralNet) {
    if (neuralNet == this) {
        return 0.0f;
    }
        
    double distanceSum = 0;
    
    vector<int> currentConfig(nodeCount[0], 0);
    
    //evil evil do while loop, sue me
    do {
        EvaluateNetwork(currentConfig, METRIC_DISTANCE);
        neuralNet->EvaluateNetwork(currentConfig, METRIC_DISTANCE);
        
        resetCurrentOutputNode();
        neuralNet->resetCurrentOutputNode();
        double bufferSum = 0;
        for (int i = 0; i < nodeCount[nodeCount.size() - 1]; i++) {
            bufferSum += pow(neuralNet->getNextOutputNode() - getNextOutputNode(), 2);
        }
        distanceSum += sqrt(bufferSum);
        
    } while (IncreaseConfig(&currentConfig));
    
    distanceSum /= (double)pow(METRIC_STEPS, nodeCount[0]);
    
    printf("Distance: %f\n", distanceSum);
    return distanceSum;
}

NeuralNetwork::~NeuralNetwork() {
}

