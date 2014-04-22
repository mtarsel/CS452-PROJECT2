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
	
	//remove cursor
	SDL_ShowCursor(0);

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
	
		
	//TEXTURE JUNK
	GLuint texture_id;
	GLint uniform_mytexture;
	GLint attribute_texcoord;
	
	
	//Generate some weird texture data	
	GLubyte imageData[]={
		0x0,0x0,0xFF //R, G, B
	};
	//GLubyte * imageData = (GLubyte*)malloc(200);

  	//glEnable(GL_DEPTH_TEST);
  
  	//glViewport(0, 0, 600, 600);
  
  	glGenTextures(1, &texture_id);
  	glBindTexture(GL_TEXTURE_2D, texture_id);
  	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  	glTexImage2D(GL_TEXTURE_2D,0, GL_RGBA,1,1,0,GL_RGBA,GL_UNSIGNED_BYTE,imageData);
	
	attribute_texcoord = glGetAttribLocation(program, "texcoord");
  	glEnableVertexAttribArray(attribute_texcoord);
  	glVertexAttribPointer(attribute_texcoord, 2, GL_FLOAT, GL_FALSE, 0, 0);
	
		
		
	// Transfer the transformation matrices to the shader program
  	GLint model = glGetUniformLocation(program, "modelMatrix" );
  	glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(Model));
  
  	//Lighting stuff  --- CAN MOVE
  	GLint tempLoc;
	GLfloat ambient[] = {0.7f, 0.7f, 0.7f, 1.0f};
	tempLoc = glGetUniformLocation(program,"Ambient");
	glUniform4fv(tempLoc,1,ambient);
	
	GLfloat light1_dir[] = {500.0f, 500.0f, 500.0f};
	GLfloat light1_color[] = {0.1f, 0.7f, 0.2f};
	
	tempLoc = glGetUniformLocation(program,"LightColor1");
	glUniform3fv(tempLoc,1,light1_color);

	tempLoc = glGetUniformLocation(program,"LightDirection1");
	glUniform3fv(tempLoc,1,light1_dir);
  
	tempLoc = glGetUniformLocation(program,"HalfVector1");
	glUniform3fv(tempLoc,1,light1_dir);
	
	
	
	Walls_t walls;
	Ball_t ball;
	Paddle_t testpaddle;
	
	EnvironmentInit();
	WallsInit(&walls);
	BallInit(&ball);
	PaddleInit(&testpaddle);
	int x_trans,y_trans;
	while(true){
	
		mouse_kb_input(window, &x_trans, &y_trans);//keyboard controls
		//clear the screen before rendering a new frame
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		
		WallsDraw(&walls);
		BallDraw(&ball, x_trans, y_trans);
		PaddleDraw(&testpaddle, x_trans, y_trans);
		SDL_GL_SwapWindow(window);
	}

	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();
 
  return 0;
}
