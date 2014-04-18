#version 130


out vec4 outColor;

in vec4 out_color;

void main(){
    //outColor = vec4(1.0, 1.0, 0.0, 0.3);
    outColor = out_color;
}
