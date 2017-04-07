//
//  radius.h
//  pequad-c
//
//  Created by Ruxandra Maritiu on 7/4/17.
//  Copyright © 2017 Michael Holmes. All rights reserved.
//

#ifndef radius_h
#define radius_h

#include "point2D.h"
#include <stdio.h>
#include "math.h"

typedef struct {
    float x;
    float y;
} radius;


radius makeradius(float r1, float r2);

#endif /* radius_h */
