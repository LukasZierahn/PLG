//
//  Camera.cpp
//  PLG
//
//  Created by Lukas Zierahn on 03.06.19.
//  Copyright © 2019 Lukas Zierahn. All rights reserved.
//

#include "Camera.hpp"

Camera::Camera(Render* render) {
    this->render = render;
    
    UpdateMatricies();
}

void Camera::UpdateMatricies() {
    ProjectionMatrix = perspective(radians(fov), render->getWidth() / (1.0f * render->getHeight()), 0.1f, 100.0f);

    ViewMatrix = lookAt(position, position + direction, up);
}
