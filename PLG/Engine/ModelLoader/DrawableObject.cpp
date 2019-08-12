//
//  DrawableObject.cpp
//  PLG
//
//  Created by Lukas Zierahn on 23.06.19.
//  Copyright © 2019 Lukas Zierahn. All rights reserved.
//

#include "Render.hpp"
#include "Camera.hpp"

#include "DrawableObject.hpp"

DrawableObject::DrawableObject(Render* render) {
    this->render = render;
    MVPID = glGetUniformLocation(render->getMainProgram(), "MVP");
    MVPmatrix = mat4(1.0f);
    
    render->addDrawableObject(this);
}

void DrawableObject::ComputeMVPMatrix() {
    MVPmatrix = glm::scale(mat4(1.0f), scale);
    MVPmatrix = glm::rotate(MVPmatrix, rotation.x, vec3(1, 0, 0));
    MVPmatrix = glm::rotate(MVPmatrix, rotation.y, vec3(0, 1, 0));
    MVPmatrix = glm::rotate(MVPmatrix, rotation.z, vec3(0, 0, 1));
    MVPmatrix = glm::translate(MVPmatrix, position);
    MVPmatrix = render->getCamera()->getJointMatrix() * MVPmatrix;
}
