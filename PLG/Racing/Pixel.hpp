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

class Pixel {
public:
    TexCoord texCoord;
    
    vec3 position;
    
    GLubyte r;
    GLubyte g;
    GLubyte b;
    
    int width;
    int height;
    
    Pixel(int x, int y, GLubyte* rgb);
    Pixel(TexCoord texturePosition, GLubyte* rgb);
    Pixel(int x, int y, GLubyte* rgb, int width, int height);
    Pixel(TexCoord texturePosition, GLubyte* rgb, int width, int height);
};


#endif /* Pixel_hpp */
