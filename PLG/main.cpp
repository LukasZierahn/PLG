//
//  main.cpp
//  PLG
//
//  Created by Lukas Zierahn on 02.06.19.
//  Copyright © 2019 Lukas Zierahn. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "render.hpp"
#include "Racing/Racing.hpp"

int main( void )
{
    Racing racing = Racing();
    
    racing.Mainloop();
    
    return 0;
}

