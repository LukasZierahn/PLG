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

class Render;
class TexturedObject;

class Map {
private:
    TexturedObject* mapObject;
public:
    Map(Render* render);
};

#endif /* Map_hpp */
