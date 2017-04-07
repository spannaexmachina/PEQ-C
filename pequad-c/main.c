//
//  main.c
//  pequad-c
//
//  Created by Michael Holmes on 4/4/17.
//  Copyright © 2017 Michael Holmes. All rights reserved.
//

#include "PEQ_engine.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
    PEQ_DATA data;
    //SDL_Renderer *renderer = 0;
    //SDL_Window *window = 0;
    
    pop_main_data(&data/*, renderer, window*/);
    printf("* Pequad-C *\nWarming up...\n");
    
    for (data.is_running = PEQ_init(&data); data.is_running != 0; PEQ_cycle(&data)) {
        }
    
    PEQ_clean(&data);
    SDL_Quit();
    
    return 0;
}



