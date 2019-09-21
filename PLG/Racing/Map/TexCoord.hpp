//
//  TexCoord.hpp
//  PLG
//
//  Created by Lukas Zierahn on 24.08.19.
//  Copyright © 2019 Lukas Zierahn. All rights reserved.
//

#ifndef TexCoord_hpp
#define TexCoord_hpp

#include <stdio.h>
#include "includeEngine.h"

class TexCoord {
public:
    int x;
    int y;
    
    TexCoord(vec3 pos, int height, int width) {
        const float tmpX = (pos.x + 1) / 2;
        const float tmpY = (pos.z + 1) / 2;
        
        x = static_cast<int>(floor(tmpX * width));
        y = static_cast<int>(floor(tmpY * height));
    }
    TexCoord(int x, int y) : x(x), y(y) {}
    
    TexCoord Offset(int xOffset, int yOffset) {
        return TexCoord(x + xOffset, y + yOffset);
    }
};

#endif /* TexCoord_hpp */
