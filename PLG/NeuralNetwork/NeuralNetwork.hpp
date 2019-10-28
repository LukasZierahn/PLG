//
//  NeuralNetwork.hpp
//  PLG
//
//  Created by Lukas Zierahn on 07.07.19.
//  Copyright © 2019 Lukas Zierahn. All rights reserved.
//

#ifndef NeuralNetwork_hpp
#define NeuralNetwork_hpp

#include <vector>
using namespace::std;

class NeuralNetwork
{
    float score = 0.0f;
    
    vector<int> nodeCount; //this is per layer
    vector<int> nodeCountSums; //this is summing up the nodes per layer
    
    int layerCount = 0;
    int totalNodeCount = 0;
    int totalConnectionCount = 0;
    
    vector<double> nodes;
    vector<double> biases;
    vector<double> connections;
    
    int currentInputNode = 0;
    int currentOutputNode = 0;

public:
    NeuralNetwork(vector<int> layerSetup);
    
    void Compute();
    void RandomizeValues();
    
    void setScore(float score) { this->score = score; }
    float getScore() { return score; }

    void setNode(int node, double value) { nodes[node] = value; }
    
    void resetCurrentInputNode() { currentInputNode = 0; }
    void setNextInputNode(double value);
    
    void resetCurrentOutputNode() { currentOutputNode = 0; }
    double getNextOutputNode(bool stretch = false);
    
    double DistanceSquared(NeuralNetwork* neuralNet);

    vector<double>* getNodes() { return &nodes; };
    vector<double>* getBiases() { return &biases; };
    vector<double>* getConnections() { return &connections; };

    ~NeuralNetwork();
};

#endif
