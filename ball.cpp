#include "ball.h"

//static GLuint ball_texture;

void GLPong_BallDraw(const Ball_t * ball, SDL_Window* screen) {
	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	glDrawElements(GL_TRIANGLE_STRIP,36,GL_UNSIGNED_BYTE,NULL);
	
	glFlush();
	SDL_GL_SwapWindow(screen);
	

void
GLPong_BallInit(Ball_t * ball) {


}

void
GLPong_BallMove(Ball_t * ball) {
	
}
