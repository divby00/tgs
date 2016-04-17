#ifndef __DISPLAY_H__
#define __DISPLAY_H__


#include <stdint.h>
#include <SDL2/SDL.h>


typedef struct TGS_DISPLAY {
    SDL_Surface* display;
    uint8_t (*set_mode)(void);

} TGS_DISPLAY;


TGS_DISPLAY* display_init(void);
void display_quit(TGS_DISPLAY* display);


#endif
