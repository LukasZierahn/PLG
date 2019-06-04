//
//  render.hpp
//  PLG
//
//  Created by Lukas Zierahn on 02.06.19.
//  Copyright © 2019 Lukas Zierahn. All rights reserved.
//

#ifndef render_hpp
#define render_hpp

#include "include.h"

class Render {
private:
    int width = 800;
    int height = 600;
    
    GLFWwindow* window;
    
    GLuint mainProgram;
    
    int InitGL();
    GLuint LoadShader(const char* path, GLenum type);
    
public:
    Render();
    
    GLFWwindow* getWindow() { return window; }
    
    void Draw();
        
    int getHeight() { return height; }
    int getWidth() { return width; }
};

#endif /* render_hpp */
