#include "logic.h"
#include "view.h"

//Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <stdio.h>

int main(int argc, char** argv)
{
  /*** Initialization ***/

  SDL_Init( SDL_INIT_VIDEO );
  
  Logic logic = Logic();
  View view = view();
      

  /*** Main Loop ***/
  bool running = true;

  unsigned int prevTicks = 0;
  unsigned int ticks = 0;
  double time;


  // While application is running
  while( running )
  {
    //getting ticks since last loop
    ticks = SDL_GetTicks() -prevTicks;
    prevTicks = SDL_GetTicks();
    //turns ticks into seconds
    time = ticks/1000.0;

    //run updates
    logic.update(time);
    running = view.update();

    //delay so it isnt too fast
    SDL_Delay(10);
  }

  /*** Clean Up ***/

  // Quit SDL subsystems
  SDL_Quit();
  
  // Done.
  return 0;
}