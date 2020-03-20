//
//  Racing.cpp
//  PLG
//
//  Created by Lukas Zierahn on 10.08.19.
//  Copyright © 2019 Lukas Zierahn. All rights reserved.
//

#include "Render.hpp"
#include "Camera.hpp"
#include "TexturedObject.hpp"
#include "ColoredObject.hpp"
#include "Map.hpp"
#include "RaceCar.hpp"
#include "Pixel.hpp"
#include "NeuralNetwork.hpp"

#include "Racing.hpp"

Racing::Racing(int carCount) {
    render = new Render();
    
    map = new Map(render);
}

void Racing::addNetworks(vector<NeuralNetwork*> networks) {
    for (auto network : networks) {
        RaceCar* car = new RaceCar(render, map, map->getStartPoint()->position);
        car->setNeuralNetwork(network);
        raceCarVec.push_back(car);
    }
}


void Racing::removeAllNetworks() {
    for (auto car : raceCarVec) {
        delete car;
    }
    
    raceCarVec.clear();
}

void Racing::setNeuralNetworks(vector<NeuralNetwork*> networks) {
    removeAllNetworks();
    
    for (auto network : networks) {
        RaceCar* car = new RaceCar(render, map, map->getStartPoint()->position);
        car->setNeuralNetwork(network);
        raceCarVec.push_back(car);
    }
}

bool Racing::Compute() {
    
    bool done = false;
    while (!done && glfwGetKey(render->getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(render->getWindow()) == 0) {
        map->getEdges();
        
        done = true;
        for (RaceCar* car : raceCarVec) {
            if (!car->getFinished()) {
                done = false;
                car->Tick(1);
                
                if (car->getTimeTraveled() >= 100000) {
                    car->Finish(-1.0f);
                }
            }
        }
        
        render->Draw();
    }
    
    for (int i = 0; i < raceCarVec.size(); i++) {
        if (raceCarVec[i]->getNeuralNetwork()->getScore() >= 0.0f) {
            render->setShow(true);
        }
    }

    return !(glfwGetKey(render->getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(render->getWindow()) == 0);
}

void Racing::Reset() {
    for (int i = 0; i < raceCarVec.size(); i++) {
        raceCarVec[i]->Reset();
        raceCarVec[i]->setPosition(startingPosition);
    }
}

Racing::~Racing() {
    glfwTerminate();

    for (int i = 0; i < raceCarVec.size(); i++) {
        delete raceCarVec[i];
    }
    
    delete map;
    delete render;
}

