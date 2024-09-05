#version 330 core
//there are 4 fragment in a pixel because we use 4x AA
in vec3 fragmentColor; 
out vec3 color;
void main(){
    //color = vec3(1,0.5,0);
    color = fragmentColor;
}