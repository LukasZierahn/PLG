//
//  Camera.hpp
//  PLG
//
//  Created by Lukas Zierahn on 03.06.19.
//  Copyright © 2019 Lukas Zierahn. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <stdio.h>

#include "render.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;


class Camera {
private:
    Render* render = nullptr;
    
    mat4 ViewMatrix;
    mat4 ProjectionMatrix;

    vec3 position = vec3(0, 0, 0);
    vec3 direction = vec3(1, 0, 0);
    vec3 up = vec3(0, 1, 0);

    float fov = 45.0f;
    
public:
    Camera(Render* render);
    
    void UpdateMatricies();
    
    void setPosition(vec3 pos) { position = pos; }
    void setDirection(vec3 dir) { direction = dir; }
    void setUp(vec3 up) { this->up = up; }
    
    void addPosition(vec3 pos) { position += pos; }
    void addDirection(vec3 dir) { direction += dir; }

};

#endif /* Camera_hpp */
