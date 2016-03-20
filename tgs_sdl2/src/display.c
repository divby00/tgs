#include "display.h"
#include "memory.h"
#include <SDL2/SDL.h>

TGS_DISPLAY* display_init(void) {
    TGS_DISPLAY* display = NULL;
    SDL_Init(SDL_INIT_VIDEO);
    display = _memalloc(sizeof(struct TGS_DISPLAY));
    if (display != NULL) {
        display->set_mode = display_set_mode;
    }
    return display;
}

void display_quit(TGS_DISPLAY* display) {
    if (display != NULL) {
        if (display->display != NULL) {
            _memfree(display->display);
        }
        _memfree(display);
    }
}

unsigned char display_set_mode(void) {
    return 1;
}
