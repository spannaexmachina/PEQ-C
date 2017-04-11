//
//  PEQ_geometry.c
//  pequad-c
//
//  Created by Michael Holmes on 7/4/17.
//  Copyright © 2017 Michael Holmes. All rights reserved.
//
//n
#include "PEQ_geometry.h"

//variable shapes
PEQ_RECT PEQ_load_rect(point2D p, int width, int height, COLOUR_NAME c)
{
    PEQ_RECT t;
    
    t.colour = get_colour(c);
    t.p = p;
    t.width = width;
    t.height = height;
    return t;
}

PEQ_LINE PEQ_load_line(point2D p1, point2D p2, COLOUR_NAME c)
{
    PEQ_LINE t;
    
    t.colour = get_colour(c);
    t.p1 = p1;
    t.p2 = p2;
    return t;
}

PEQ_POINT PEQ_load_point(point2D p, COLOUR_NAME c)
{
    PEQ_POINT t;
    t.colour = get_colour(c);
    t.p = p;
    return t;
}

PEQ_CIRCLE PEQ_load_circle(point2D center, float rad, COLOUR_NAME c)
{
    PEQ_CIRCLE t;

    t.colour = get_colour(c);
    t.center = center;
    t.rad = rad;
    return t;
}



//circle
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


//point 2d
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

SDL_Point makeSDLpoint(int x, int y)
{
    SDL_Point temp;
    
    temp.x = x;
    temp.y = y;
    return temp;
}

void addpoints(point2D *dest, point2D src)
{
    dest->x += src.x;
    dest->y += src.y;
}

void subtractpoints(point2D *dest, point2D src)
{
    dest->x -= src.x;
    dest->y -= src.y;
}

//radius
radius makeradius(float r1, float r2)
{
    radius temp;
    
    temp.x = r1;
    temp.y = r2;
    
    return temp;
}







