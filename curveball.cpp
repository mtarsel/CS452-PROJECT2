#include "curveball.h"

//includes for paddles and balls
#include "paddle.h"
#include "ball.h"
#include "shaders.h"

/*static int  GLPong_Init(GLPong_t * GLPong);
static int  GLPong_HandleEvents(void);
static void GLPong_Draw(const GLPong_t * GLPong);
static bool GLPong_Collide(const Ball_t * ball, const Paddle_t * paddle);
static void GLPong_CleanUp(void);
static void GLPong_Move(GLPong_t * GLPong);
static void SDL_GL_GetMouseState(GLfloat * x, GLfloat * y);
static GLuint SDL_GL_SurfaceToTexture(SDL_Surface * surface);*/


void input(SDL_Window* screen){

  SDL_Event event;

  while (SDL_PollEvent(&event)){//Handling the keyboard
    switch (event.type){
    case SDL_QUIT:exit(0);break;
    case SDL_KEYDOWN:
      switch(event.key.keysym.sym){
      case SDLK_ESCAPE:exit(0);
      }
    }
  }
}

void display(SDL_Window* screen){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glFlush();
	SDL_GL_SwapWindow(screen);
}

int init(SDL_Window* window){
	SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

   	 // Create an application window with the following settings:
    	window = SDL_CreateWindow(
        	"OpenGL Curveball",                  // window title
        	SDL_WINDOWPOS_CENTERED,           // initial x position
       	SDL_WINDOWPOS_CENTERED,           // initial y position
       	640,                               // width, in pixels
       	480,                               // height, in pixels
       	SDL_WINDOW_OPENGL                  // flags - see below
    	);

    // Check that the window was successfully made
    if (window == NULL) {
        // In the event that the window could not be made...
        fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
        return 1;
    }
    return 0;

}

int main(int argc, char * argv[]) {
	GLPong_t GLPong;
	unsigned int frames = 0;
	bool done = false;
	int action;

	//Declare Window
	SDL_Window *window;   

	if (argc) {
		if (argv) {}
	}
	
/*	if (GLPong_Init(&GLPong) < 0) {
		fprintf(stderr, "Bailing out.\n");
		return -1;
	}

	GLPong_FPSInit();*/
    	
    	if(init(window)){
    		SDL_Quit();
    		exit(1);
    	}
    	
    	//TODO -- write our shaders
	ShaderInfo shaders[]={
	    { GL_VERTEX_SHADER , "vertexshader.glsl"},
	    { GL_FRAGMENT_SHADER , "fragmentshader.glsl"},
	    { GL_NONE , NULL}
	};
	
	
	while (!done) {
		input(window);
//		action = GLPong_HandleEvents();

		//Not sure if we need this part, as our action inputs will be handled with SDL and the input() function
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
