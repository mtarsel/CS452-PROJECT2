#ifndef PADDLE_H
#define PADDLE_H

#include "globals.h"

typedef struct {
    GLfloat x, y, z;
    GLfloat prev_x, prev_y;
    GLfloat vertexarray[12];
    GLfloat normalsarray[12];
    GLfloat colorarray[16];
    GLubyte elems[12];
    GLuint vaoID,vboID[2],eboID;//buffer objects
} Paddle_t;

typedef struct{
    GLfloat vertexarray[24];
    GLfloat normalsarray[12];
    GLfloat colorarray[32];
    GLubyte elems[24];
    GLuint vaoID,vboID[2],eboID;//buffer objects
} Walls_t;

void WallsDraw(Walls_t * walls, SDL_Window* screen);
void WallsInit(Walls_t * walls);
void PaddleDraw(Paddle_t * paddle, SDL_Window* screen, GLfloat x_trans, GLfloat y_trans);
void PaddleInit(Paddle_t * paddle);
void EnvironmentInit();


#endif /* PADDLE_H */

