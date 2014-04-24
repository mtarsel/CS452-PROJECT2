#include "ball.h"

//static GLuint ball_texture;

void BallDraw(Ball_t * ball, GLuint program) {
	
	
	GLint uniform_mytexture;
	GLint attribute_texcoord;
	
	//Texcoordinates
	GLfloat cube_texcoords[2*4*6] = {
    		
    		
    		0.0f, 0.0f,
    		1.0f, 0.0f,
    		0.0f, 1.0f,
    		1.0f, 1.0f,
    		
    		0.0f, 0.0f,
    		1.0f, 0.0f,
    		0.0f, 1.0f,
    		1.0f, 1.0f,
    		
    		0.0f, 0.0f,
    		1.0f, 0.0f,
    		0.0f, 1.0f,
    		1.0f, 1.0f,
    		
    		0.0f, 0.0f,
    		1.0f, 0.0f,
    		0.0f, 1.0f,
    		1.0f, 1.0f,
    		
    		0.0f, 0.0f,
    		1.0f, 0.0f,
    		0.0f, 1.0f,
    		1.0f, 1.0f,
    		
    		0.0f, 0.0f,
    		1.0f, 0.0f,
    		0.0f, 1.0f,
    		1.0f, 1.0f,
    		
    		
	};

	
	//THIS IS THE TRANSLATION
	int i;
	for(i=0; i<sizeof(ball->vertexarray)/4; i++){
		if((i%3)==0){
			ball->vertexarray[i]=ball->vertexarray[i]+(ball->dir_x)*ball->speed;
			//printf("x: %f\n", trans_vert_array[i]);
		}
		else if((i%3)==1){
			ball->vertexarray[i]=ball->vertexarray[i]+(ball->dir_y)*ball->speed;
		//	printf("y: %f\n", trans_vert_array[i]);
		} 
		else if((i%3)==2){
			ball->vertexarray[i]=ball->vertexarray[i]+(ball->dir_z)*(ball->speed)*3;
			//printf("z: %f\n", trans_vert_array[i]);
		}
		//else ball->vertexarray[i]=ball->vertexarray[i];
		
	}
	
	
	//glGenVertexArrays(1,&paddle->vaoID);
	glBindVertexArray(ball->vaoID);
	
	//glGenBuffers(2, paddle->vboID);
	glBindBuffer(GL_ARRAY_BUFFER,ball->vboID[0]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(ball->vertexarray),ball->vertexarray,GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER,sizeof(paddle->vertexarray),paddle->vertexarray,GL_STATIC_DRAW);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, ball->vboID[1]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(ball->colorarray),ball->colorarray,GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	
	glBindBuffer(GL_ARRAY_BUFFER,ball->vboID[2]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(ball->normalsarray),ball->normalsarray,GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER,sizeof(paddle->vertexarray),paddle->vertexarray,GL_STATIC_DRAW);
	glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,0,(void*)0);
	
	//glGenBuffers(1,&paddle->eboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ball->eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(ball->elems),ball->elems,GL_STATIC_DRAW);
	
	
	//glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	
	//TEXTURE BINDING. IT HAS TO BE HERE! UNDERNEATH THE BIND ARRAYS
	glActiveTexture(GL_TEXTURE0);
  	glBindTexture(GL_TEXTURE_2D, ball->texture_id);
  	uniform_mytexture = glGetUniformLocation(program, "texture");
  	glUniform1i(uniform_mytexture, 0);
  
  	glBindBuffer(GL_ARRAY_BUFFER, ball->vbo_cube_texcoords);
  	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_texcoords), cube_texcoords, GL_STATIC_DRAW);

	attribute_texcoord = glGetAttribLocation(program, "texcoord");
  	glEnableVertexAttribArray(attribute_texcoord);
 	glVertexAttribPointer(attribute_texcoord, 2, GL_FLOAT, GL_FALSE, 0, 0);
	//END TEXTURING
	
	glDrawElements(GL_QUADS,24,GL_UNSIGNED_BYTE,NULL);
	glFlush();
}
	
GLfloat GetBallCoord(Ball_t * ball, char face){
	if(face == 'f'){ //forward face
		return ball->vertexarray[2];
	}
	else if(face == 'd'){ //dorsal face
		return ball->vertexarray[14];
	}
	else if(face == 't'){ //top face
		return ball->vertexarray[1];
	}
	else if(face == 'b'){ //bottom face
		return ball->vertexarray[7];
	}
	else if(face == 'l'){ //left face
		return ball->vertexarray[3];
	}
	else if(face == 'r'){ //right face
		return ball->vertexarray[0];
	}
}

void BallInit(Ball_t * ball) {
	
	//generate the buffers in the init to save resources
	glGenVertexArrays(1,&ball->vaoID);
	glGenBuffers(3, ball->vboID);
	glGenBuffers(1,&ball->eboID);	
	
	glGenTextures(1, &ball->texture_id);
 	glGenBuffers(1, &ball->vbo_cube_texcoords);
 	
 	int img_width, img_height;
	unsigned char* img = SOIL_load_image("baby.jpeg", &img_width, &img_height, NULL, 0);
	
	glBindTexture(GL_TEXTURE_2D, ball->texture_id);
  	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
 	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  	glTexImage2D(GL_TEXTURE_2D,0, GL_RGB,img_width,img_height,0,GL_RGB,GL_UNSIGNED_BYTE,img);
 
 
	//glViewport(0, 0, 640, 640);
	//GLuint program;
	
	GLfloat size=1.5;
	GLfloat normalVector = 1.0f / sqrt(3.0f);

	GLfloat vertexarray[]={
				size,size,size-10,	//front top right
				-size,size,size-10,	//front top left
				size,-size,size-10,	//front bottom right
				-size,-size,size-10,	//front bottom left
				size,size,-size-10,	//back top right
				-size,size,-size-10,	//back top left
				size,-size,-size-10,	//back bottom right
				-size,-size,-size-10	//back bottom left
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
	
	GLfloat normalsarray[] = {
				normalVector,normalVector,normalVector,	//front top right
				-normalVector,normalVector,normalVector,	//front top left
				normalVector,-normalVector,normalVector,	//front bottom right
				-normalVector,-normalVector,normalVector,	//front bottom left
				normalVector,normalVector,-normalVector,	//back top right
				-normalVector,normalVector,-normalVector,	//back top left
				normalVector,-normalVector,-normalVector,	//back bottom right
				-normalVector,-normalVector,-normalVector	//back bottom left
	};
						   									
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
		ball->normalsarray[i]=normalsarray[i];
	}
	for(i=0; i<sizeof(colorarray)/4; i++){
		ball->colorarray[i]=colorarray[i];
	}
	for(i=0; i<sizeof(elems); i++){
		ball->elems[i]=elems[i];
	}
	
	//set the direction of the ball elements
	ball->dir_x = 0;
	ball->dir_y = 0;
	ball->dir_z = 0;
	ball->speed = 0.0;
	
}

