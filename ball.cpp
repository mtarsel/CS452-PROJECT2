#include "ball.h"

//static GLuint ball_texture;

void BallDraw(const Ball_t * ball, GLfloat x_trans, GLfloat y_trans) {
	
	//THIS IS THE TRANSLATION
	GLfloat trans_vert_array[24];
	int i;
	for(i=0; i<sizeof(trans_vert_array)/4; i++){
		if((i%3)==0) trans_vert_array[i]=ball->vertexarray[i]+(x_trans/30);
		//else if((i%3)==1) trans_vert_array[i]=paddle->vertexarray[i]+((1-y_trans)/350);
		else if((i%3)==2){
			trans_vert_array[i]=ball->vertexarray[i]+(y_trans);
			//printf("z: %f\n", trans_vert_array[i]);
		}
		
		else trans_vert_array[i]=ball->vertexarray[i];
		
	}
	
	
	//glGenVertexArrays(1,&paddle->vaoID);
	glBindVertexArray(ball->vaoID);
	
	//glGenBuffers(2, paddle->vboID);
	glBindBuffer(GL_ARRAY_BUFFER,ball->vboID[0]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(trans_vert_array),trans_vert_array,GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER,sizeof(paddle->vertexarray),paddle->vertexarray,GL_STATIC_DRAW);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, ball->vboID[1]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(ball->colorarray),ball->colorarray,GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	
	//glGenBuffers(1,&paddle->eboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ball->eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(ball->elems),ball->elems,GL_STATIC_DRAW);
	
	//glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	
	glDrawElements(GL_QUADS,24,GL_UNSIGNED_BYTE,NULL);
	glFlush();
}
	

void BallInit(Ball_t * ball) {
	
	//generate the buffers in the init to save resources
	glGenVertexArrays(1,&ball->vaoID);
	glGenBuffers(2, ball->vboID);
	glGenBuffers(1,&ball->eboID);	
	
 
	//glViewport(0, 0, 640, 640);
	//GLuint program;
	
	GLfloat size=1.5;
	//GLfloat normalVector = 1.0f / sqrt(3.0f);

	GLfloat vertexarray[]={
				size,size,size,	//front top right
				-size,size,size,	//front top left
				size,-size,size,	//front bottom right
				-size,-size,size,	//front bottom left
				size,size,-size,	//back top right
				-size,size,-size,	//back top left
				size,-size,-size,	//back bottom right
				-size,-size,-size	//back bottom left
                       };
      
	
	GLfloat colorarray[]={1.0f, 1.0f, 1.0f, 1.0f,
				    1.0f, 1.0f, 1.0f, 1.0f,
				    1.0f, 1.0f, 1.0f, 1.0f,
				    1.0f, 1.0f, 1.0f, 1.0f,
				    1.0f, 1.0f, 1.0f, 1.0f,
				    1.0f, 1.0f, 1.0f, 1.0f,
				    1.0f, 1.0f, 1.0f, 1.0f,
				    1.0f, 1.0f, 1.0f, 1.0f
					};
	
	/*GLfloat normalsarray[] = {normalVector,normalVector,-normalVector,
                       normalVector,-normalVector,-normalVector,
                       -normalVector,-normalVector,-normalVector,
                       -normalVector,normalVector,-normalVector
	};*/
						   									
	GLubyte elems[]={
				0,1,3,2,
				5,4,6,7,
				1,0,4,5,
				0,2,6,4,
				2,3,7,6,
				1,3,7,5
		     };
		
	//copy the vertex and normal arrays into the paddle object.     
	int i;
	for(i=0;i<sizeof(vertexarray)/4;i++){
		
		ball->vertexarray[i]=vertexarray[i];
		//ball->normalsarray[i]=normalsarray[i];
	}
	for(i=0; i<sizeof(colorarray)/4; i++){
		ball->colorarray[i]=colorarray[i];
	}
	for(i=0; i<sizeof(elems); i++){
		ball->elems[i]=elems[i];
	}
}

