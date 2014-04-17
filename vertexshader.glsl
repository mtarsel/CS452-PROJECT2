#version 130

uniform mat4 projMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

attribute vec2 texcoord;
varying vec2 f_texcoord;

in vec3 in_position;

void main(){
  gl_Position=projMatrix*viewMatrix*modelMatrix*vec4(in_position,1.0);
  //f_texcoord = texcoord;
}
