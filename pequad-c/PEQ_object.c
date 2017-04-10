//
//  PEQ_object.c
//  pequad-c
//
//  Created by Michael Holmes on 8/4/17.
//  Copyright © 2017 Michael Holmes. All rights reserved.
//

#include "PEQ_object.h"

pbool obj_fade(PEQ_OBJECT *object, Uint8 speed)
{
    
    if (object->graphic.type == GRAPHIC) {
       if (object->graphic.shape.circle.type == PEQ_CIRCLE) {
            if (object->graphic.shape.circle.colour.r != 0) object->graphic.shape.circle.colour.r -= speed;
            if (object->graphic.shape.circle.colour.g != 0) object->graphic.shape.circle.colour.g -= speed;
            if (object->graphic.shape.circle.colour.b != 0) object->graphic.shape.circle.colour.b -= speed;
            if (object->graphic.shape.circle.colour.a != 0) object->graphic.shape.circle.colour.a -= speed;
            if (object->graphic.shape.circle.colour.r == 0 || object->graphic.shape.circle.colour.g == 0 ||
                object->graphic.shape.circle.colour.b == 0 || object->graphic.shape.circle.colour.a == 0)
                return TRUE;
            else return FALSE;
       } else if (object->graphic.shape.line.type == PEQ_LINE) {
           if (object->graphic.shape.line.colour.r != 0) object->graphic.shape.line.colour.r -= speed;
           if (object->graphic.shape.line.colour.g != 0) object->graphic.shape.line.colour.g -= speed;
           if (object->graphic.shape.line.colour.b != 0) object->graphic.shape.line.colour.b -= speed;
           if (object->graphic.shape.line.colour.a != 0) object->graphic.shape.line.colour.a -= speed;
           if (object->graphic.shape.line.colour.r == 0 || object->graphic.shape.line.colour.g == 0 ||
               object->graphic.shape.line.colour.b == 0 || object->graphic.shape.line.colour.a == 0)
               return TRUE;
           else return FALSE;
       } else if (object->graphic.shape.point.type == PEQ_POINT) {
           if (object->graphic.shape.point.colour.r != 0) object->graphic.shape.point.colour.r -= speed;
           if (object->graphic.shape.point.colour.g != 0) object->graphic.shape.point.colour.g -= speed;
           if (object->graphic.shape.point.colour.b != 0) object->graphic.shape.point.colour.b -= speed;
           if (object->graphic.shape.point.colour.a != 0) object->graphic.shape.point.colour.a -= speed;
           if (object->graphic.shape.point.colour.r == 0 || object->graphic.shape.point.colour.g == 0 ||
               object->graphic.shape.point.colour.b == 0 || object->graphic.shape.point.colour.a == 0)
               return TRUE;
           else return FALSE;
        } else if (object->graphic.shape.rect.type == PEQ_RECT) {
            if (object->graphic.shape.rect.colour.r != 0) object->graphic.shape.rect.colour.r -= speed;
            if (object->graphic.shape.rect.colour.g != 0) object->graphic.shape.rect.colour.g -= speed;
            if (object->graphic.shape.rect.colour.b != 0) object->graphic.shape.rect.colour.b -= speed;
            if (object->graphic.shape.rect.colour.a != 0) object->graphic.shape.rect.colour.a -= speed;
            if (object->graphic.shape.rect.colour.r == 0 || object->graphic.shape.rect.colour.g == 0 ||
                object->graphic.shape.rect.colour.b == 0 || object->graphic.shape.rect.colour.a == 0)
                return TRUE;
            else return FALSE;
        }
    } else if (object->graphic.type == TEXTURE)
        return TRUE;
    
    return FALSE;
}

void PEQ_draw_obj(SDL_Renderer *r, PEQ_OBJECT *o)
{
    if (o->texture.type == TEXTURE) {
        PEQ_draw_texture(r, &o->texture.texture, o->texture.texture.position.x, o->texture.texture.position.y, o->texture.texture.w, o->texture.texture.h, o->texture.texture.flip_flag);
    }
    
    //todo add shape draw
}
