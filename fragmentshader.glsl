#version 130


out vec4 outColor;

in vec4 pass_color;

void main(){
    //outColor = vec4(1.0, 1.0, 1.0, 1.0);
    outColor = pass_color;
}
