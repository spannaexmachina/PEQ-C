//
//  circle.c
//  pequad-c
//
//  Created by Ruxandra Maritiu on 7/4/17.
//  Copyright © 2017 Michael Holmes. All rights reserved.
//

#include "circle.h"
#include "point2D.h"
#include "radius.h"

circle makecircle(point2D p, radius r)
{
    circle temp;
   
    temp.p = p;
    temp.r = r;
    
    return temp;
}


point2D ClosestPoint(point2D FromPoint, radius r)
{
    FromPoint.x += r.x;
    FromPoint.y += r.y;
    return FromPoint;
}
