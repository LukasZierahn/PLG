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
    
    TexCoord(vec3 pos) : TexCoord(pos.x, pos.z) {}
    TexCoord(int x, int y) : x(x), y(y) {}
    
    TexCoord Offset(int xOffset, int yOffset) {
        return TexCoord(x + xOffset, y + yOffset);
    }
};

#endif /* TexCoord_hpp */
