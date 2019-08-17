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

#include "Racing.hpp"

Racing::Racing() {
    render = new Render();
    
    map = new Map(render);
}

void Racing::Mainloop() {
    do {
        render->Draw();
    } 
    while(glfwGetKey(render->getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(render->getWindow()) == 0 );

}

Racing::~Racing() {
    glfwTerminate();

    delete map;
    delete render;
}
