#include "ball.h"

//static GLuint ball_texture;

void GLPong_BallDraw(const Ball_t * ball, SDL_Window* screen) {
	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	glDrawElements(GL_TRIANGLE_STRIP,36,GL_UNSIGNED_BYTE,NULL);
	
	glFlush();
	SDL_GL_SwapWindow(screen);
	
/* --------------------------------- TODO change these functions below to utilize our display methods and shaders -------------------------- */
	/*glLoadIdentity();
	glBindTexture(GL_TEXTURE_2D, ball_texture);
	glEnable(GL_TEXTURE_2D);
	glColor3f(ball->r, ball->g, ball->b);
	glTranslatef(ball->x, ball->y, ball->z);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex2f(ball->w, ball->h);	//Lower Left
		glTexCoord2f(1.0f, 1.0f); glVertex2f(0.0f, ball->h);	//Lower Right
		glTexCoord2f(1.0f, 0.0f); glVertex2f(0.0f, 0.0f);		//Upper Right
		glTexCoord2f(0.0f, 0.0f); glVertex2f(ball->w, 0.0f);	//Upper Left
	glEnd();
	glDisable(GL_TEXTURE_2D);

#ifdef DEBUG
	//Lower Left
	glLoadIdentity();
	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslatef(ball->x, ball->y, ball->z);
	glBegin(GL_POINTS);
		glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();

	//Lower Right
	glLoadIdentity();
	glTranslatef(ball->x + ball->w, ball->y, ball->z);
	glBegin(GL_POINTS);
		glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	
	//Top Right
	glLoadIdentity();
	glTranslatef(ball->x + ball->w, ball->y + ball->h, ball->z);
	glBegin(GL_POINTS);
		glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	//Top Left
	glLoadIdentity();
	glTranslatef(ball->x, ball->y + ball->h, ball->z);
	glBegin(GL_POINTS);
		glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
#endif
	
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, ball->z);
	glCallList(box);*/
}

void
GLPong_BallInit(Ball_t * ball) {

	GLfloat normalVector = 1.0f / sqrt(3.0f);

	//This is what we'll be using for the geometry of the ball -- changeme
	ball.vertexarray[]={-ball.w, ball.h, 0.0f	//Lower Left
			     ball.w, ball.h, 0.0f		//Lower Right
			     ball.w, -ball.h, 0.0f	//Upper Right
			     -ball.w, -ball.h, 0.0f	//Upper Left
	};
		     
	ball.normalsarray[] = {-normalVector,normalVector,0.0f,	//Lower Left
                       normalVector,normalVector,0.0f,	//Lower Right
                       normalVector,-normalVector,0.0f,	//Upper Right
                       -normalVector,-normalVector,0.0f	//Upper Left
	};

	ball.elems[] = {0,1,2,3,4};

	//TODO -- write our shaders
	ball.shaders[]={
  	  { GL_VERTEX_SHADER , "ballvertexshader.glsl"},
 	  { GL_FRAGMENT_SHADER , "ballfragmentshader.glsl"},
 	  { GL_NONE , NULL}
	};

/*
	ball->w = 0.5f;
	ball->h = 0.5f;
	ball->x = -(ball->w / 2);
	ball->y = -(ball->h / 2);
	ball->z = GLPONG_FRONT_Z;
	ball->r = 1.0f;
	ball->g = 0.0f;
	ball->b = 0.0f;
	ball->xv = 0.02f;
	ball->yv = 0.01f;
	ball->zv = -0.05f;

	ball_texture = texture;
	*/
}

void
GLPong_BallMove(Ball_t * ball) {
	ball->x += ball->xv;
	if (ball->x > 1.0f) {
		ball->x = 1.0f;
		ball->xv = -ball->xv;
	} else if (ball->x  + ball->w < -1.0f) {
		ball->x = -1.0f - ball->w;
		ball->xv = -ball->xv;
	}

	ball->y += ball->yv;
	if (ball->y > 0.5f) {
		ball->y = 0.5f;
		ball->yv = -ball->yv;
	} else if (ball->y + ball->h < -0.5f) {
		ball->y = -0.5f - ball->h;
		ball->yv = -ball->yv;
	}

	ball->z += ball->zv;
	if (ball->z < GLPONG_BACK_Z) {
		ball->z = GLPONG_BACK_Z;
		ball->zv = -ball->zv;
	} else if (ball->z > GLPONG_FRONT_Z) {
		ball->z = GLPONG_FRONT_Z;
		ball->zv = -ball->zv;
	}
}
