//
//  point2D.h
//  pequad-c
//
//  Created by Michael Holmes on 4/4/17.
//  Copyright © 2017 Michael Holmes. All rights reserved.
//

#ifndef point2D_h
#define point2D_h

#include <stdio.h>
#include "math.h"

typedef struct {
    double x;
    double y;
} point2D;

point2D result_add_points(point2D p1, point2D p2);
void addpoints(point2D *dest, point2D *src);
void subtractpoints(point2D *dest, point2D *src);
point2D makepoint(double x, double y);

#endif /* point2D_h */
