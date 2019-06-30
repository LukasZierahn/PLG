//
//  render.hpp
//  PLG
//
//  Created by Lukas Zierahn on 02.06.19.
//  Copyright © 2019 Lukas Zierahn. All rights reserved.
//

#ifndef render_hpp
#define render_hpp

#include "Include.h"
#include "ModelLoader/ModelLoader.hpp"
#include "Camera.hpp"
#include "ModelLoader/TexturedObject.hpp"

class ColoredObject;

class Render {
private:
    int width = 800;
    int height = 600;
    
    ModelLoader* modelLoader;
    Camera* camera;
    
    TexturedObject* cube;
    
    GLFWwindow* window;
    
    GLuint mainProgram;
    GLuint VertexArrayID;
    
    void InitGL();
    GLuint LoadShader(const char* path, GLenum type);
    
public:
    Render();
    
    GLFWwindow* getWindow() { return window; }
    
    void Draw();
        
    int getHeight() { return height; }
    int getWidth() { return width; }
    GLuint getMainProgram() { return mainProgram; }
    ModelLoader* getModelLoader() { return modelLoader; }
    
    Camera* getCamera() { return camera; }
    
    ~Render();
};

#endif /* render_hpp */
