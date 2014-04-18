#include "curveball.h"

//includes for paddles and balls
#include "environment.h"
#include "ball.h"
#include "shaders.h"
#include "globals.h"

void mouse_kb_input(SDL_Window* screen,int * x_trans, int * y_trans){

  SDL_Event event;

  while (SDL_PollEvent(&event)){//Handling the keyboard
  	int x,y;
  	SDL_GetMouseState(&x,&y);
  	x=x-(WINDOW_SIZE/2);
  	y=y-(WINDOW_SIZE/2);
  	memcpy(x_trans, &x, sizeof(int));
  	memcpy(y_trans, &y, sizeof(int));
   	switch (event.type){
    	case SDL_QUIT:exit(0);break;
    	case SDL_KEYDOWN:
      if(event.key.keysym.sym == SDLK_ESCAPE) exit(0);
    }
  }
}


int main(int argc, char * argv[]) {
	//SDL window and context management
	SDL_Window *window;
	
	if(SDL_Init(SDL_INIT_VIDEO)<0){//initilizes the SDL video subsystem
		fprintf(stderr,"Unable to create window: %s\n", SDL_GetError());
		SDL_Quit();
		exit(1);//die on error
	}

	//create window
	window = SDL_CreateWindow(
		"OpenGL Curveball", //Window title
		SDL_WINDOWPOS_UNDEFINED, //initial x position
		SDL_WINDOWPOS_UNDEFINED, //initial y position
		640,				 //width, in pixels
		640,				 //height, in pixels
		SDL_WINDOW_OPENGL	//flags to be had
	);
	
	//check window creation
	if(window==NULL){
		fprintf(stderr,"Unable to create window: %s\n",SDL_GetError());
	}
	

	//creates opengl context associated with the window
	SDL_GLContext glcontext=SDL_GL_CreateContext(window);
	
	//initializes glew
	glewExperimental=GL_TRUE;
	if(glewInit()){
		fprintf(stderr, "Unable to initalize GLEW");
		exit(EXIT_FAILURE);
	}
  
	
	
		

	glm::mat4 Model;
	
  //Load our shaders into the "program" variable
	GLuint program;
	ShaderInfo shaders[]={
		{ GL_VERTEX_SHADER , "vertexshader.glsl"},
		{ GL_FRAGMENT_SHADER , "fragmentshader.glsl"}, 
		{ GL_NONE , NULL} 
	};
	program = initShaders(shaders);	
		
	// Transfer the transformation matrices to the shader program
  GLint model = glGetUniformLocation(program, "modelMatrix" );
  glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(Model));
	
	Paddle_t testpaddle;
	PaddleInit(&testpaddle);
	int x_trans,y_trans;
	while(true){
	
		mouse_kb_input(window, &x_trans, &y_trans);//keyboard controls
		//clear the screen before rendering a new frame
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		PaddleDraw(&testpaddle, window, x_trans, y_trans);
		
	}

	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();
 
  return 0;
}
