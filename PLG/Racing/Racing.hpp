//
//  Racing.hpp
//  PLG
//
//  Created by Lukas Zierahn on 10.08.19.
//  Copyright © 2019 Lukas Zierahn. All rights reserved.
//

#ifndef Racing_hpp
#define Racing_hpp

#include <stdio.h>
#include <vector>

#define CAR_COUNT 1

using namespace std;

class Render;
class Map;
class RaceCar;

class Racing {
private:
    Render* render;
    Map* map;
    
    vector<RaceCar*> raceCarVec;
    
public:
    Racing();
    
    void Mainloop();
    
    ~Racing();
};

#endif /* Racing_hpp */
