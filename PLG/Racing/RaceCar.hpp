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
#define CAR_SENSORS {0.0, M_PI * 0.125, M_PI * 0.25, M_PI * 0.5, M_PI, M_PI * 1.5, M_PI * 1.75, M_PI * 1.875}

class ColoredObject;
class Render;
class Map;

class RaceCar {
    ColoredObject* triangle;
    vec3 velocity = vec3(0.05, 0, 0);
    
    vector<ColoredObject*> visionIndicators;
    
    Map* map;
    
public:
    RaceCar(Render* render, Map* map, vec3 position);
    
    void Tick(int time);
    
    ~RaceCar();
};

#endif /* RaceCar_hpp */
