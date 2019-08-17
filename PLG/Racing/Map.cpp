//
//  Map.cpp
//  PLG
//
//  Created by Lukas Zierahn on 13.08.19.
//  Copyright © 2019 Lukas Zierahn. All rights reserved.
//

#include "Render.hpp"
#include "Camera.hpp"
#include "TexturedObject.hpp"

#include "Map.hpp"


Map::Map(Render* render) {
    render->getCamera()->setPosition(vec3(0, 2.5, 0));
    render->getCamera()->setDirection(vec3(0, -1, 0));
    render->getCamera()->setUp(vec3(0, 0, 1));
    
    TexturedObject* map = new TexturedObject(render);
    map->setModelDataByKey("plane");
    map->setTextureByKey("RaceTrack");
}
