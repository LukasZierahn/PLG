//
//  Racing.hpp
//  PLG
//
//  Created by Lukas Zierahn on 10.08.19.
//  Copyright © 2019 Lukas Zierahn. All rights reserved.
//

#ifndef Racing_hpp
#define Racing_hpp

#include <stdio.h>
#include <vector>
using namespace std;

#include "NeuralNetworkScenario.hpp"

#define TIME_STEPS 1


class Pixel;
class Render;
class Map;
class RaceCar;

class Racing : public NeuralNetworkScenario {
private:
    Render* render;
    
    Map* map;
    
    vec3 startingPosition;
    
    vector<RaceCar*> raceCarVec;
    
public:
    Racing(int carCount);
    
    void setNeuralNetworks(vector<NeuralNetwork*> Networks);
    vector<NeuralNetwork*> getNeuralNetworks();
    
    bool Compute();
    void Reset();
    
    vector<RaceCar*>* getRaceCarVec() { return &raceCarVec; }
    
    ~Racing();
};

#endif /* Racing_hpp */
