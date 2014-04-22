#include "environment.h"
//#include "shaders.h"

void PaddleDraw(Paddle_t * paddle, GLfloat x_trans, GLfloat y_trans){

	//glGenVertexArrays(1,&paddle->vaoID);
	//glGenBuffers(2, paddle->vboID);
	//glGenBuffers(1,&paddle->eboID);

	//THIS IS THE TRANSLATION
	GLfloat trans_vert_array[12];
	int i;
	for(i=0; i<12; i++){
		if((i%3)==0) trans_vert_array[i]=paddle->vertexarray[i]+(x_trans/30);
		else if((i%3)==1) trans_vert_array[i]=paddle->vertexarray[i]+((1-y_trans)/30);  //for normal paddle translation
		//else if((i%3)==2) trans_vert_array[i]=paddle->vertexarray[i]+(y_trans/350);		//for depth paddle translation (for testing)
		else trans_vert_array[i]=paddle->vertexarray[i];
		
	}
	
	
	//glGenVertexArrays(1,&paddle->vaoID);
	glBindVertexArray(paddle->vaoID);
	
	//glGenBuffers(2, paddle->vboID);
	glBindBuffer(GL_ARRAY_BUFFER,paddle->vboID[0]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(trans_vert_array),trans_vert_array,GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER,sizeof(paddle->vertexarray),paddle->vertexarray,GL_STATIC_DRAW);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);


	glBindBuffer(GL_ARRAY_BUFFER, paddle->vboID[1]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(paddle->colorarray),paddle->colorarray,GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	
	glBindBuffer(GL_ARRAY_BUFFER, paddle->vboID[2]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(paddle->normalsarray),paddle->normalsarray,GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);	
	
	//glGenBuffers(1,&paddle->eboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,paddle->eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(paddle->elems),paddle->elems,GL_STATIC_DRAW);
	
	//glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	//glEnableVertexAttribArray(2);
	
	glDrawElements(GL_QUADS,4,GL_UNSIGNED_BYTE,NULL);
	glFlush();
	
	//SDL_GL_SwapWindow(screen);
};

/* --------------------------------- IF YOU CHANGE THESE SIZES, change the declarations in the header file. Global declarations are probably a good idea -------------------------- */
void PaddleInit(Paddle_t * paddle){

	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_COLOR_MATERIAL);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	//glEnable(GL_NORMALIZE);
	
	//generate the buffers in the init to save resources
	glGenVertexArrays(1,&paddle->vaoID);
	glGenBuffers(3, paddle->vboID);
	glGenBuffers(1,&paddle->eboID);	
	
 
	//glViewport(0, 0, 640, 640);
	//GLuint program;
	
	GLfloat size=4.5;
	GLfloat normalVector = 1.0f / sqrt(2.0f);

	GLfloat vertexarray[]={size,size/1.5,0.0f,
				size,-size/1.5,0.0f,
                       -size,-size/1.5,0.0f,
                       -size,size/1.5,0.0f
                       };
      
	
	GLfloat colorarray[]={1.0f, 0.0f, 0.0f, 0.5f,
				    1.0f, 0.0f, 0.0f, 0.5f,
				    1.0f, 0.0f, 0.0f, 0.5f,
				    1.0f, 0.0f, 0.0f, 0.5f
					};
	
	GLfloat normalsarray[] = {
					normalVector,normalVector, 0.0f,
					normalVector,-normalVector, 0.0f,
					-normalVector,-normalVector, 0.0f,
					-normalVector,normalVector, 0.0f
					};
	
	/*normalVector,normalVector,-normalVector,
                       normalVector,-normalVector,-normalVector,
                       -normalVector,-normalVector,-normalVector,
                       -normalVector,normalVector,-normalVector
	};*/
						   									
	GLubyte elems[]={0,1,2,3};
		
	//copy the vertex and normal arrays into the paddle object.     
	int i;
	for(i=0;i<sizeof(vertexarray)/4;i++){
		
		paddle->vertexarray[i]=vertexarray[i];
		paddle->normalsarray[i]=normalsarray[i];
	}
	for(i=0; i<sizeof(colorarray)/4; i++){
		paddle->colorarray[i]=colorarray[i];
	}
	for(i=0; i<sizeof(elems); i++){
		paddle->elems[i]=elems[i];
	}
}

