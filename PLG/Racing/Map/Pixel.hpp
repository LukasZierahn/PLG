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
#include "Include.h"
#include "TexCoord.hpp"

class Map;

class Pixel {
private:
    Map* map;
    int edgeDepth = -1;
    int edgeId = -1;
    
    float score = -1;
    
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
    Pixel(Map* map, TexCoord texturePosition, GLubyte r, GLubyte g, GLubyte b);
    Pixel(Pixel* pixel);
    
    int CountNeighbours(bool(*condition)(Pixel*));
    Pixel* FindNeighbour(bool(*condition)(Pixel*));
    void RecursiveAddAllNeighbours(vector<Pixel*>* addingTarget, int edgeDepth, int edgeId, TexCoord previousNode);
    
    float getEdgePercent();
    float getScore();
    
    void EditPixelOnMap(unsigned char r, unsigned char g, unsigned char b);
    
    static bool IsWhite(Pixel* pixel) { return pixel->r == 255 && pixel->g == 255 && pixel->b == 255; }
    static bool IsBlack(Pixel* pixel) { return pixel->r == 0 && pixel->g == 0 && pixel->b == 0; }
    static bool IsColoured(Pixel* pixel) { return !(pixel->IsWhite(pixel) || pixel->IsBlack(pixel)); }
};


#endif /* Pixel_hpp */
