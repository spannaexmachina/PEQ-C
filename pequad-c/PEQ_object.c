//
//  PEQ_object.c
//  pequad-c
//
//  Created by Michael Holmes on 8/4/17.
//  Copyright © 2017 Michael Holmes. All rights reserved.
//

#include "PEQ_object.h"

void obj_fade(PEQ_OBJECT *object, Uint8 speed)
{
    
    if (object->graphic.type == GRAPHIC) {
        if (object->graphic.shape.circle.type == PEQ_CIRCLE) {
            if (object->graphic.shape.circle.colour.a >= 0) {
                    object->graphic.shape.circle.colour.r -= speed;
                    //object->graphic.shape.circle.colour.g -= speed;
                    //object->graphic.shape.circle.colour.b -= speed;
            }
        } else if (object->graphic.shape.line.type == PEQ_LINE) {
            if (object->graphic.shape.line.colour.a <= 0)
                    object->graphic.shape.line.colour.a -= speed;
        } else if (object->graphic.shape.point.type == PEQ_POINT) {
            if (object->graphic.shape.point.colour.a <= 0)
                    object->graphic.shape.point.colour.a -= speed;
        } else if (object->graphic.shape.rect.type == PEQ_RECT) {
            if (object->graphic.shape.rect.colour.a <= 0)
                    object->graphic.shape.rect.colour.a -= speed;
        }
    } else if (object->graphic.type == TEXTURE)
        return;
}
