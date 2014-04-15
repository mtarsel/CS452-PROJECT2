#include <time.h>

#include "fps.h"

static clock_t start;
static GLfloat fps;

void
GLPong_FPSInit(void) {
        start = SDL_GetTicks();
}

GLfloat
GLPong_FPSCount(void) {
        /* 10.0f is the number of frames we let draw before calculating FPS */
        fps = 10.0f / (SDL_GetTicks() - start) * 1000; /* 1 sec / 1 millisec == 1000 */
        start = SDL_GetTicks();
        return fps;
}

