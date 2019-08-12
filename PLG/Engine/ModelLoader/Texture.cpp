//
//  Texture.cpp
//  
//
//  Created by Lukas Zierahn on 23.06.19.
//

#include <stdio.h>
#include <stdlib.h>
#include "Texture.hpp"

Texture::Texture(string key, string path) {
    this->key = key;
    LoadBMPFromPath(path);
}

void Texture::LoadBMPFromPath(string path) {
    // Data read from the header of the BMP file
    unsigned char header[54];
    unsigned int dataPos;
    unsigned int imageSize;
    unsigned int width, height;
    // Actual RGB data
    unsigned char * data;
    
    // Open the file
    FILE* file = fopen(path.c_str(), "rb");
    if (!file) {
        printf("Texture: %s not found\n", path.c_str());
        getchar();
        return;
    }
    
    // Read the header, i.e. the 54 first bytes
    
    // If less than 54 bytes are read, problem
    if ( fread(header, 1, 54, file) != 54 ){
        printf("Not a correct BMP file\n");
        fclose(file);
        return;
    }
    // A BMP files always begins with "BM"
    if ( header[0] != 'B' || header[1] != 'M' ){
        printf("Tried to open a none BMP-file as a BMP-file\n");
        fclose(file);
        return;
    }
    // Make sure this is a 24bpp file
    if ( *(int*)&(header[0x1E])!=0  ) { printf("Not a 24bpp BMP file\n"); fclose(file); return; }
    if ( *(int*)&(header[0x1C])!=24 ) { printf("Not a 24bpp BMP file\n"); fclose(file); return;}
    
    // Read the information about the image
    dataPos    = *(int*)&(header[0x0A]);
    imageSize  = *(int*)&(header[0x22]);
    width      = *(int*)&(header[0x12]);
    height     = *(int*)&(header[0x16]);
    
    // Some BMP files are misformatted, guess missing information
    if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
    if (dataPos==0)      dataPos=54; // The BMP header is done that way
    
    // Create a buffer
    data = new unsigned char [imageSize];
    
    // Read the actual data from the file into the buffer
    fread(data, 1, imageSize, file);
    
    // Everything is in memory now, the file can be closed.
    fclose (file);
    
    // Create one OpenGL texture
    glGenTextures(1, &texture);
    
    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, texture);
    
    // Give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    
    // OpenGL has now copied the data. Free our own version
    delete [] data;
    
    // nice trilinear filtering ...
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    // ... which requires mipmaps. Generate them automatically.
    glGenerateMipmap(GL_TEXTURE_2D);
}