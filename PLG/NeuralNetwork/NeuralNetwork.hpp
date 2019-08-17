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
    

public:
    NeuralNetwork(vector<int> layerSetup);
    
    void Compute();
    void RandomizeValues();

    void setScore(float score) { this->score = score; }
    float getScore() { return score; }

    ~NeuralNetwork();
};

#endif
