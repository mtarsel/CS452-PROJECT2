#ifndef PADDLE_H
#define PADDLE_H

#include "globals.h"

typedef struct {
        GLfloat x, y, z;
        GLfloat prev_x, prev_y;
        GLfloat vertexarray[12];
        GLfloat normalsarray[12];
        GLfloat colorarray[12];
        GLubyte elems[12];
        GLuint vaoID,vboID[2],eboID;//buffer objects
} Paddle_t;

void GLPong_PaddleDraw(Paddle_t * paddle, SDL_Window* screen, GLfloat x_trans, GLfloat y_trans);
void GLPong_PaddleInit(Paddle_t * paddle);
void GLPong_PaddleMove(Paddle_t * paddle, GLfloat * array, int x, int y);

/*
static inline GLfloat
GLPong_PaddleXV(const Paddle_t * paddle) {
        return paddle->x - paddle->prev_x;
}

static inline GLfloat
GLPong_PaddleYV(const Paddle_t * paddle) {
        return paddle->y - paddle->prev_y;
}
*/
#endif /* PADDLE_H */

