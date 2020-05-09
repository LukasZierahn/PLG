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

class NetworkMerger;

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
    vector<int> connectionCountSums;

    int currentInputNode = 0;
    int currentOutputNode = 0;
    
    float r;
    float g;
    float b;
    
    
    void EvaluateNetwork(vector<int> config, float stepSize);
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
    
    double Distance(NeuralNetwork* neuralNet);

    double getNode(int layer, int node) { return nodes[nodeCountSums[layer] + node]; }
    double getBias(int layer, int node) { return biases[nodeCountSums[layer] + node]; }
    double getConnection(int layer, int from, int to) { return connections[connectionCountSums[layer - 1] + (to * nodeCount[layer - 1]) + from]; }

    vector<double>* getNodes() { return &nodes; };
    vector<double>* getBiases() { return &biases; };
    vector<double>* getConnections() { return &connections; };
    
    vector<int>* getNodeCount() { return &nodeCount; }
    
    void setColor(float r, float g, float b) {
        this->r = r;
        this->g = g;
        this->b = b;
    }
    float getR() { return r; }
    float getG() { return g; }
    float getB() { return b; }
    
    ~NeuralNetwork();
    
    friend class NetworkMerger;
};

#endif
