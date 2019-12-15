//
//  Map.hpp
//  PLG
//
//  Created by Lukas Zierahn on 13.08.19.
//  Copyright © 2019 Lukas Zierahn. All rights reserved.
//

#ifndef Map_hpp
#define Map_hpp

#include <stdio.h>
#include <string>
#include <map>
#include "includeEngine.h"

class Render;
class TexturedObject;
class ColoredObject;
class Texture;
class Pixel;
class TexCoord;

class Map {
private:
    Render* render;
    
    TexturedObject* mapObject;
    
    int width;
    int height;
    
    long mapDataLength;
    GLubyte* mapData;
    
    Pixel* startPoint = nullptr;
    
    vector<Pixel*> pixelVec;
    int getPixelPosition(int x, int y) {
        return x + y * width;
    }
    
    vector<Pixel*> startLine;
    vector<vector<Pixel*>> edges;
    
public:
    Map(Render* render);
    
    Render* getRender() { return render; }
    
    Pixel* getPixel(TexCoord texCoord);
    Pixel* getPixel(int x, int y);
    Pixel* getPixel(long absolutePosition);
    
    Pixel* SendRay(TexCoord texCoord, float direction, bool (*condition)(Pixel*));
    
    Pixel* getStartPoint();
    vector<Pixel*>* getStartLine();
    vector<vector<Pixel*>>* getEdges();
    
    int getEdgeCount(int id) { return edges[id].size(); }
    float getProgress(vec3 position);
    
    int getHeight() { return height; }
    int getWidth() { return width; }
    
    TexturedObject* getMapObject() { return mapObject; }

    ~Map();
};

#endif /* Map_hpp */
