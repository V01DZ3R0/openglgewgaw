#version 330 core
//“in” means that this is some input data.
layout(location=0) in vec3 vertexPosition_modelspace; //vertexPosition_modelspace contain the position of the vertex for each run of the vertex shader.
layout(location = 1) in vec3 vertexColor;
layout(location=2) in vec3 vertexPosition_modelspace1;

out vec3 fragmentColor;
uniform mat4 MVP;

//function that is called for each vertex
void main(){ 
gl_Position=MVP*vec4(vertexPosition_modelspace,1.0);
fragmentColor = vertexColor;
}
