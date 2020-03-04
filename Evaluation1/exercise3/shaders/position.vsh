#version 330

in vec2 vertexPosition;
in vec3 color;
in int flags;
out vec3 colorToFs;

uniform float indoorFactor;
uniform float outdoorFactor;

void main() {
	gl_Position = vec4(vertexPosition, 0.0, 1.0);
	
	colorToFs = color;
	
	if(flags < 0) {
		
	} else if(flags == 0) {
		gl_Position = vec4(vertexPosition*indoorFactor, 0.0, 1.0);
	} else if(flags > 1) {
		gl_Position = vec4(vertexPosition*outdoorFactor, 0.0, 1.0);
	} 
}