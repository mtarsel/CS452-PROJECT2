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
	//Ball stuff
	BallInit(&ball);
	
	ball.dir_z=-1;
	ball.dir_x=0;
	ball.dir_y=0;
	ball.speed=0.5;
	int score = 0;
	
	PaddleInit(&testpaddle);
	int x_trans,y_trans;
	while(true){
		mouse_kb_input(window, &x_trans, &y_trans);//mouse/keyboard controls
		
		//printf("Bx: %f, By: %f", GetBallCoord(&ball, 'r')-.75, GetBallCoord(&ball, 't')-.75);
		//printf("   ------     Px: %f, Py: %f\n", x_trans/30.0, 1-(y_trans/30.0));
		
		if((GetBallCoord(&ball, 'r') >= ((x_trans/30)-3.5)) && 
		   (GetBallCoord(&ball, 'l') <= ((x_trans/30)+3.5)) &&
		   (GetBallCoord(&ball, 't') >= ((1-(y_trans/30.0))-2.0)) &&
		   (GetBallCoord(&ball, 'b') <= ((1-(y_trans/30.0))+2.0)) &&
		   (GetBallCoord(&ball, 'f') >= -1.0f) &&	//The paddle collision calculations
		   (GetBallCoord(&ball, 'f') <= 1.0f)){	//
		   	ball.dir_z=-1;
		   	score++;
		   	ball.speed+=0.1; //speeds up the ball on paddle hit
		   	printf("X_TRANS: %f, %f\n", (x_trans/30)-3.5, x_trans/30);
		   	printf("BALLCOORD: %f, %f\n", GetBallCoord(&ball, 'r'), GetBallCoord(&ball, 'l'));
		   	
		   	//for x,y modification of the ball
		   	if((GetBallCoord(&ball, 'r') >= ((x_trans/30)-3.5)) && (GetBallCoord(&ball, 'l') <= ((x_trans/30)))) { 
		   	   		printf("Hit left side.\n"); 
		   	   		ball.dir_x-=(ball.speed/4);
		   	   		//This if is for top
		   	   		if((GetBallCoord(&ball, 't') >= ((1-(y_trans/30.0))-2.0)) && (GetBallCoord(&ball, 't') <= ((1-(y_trans/30.0))))) {
		   	   			printf("Hit top side.\n"); 
		   	   			ball.dir_y+=(ball.speed/4);
		   	   		}
		   	   		//This if is for bottom
		   	   		if((GetBallCoord(&ball, 'b') <= ((1-(y_trans/30.0))+2.0)) && (GetBallCoord(&ball, 't') >= ((1-(y_trans/30.0))))) {
		   	   			printf("Hit bottom side.\n"); 
		   	   			ball.dir_y-=(ball.speed/4);
		   	   		}
		   	   	}
		   	   
		   	if((GetBallCoord(&ball, 'l') <= ((x_trans/30)+3.5)) && (GetBallCoord(&ball, 'l') >= ((x_trans/30)))) { 
		   	   		printf("Hit right side.\n"); 
		   	   		ball.dir_x+=(ball.speed/4);
		   	   		//This if is for top
		   	   		if((GetBallCoord(&ball, 't') >= ((1-(y_trans/30.0))-2.0)) && (GetBallCoord(&ball, 'b') <= ((1-(y_trans/30.0))))) {
		   	   			printf("Hit top side.\n"); 
		   	   			ball.dir_y+=(ball.speed/4);
		   	   		}
		   	   		//This if is for bottom
		   	   		if((GetBallCoord(&ball, 'b') <= ((1-(y_trans/30.0))+2.0)) && (GetBallCoord(&ball, 'b') >= ((1-(y_trans/30.0))))) {
		   	   			printf("Hit bottom side.\n"); 
		   	   			ball.dir_y-=(ball.speed/4);
		   	   		}
		   	   }
		   	
		   } 
		//Collision detections -- paddle comes first
		//if(GetBallCoord(&ball, 'd') == 50.0f) ball.dir_z=-1;
		
		if(GetBallCoord(&ball, 'd') < -320.0f) ball.dir_z=-ball.dir_z; //bounce off back wall
		if(GetBallCoord(&ball, 'r') > 11.5f) ball.dir_x=-ball.dir_x; //bounce off right wall
		if(GetBallCoord(&ball, 'l') < -11.5f) ball.dir_x=-ball.dir_x; //bounce off left wall
		if(GetBallCoord(&ball, 't') > 11.5f) ball.dir_y=-ball.dir_y; //bounce off top wall
		if(GetBallCoord(&ball, 'b') < -11.5f) ball.dir_y=-ball.dir_y; //bounce off bottom wall
		if(GetBallCoord(&ball, 'f') > 50.0f) break; //losing condition
		//else if(GetBallCoord(&ball, 'f') > 0.0f) exit(0); //you lost
		
		//clear the screen before rendering a new frame
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		
		WallsDraw(&walls, program);
		BallDraw(&ball, program);
		PaddleDraw(&testpaddle, x_trans, y_trans, program);
		SDL_GL_SwapWindow(window);
	}
	
	printf("Your score is: %i\n", score);

	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();
 
  return 0;
}
