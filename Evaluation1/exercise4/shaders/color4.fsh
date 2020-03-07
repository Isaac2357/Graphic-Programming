#version 330

in vec3 vertexColorToFS;

out vec4 pixCol;

void main() {
	pixCol = vec4(vertexColorToFS, 1.0);
}
