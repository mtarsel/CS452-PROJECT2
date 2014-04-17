#ifndef CURVEBALL_H
#define CURVEBALL_H

#include "globals.h"
#include "paddle.h"

#define GLPONG_WIDTH    800.0f
#define GLPONG_HEIGHT   600.0f

#define GLPONG_FRONT_Z  -3.0f
#define GLPONG_BACK_Z   -9.0f

#define GLPONG_NOACTION 0
#define GLPONG_EXIT     1

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
#define RMASK 0xff000000
#define GMASK 0x00ff0000
#define BMASK 0x0000ff00
#define AMASK 0x000000ff
#else
#define RMASK 0x000000ff
#define GMASK 0x0000ff00
#define BMASK 0x00ff0000
#define AMASK 0xff000000
#endif

/*typedef struct {
        Paddle_t front_paddle;
        Paddle_t back_paddle;
        Ball_t ball;
} GLPong_t;

GLuint box;
*/
#endif

