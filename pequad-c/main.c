

#include "PEQ_engine.h"
#include <stdio.h>
#include <stdlib.h>
//n

int main(int argc, char* argv[])
{
    PEQ_boot(); //this has to occur before any images are loaded etc.
    
    //sample objects
    PEQ_IMAGE image = PEQ_load_image("darkstar", "assets/images/darkstar.png");
    PEQ_CIRCLE circ = PEQ_load_circle(makepoint(100, 300), 30, RANDOM);
    PEQ_POINT point = PEQ_load_point(makepoint(0, 0), RED);
    
    PEQ_LABEL lab = PEQ_load_label("HELLO WORLD", "assets/fonts/Arial.ttf", 15, RED, BLUE, SOLID);
    
    //centre image
    image.position.y = (PEQ_get_window_height() / 2) - (image.height / 2);
    
    lab.pos = makepoint(300, 300);
    
    
    //main loop
    while (PEQ_exit_request() != 0) {
        PEQ_frame_start();
        PEQ_handle_events();
        
        PEQ_clear_render();
        //loop code here
        //
        

          //DEMO
        //crazy circle
        circ.center.x += PEQ_rand(-3, 5);
        circ.center.y += PEQ_rand(-3, 4);
        circ.colour = PEQ_rand_colour(255);
        PEQ_draw_circle(&circ);
      
        //ranbow space dust
        for (int i = 0; i < 300; i++)
        {
            point.colour = PEQ_rand_colour(255);
            point.p.x = PEQ_rand(0, PEQ_get_window_width());
            point.p.y = PEQ_rand(0, PEQ_get_window_height());
            PEQ_draw_point(&point);
        }
        
        //image line
        while (image.position.x < PEQ_get_window_width()) {
                PEQ_draw_image(&image);
                image.position.x += image.width;
            }
        //level out line
        image.position.x = 0;
        
        //jitter image line
        image.position.y += jitterrand(-3, 4);
        
        PEQ_draw_label(&lab);
        
        
        //
        //end of loop calls
        PEQ_draw_render();
        
        PEQ_frame_end();
        
        PEQ_delay(100);
    }
    return 0;
}



