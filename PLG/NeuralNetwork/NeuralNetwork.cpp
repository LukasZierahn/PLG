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
    nodeCount = layerSetup;
    
    nodeCountSums.push_back(0);
    
    for (int i = 0; i < layerSetup.size(); i++) {
        totalNodeCount += layerSetup[i];
        if (i != layerSetup.size() - 1) {
            nodeCountSums.push_back(totalNodeCount);
            totalConnectionCount += layerSetup[i] * layerSetup[i + 1];
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

void IncreaseConfig(vector<int>* config) {
    for (unsigned long i = config->size() - 1; i >= 0; i--) {
        if ((*config)[i] + 1 < METRIC_STEPS || i == 0) {
            (*config)[i] += 1;
            return;
        }
        
        (*config)[i] = 0;
    }
}

void EvaluateNetwork(NeuralNetwork* network, vector<int> config, float stepSize) {
    network->resetCurrentInputNode();
    for (auto configValue : config) {
        network->setNextInputNode((METRIC_STEPS_START + configValue) * stepSize);
    }
    
    network->Compute();
}

double NeuralNetwork::Distance(NeuralNetwork* neuralNet) {
    if (neuralNet == this) {
        return 0.0f;
    }
    
    double distanceSum = 0;
    float stepSize = METRIC_DISTANCE;
    
    vector<int> currentConfig(nodeCount[0], 0);
    
    while (currentConfig[0] < METRIC_STEPS) {
        EvaluateNetwork(this,       currentConfig, stepSize);
        EvaluateNetwork(neuralNet,  currentConfig, stepSize);
        
        resetCurrentOutputNode();
        neuralNet->resetCurrentOutputNode();
        double bufferSum = 0;
        for (int i = 0; i < nodeCount[nodeCount.size() - 1]; i++) {
            bufferSum += pow(neuralNet->getNextOutputNode() - getNextOutputNode(), 2);
        }
        distanceSum += sqrt(bufferSum);
        
        IncreaseConfig(&currentConfig);
    }
    
    distanceSum /= (double)pow(METRIC_STEPS, nodeCount[0]);
    
    printf("Distance: %f\n", distanceSum);
    return distanceSum;
}

NeuralNetwork::~NeuralNetwork() {
}

