//
//  Pixel.hpp
//  PLG
//
//  Created by Lukas Zierahn on 17.08.19.
//  Copyright © 2019 Lukas Zierahn. All rights reserved.
//

#ifndef Pixel_hpp
#define Pixel_hpp

#include <stdio.h>
#include "includeEngine.h"
#include "TexCoord.hpp"

class Map;

class Pixel {
private:
    Map* map;
    
    bool IsInBounds(TexCoord texcoord);
    
public:
    TexCoord texCoord;
    
    vec3 position;
    
    GLubyte r;
    GLubyte g;
    GLubyte b;
    
    int width;
    int height;
    
    Pixel(Map* map, int x, int y, GLubyte* rgb);
    Pixel(Map* map, TexCoord texturePosition, GLubyte* rgb);
    
    int CountNeighbours(bool(*condition)(Pixel));
    Pixel FindNeighbour(bool(*condition)(Pixel));
    void RecursiveAddAllNeighbours(vector<Pixel*>* addingTarget, TexCoord previousNode);
    
    static bool IsWhite(Pixel pixel) { return pixel.r == 255 && pixel.g == 255 && pixel.b == 255; }
    static bool IsBlack(Pixel pixel) { return pixel.r == 0 && pixel.g == 0 && pixel.b == 0; }
    static bool IsColoured(Pixel pixel) { return !(pixel.IsWhite(pixel) || pixel.IsBlack(pixel)); }
};


#endif /* Pixel_hpp */