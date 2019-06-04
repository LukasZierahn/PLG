//
//  ModelLoader.cpp
//  PLG
//
//  Created by Lukas Zierahn on 03.06.19.
//  Copyright © 2019 Lukas Zierahn. All rights reserved.
//

#include "ModelLoader.hpp"

ModelLoader::ModelLoader(Render* render) {
    this->render = render;
}

void ModelLoader::LoadModelFromFile(string key) {
    LoadModelFromFile(key, "data/" + key + ".cng");
}

void ModelLoader::LoadModelFromFile(string key, string path) {
    ModelData* newModel = new ModelData();
    
    ifstream modelStream;
    char input;
    
    //open the document
    modelStream.open(path.c_str(), ifstream::in);
    
    if (modelStream.fail())
    {
        modelStream.close();
        ConvertFileToCng(key);
        modelStream.open(path.c_str(), ifstream::in);
    }
    
    if (modelStream.fail()) {
        throw new exception("failed to load Model: " + key);
        return;
    }
    
    //TODO: Finish this
}

void ModelLoader::ConvertFileToCng(string key) {
    ConvertFileToCng(string key, "datasrc/" + key + ".obj", "data/" + key + ".cng");
}

void ModelLoader::ConvertFileToCng(string key, string srcPath, string targetPath) {
    
}

