//
//  main.cpp
//  PLG
//
//  Created by Lukas Zierahn on 02.06.19.
//  Copyright © 2019 Lukas Zierahn. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "render.hpp"

int main( void )
{
    Render render = Render();
    
    do{
        render.Draw();
    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(render.getWindow(), GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(render.getWindow()) == 0 );
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}

