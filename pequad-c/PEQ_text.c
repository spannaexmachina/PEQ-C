//
//  PEQ_text.c
//  pequad-c
//
//  Created by Michael Holmes on 9/4/17.
//  Copyright © 2017 Michael Holmes. All rights reserved.
//

#include "PEQ_text.h"


PEQ_Font *PEQ_load_font(char *filename, int size)
{
    PEQ_Font *t;
    
    
    
    t = TTF_OpenFont(filename, size);
    if (t == NULL)
        printf("failed to load font %s: %s", filename, SDL_GetError());
    return t;
}


