#include "curveball.h"

/*static int  GLPong_Init(GLPong_t * GLPong);
static int  GLPong_HandleEvents(void);
static void GLPong_Draw(const GLPong_t * GLPong);
static bool GLPong_Collide(const Ball_t * ball, const Paddle_t * paddle);
static void GLPong_CleanUp(void);
static void GLPong_Move(GLPong_t * GLPong);
static void SDL_GL_GetMouseState(GLfloat * x, GLfloat * y);
static GLuint SDL_GL_SurfaceToTexture(SDL_Surface * surface);*/

int main(int argc, char * argv[]) {
	GLPong_t GLPong;
	unsigned int frames = 0;
	int done = 0;
	int action;

	if (argc) {
		if (argv) {}
	}
	
/*	if (GLPong_Init(&GLPong) < 0) {
		fprintf(stderr, "Bailing out.\n");
		return -1;
	}

	GLPong_FPSInit();*/
	
	while (!done) {
//		action = GLPong_HandleEvents();
		switch (action) {
			case GLPONG_EXIT:	/* exit */
				done = 1;
				break;
		}

//		GLPong_Move(&GLPong);

		/* begin drawing */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//		GLPong_Draw(&GLPong);

		frames++;
		if (frames == 30) {
			frames = 0;
		}

		//GLPong_TextDrawFPS(GLPong_FPSCount());

	//	SDL_GL_SwapBuffers();
		/* end drawing */

		SDL_Delay(10);
	}
	//GLPong_CleanUp();
	
	return 0;
}
