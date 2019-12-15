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
    
    startingPosition = map->getStartPoint()->position;
    for (int i = 0; i < carCount; i++) {
        raceCarVec.push_back(new RaceCar(render, map, startingPosition));
    }
    raceCarVec.shrink_to_fit();
}

void Racing::setNeuralNetworks(vector<NeuralNetwork*> networks) {
    for (int i = 0; i < raceCarVec.size(); i++) {
        raceCarVec[i]->setNeuralNetwork(networks[i]);
    }
}

vector<NeuralNetwork*> Racing::getNeuralNetworks() {
    vector<NeuralNetwork*> output;
    
    for (RaceCar* raceCar : raceCarVec) {
        output.push_back(raceCar->getNeuralNetwork());
    }
    
    return output;
}

bool Racing::Compute() {
    bool done = false;
    while (!done && glfwGetKey(render->getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(render->getWindow()) == 0) {
        map->getEdges();
        
        done = true;
        for (int i = 0; i < raceCarVec.size(); i++) {
            if (!raceCarVec[i]->getFinished()) {
                done = false;
                raceCarVec[i]->Tick(TIME_STEPS);
            }
        }
        
        render->Draw();
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
