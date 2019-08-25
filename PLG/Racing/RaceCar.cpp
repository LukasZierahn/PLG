//
//  RaceCar.cpp
//  PLG
//
//  Created by Lukas Zierahn on 13.08.19.
//  Copyright © 2019 Lukas Zierahn. All rights reserved.
//

#include "RaceCar.hpp"
#include "ColoredObject.hpp"
#include "Map.hpp"
#include "Pixel.hpp"

bool IsBlack(Pixel input) {
    return input.r == 0 && input.g == 0 && input.b == 0;
}

RaceCar::RaceCar(Render* render, Map* map, vec3 position): map(map) {
    triangle = new ColoredObject(render);
    triangle->setModelDataByKey("triangle");
    triangle->setScale(CAR_SCALE);
    triangle->setPosition(position);
    
    for (double dir : CAR_SENSORS) {
        visionIndicators.push_back(new ColoredObject(triangle->getRender()));
        visionIndicators[visionIndicators.size() - 1]->setModelDataByKey("cube");
        visionIndicators[visionIndicators.size() - 1]->setScale(0.01);
    }
}

void RaceCar::Tick(int time) {
    
    TexCoord position = TexCoord(triangle->getPosition(), map->getHeight(), map->getWidth());
    
    int i = 0;
    for (double dir : CAR_SENSORS) {
        Pixel rayPosition = map->SendRay(position, dir, IsBlack);
        visionIndicators[i]->setPosition(rayPosition.position);
        i++;
    }
    
    vec3 addingPosition = vec3(-0.0001, 0, -0.0001);
    addingPosition *= time * VELOCITY_FACTOR;
    triangle->addPosition(addingPosition);
}

RaceCar::~RaceCar() {
    delete triangle;
    
    for (int i = 0; i < visionIndicators.size(); i++) {
        delete visionIndicators[i];
    }
}
