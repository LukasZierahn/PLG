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

bool IsBlack(Pixel input) {
//    printf("checking: %d, %d, %d %s\n", input.r, input.b, input.g, input.r == 0 && input.g == 0 && input.b == 0 ? "true" : "false");
    return input.r == 0 && input.g == 0 && input.b == 0;
}

Racing::Racing() {
    render = new Render();
    
    map = new Map(render);
    
    Pixel startingPositing = map->getStartPoint() ;
    
//    Pixel output = map->SendRay(startingPositing.texCoord, M_PI, IsBlack);
    
    printf("Ray Tracing Output: %d/%d\n", output.texCoord.x, output.texCoord.y);
    
    for (int i = 0; i < CAR_COUNT; i++) {
        raceCarVec.push_back(new RaceCar(render, startingPositing.position));
    }
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
