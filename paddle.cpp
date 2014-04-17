#include "paddle.h"
//#include "shaders.h"

void GLPong_PaddleDraw(Paddle_t * paddle, SDL_Window* screen, GLfloat x_trans, GLfloat y_trans){

	
	//THIS IS THE TRANSLATION
	GLfloat trans_vert_array[12];
	int i;
	for(i=0; i<12; i++){
		if((i%3)==0) trans_vert_array[i]=paddle->vertexarray[i]+(x_trans/350);
		//else if((i%3)==1) trans_vert_array[i]=paddle->vertexarray[i]+((1-y_trans)/350);
		else if((i%3)==2) trans_vert_array[i]=paddle->vertexarray[i]+(y_trans/200);
		else trans_vert_array[i]=paddle->vertexarray[i];
		
	}
	
	glGenVertexArrays(1,&paddle->vaoID);
	glBindVertexArray(paddle->vaoID);
	
	glGenBuffers(2, paddle->vboID);
	glBindBuffer(GL_ARRAY_BUFFER,paddle->vboID[0]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(trans_vert_array),trans_vert_array,GL_STATIC_DRAW);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);
	
	glBindBuffer(GL_ARRAY_BUFFER, paddle->vboID[1]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(paddle->normalsarray),paddle->normalsarray,GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	
	glGenBuffers(1,&paddle->eboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,paddle->eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(paddle->elems),paddle->elems,GL_STATIC_DRAW);

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);	
  
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	
	
	glDrawElements(GL_QUADS,12,GL_UNSIGNED_BYTE,NULL);
	glFlush();
	
	SDL_GL_SwapWindow(screen);

	
	
};

/* --------------------------------- IF YOU CHANGE THESE SIZES, change the declarations in the header file -------------------------- */
void GLPong_PaddleInit(Paddle_t * paddle){

	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	//glEnable(GL_NORMALIZE);
	
 
	glViewport(0, 0, 640, 640);
	//GLuint program;
	
	GLfloat size=.4;
	GLfloat normalVector = 1.0f / sqrt(3.0f);

	GLfloat vertexarray[]={size,size/1.5,0.0,
												size,-size/1.5,0.0,
                       -size,-size/1.5,0.0,
                       -size,size/1.5,0.0
                       };
      

	GLfloat normalsarray[] = {normalVector,normalVector,-normalVector,
                       normalVector,-normalVector,-normalVector,
                       -normalVector,-normalVector,-normalVector,
                       -normalVector,normalVector,-normalVector
	};
						   									
	GLubyte elems[]={0,1,2,3
		     };
		
	//copy the vertex and normal arrays into the paddle object.     
	int i;
	for(i=0;i<12;i++){
		
		paddle->vertexarray[i]=vertexarray[i];
		paddle->normalsarray[i]=normalsarray[i];
	}
	for(i=0; i<4; i++){
		paddle->elems[i]=elems[i];
	}
	
};


