//
//  DrawableObject.hpp
//  
//
//  Created by Lukas Zierahn on 23.06.19.
//

#ifndef DrawableObject_hpp
#define DrawableObject_hpp

class ModelData;
class Render;
class Texture;

#include "Include.h"

class DrawableObject {
protected:
    Render* render;
    
    ModelData* modelData = nullptr;
    
    vec3 position = vec3(0, 0, 0);
    vec3 rotation = vec3(0, 0, 0);
    vec3 scale = vec3(1, 1, 1);
    mat4 MVPmatrix;
    GLuint MVPID;
    
public:
    DrawableObject(Render* render);
    
    void Draw() { cout << "Drawable Object Draw function called!" << endl; }
    
    void ComputeMVPMatrix();
};

#endif /* DrawableObject_hpp */
