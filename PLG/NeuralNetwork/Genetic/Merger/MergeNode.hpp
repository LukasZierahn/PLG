//
//  MergeNode.hpp
//  PLG
//
//  Created by Lukas on 01.05.20.
//  Copyright © 2020 Lukas. All rights reserved.
//

#ifndef MergeNode_hpp
#define MergeNode_hpp

#include <stdio.h>
#include <vector>

using namespace std;

class NetworkModel;
class NeuralNetwork;

struct MergeNode {
    NetworkModel* networkModel = nullptr;
    NeuralNetwork* network = nullptr;
    vector<int> layerSetup;
    
    int layer = 0;
    int node = 0;

    vector<double> values;
    vector<double> forwardImportance; //Importance for the nodes in the next layer
    vector<double> backwardsImportance; //Importance of the nodes in the previous layer for this node
    vector<double> relation;
    
    bool include = false;
    
    MergeNode(NetworkModel* networkModel, int layer, int node);
    
    double getImportance();
    
    void ComputeImportance();
};

#endif /* MergeNode_hpp */
