#ifndef BALL_H
#define BALL_H

#include "globals.h"
#include "shaders.h"

typedef struct {
        GLfloat x, y, z;	//How should we go about these two? (translation)
        GLfloat w, h;		//
        GLfloat vertexarray[];
        GLfloat normalsarray[];
        GLubyte elems[];
        ShaderInfo shaders[];
} Ball_t;

void GLPong_BallDraw(const Ball_t * ball);
void GLPong_BallInit(Ball_t * ball);
void GLPong_BallMove(Ball_t * ball);

#endif

