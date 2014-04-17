#version 130

uniform mat4 projMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

attribute vec2 texcoord;
varying vec2 f_texcoord;

in vec3 in_position;

float scale = 1-in_position[2];

mat4 testscale = mat4(
   scale, 0.0, 0.0, 0.0, // first column (not row!)
   0.0, scale, 0.0, 0.0, // second column
   0.0, 0.0, scale, 0.0,  // third column
   0.0, 0.0, 0.0, 1.0
);

void main(){
  gl_Position=testscale*viewMatrix*modelMatrix*vec4(in_position,1.0);
  //gl_Position=projMatrix*viewMatrix*modelMatrix*vec4(in_position,1.0);
  //f_texcoord = texcoord;
}
