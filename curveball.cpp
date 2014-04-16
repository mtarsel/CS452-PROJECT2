#include "curveball.h"

//includes for paddles and balls
#include "paddle.h"
#include "ball.h"
#include "shaders.h"
//#include "shaders.h"

/*static int  GLPong_Init(GLPong_t * GLPong);
static int  GLPong_HandleEvents(void);
static void GLPong_Draw(const GLPong_t * GLPong);
static bool GLPong_Collide(const Ball_t * ball, const Paddle_t * paddle);
static void GLPong_CleanUp(void);
static void GLPong_Move(GLPong_t * GLPong);
static void SDL_GL_GetMouseState(GLfloat * x, GLfloat * y);
static GLuint SDL_GL_SurfaceToTexture(SDL_Surface * surface);*/

GLuint vaoID,vboID[2],eboID;
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
	
	glDrawElements(GL_QUADS,24,GL_UNSIGNED_BYTE,NULL);
	glFlush();
	SDL_GL_SwapWindow(screen);
}

int init(){
	
	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	//glEnable(GL_NORMALIZE);
	
	glViewport(0, 0, 640, 640);
	
	glGenVertexArrays(1,&vaoID);
	glBindVertexArray(vaoID);
	
	glGenBuffers(2, vboID);
	glBindBuffer(GL_ARRAY_BUFFER,vboID[0]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertexarray),vertexarray,GL_STATIC_DRAW);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);
	
	glBindBuffer(GL_ARRAY_BUFFER, vboID[1]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(normalsarray),normalsarray,GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	
	glGenBuffers(1,&eboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(elems),elems,GL_STATIC_DRAW);

	ShaderInfo shaders[]={
		{ GL_VERTEX_SHADER , "vertexshader.glsl"},
		{ GL_FRAGMENT_SHADER , "fragmentshader.glsl"}, 
		{ GL_NONE , NULL} 
	};
		
	program=initShaders(shaders);
  
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

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
  
	init();
	
	while(true){
		input(window);//keyboard controls
		display(window);//displaying
	}

	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();
 
  return 0;
}
