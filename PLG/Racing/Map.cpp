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
#include "Texture.hpp"
#include "Pixel.hpp"

#include "Map.hpp"


Map::Map(Render* render) {
    render->getCamera()->setPosition(vec3(0, 2.5, 0));
    render->getCamera()->setDirection(vec3(0, -1, 0));
    render->getCamera()->setUp(vec3(0, 0, 1));
    
    mapObject = new TexturedObject(render);
    mapObject->setModelDataByKey("plane");
    mapObject->setTextureByKey("RaceTrack");
    mapObject->setPosition(vec3(0, -0.00001, 0));
    
    width = mapObject->getTexture()->getWidth();
    height = mapObject->getTexture()->getHeight();
    
    mapDataLength = width * height * 3;
    mapData = new GLubyte[mapDataLength];
    cout << mapObject->getTexture()->getTextureId() << endl;
    
    glBindTexture(GL_TEXTURE_2D, mapObject->getTexture()->getTextureId());
    glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, mapData);
}

Pixel Map::getPixel(long absolutePosition) {
    int x = (absolutePosition / 3) % width;
    int y = floor((absolutePosition / 3) / static_cast<float>(width));
    return Pixel(x, y, &mapData[absolutePosition], width, height);
}

vec3 Map::getStartPoint() {
    for (long i = 0; i < mapDataLength; i += 3) {
        if (mapData[i] != 255 && mapData[i] != 0) {
            Pixel pixel = getPixel(i);
            
            printf("found staring position %d/%d %f/%f\n", pixel.x, pixel.y, pixel.position.x, pixel.position.y);
            return pixel.position;
        }
    }
    
    printf("failed to find start\n");
    return vec3(0);
}

Map::~Map() {
    delete [] mapData;
}
