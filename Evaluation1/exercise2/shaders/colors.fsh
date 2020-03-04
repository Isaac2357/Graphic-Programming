#version 330

out vec4 pixelColor;
in vec3 colorToFs;

void main() {
	pixelColor =  vec4(colorToFs, 1);
}