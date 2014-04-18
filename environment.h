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

void PaddleDraw(Paddle_t * paddle, SDL_Window* screen, GLfloat x_trans, GLfloat y_trans);
void PaddleInit(Paddle_t * paddle);


#endif /* PADDLE_H */

