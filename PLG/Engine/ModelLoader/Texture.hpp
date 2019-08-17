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
    
    unsigned char* data = nullptr;
    
    GLuint texture;
    
public:
    Texture(string key, string path);
    
    void LoadBMPFromPath(string path);
    
    GLuint getTexture() { return texture; }
    
    ~Texture();
};

#endif /* Texture_hpp */
