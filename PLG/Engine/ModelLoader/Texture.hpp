//
//  Texture.hpp
//  
//
//  Created by Lukas Zierahn on 23.06.19.
//

#ifndef Texture_hpp
#define Texture_hpp

#include "includeEngine.h"

class Texture {
    string key;
    
    GLuint texture;
    
public:
    Texture(string key, string path);
    
    void LoadBMPFromPath(string path);
    
    GLuint getTexture() { return texture; }
    
    ~Texture() { glDeleteTextures(1, &texture); }
};

#endif /* Texture_hpp */
