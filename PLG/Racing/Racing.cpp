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

#include "Racing.hpp"

Racing::Racing() {
    render = new Render();
    
    render->getCamera()->setPosition(vec3(0, 2.5, 0));
    render->getCamera()->setDirection(vec3(0, -1, 0));
    render->getCamera()->setUp(vec3(0, 0, 1));
    
    TexturedObject* map = new TexturedObject(render);
    map->setModelDataByKey("plane");
    map->setTextureByKey("RaceTrack");
}

void Racing::Mainloop() {
    do {
        render->Draw();
    } 
    while(glfwGetKey(render->getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(render->getWindow()) == 0 );

}

Racing::~Racing() {
    glfwTerminate();

    delete render;
}
