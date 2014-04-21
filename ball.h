#ifndef BALL_H
#define BALL_H

#include "globals.h"

typedef struct {
        GLfloat x, y, z;	//How should we go about these two? (translation)
        GLfloat w, h;		//
        GLfloat vertexarray[24];
	  GLfloat normalsarray[24];
     	  GLfloat colorarray[32];
    	  GLubyte elems[24];
        GLuint vaoID,vboID[3],eboID;//buffer objects
} Ball_t;

void BallDraw(const Ball_t * ball, GLfloat x_trans, GLfloat y_trans);
void BallInit(Ball_t * ball);

#endif

