#ifndef PADDLE_H
#define PADDLE_H

#include "globals.h"
#include "shaders.h"

typedef struct {
        GLfloat x, y, z;
        GLfloat prev_x, prev_y;
        GLfloat vertexarray[];
        GLfloat normalsarray[];
        GLubyte elems[];
        ShaderInfo shaders[];
} Paddle_t;

void GLPong_PaddleDraw(const Paddle_t * paddle);
void GLPong_PaddleInit(Paddle_t * paddle);
void GLPong_PaddleMove(Paddle_t * paddle, GLfloat x, GLfloat y);

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

