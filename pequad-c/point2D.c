//
//  point2D.c
//  pequad-c
//
//  Created by Michael Holmes on 4/4/17.
//  Copyright © 2017 Michael Holmes. All rights reserved.
//

#include "point2D.h"

point2D result_add_points(point2D p1, point2D p2)
{
    p1.x += p2.x;
    p1.y += p2.y;
    return p1;
}

point2D makepoint(int x, int y)
{
    point2D temp;
    
    temp.x = x;
    temp.y = y;
    return temp;
}

void addpoints(point2D *dest, point2D *src)
{
    dest->x += src->x;
    dest->y += src->y;
}

void subtractpoints(point2D *dest, point2D *src)
{
    dest->x -= src->x;
    dest->y -= src->y;
}
