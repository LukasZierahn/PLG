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
#include "ColorData.hpp"

#include "RaceCar.hpp"


bool IsBlack(Pixel* input) {
    return input->IsBlack(input);
}

RaceCar::RaceCar(Render* render, Map* map, vec3 position): map(map), render(render) {
    triangle = new ColoredObject(render);
    triangle->setModelDataByKey("triangle");
    triangle->getColorData()->SetUnicodeColour(0.7f, 0.7f, 0.7f);
    triangle->setScale(vec3(0.5 * CAR_SCALE, 1, 1 * CAR_SCALE));
    triangle->setPosition(position);
    
    for (double _ : CAR_SENSORS) {
        ColoredObject* currVisIndicator = new ColoredObject(triangle->getRender());
        currVisIndicator->setModelDataByKey("cube");
        currVisIndicator->setScale(0.01);
        currVisIndicator->getColorData()->SetUnicodeColour(0.3f, 0.3f, 0.3f);
        visionIndicators.push_back(currVisIndicator);
    }
}

void RaceCar::setNeuralNetwork(NeuralNetwork* newNeuralNet) {
    neuralNet = newNeuralNet;
    triangle->getColorData()->SetUnicodeColour(neuralNet->getR(), neuralNet->getG(), neuralNet->getB());
}

void RaceCar::CheckLapProgress() {
    float progress = map->getProgress(triangle->getPosition());
    
    if (progress < 0.70 && progress > 0.30) {
        passedHalfway = true;
    }
    
    if (progress < 0.3 && !passedHalfway) {
        score = progress;
    }
    
    if (progress > 0.3 && passedHalfway) {
        score = progress;
    }

    if ((progress > 0.995 || progress < 0.005) && passedHalfway) {
        score = 1.0f + (1000.0f / timeTraveled);
        printf("Car finished track after %d ticks with score %f\n", timeTraveled, score);
        Finish(score);
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
    CheckLapProgress();

    //killing spinners
    if (timeTraveled % (1000 * time) == 0) {
        if (abs(rotation) > 3 * 2 * M_PI) {
            Finish();
            neuralNet->setScore(0);
        } else {
            rotation -= M_PI * 2 * floor((rotation / (M_PI * 2)));
        }
    }
    
    //killing slowpokes
    if (timeTraveled % 1000 * time == 0) {
        
        if (score < 0.02f) {
            Finish();
        }
    }
            
    neuralNet->resetCurrentInputNode();
    
    TexCoord position = TexCoord(triangle->getPosition(), map->getHeight(), map->getWidth());
    
    int i = 0;
    for (double dir : CAR_SENSORS) {
        Pixel* rayPosition = map->SendRay(position, rotation + dir, IsBlack);
        vec3 relativePosition = rayPosition->position - triangle->getPosition();
        neuralNet->setNextInputNode(length(relativePosition));
        
        if (i == 0) {
            const TexCoord myTexPos = TexCoord(triangle->getPosition(), map->getHeight(), map->getWidth());
            if (rayPosition->texCoord.x == myTexPos.x && rayPosition->texCoord.y == myTexPos.y) {
                Finish();
                return;
            }
        }
        
        visionIndicators[i]->setPosition(rayPosition->position);
        i++;
    }
    
    neuralNet->Compute();
    neuralNet->resetCurrentOutputNode();
    
    const double rotationNode = neuralNet->getNextOutputNode(true);
    rotation += time * ROTATION_FACTOR * rotationNode * TIME_STEPS ;
    
    velocity *= INERTIA_FACTOR;
    const double neuralNetAcceleration = neuralNet->getNextOutputNode(true);
    velocity += vec3(neuralNetAcceleration * sin(rotation), 0, neuralNetAcceleration * cos(rotation));
    
    if (neuralNetAcceleration > 0) {
        distanceTraveled += time * length(velocity);
    }

    //killing slowpokes
    if (length(velocity) < 0.01) {
        Finish();
    }
    
    vec3 addingPosition = velocity;
    addingPosition *= time * VELOCITY_FACTOR;
    triangle->addPosition(addingPosition);
    triangle->setRotation(vec3 (0, rotation, 0));
}

void RaceCar::Finish(float score) {
    neuralNet->setScore(score);
    
    render->removeColordObject(triangle);
    for (int i = 0; i < visionIndicators.size(); i++) {
        render->removeColordObject(visionIndicators[i]);
    }
    
    finished = true;
}

void RaceCar::Finish() {        
    Finish(score);
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
