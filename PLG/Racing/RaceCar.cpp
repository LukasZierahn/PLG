//
//  RaceCar.cpp
//  PLG
//
//  Created by Lukas Zierahn on 13.08.19.
//  Copyright © 2019 Lukas Zierahn. All rights reserved.
//

#include "ColoredObject.hpp"
#include "Map.hpp"
#include "Pixel.hpp"
#include "NeuralNetwork.hpp"
#include "Render.hpp"
#include "HelperFunction.h"

#include "RaceCar.hpp"


bool IsBlack(Pixel input) {
    return input.IsBlack(input);
}

RaceCar::RaceCar(Render* render, Map* map, vec3 position): map(map), render(render) {
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

void RaceCar::Reset() {
    timeTraveled = 0;
    distanceTraveled = 0;
    
    finished = false;
    
    rotation = INITIAL_ORIENTATION;
    velocity = vec3(0);
    
    render->addColoredObject(triangle);
    for (int i = 0; i < visionIndicators.size(); i++) {
        render->addColoredObject(visionIndicators[i]);
    }
}

void RaceCar::Tick(int time) {
    timeTraveled += time;
    
    if (timeTraveled % (1000 * time) == 0) {
        if (abs(rotation) > 3 * 2 * M_PI) {
            Finish();
            neuralNet->setScore(0);
        } else {
            rotation -= M_PI * 2 * floor((rotation / (M_PI * 2)));
        }
    }
    
    neuralNet->resetCurrentInputNode();
    
    TexCoord position = TexCoord(triangle->getPosition(), map->getHeight(), map->getWidth());
    
    int i = 0;
    for (double dir : CAR_SENSORS) {
        Pixel rayPosition = map->SendRay(position, rotation + dir, IsBlack);
        vec3 relativePosition = rayPosition.position - triangle->getPosition();
        neuralNet->setNextInputNode(length(relativePosition));
        
        if (i == 0) {
            const TexCoord myTexPos = TexCoord(triangle->getPosition(), map->getHeight(), map->getWidth());
            if (rayPosition.texCoord.x == myTexPos.x && rayPosition.texCoord.y == myTexPos.y) {
                Finish();
                return;
            }
        }
        
        visionIndicators[i]->setPosition(rayPosition.position);
        i++;
    }
    
    neuralNet->Compute();
    neuralNet->resetCurrentOutputNode();
    
    const double rotationNode = neuralNet->getNextOutputNode(true);
    rotation += time * ROTATION_FACTOR * rotationNode;
    
    velocity *= INERTIA_FACTOR;
    const double neuralNetAcceleration = neuralNet->getNextOutputNode(true);
    velocity += vec3(neuralNetAcceleration * sin(rotation), 0, neuralNetAcceleration * cos(rotation));
    
    if (neuralNetAcceleration > 0) {
        distanceTraveled += time * length(velocity);
    }

    if (length(velocity) < 0.01) {
        Finish();
    }
    
    vec3 addingPosition = velocity;
    addingPosition *= time * VELOCITY_FACTOR;
    triangle->addPosition(addingPosition);
    triangle->setRotation(vec3 (0, rotation, 0));
}

void RaceCar::Finish() {
//    neuralNet->setScore(pow(distanceTraveled, 1.5) / timeTraveled);
    neuralNet->setScore(distanceTraveled);
    
    render->removeColordObject(triangle);
    for (int i = 0; i < visionIndicators.size(); i++) {
        render->removeColordObject(visionIndicators[i]);
    }
    
    finished = true;
}

void RaceCar::setPosition(vec3 newPosition) {
    triangle->setPosition(newPosition);
}

RaceCar::~RaceCar() {
    delete triangle;
    
    for (int i = 0; i < visionIndicators.size(); i++) {
        delete visionIndicators[i];
    }
}
