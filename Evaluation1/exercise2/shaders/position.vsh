#version 330

in vec2 vertexPosition;
in vec3 color;
out vec3 colorToFs;

void main() {
	gl_Position = vec4(vertexPosition, 0.0, 1.0);
	colorToFs = color;
}