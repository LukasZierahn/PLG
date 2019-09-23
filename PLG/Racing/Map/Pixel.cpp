//
//  Pixel.cpp
//  PLG
//
//  Created by Lukas Zierahn on 17.08.19.
//  Copyright © 2019 Lukas Zierahn. All rights reserved.
//
#include "Map.hpp"
#include "TexturedObject.hpp"
#include "Texture.hpp"

#include "Pixel.hpp"

bool Pixel::IsInBounds(TexCoord texCoord) {
    return texCoord.y >= height || texCoord.y < 0
    || texCoord.x >= width || texCoord.x < 0;
}

Pixel::Pixel(Map* map, int x, int y, GLubyte* rgb): Pixel(map, TexCoord(x, y), rgb) {}

Pixel::Pixel(Map* map, TexCoord texturePosition, GLubyte* rgb): Pixel(map, texturePosition, rgb[0], rgb[1], rgb[2]) {}

Pixel::Pixel(Map* map, TexCoord texturePosition, GLubyte r, GLubyte g, GLubyte b): map(map), texCoord(texturePosition), r(r), g(g), b(b) {
    this->width = map->getWidth();
    this->height = map->getHeight();
    
    position = vec3(texturePosition.x / static_cast<float>(width), 0, texturePosition.y / (static_cast<float>(height)));
    position *= 2;
    position -= 1;
    position.y = 0;
}

Pixel::Pixel(Pixel* pixel): Pixel(pixel->map, pixel->texCoord, pixel->r, pixel->g, pixel->b) {}

int Pixel::CountNeighbours(bool(*condition)(Pixel)) {
    int totalCount = 0;
    for (int checkX = -1; checkX < 2; checkX++) {
        for (int checkY = -1; checkY < 2; checkY++) {
            
            if (checkX == 0 && checkY == 0) continue;
            
            if (IsInBounds(texCoord.Offset(checkX, checkY))) {
                Pixel neighbour = map->getPixel(texCoord.Offset(checkX, checkY));
                if (condition(neighbour)) {
                    totalCount++;
                }
            }
        }
    }
    
    return totalCount;
}

Pixel Pixel::FindNeighbour(bool(*condition)(Pixel)) {
    for (int checkX = 0; checkX < 3; checkX++) {
        for (int checkY = 0; checkY < 3; checkY++) {
            
            if (checkX == 0 && checkY == 0) continue;
            
            if (IsInBounds(texCoord.Offset(checkX, checkY))) {
                Pixel neighbour = map->getPixel(texCoord.Offset(checkX, checkY));
                if (condition(neighbour)) {
                    return neighbour;
                }
            }
        }
    }
    
    GLubyte colourData [] = {0, 0, 0};
    return Pixel(map, -1, -1, colourData);
}

void Pixel::RecursiveAddAllNeighbours(vector<Pixel*>* addingTarget, TexCoord previousNode) {
    EditPixelOnMap(255, 0, 0);
    
    for (int checkX = -1; checkX < 2; checkX++) {
        for (int checkY = -1; checkY < 2; checkY++) {
            
            if (checkX == 0 && checkY == 0) continue;

            TexCoord newPosition = texCoord.Offset(checkX, checkY);
            
            Pixel* neighbour = new Pixel(map->getPixel(newPosition));
            cout << neighbour->CountNeighbours(&neighbour->IsWhite) << endl;
            if (neighbour->CountNeighbours(&neighbour->IsWhite) >= 1) {
                addingTarget->push_back(neighbour);
                neighbour->RecursiveAddAllNeighbours(addingTarget, texCoord);
            }
        }
    }
}

void Pixel::EditPixelOnMap(unsigned char r, unsigned char g, unsigned char b) {
    map->getMapObject()->getTexture()->EditPixel(texCoord.x, texCoord.y, r, g, b);
}
