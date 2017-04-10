

#include "PEQ_engine.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[])
{
    PEQ_boot(); //this has to occur before any images are loaded etc.
    
    //sample objects
    PEQ_IMAGE image = PEQ_load_image("darkstar", "assets/images/darkstar.png");
    PEQ_CIRCLE circ = PEQ_load_circle(makepoint(100, 300), 30, RANDOM);
    PEQ_POINT point = PEQ_load_point(makepoint(0, 0), RED);
    
    //centre image
    image.position.y = (PEQ_get_window_height() / 2) - (image.height / 2);
    
    
    //main loop
    while (PEQ_exit_request() != 0) {
        PEQ_handle_events();
        PEQ_start_render();
        //loop code here
        //
        
        
        //crazy circle
        circ.center.x += PEQ_rand(-2, 3);
        circ.center.y += PEQ_rand(-2, 3);
        circ.colour = PEQ_rand_colour(255);
        PEQ_draw_circle(&circ);
        
        //ranbow space dust
        for (int i = 0; i < 200; i++)
        {
            point.colour = PEQ_rand_colour(255);
            point.p.x = PEQ_rand(0, WINDOW_WIDTH);
            point.p.y = PEQ_rand(0, WINDOW_HEIGHT);
            PEQ_draw_point(&point);
        }
        
        //image line
        while (image.position.x < WINDOW_WIDTH) {
                PEQ_draw_image(&image);
                image.position.x += image.width;
            }
        //level out line
        image.position.x = 0;
        
        //jitter image line
        image.position.y += jitterrand(-3, 4);
        
        
        
        //
        //end of loop calls
        PEQ_draw_render();
        PEQ_delay(50);
    }
    return 0;
}



