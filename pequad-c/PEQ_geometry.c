//
//  PEQ_geometry.c
//  pequad-c
//
//  Created by Michael Holmes on 7/4/17.
//  Copyright © 2017 Michael Holmes. All rights reserved.
//

#include "PEQ_geometry.h"

//variable shapes
PEQ_2D_shape PEQ_get_rect(point2D p, int width, int height, COLOUR_NAME c)
{
    PEQ_2D_shape t;
    
    t.rect.type = PEQ_RECT;
    t.rect.colour = c;
    t.rect.p = p;
    t.rect.width = width;
    t.rect.height = height;
    return t;
}

PEQ_2D_shape PEQ_get_line(point2D p1, point2D p2, COLOUR_NAME c)
{
    PEQ_2D_shape t;
    
    t.line.type = PEQ_LINE;
    t.line.colour = c;
    t.line.p1 = p1;
    t.line.p2 = p2;
    return t;
}

PEQ_2D_shape PEQ_get_point(point2D p, COLOUR_NAME c)
{
    PEQ_2D_shape t;
    
    t.point.type = PEQ_POINT;
    t.point.colour = c;
    t.point.p = p;
    return t;
}

PEQ_2D_shape PEQ_get_circ(COLOUR_NAME c, SDL_Point center, float rad)
{
    PEQ_2D_shape t;
    
    t.circle.type = PEQ_CIRCLE;
    t.circle.colour = c;
    t.circle.center = center;
    t.circle.rad = rad;
    return t;
}


void PEQ_draw_shape(SDL_Renderer *r, PEQ_2D_shape *shape)
{
    if (shape->line.type == PEQ_LINE)
        PEQ_draw_line(r, shape->line.colour, shape->line.p1, shape->line.p2);
    else if (shape->rect.type == PEQ_RECT)
        PEQ_draw_rect(r, shape->rect.colour, shape->rect.p, shape->rect.width, shape->rect.height);
    else if (shape->point.type == PEQ_POINT)
        PEQ_draw_point(r, shape->point.colour, shape->point.p);
    else if (shape->point.type == PEQ_CIRCLE)
        PEQ_draw_circle(r, shape->circle.colour, shape->circle.center, shape->circle.rad);  //todo convert to point2D at some point****
}
//variable shape functions
void scale_shape(PEQ_2D_shape s, float scaler)
{
    
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

void PEQ_draw_circle(SDL_Renderer *r, COLOUR_NAME colour, SDL_Point center, float rad)
{
    PEQ_COLOUR c = get_colour(colour);
    SDL_SetRenderDrawColor(r, c.r, c.g, c.b, c.a);
    
    for (float w = 0; w < rad * 2; w++)
    {
        for (float h = 0; h < rad * 2; h++)
        {
            float dx = rad - w; // horizontal offset
            float dy = rad - h; // vertical offset
            if ((dx*dx + dy*dy) <= (rad * rad))
            {
            SDL_RenderDrawPoint(r, center.x + dx, center.y + dy);
            }
        }
    }
}

void PEQ_draw_point(SDL_Renderer *r, COLOUR_NAME colour, point2D p)
{
    PEQ_COLOUR c = get_colour(colour);
    SDL_SetRenderDrawColor(r, c.r, c.g, c.b, c.a);
    
    SDL_RenderDrawPoint(r, p.x, p.y);
}




