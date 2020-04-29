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

#define METRIC_STEPS 3
#define METRIC_STEPS_START 1
#define METRIC_DISTANCE 100.0f

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
    
    float r;
    float g;
    float b;
public:
    NeuralNetwork(vector<int> layerSetup);
    //NeuralNetwork(vector<int> layerSetup);

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

    vector<double>* getNodes() { return &nodes; };
    vector<double>* getBiases() { return &biases; };
    vector<double>* getConnections() { return &connections; };
    
    void setColor(float r, float g, float b) {
        this->r = r;
        this->g = g;
        this->b = b;
    }
    float getR() { return r; }
    float getG() { return g; }
    float getB() { return b; }
    
    ~NeuralNetwork();
};

#endif
