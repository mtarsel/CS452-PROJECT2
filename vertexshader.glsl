#version 130

uniform mat4 projMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

uniform vec2 texcoord;
out vec2 f_texcoord;

in vec3 in_position;
in vec3 in_normal;
in vec4 in_color;

out vec4 pass_color;
out vec3 pass_normal;

void main(){
  pass_normal = in_normal;
  pass_color=in_color;
  //pass_color = color;
  gl_Position=projMatrix*viewMatrix*modelMatrix*vec4(in_position,1.0); 
  f_texcoord = texcoord;
}
