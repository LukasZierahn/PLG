//
//  RaceCar.hpp
//  PLG
//
//  Created by Lukas Zierahn on 13.08.19.
//  Copyright © 2019 Lukas Zierahn. All rights reserved.
//

#ifndef RaceCar_hpp
#define RaceCar_hpp

#include <stdio.h>
#include "includeEngine.h"

#define CAR_SCALE 0.25f
#define VELOCITY_FACTOR 1

class ColoredObject;
class Render;

class RaceCar {
    ColoredObject* triangle;
    vec3 velocity = vec3(0.05, 0, 0);
    
public:
    RaceCar(Render* render, vec3 position);
    
    void Tick(int time);
    
    ~RaceCar();
};

#endif /* RaceCar_hpp */
