//
//  ColoredObject.hpp
//  PLG
//
//  Created by Lukas Zierahn on 23.06.19.
//  Copyright © 2019 Lukas Zierahn. All rights reserved.
//

#ifndef ColoredObject_hpp
#define ColoredObject_hpp

#include "include.h"
#include "DrawableObject.hpp"

class ColoredObject : public DrawableObject{
public:
    ColoredObject(Render* render);
    
    void setModelDataByKey(string key);
    
    void Draw();

};

#endif /* ColoredObject_hpp */