void WallsDraw(Walls_t * walls){

	//glGenVertexArrays(1,&paddle->vaoID);
	//glGenBuffers(2, paddle->vboID);
	//glGenBuffers(1,&paddle->eboID);

	//glGenVertexArrays(1,&paddle->vaoID);
	glBindVertexArray(walls->vaoID);
	
	//glGenBuffers(2, paddle->vboID);
	glBindBuffer(GL_ARRAY_BUFFER,walls->vboID[0]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(walls->vertexarray),walls->vertexarray,GL_STATIC_DRAW);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, walls->vboID[1]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(walls->colorarray),walls->colorarray,GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	
	glBindBuffer(GL_ARRAY_BUFFER,walls->vboID[2]);
	//glBufferData(GL_ARRAY_BUFFER,sizeof(walls->vertexarray),walls->vertexarray,GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER,sizeof(walls->normalsarray),walls->normalsarray,GL_STATIC_DRAW);
	glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,0,(void*)0);

	
	//glGenBuffers(1,&paddle->eboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,walls->eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(walls->elems),walls->elems,GL_STATIC_DRAW);
	
	//glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	
	glDrawElements(GL_QUADS,24,GL_UNSIGNED_BYTE,NULL);
	glFlush();
	
	//SDL_GL_SwapWindow(screen);
};

/* --------------------------------- IF YOU CHANGE THESE SIZES, change the declarations in the header file. Global declarations are probably a good idea -------------------------- */
void WallsInit(Walls_t * walls){


	
	//generate the buffers in the init to save resources
	glGenVertexArrays(1,&walls->vaoID);
	glGenBuffers(3, walls->vboID);
	glGenBuffers(1,&walls->eboID);	
	
 
	//GLuint program;
	
	GLfloat size=11.5f;
	GLfloat normalVector = 1.0f / sqrt(3.0f);

	GLfloat vertexarray[]={
	
				size,size,0.0f,	// front top right
				-size,size,0.0f,	// front top left
                        -size,size,-320.0f,	// back top left
                        size,size,-320.0f,	// back top right
	
	
				size, -size, 0.0f,// front bottom right
				-size, -size, 0.0f,// front bottom left
				-size, -size, -320.0f,// back bottom left
				size, -size, -320.0f// back bottom right

                       };
      
	
	GLfloat colorarray[]={   
				    1.0f, 1.0f, 1.0f, 1.0f,
				    1.0f, 1.0f, 1.0f, 1.0f,
				    1.0f, 1.0f, 1.0f, 1.0f,
				    1.0f, 1.0f, 1.0f, 1.0f,
				    
				    0.8f, 0.8f, 0.8f, 1.0f,
				    0.8f, 0.8f, 0.8f, 1.0f,
				    0.8f, 0.8f, 0.8f, 1.0f,
				    0.8f, 0.8f, 0.8f, 1.0f
					};
	
	GLfloat normalsarray[] = {normalVector,normalVector,normalVector,
                       	-normalVector,normalVector,normalVector,
                       	-normalVector,normalVector,-normalVector,
                       	normalVector,normalVector,-normalVector,
                       	normalVector,-normalVector,normalVector,
                       	-normalVector,-normalVector,normalVector,
                       	-normalVector,-normalVector,-normalVector,
                       	normalVector,-normalVector,-normalVector
	};
						   									
	GLubyte elems[]={
			0,1,2,3,
			0,3,7,4,
			4,5,6,7,
			1,2,6,5,
			3,2,6,7
		     };
		
	//copy the vertex and normal arrays into the paddle object. (the sizes are divided by 4 due to floats)
	int i;
	for(i=0;i<sizeof(vertexarray)/4;i++){
		
		walls->vertexarray[i]=vertexarray[i];
		walls->normalsarray[i]=normalsarray[i];
	}
	for(i=0; i<sizeof(colorarray)/4; i++){
		walls->colorarray[i]=colorarray[i];
	}
	for(i=0; i<sizeof(elems); i++){
		walls->elems[i]=elems[i];
	}
}

void EnvironmentInit(){
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	//Next two lines are to create a transluscent paddle
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);
	
	glViewport(0, 0, 640, 640);
}


