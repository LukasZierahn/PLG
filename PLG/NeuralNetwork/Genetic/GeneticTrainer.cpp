//
//  GeneticTrainer.cpp
//  PLG
//
//  Created by Lukas Zierahn on 14.08.19.
//  Copyright © 2019 Lukas Zierahn. All rights reserved.
//

#include "NeuralNetwork.hpp"

#include "GeneticTrainer.hpp"


GeneticTrainer::GeneticTrainer(int population, vector<int> layerSetup) {
    this->population = population;
    for (int i = 0; i < population; i++) {
        networks.push_back(new NeuralNetwork(layerSetup));
        networks[i]->RandomizeValues();
    }
}

GeneticTrainer::~GeneticTrainer() {
    for (int i = 0; i < population; i++) {
        delete networks[i];
    }
}
