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

/*GLuint vaoID,vboID[2],eboID;
GLuint program;

GLfloat size=.5;
GLfloat normalVector = 1.0f / sqrt(3.0f);

GLfloat vertexarray[]={size,size,-size,
				size,-size,-size,
                       -size,-size,-size,
                       -size,size,-size,
                       size,size,size,
                       size,-size,size,
                       -size,-size,size,
                       -size,size,size
                       };

GLfloat normalsarray[] = {normalVector,normalVector,-normalVector,
                       normalVector,-normalVector,-normalVector,
                       -normalVector,-normalVector,-normalVector,
                       -normalVector,normalVector,-normalVector,
                       normalVector,normalVector,normalVector,
                       normalVector,-normalVector,normalVector,
                       -normalVector,-normalVector,normalVector,
                       -normalVector,normalVector,normalVector
};
					   									
GLubyte elems[]={0,1,2,3,
		     7,4,5,6,
     		     7,3,0,4,
     		     5,6,2,1,
     		     0,1,5,4,
		     7,3,2,6};
*/
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

void display(SDL_Window* screen){
	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	glDrawElements(GL_QUADS,24,GL_UNSIGNED_BYTE,NULL);
	glFlush();
	SDL_GL_SwapWindow(screen);
}

int init(){

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
  
	//Load our shaders into the "program" variable
	//GLuint program;
	ShaderInfo shaders[]={
		{ GL_VERTEX_SHADER , "vertexshader.glsl"},
		{ GL_FRAGMENT_SHADER , "fragmentshader.glsl"}, 
		{ GL_NONE , NULL} 
	};
	initShaders(shaders);	
	//program=initShaders(shaders);
  
	//init();
	
	Paddle_t testpaddle;
	GLPong_PaddleInit(&testpaddle);
	int x_trans,y_trans;
	while(true){
		mouse_kb_input(window, &x_trans, &y_trans);//keyboard controls
		GLPong_PaddleDraw(&testpaddle, window, x_trans, y_trans);
	}

	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();
 
  return 0;
}
