//
//  render.hpp
//  PLG
//
//  Created by Lukas Zierahn on 02.06.19.
//  Copyright © 2019 Lukas Zierahn. All rights reserved.
//

#ifndef render_hpp
#define render_hpp

#include "includeEngine.h"

class ColoredObject;
class DrawableObject;
class Camera;
class ModelLoader;

class Render {
private:
    int width = 1000;
    int height = 1000;
    
    ModelLoader* modelLoader;
    Camera* camera;
    
    GLuint colordProgram;
    vector<ColoredObject*> coloredDrawVector;
    GLuint mainProgram;
    vector<DrawableObject*> drawVector;

    GLFWwindow* window;
    
    GLuint vertexArrayID;
    
    void InitGL();
    GLuint LoadShader(const char* path, GLenum type);
    
public:
    Render();
    
    GLFWwindow* getWindow() { return window; }
    
    void Draw();
    
    void addDrawableObject(DrawableObject* drawObject) { drawVector.push_back(drawObject); }
    void addColordObject(ColoredObject* drawObject) { coloredDrawVector.push_back(drawObject); }
    
    void removeColordObject(ColoredObject* drawObject) {
        for (int i = coloredDrawVector.size() - 1; i >= 0; i--) {
            if (coloredDrawVector[i] == drawObject) {
                coloredDrawVector.erase(coloredDrawVector.begin() + i);
            }
        }
    }

    int getHeight() { return height; }
    int getWidth() { return width; }
    GLuint getMainProgram() { return mainProgram; }
    ModelLoader* getModelLoader() { return modelLoader; }
    
    Camera* getCamera() { return camera; }
    
    ~Render();
};

#endif /* render_hpp */
