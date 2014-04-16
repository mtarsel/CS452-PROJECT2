#include "paddle.h"
//#include "shaders.h"

void GLPong_PaddleDraw(Paddle_t * paddle, SDL_Window* screen){
	
	
	
	int i;
	for(i=0;i<3;i++){
		printf("paddle.vertexarray %f\n", paddle->vertexarray[i]);
		printf("paddle.normalsarray %f\n", paddle->normalsarray[i]);
		printf("paddle.colorarray %f\n", paddle->colorarray[i]);
		printf("paddle.elems %i\n\n", paddle->elems[i]);
	}
	
	/*glViewport(0, 0, 600, 600);
	
	glGenVertexArrays(1,&paddle->vaoID);
	glBindVertexArray(paddle->vaoID);

	glGenBuffers(2, paddle->vboID);
	glBindBuffer(GL_ARRAY_BUFFER,paddle->vboID[0]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(paddle->vertexarray),paddle->vertexarray,GL_STATIC_DRAW);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, paddle->vboID[1]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(paddle->colorarray),paddle->colorarray,GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	
	glGenBuffers(1,&paddle->eboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,paddle->eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(paddle->elems),paddle->elems,GL_STATIC_DRAW);
  
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glDrawElements(GL_TRIANGLE_STRIP,36,GL_UNSIGNED_BYTE,NULL);
    
	glFlush();
	SDL_GL_SwapWindow(screen);*/
	
	
};

/* --------------------------------- IF YOU CHANGE THESE SIZES, change the declarations in the header file -------------------------- */
void GLPong_PaddleInit(Paddle_t * paddle){

	
	GLfloat paddlesize = 1.0f;
	GLfloat normalVector = 1.0f / sqrt(3.0f);

	//This is what we'll be using for the geometry of the paddle
	GLfloat vertexarray[]={-paddlesize, paddlesize, 0.0f,	//Lower Left
			     paddlesize, paddlesize, 0.0f,	//Lower Right
			     paddlesize, -paddlesize, 0.0f,	//Upper Right
			     -paddlesize, -paddlesize, 0.0f	//Upper Left
	};
	memcpy(paddle->vertexarray, vertexarray, sizeof(vertexarray));
			     
	GLfloat normalsarray[] = {-normalVector,normalVector,0.0f,	//Lower Left
                       normalVector,normalVector,0.0f,	//Lower Right
                       normalVector,-normalVector,0.0f,	//Upper Right
                       -normalVector,-normalVector,0.0f	//Upper Left
	};
	memcpy(paddle->normalsarray, normalsarray, sizeof(normalsarray));
	
	GLfloat colorarray[] = {1.0f, 1.0f, 1.0f, 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f
	};
	memcpy(paddle->colorarray, colorarray, sizeof(colorarray));

	GLfloat elems[] = {0,1,2,3,4};
	memcpy(paddle->elems, elems, sizeof(elems));
	
};

void GLPong_PaddleMove(Paddle_t * paddle, GLfloat x, GLfloat y){

};
