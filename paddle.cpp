#include "paddle.h"


void GLPong_PaddleDraw(const Paddle_t * paddle){

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	glDrawElements(GL_TRIANGLE_STRIP,36,GL_UNSIGNED_BYTE,NULL);
	
	glFlush();
	SDL_GL_SwapWindow(screen);
};

/* --------------------------------- TODO change these functions below to utilize our display methods and shaders -------------------------- */

void GLPong_PaddleInit(Paddle_t * paddle){

	
	GLfloat paddlesize = 1.0f;
	GLfloat normalVector = 1.0f / sqrt(3.0f);

	//This is what we'll be using for the geometry of the ball
	paddle.vertexarray[]={-paddlesize, paddlesize, 0.0f	//Lower Left
			     paddlesize, paddlesize, 0.0f	//Lower Right
			     paddlesize, -paddlesize, 0.0f	//Upper Right
			     -paddlesize, -paddlesize, 0.0f	//Upper Left
	};
			     
	paddle.normalsarray[] = {-normalVector,normalVector,0.0f,	//Lower Left
                       normalVector,normalVector,0.0f,	//Lower Right
                       normalVector,-normalVector,0.0f,	//Upper Right
                       -normalVector,-normalVector,0.0f	//Upper Left
	};

	paddle.elems[] = {0,1,2,3,4};

	
};

void GLPong_PaddleMove(Paddle_t * paddle, GLfloat x, GLfloat y){

};
