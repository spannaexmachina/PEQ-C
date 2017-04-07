//
//  PEQ_geometry.c
//  pequad-c
//
//  Created by Michael Holmes on 7/4/17.
//  Copyright © 2017 Michael Holmes. All rights reserved.
//

#include "PEQ_geometry.h"

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


//drawing
void PEQ_draw_line(SDL_Renderer *r, COLOUR_NAME colour, point2D p1, point2D p2)
{
    PEQ_COLOUR c = get_colour(colour);
    
    SDL_SetRenderDrawColor(r, c.r, c.g, c.b, c.a);
    SDL_RenderDrawLine(r, p1.x, p1.y, p2.x, p2.y);
}

void PEQ_draw_rect(SDL_Renderer *r, COLOUR_NAME colour, point2D p, int width, int height)
{
    PEQ_COLOUR c = get_colour(colour);
    SDL_Rect rect;
    
    SDL_SetRenderDrawColor(r, c.r, c.g, c.b, c.a);
    rect.x = p.x;
    rect.y = p.y;
    rect.w = width;
    rect.h = height;
    SDL_RenderDrawRect(r, &rect);
}

/*
void PEQ_draw_all_2D(SDL_Renderer *r, PEQ_2D_graphic *objects[])
{
    int i;
    for (i = 0; i != '\0'; i++) {
        if (objects[i] == PEQ_RECT) {
            PEQ_draw_rect(r, objects[i]->rect.colour, objects[i]->rect.p, objects[i]->rect.width, objects[i]->rect.height);
        }
    }
}
 
 */
