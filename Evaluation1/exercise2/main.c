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
#include <math.h>
#define PEAKS 16

static void onKeyPressed(unsigned char key, int x, int y) {
	if (key == 27) exit(0);
}

GLuint programId;
GLuint heightScreenLoc, widthScreenLoc;

double degreesToRadians(double degrees) {
	return degrees * (M_PI/180);
}

double my_abs(double x) {
	if (x < 0) return -1 * x;
	else return x;
}

void generateStar(/*float ** model, float ** color,*/ int peaks, float indoorRadio, float outdoorRadio) {

//	*model = (float*) malloc(sizeof(float) * (peaks * 2 + peaks * 2  + 2 + 2 + 2));
//	*color = (float*) malloc(sizeof(float) * (peaks * 3 + peaks * 3  + 3 + 3 + 3));
//
//	float angle = 0;
//	float deltaAngle = 360.0 / peaks;
//	float angle2 = deltaAngle/2;
//
//	(*model)[0] = 0;
//	(*model)[1] = 0;
//
//	(*color)[0] = 1;
//	(*color)[1] = 1;
//	(*color)[2] = 1;
//
//	int idx = 2;
//	int idxc = 3;
//	float blue = 0;
//	for(int i = 0; i <= peaks; i++) {
//
//		(*model)[idx++] = outdoorRadio * cos(degreesToRadians(angle));
//		(*model)[idx++] = outdoorRadio * sin(degreesToRadians(angle));
//
//		(*model)[idx++] = indoorRadio * cos(degreesToRadians(angle2));
//		(*model)[idx++] = indoorRadio * sin(degreesToRadians(angle2));
//
//		if(blue == 0 && angle > 180) blue = 0.5;
//
//		(*color)[idxc++] = my_abs(sin(degreesToRadians(angle)));
//		(*color)[idxc++] = my_abs(cos(degreesToRadians(angle)));
//		(*color)[idxc++] = blue;
//
//		(*color)[idxc++] = my_abs(sin(degreesToRadians(angle2)));
//		(*color)[idxc++] = my_abs(cos(degreesToRadians(angle2)));
//		(*color)[idxc++] = blue;
//
//
//		angle +=  deltaAngle;
//		angle2 +=  deltaAngle;
//	}

	float model [(peaks * 2 + peaks * 2  + 2 + 2 + 2)];
	float color [(peaks * 3 + peaks * 3  + 3 + 3 + 3)];

	float angle = 0;
	float deltaAngle = 360.0 / peaks;
	float angle2 = deltaAngle/2;

	model[0] = 0;
	model[1] = 0;

	color[0] = 1;
	color[1] = 1;
	color[2] = 1;

	int idx = 2;
	int idxc = 3;
	float blue = 0;
	for(int i = 0; i <= peaks; i++) {

		model[idx++] = outdoorRadio * cos(degreesToRadians(angle));
		model[idx++] = outdoorRadio * sin(degreesToRadians(angle));

		model[idx++] = indoorRadio * cos(degreesToRadians(angle2));
		model[idx++] = indoorRadio * sin(degreesToRadians(angle2));

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

	glBindBuffer(GL_ARRAY_BUFFER, 2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (PEAKS * 2 + PEAKS * 2  + 2 + 2 + 2), model, GL_STATIC_DRAW);
	GLuint vPosLoc = glGetAttribLocation(programId, "vertexPosition");
	glVertexAttribPointer(vPosLoc, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vPosLoc);

	glBindBuffer(GL_ARRAY_BUFFER, 3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (PEAKS * 3 + PEAKS * 3  + 3 + 3 + 3), color, GL_STATIC_DRAW);
	GLuint colorLoc = glGetAttribLocation(programId, "color");
	glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colorLoc);

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
	generateStar(PEAKS, 0.5, 1.0);

//	glBindBuffer(GL_ARRAY_BUFFER, 2);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (PEAKS * 2 + PEAKS * 2  + 2 + 2 + 2), x, GL_STATIC_DRAW);
//	GLuint vPosLoc = glGetAttribLocation(programId, "vertexPosition");
//	glVertexAttribPointer(vPosLoc, 2, GL_FLOAT, GL_FALSE, 0, 0);
//	glEnableVertexAttribArray(vPosLoc);
//
//	glBindBuffer(GL_ARRAY_BUFFER, 3);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (PEAKS * 3 + PEAKS * 3  + 3 + 3 + 3), y, GL_STATIC_DRAW);
//	GLuint colorLoc = glGetAttribLocation(programId, "color");
//	glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
//	glEnableVertexAttribArray(colorLoc);

}

static void onDisplayImage() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(1);
	glUseProgram(programId);
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
	glutCreateWindow("Evaluation 1 - 2");
	glutKeyboardFunc(onKeyPressed);
	glutDisplayFunc(onDisplayImage);
	glewInit();
	glClearColor(1, 1, 1, 1);
	init();
	glutMainLoop();
	return 0;
}

