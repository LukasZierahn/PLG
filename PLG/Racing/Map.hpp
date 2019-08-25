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
#include "includeEngine.h"

class Render;
class TexturedObject;
class Texture;
class Pixel;
class TexCoord;

class Map {
private:
    TexturedObject* mapObject;
    
    int width;
    int height;
    
    long mapDataLength;
    GLubyte* mapData;
    
public:
    Map(Render* render);
    
    Pixel getPixel(TexCoord texCoord);
    Pixel getPixel(int x, int y);
    Pixel getPixel(long absolutePosition);
        
    Pixel SendRay(TexCoord texCoord, float direction, bool (*condition)(Pixel));
    Pixel getStartPoint();
    
    int getHeight() { return height; }
    int getWidth() { return width; }

    ~Map();
};

#endif /* Map_hpp */
