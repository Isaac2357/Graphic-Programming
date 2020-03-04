/*
 * main.c
 *
 *  Created on: Mar 2, 2020
 *      Author: isaac
 */

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Utils.h"


static void onKeyPressed(unsigned char key, int x, int y) {
	if (key == 27) exit(0);
}

GLuint programId;
GLuint heightScreenLoc, widthScreenLoc;

void init() {

	GLuint posVshId = compileShader("shaders/position.vsh", GL_VERTEX_SHADER);
	GLuint orangeFshId = compileShader("shaders/grays.fsh", GL_FRAGMENT_SHADER);
	programId = glCreateProgram();

	if (!shaderCompiled(posVshId)) return;
	if (!shaderCompiled(orangeFshId)) return;

	glAttachShader(programId, posVshId);
	glAttachShader(programId, orangeFshId);
	glLinkProgram(programId);

	float juliaSet[] = {
			 -1, -1 * 0.8,
			  1, -1 * 0.8,
			 -1,  1 * 0.8,
			  1,  1 * 0.8
	};

	glBindVertexArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(juliaSet), juliaSet, GL_STATIC_DRAW);

	GLuint vPosLoc = glGetAttribLocation(programId, "vertexPosition");
	glVertexAttribPointer(vPosLoc, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vPosLoc);

	widthScreenLoc = glGetUniformLocation(programId, "widthScreen");
	heightScreenLoc = glGetUniformLocation(programId, "heightScreen");

}

static void onDisplayImage() {
	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(1);
	glUseProgram(programId);
	glUniform1f(widthScreenLoc, (float)w);
	glUniform1f(heightScreenLoc, (float)h);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glutSwapBuffers();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	int w = 500, h = 500;
	int x = (glutGet(GLUT_SCREEN_WIDTH) - w) / 2;
	int y = (glutGet(GLUT_SCREEN_HEIGHT) - h) / 2;

	glutInitWindowSize(w, h);
	glutInitWindowPosition(x, y);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("Evaluation 1 - 1");
	glutKeyboardFunc(onKeyPressed);
	glutDisplayFunc(onDisplayImage);
	glewInit();
	glClearColor(1, 1, 1, 1);
	//glutFullScreen();
	init();

	glutMainLoop();
	return 0;
}

