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
    
    pop_main_data(&data);
    printf("* Pequad-C *\nWarming up...\n");
    for (data.is_running = PEQ_init(&data); data.is_running != 0; PEQ_cycle(&data))
        ;
    PEQ_clean(&data);
    SDL_Quit();
    
    return 0;
}



