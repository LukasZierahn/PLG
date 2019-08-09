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
#include "NeuralNetwork.hpp"

int main( void )
{
    vector<int> layer;
    layer.push_back(2);
    layer.push_back(2);
    NeuralNetwork* neuralNetwork = new NeuralNetwork(layer);
    
    neuralNetwork->setNode(0, 0, 0.5);
    neuralNetwork->setNode(0, 1, 0.5);
    neuralNetwork->setConnection(0, 0.5);
    neuralNetwork->setConnection(1, 0.5);
    neuralNetwork->setConnection(2, 1);
    neuralNetwork->setConnection(3, 0.5);
    neuralNetwork->setBiases(0, 0);
    neuralNetwork->setBiases(1, -1);

    neuralNetwork->Compute();
    cout << neuralNetwork->getNode(1, 0) << " " << neuralNetwork->getNode(1, 1) << endl;
//    Render render = Render();
//
//    do{
//        render.Draw();
//    } // Check if the ESC key was pressed or the window was closed
//    while( glfwGetKey(render.getWindow(), GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(render.getWindow()) == 0 );
//
//    // Close OpenGL window and terminate GLFW
//    glfwTerminate();

    return 0;
}

