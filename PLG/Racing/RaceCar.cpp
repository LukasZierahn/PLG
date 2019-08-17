//
//  RaceCar.cpp
//  PLG
//
//  Created by Lukas Zierahn on 13.08.19.
//  Copyright © 2019 Lukas Zierahn. All rights reserved.
//

#include "RaceCar.hpp"
#include "ColoredObject.hpp"

RaceCar::RaceCar(Render* render, vec3 position) {
    triangle = new ColoredObject(render);
    triangle->setModelDataByKey("triangle");
    triangle->setScale(CAR_SCALE);
    triangle->setPosition(position);
}


void RaceCar::Tick(int time) {
    vec3 addingPosition = vec3(-0.0001, 0, -0.0001);
    addingPosition *= time * VELOCITY_FACTOR;
//    triangle->addPosition(addingPosition);
}

RaceCar::~RaceCar() {
    delete triangle;
}
