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
    return Pixel(this, x, y, &mapData[absolutePosition]);
}

Pixel Map::getStartPoint() {
    if (startPoint != nullptr) {
        return *startPoint;
    }
    
    TexCoord pos = TexCoord(0, 0);
    for (Pixel pixel : (*getStartLine())) {
        pos.x += pixel.texCoord.x;
        pos.y += pixel.texCoord.y;
    }
    
    pos.x = round(static_cast<float>(pos.x) / getStartLine()->size());
    pos.y = round(static_cast<float>(pos.y) / getStartLine()->size());

    startPoint = new Pixel(getPixel(pos));
    return *startPoint;
}

vector<Pixel>* Map::getStartLine() {
    if (startLine.size()) {
        return &startLine;
    }
    
    for (long i = 0; i < mapDataLength; i += 3) {
        if (mapData[i] != 255 && mapData[i] != 0) {
            startLine.push_back(getPixel(i));
        }
    }
    
    if (!startLine.size()) {
        throw new runtime_error("failed to find startline\n");
    }
    
    return &startLine;
}

bool isFirstEdgePixel(Pixel pixel) {
    if (pixel.IsWhite(pixel)) return false;
    
    Pixel startLineEnd = pixel.FindNeighbour(&pixel.IsColoured);
    return !(startLineEnd.texCoord.x == pixel.texCoord.x && startLineEnd.texCoord.y == pixel.texCoord.y);
}

vector<vector<Pixel*>>* Map::getEdges() {
    if (edges.size()) {
        return &edges;
    }
    
    int startLineEndIndexes [] = {0, (int)getStartLine()->size()};
    for (int i = 0; i < 2; i++) {
        Pixel startLineEnd = startLine[startLineEndIndexes[i]];
        
        Pixel* firstEdgePixel = new Pixel(startLineEnd.FindNeighbour(isFirstEdgePixel));
        edges[i].push_back(firstEdgePixel);
        firstEdgePixel->RecursiveAddAllNeighbours(&edges[i], firstEdgePixel->texCoord);
    }
    
    return &edges;
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
                
        if (abs(sinDir * (ySteps + 1)) > abs(cosDir * (xSteps + 1))) {
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
    
    delete startPoint;
    
    for (vector<Pixel*> edge : edges) {
        for (Pixel* edgeNode : edge) {
            delete edgeNode;
        }
    }
}
