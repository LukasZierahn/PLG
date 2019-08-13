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
    render->addColordObject(this);
}

void ColoredObject::setModelDataByKey(string key) {
    modelData = render->getModelLoader()->getModel(key);
    if (!modelData->hasColor) {
        throw new runtime_error("Tried to assign ModelData to ColoredObject without color buffer: " + key);
    }
}

void ColoredObject::Draw() {
    ComputeMVPMatrix();
    
    glUniformMatrix4fv(MVPID, 1, GL_FALSE, &MVPmatrix[0][0]);
    
    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, modelData->vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    
    // 2nd attribute buffer : colors
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, modelData->colorBuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    
    glDrawArrays(GL_TRIANGLES, 0, modelData->vertexCount);

}
