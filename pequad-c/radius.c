//
//  radius.c
//  pequad-c
//
//  Created by Ruxandra Maritiu on 7/4/17.
//  Copyright © 2017 Michael Holmes. All rights reserved.
//

#include "radius.h"

radius makeradius(float r1, float r2)
{
    radius temp;
    
    temp.x = r1;
    temp.y = r2;
    
    return temp;
}

