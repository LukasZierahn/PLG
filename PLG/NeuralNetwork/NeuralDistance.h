//
//  NeuralDistance.h
//  PLG
//
//  Created by Lukas on 29.04.20.
//  Copyright © 2020 Lukas. All rights reserved.
//

#ifndef NeuralDistance_h
#define NeuralDistance_h

#define METRIC_STEPS 3
#define METRIC_STEPS_START 1
#define METRIC_DISTANCE 100.0f

bool IncreaseConfig(vector<int>* config) {
    for (long i = config->size() - 1; i >= 0; i--) {
        if ((*config)[i] + 1 < METRIC_STEPS) {
            (*config)[i] += 1;
            return true;
        }
        
        (*config)[i] = 0;
    }
    
    return false;
}

#endif /* NeuralDistance_h */
