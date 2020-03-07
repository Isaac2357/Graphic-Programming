#version 330

in vec2 vPosition;
in vec3 vColor;

out vec3 vertexColorToFS;

void main(){
	gl_Position = vec4(vPosition, 0, 1);
	vertexColorToFS = vColor;
}