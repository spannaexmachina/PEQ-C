
#ifndef PEQ_object_h
#define PEQ_object_h

#include <stdio.h>
#include "PEQ_geometry.h"
#include "PEQ_utility.h"
//n
typedef enum
{
    GRAPHIC,
    TEXTURE,
} PEQ_OBJECT_TYPE;
/*
typedef union
{
    struct graphic {
        PEQ_OBJECT_TYPE type;
        PEQ_2D_shape shape;
        point2D acc;
    } graphic;
    
    struct texture {
        PEQ_OBJECT_TYPE type;
        PEQ_TEXTURE texture;
        point2D acc;
    } texture;
    
} PEQ_OBJECT;

pbool obj_fade(PEQ_OBJECT *object, Uint8 speed);

void PEQ_draw_obj(SDL_Renderer *r, PEQ_OBJECT *o);

*/
#endif /* PEQ_object_h */
