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

Pixel Map::getPixel(int x, int y) {
    return getPixel((y * width + x) * 3);
}

Pixel Map::getPixel(TexCoord texCoord) {
    return getPixel(texCoord.x, texCoord.y);
}

Pixel Map::getPixel(long absolutePosition) {
    int x = (absolutePosition / 3) % width;
    int y = floor((absolutePosition / 3) / static_cast<float>(width));
    return Pixel(x, y, &mapData[absolutePosition], width, height);
}

Pixel Map::getStartPoint() {
    for (long i = 0; i < mapDataLength; i += 3) {
        if (mapData[i] != 255 && mapData[i] != 0) {
            Pixel pixel = getPixel(i);
            
            printf("found starting position %d/%d %f/%f\n", pixel.texCoord.x, pixel.texCoord.y, pixel.position.x, pixel.position.z);
            return pixel;
        }
    }
    
    throw new runtime_error("failed to find start\n");
}

Pixel Map::SendRay(TexCoord texCoord, float direction, bool (*condition)(Pixel)) {
    const float sinDir = sin(direction);
    const float cosDir = cos(direction);
    
    if (condition(getPixel(texCoord))) {
        return getPixel(texCoord);
    }
    
    int xSteps = 0;
    int ySteps = 0;
    while (texCoord.x + xSteps >= 0 && texCoord.x + xSteps < width &&
           texCoord.y + ySteps >= 0 && texCoord.y + ySteps < height) {
                
        if (sinDir * (ySteps + 1) > cosDir * (xSteps + 1)) {
            xSteps += sinDir > 0 ? 1 : -1;
            if (condition(getPixel(texCoord.Offset(xSteps, ySteps)))) {
                return getPixel(texCoord.Offset(xSteps, ySteps));
            }
        } else {
            ySteps += cosDir > 0 ? 1 : -1;
            if (condition(getPixel(texCoord.Offset(xSteps, ySteps)))) {
                return getPixel(texCoord.Offset(xSteps, ySteps));
            }
        }
    }
    
    throw new runtime_error("ray unsuccessful");
}

Map::~Map() {
    delete [] mapData;
}
