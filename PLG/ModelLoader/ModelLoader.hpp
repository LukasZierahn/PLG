//
//  ModelLoader.hpp
//  PLG
//
//  Created by Lukas Zierahn on 03.06.19.
//  Copyright © 2019 Lukas Zierahn. All rights reserved.
//

#ifndef ModelLoader_hpp
#define ModelLoader_hpp

#include "include.h"
#include <map>

#include "Render.hpp"


struct ModelData {
    string name;
    GLuint vertexBuffer;
    GLuint uvBuffer;
    GLuint normalBuffer;
    GLuint indexBuffer;
};

class ModelLoader {
private:
    Render* render;
    
    map<string, ModelData> modelData;
    
public:
    ModelLoader(Render* render);
    ModelData* getModel(string key);
    
    void LoadModelFromFile(string key);
    void LoadModelFromFile(string key, string path);
    
    void ConvertFileToCng(string key);
    void ConvertFileToCng(string key, string srcPath, string targetPath);
};

#endif /* ModelLoader_hpp */
