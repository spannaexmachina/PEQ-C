//
//  circle.h
//  pequad-c
//
//  Created by Ruxandra Maritiu on 7/4/17.
//  Copyright © 2017 Michael Holmes. All rights reserved.
//

#ifndef circle_h
#define circle_h


#include "point2D.h"
#include "radius.h"
#include <stdio.h>
#include "math.h"

typedef struct {
    point2D p;
    radius r;
} circle;

circle makecircle(point2D pt, radius r);
point2D ClosestPoint(point2D FromPoint, radius r);

#endif /* circle_h */
