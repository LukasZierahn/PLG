//
//  ColoredObject.cpp
//  PLG
//
//  Created by Lukas Zierahn on 23.06.19.
//  Copyright © 2019 Lukas Zierahn. All rights reserved.
//
#include "ModelLoader.hpp"
#include "Render.hpp"

#include "ColoredObject.hpp"

ColoredObject::ColoredObject(Render* render) : DrawableObject(render) {
}

void ColoredObject::setModelDataByKey(string key) {
    modelData = render->getModelLoader()->getModel(key);
    if (!modelData->hasColor) {
        throw new runtime_error("Tried to assign ModelData to ColoredObject without color buffer: " + key);
    }
}

void ColoredObject::Draw() {
    ComputeMVPMatrix();
    
    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform
    glUniformMatrix4fv(MVPID, 1, GL_FALSE, &MVPmatrix[0][0]);
    
    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, modelData->vertexBuffer);
    glVertexAttribPointer(
                          0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
                          3,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          0,                  // stride
                          (void*)0            // array buffer offset
                          );
    
    // 2nd attribute buffer : colors
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, modelData->colorBuffer);
    glVertexAttribPointer(
                          1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
                          3,                                // size
                          GL_FLOAT,                         // type
                          GL_FALSE,                         // normalized?
                          0,                                // stride
                          (void*)0                          // array buffer offset
                          );
    
    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, modelData->vertexCount); // 12*3 indices starting at 0 -> 12 triangles

}
