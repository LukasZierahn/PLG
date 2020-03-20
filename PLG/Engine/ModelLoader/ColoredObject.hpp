//
//  ColoredObject.hpp
//  PLG
//
//  Created by Lukas Zierahn on 23.06.19.
//  Copyright © 2019 Lukas Zierahn. All rights reserved.
//

#ifndef ColoredObject_hpp
#define ColoredObject_hpp

#include "includeEngine.h"
#include "DrawableObject.hpp"


class ColorData;

class ColoredObject : public DrawableObject{
    Render* render;
    
    ColorData* colorData;
    
public:
    ColoredObject(Render* render);
    
    void setModelDataByKey(string key);
    ColorData* getColorData() { return colorData; }
    
    void Draw();

    ~ColoredObject();
};

#endif /* ColoredObject_hpp */
