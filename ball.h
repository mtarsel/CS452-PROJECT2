#ifndef BALL_H
#define BALL_H

#include "globals.h"

typedef struct {
        GLfloat dir_x, dir_y, dir_z;
        GLfloat speed;
        GLfloat vertexarray[24];
	  GLfloat normalsarray[24];
     	  GLfloat colorarray[32];
    	  GLubyte elems[24];
        GLuint vaoID,vboID[3],eboID;//buffer objects
        //texture stuff
    	  GLuint vbo_cube_texcoords;
    	  GLuint texture_id;
} Ball_t;

void BallDraw(Ball_t * ball, GLuint program);
void BallInit(Ball_t * ball);
GLfloat GetBallCoord(Ball_t * ball, char face);

#endif

