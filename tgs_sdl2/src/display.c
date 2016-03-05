#include "display.h"
#include "memory.h"

TGS_DISPLAY* display_init(void) {
    TGS_DISPLAY* display = NULL;
    display = (TGS_DISPLAY*)memalloc(sizeof(struct TGS_DISPLAY));
    if (display != NULL) {
        display->set_mode = display_set_mode;
    }
    return display;
}

void display_quit(TGS_DISPLAY* display) {
    if (display != NULL) {
        if (display->display != NULL) {
            memfree(display->display);
        }
        memfree(display);
    }
}

bool display_set_mode(void) {
    return 1;
}
