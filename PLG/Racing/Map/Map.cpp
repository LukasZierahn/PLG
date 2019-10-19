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


Map::Map(Render* render): render(render) {
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
    if (!pixel.IsBlack(pixel)) return false;
    
    Pixel startLineEnd = pixel.FindNeighbour(&Pixel::IsColoured);
    return !(startLineEnd.texCoord.x == pixel.texCoord.x && startLineEnd.texCoord.y == pixel.texCoord.y);
}

vector<vector<Pixel*>>* Map::getEdges() {
    if (edges.size()) {
        return &edges;
    }
    
    edges.push_back(vector<Pixel*>());
    edges.push_back(vector<Pixel*>());

    int startLineEndIndexes [] = {0, (int)getStartLine()->size() - 1};
    for (int i = 0; i < 2; i++) {
        Pixel startLineEnd = startLine[startLineEndIndexes[i]];
        startLineEnd.EditPixelOnMap(255, 0, 0);
        
        cout << startLineEnd.texCoord.x << "/" << 1024 - startLineEnd.texCoord.y << endl;
        
        Pixel* firstEdgePixel = new Pixel(startLineEnd.FindNeighbour(isFirstEdgePixel));
        cout << firstEdgePixel->texCoord.x << "/" << 1024 - firstEdgePixel->texCoord.y << endl;
        edges[i].push_back(firstEdgePixel);
        firstEdgePixel->RecursiveAddAllNeighbours(&edges[i], 0, i, firstEdgePixel->texCoord);
    }
    
    getMapObject()->getTexture()->GenerateTexture();
    
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

float Map::getProgress(vec3 position) {
    float scores [] = {0.0f, 0.0f};
    
    for (int i = 0; i < 2; i++) {
        float smallestDistance = MAXFLOAT;
        for (auto pixel : edges[i]) {
            if (distance(pixel->position, position) <= smallestDistance) {
                smallestDistance = distance(pixel->position, position);
                scores[i] = pixel->getEdgePercent();
            }
        }
    }
    
    return (scores[0] + scores[1]) / 2.0f;
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
