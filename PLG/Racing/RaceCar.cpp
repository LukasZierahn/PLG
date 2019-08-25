//
//  RaceCar.cpp
//  PLG
//
//  Created by Lukas Zierahn on 13.08.19.
//  Copyright © 2019 Lukas Zierahn. All rights reserved.
//

#include "RaceCar.hpp"
#include "ColoredObject.hpp"
#include "Map.hpp"
#include "Pixel.hpp"
#include "NeuralNetwork.hpp"

bool IsBlack(Pixel input) {
    return input.r == 0 && input.g == 0 && input.b == 0;
}

RaceCar::RaceCar(Render* render, Map* map, vec3 position, vector<int> neuralNetworkSetup): map(map) {
    neuralNet = new NeuralNetwork(neuralNetworkSetup);
    neuralNet->RandomizeValues();
    
    triangle = new ColoredObject(render);
    triangle->setModelDataByKey("triangle");
    triangle->setScale(vec3(0.5 * CAR_SCALE, 1, 1 * CAR_SCALE));
    triangle->setPosition(position);
    
    for (double dir : CAR_SENSORS) {
        visionIndicators.push_back(new ColoredObject(triangle->getRender()));
        visionIndicators[visionIndicators.size() - 1]->setModelDataByKey("cube");
        visionIndicators[visionIndicators.size() - 1]->setScale(0.01);
    }
}

void RaceCar::Tick(int time) {
    neuralNet->resetCurrentInputNode();
    
    TexCoord position = TexCoord(triangle->getPosition(), map->getHeight(), map->getWidth());
    
    int i = 0;
    for (double dir : CAR_SENSORS) {
        Pixel rayPosition = map->SendRay(position, rotation + dir, IsBlack);
        vec3 relativePosition = rayPosition.position - triangle->getPosition();
        neuralNet->setNextInputNode(sqrt(pow(relativePosition.x, 2) + pow(relativePosition.z, 2)));
        visionIndicators[i]->setPosition(rayPosition.position);
        i++;
    }
    
    neuralNet->Compute();
    neuralNet->resetCurrentOutputNode();
    
    rotation += time * ROTATION_FACTOR * neuralNet->getNextOutPutNode();
    
    velocity *= INERTIA_FACTOR;
    const double neuralNetAcceleration = neuralNet->getNextOutPutNode();
    velocity += vec3(neuralNetAcceleration * sin(rotation), 0, neuralNetAcceleration * cos(rotation));
    
    vec3 addingPosition = velocity;
    addingPosition *= time * VELOCITY_FACTOR;
    triangle->addPosition(addingPosition);
    triangle->setRotation(vec3 (0, rotation, 0));
}

RaceCar::~RaceCar() {
    delete neuralNet;
    delete triangle;
    
    for (int i = 0; i < visionIndicators.size(); i++) {
        delete visionIndicators[i];
    }
}
