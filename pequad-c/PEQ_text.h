//
//  PEQ_text.h
//  pequad-c
//
//  Created by Michael Holmes on 9/4/17.
//  Copyright © 2017 Michael Holmes. All rights reserved.
//

#ifndef PEQ_text_h
#define PEQ_text_h

#include <stdio.h>
#include <SDL2_ttf/SDL_ttf.h>

enum PEQ_TEXT_QLTY
{
    SOLID,
    SHADED,
    BLENDED
};
typedef TTF_Font PEQ_Font;

typedef struct {
    PEQ_Font (*PEQ_load_font) (char *filename, int size);
} text;









#endif /* PEQ_text_h */
