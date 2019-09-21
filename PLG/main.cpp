//
//  main.cpp
//  PLG
//
//  Created by Lukas Zierahn on 02.06.19.
//  Copyright © 2019 Lukas Zierahn. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "render.hpp"
#include "Racing/Racing.hpp"
#include "GeneticTrainer.hpp"
#include "Racing/RaceCar.hpp"

int main( void )
{
    vector<int> neuralLayerSetup;
    neuralLayerSetup.push_back(CAR_NN_INPUT_NODES);
    neuralLayerSetup.push_back(5);
    neuralLayerSetup.push_back(CAR_NN_OUTPUT_NODES);

    const int population = 20;
    
    Racing racing = Racing(population);
    GeneticTrainer trainer = GeneticTrainer(population, neuralLayerSetup, &racing);
    
    
    trainer.Mainloop();
    
    return 0;
}

