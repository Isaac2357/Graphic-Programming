/*
 * main.c
 *
 *  Created on: Mar 3, 2020
 *      Author: isaac
 */

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Utils.h"
#include <math.h>
#define PEAKS 32

GLuint programId;
GLuint heightScreenLoc, widthScreenLoc;
GLuint indoorFactorLoc, outdoorFactorLoc;
float indoorFactor = 1.0, outdoorFactor = 1.0;

static void onKeyPressed(unsigned char key, int x, int y) {
	if (key == 27) {
		exit(0);
	} else if(key == 65 || key == 97) { //A or a
		if(outdoorFactor > 0.1) outdoorFactor =  outdoorFactor - 0.1;
	}else if(key == 66 || key == 98) { //B or b
		if(indoorFactor > 0.1)indoorFactor =  indoorFactor - 0.1;
	}else if(key == 67 || key == 99) { //C or c
		if(outdoorFactor < 1.0) outdoorFactor = outdoorFactor + 0.1;
	}else if(key == 68 || key == 100) { //D or d
		if(indoorFactor < 1.0) indoorFactor = indoorFactor +  0.1;
	}
	glutPostRedisplay();
}

double degreesToRadians(double degrees) {
	return degrees * (M_PI/180);
}

double my_abs(double x) {
	if (x < 0) return -1 * x;
	else return x;
}

void generateStar(int peaks, float indoorRadio, float outdoorRadio) {

	float model [(peaks * 2 + peaks * 2  + 2 + 2 + 2)];
	float color [(peaks * 3 + peaks * 3  + 3 + 3 + 3)];
	short flags [(peaks + peaks + 1 + 1 + 1)];

	float angle = 0;
	float deltaAngle = 360.0 / peaks;
	float angle2 = deltaAngle/2;

	model[0] = 0;
	model[1] = 0;

	color[0] = 1;
	color[1] = 1;
	color[2] = 1;

	flags[0] = -1;

	int idx = 2;
	int idxc = 3;
	int idf = 1;
	float blue = 0;
	for(int i = 0; i <= peaks; i++) {

		model[idx++] = outdoorRadio * cos(degreesToRadians(angle));
		model[idx++] = outdoorRadio * sin(degreesToRadians(angle));

		model[idx++] = indoorRadio * cos(degreesToRadians(angle2));
		model[idx++] = indoorRadio * sin(degreesToRadians(angle2));

		flags[idf++] = 1;
		flags[idf++] = 0;

		if(blue == 0 && angle > 180) blue = 0.5;

		color[idxc++] = my_abs(sin(degreesToRadians(angle)));
		color[idxc++] = my_abs(cos(degreesToRadians(angle)));
		color[idxc++] = blue;

		color[idxc++] = my_abs(sin(degreesToRadians(angle2)));
		color[idxc++] = my_abs(cos(degreesToRadians(angle2)));
		color[idxc++] = blue;


		angle +=  deltaAngle;
		angle2 +=  deltaAngle;
	}

	glBindBuffer(GL_ARRAY_BUFFER, 1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (peaks * 2 + peaks * 2  + 2 + 2 + 2), model, GL_STATIC_DRAW);
	GLuint vPosLoc = glGetAttribLocation(programId, "vertexPosition");
	glVertexAttribPointer(vPosLoc, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vPosLoc);

	glBindBuffer(GL_ARRAY_BUFFER, 2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (peaks * 3 + peaks * 3  + 3 + 3 + 3), color, GL_STATIC_DRAW);
	GLuint colorLoc = glGetAttribLocation(programId, "color");
	glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colorLoc);

	glBindBuffer(GL_ARRAY_BUFFER, 3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(int) * (peaks + peaks + 1 + 1 + 1), flags, GL_STATIC_DRAW);
	GLuint flagsLoc = glGetAttribLocation(programId, "flags");
	glVertexAttribPointer(flagsLoc, 1, GL_SHORT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(flagsLoc);

	indoorFactorLoc = glGetUniformLocation(programId, "indoorFactor");
	outdoorFactorLoc = glGetUniformLocation(programId, "outdoorFactor");
}

void init() {

	GLuint posVshId = compileShader("shaders/position.vsh", GL_VERTEX_SHADER);
	GLuint orangeFshId = compileShader("shaders/colors.fsh", GL_FRAGMENT_SHADER);
	programId = glCreateProgram();

	if (!shaderCompiled(posVshId)) return;
	if (!shaderCompiled(orangeFshId)) return;

	glAttachShader(programId, posVshId);
	glAttachShader(programId, orangeFshId);
	glLinkProgram(programId);

	glBindVertexArray(1);
	generateStar(PEAKS, 0.8, 1.0);
}

static void onDisplayImage() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(1);
	glUseProgram(programId);
	glUniform1f(indoorFactorLoc, indoorFactor);
	glUniform1f(outdoorFactorLoc, outdoorFactor);
	glDrawArrays(GL_TRIANGLE_FAN, 0, PEAKS * 2 + 3);
	glutSwapBuffers();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	int w = 600, h = 600;
	int x = (glutGet(GLUT_SCREEN_WIDTH) - w) / 2;
	int y = (glutGet(GLUT_SCREEN_HEIGHT) - h) / 2;

	glutInitWindowSize(w, h);
	glutInitWindowPosition(x, y);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("Evaluation 1 - 3");
	glutKeyboardFunc(onKeyPressed);
	glutDisplayFunc(onDisplayImage);
	glewInit();
	glClearColor(1, 1, 1, 1);
	init();
	glutMainLoop();
	return 0;
}

