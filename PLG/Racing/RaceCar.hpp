//
//  RaceCar.hpp
//  PLG
//
//  Created by Lukas Zierahn on 13.08.19.
//  Copyright © 2019 Lukas Zierahn. All rights reserved.
//

#ifndef RaceCar_hpp
#define RaceCar_hpp

#include <stdio.h>
#include "includeEngine.h"

#define CAR_SCALE 0.05f
#define CAR_SENSORS {0.0, M_PI * 0.125, M_PI * 0.25, M_PI * 0.5, M_PI, M_PI * 1.5, M_PI * 1.75, M_PI * 1.875}

#define CAR_NN_INPUT_NODES 8
#define CAR_NN_OUTPUT_NODES 2

#define VELOCITY_FACTOR 0.00001
#define ROTATION_FACTOR 0.01
#define INERTIA_FACTOR 0.975f

#define INITIAL_ORIENTATION -M_PI / 2

class ColoredObject;
class Render;
class Map;
class NeuralNetwork;

class RaceCar {
    bool finished = false;
    
    Render* render;
    
    NeuralNetwork* neuralNet = nullptr;
    double distanceTraveled = 0;
    long timeTraveled = 0;
    
    bool passedHalfway = false;
    
    ColoredObject* triangle;
    vec3 velocity = vec3(0, 0, 0);
    float rotation = INITIAL_ORIENTATION;
    
    vector<ColoredObject*> visionIndicators;
    
    Map* map;
    
public:
    RaceCar(Render* render, Map* map, vec3 position);
    
    NeuralNetwork* getNeuralNetwork() { return neuralNet; }
    void setNeuralNetwork(NeuralNetwork* newNeuralNet) { neuralNet = newNeuralNet; }

    void setPosition(vec3 newPosition);
    
    void CheckLapProgress();
    
    void Reset();
    void Tick(int time);
    void Finish();
    void Finish(float percentage);

    bool getFinished() { return finished; }
    
    ~RaceCar();
};

#endif /* RaceCar_hpp */
