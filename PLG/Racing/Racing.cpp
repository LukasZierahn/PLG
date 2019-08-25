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

#include "Racing.hpp"

Racing::Racing() {
    render = new Render();
    
    map = new Map(render);
    
    Pixel startingPositing = map->getStartPoint() ;
    
    for (int i = 0; i < CAR_COUNT; i++) {
        raceCarVec.push_back(new RaceCar(render, map, startingPositing.position));
    }
    raceCarVec.shrink_to_fit();
}

void Racing::Mainloop() {
    do {
        for (int i = 0; i < raceCarVec.size(); i++) {
            raceCarVec[i]->Tick(10);
        }

        render->Draw();
    } 
    while(glfwGetKey(render->getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(render->getWindow()) == 0 );

}

Racing::~Racing() {
    glfwTerminate();

    for (int i = 0; i < raceCarVec.size(); i++) {
        delete raceCarVec[i];
    }
    
    delete map;
    delete render;
}
