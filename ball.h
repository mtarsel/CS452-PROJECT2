#ifndef BALL_H
#define BALL_H

#include "globals.h"

typedef struct {
        GLfloat x, y, z;
        GLfloat w, h;
        GLfloat r, g, b;
        GLfloat xv, yv, zv;
        GLfloat rotate;
} Ball_t;

void GLPong_BallDraw(const Ball_t * ball);
void GLPong_BallInit(Ball_t * ball, GLuint texture);
void GLPong_BallMove(Ball_t * ball);

#endif

