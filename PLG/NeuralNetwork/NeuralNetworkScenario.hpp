//
//  NeuralNetworkScenario.hpp
//  PLG
//
//  Created by Lukas Zierahn on 25.08.19.
//  Copyright © 2019 Lukas Zierahn. All rights reserved.
//

#ifndef NeuralNetworkScenario_hpp
#define NeuralNetworkScenario_hpp

#include <stdio.h>
#include <vector>
using namespace std;

class NeuralNetwork;

class NeuralNetworkScenario {
public:
    
    virtual void removeAllNetworks() { throw new runtime_error("Called virtual function removeAllNetworks"); }
    virtual void addNetworks(vector<NeuralNetwork*> networks) { throw new runtime_error("Called virtual function addNetworks"); }
    virtual void setNeuralNetworks(vector<NeuralNetwork*> networks) { throw new runtime_error("Called virtual function networks"); }
    
    virtual bool Compute() { throw new runtime_error("Called virtual function Compute"); }
    
    virtual void Reset() { throw new runtime_error("Called virtual function Reset"); }
};

#endif /* NeuralNetworkScenario_hpp */
