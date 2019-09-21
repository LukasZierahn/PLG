//
//  HelperFunction.hpp
//  PLG
//
//  Created by Lukas Zierahn on 25.08.19.
//  Copyright © 2019 Lukas Zierahn. All rights reserved.
//

#ifndef HelperFunction_hpp
#define HelperFunction_hpp

#include <stdio.h>
#include <vector>
using namespace std;

#include <glm/glm.hpp>
using namespace glm;

template<typename T>
void SortArray(vector<T>* array, bool (*isBigger)(T, T)) {
    bool swapped = true;
    
    while (swapped) {
        swapped = false;
        for (int i = 0; i < array->size() - 1; i++) {
            if (isBigger((*array)[i], (*array)[i + 1])) {
                T tmp = (*array)[i];
                array->assign(i, (*array)[i + 1]);
                array->assign(i + 1, tmp);
                swapped = true;
            }
        }
    }
    
    return;
}

#endif /* HelperFunction_hpp */
