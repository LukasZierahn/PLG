//
//  Pixel.cpp
//  PLG
//
//  Created by Lukas Zierahn on 17.08.19.
//  Copyright © 2019 Lukas Zierahn. All rights reserved.
//

#include "Pixel.hpp"

Pixel::Pixel(int x, int y, GLubyte* rgb): x(x), y(y), r(rgb[0]), g(rgb[1]), b(rgb[2]) {
}

Pixel::Pixel(int x, int y, GLubyte* rgb, int width, int height): Pixel(x, y, rgb) {
    // After this position has values between 0 and 1, we need to scale those to be between -1 and 1
    position = vec3(x / static_cast<float>(width), 0, y / (static_cast<float>(height)));
    position *= 2;
    position -= 1;
    position.y = 0;
}
