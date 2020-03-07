/*
 *	PARA MODIFICAR: Solo es necesario cambiar el POINT_PERIMETER y la primitiva
 *
 */


#include <stdio.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Utils.h"

//CAMBIA ESTE NUMERO PARA CAMBIAR LAS DIMENSIONES DE LA MALLAS
// EJEMPLO: #define POINT_PERIMETER 3
// ^ Esto crea una malla de 3x3

#define POINT_PERIMETER 8


#define RST 0xFF
#define SQUARES (POINT_PERIMETER -1)
static float Squares = (POINT_PERIMETER - 1.0);

//Cuantos "Cuadrados se forman por linea"
//Los vertices totales que dependen de los cuadrados
//static float points = ((SQUARES * 2) +1) * SQUARES;
//Incremento de puntos
//static float inc = 2/SQUARES;
//Puntos * 2 debido a que tiene 2 datos por vertice

static float figDat[(POINT_PERIMETER * POINT_PERIMETER) * 2];

//static float figDat[] = {	-1.0, -1.0,	-1.0, 0.0,
//							0.0, -1.0,	0.0, 0.0,
//
//							1.0, -1.0,	1.0, 0.0,
//
//							-1.0, 0.0,	-1.0, 1.0,
//							0.0, 0.0,	0.0, 1.0,
//
//							1.0, 0.0,	1.0, 1.0};

//static float figDat[] = {
//							-1, 1, 	0, 1,	1, 1,
//							-1, 0, 	0, 0,	1, 0,
//							-1, -1, 0, -1,	1, -1,
//};

//Puntos * 3

static float figCol[((POINT_PERIMETER * POINT_PERIMETER) * 3)];

//static float figCol[] = {	1.0, 0.0, 0.0,	0.0, 1.0 ,0.0,
//							0.0 ,0.0 ,1.0 ,	1.0 ,0.0 ,0.0,
//
//							0,1,0,	0,0,1,
//
//							1,0,0,	0,1,0,
//							0,0,1,	1,0,0,
//
//							0,1,0,	0,0,1};

//static float figCol[] = {
//							0.5,0.3,0.4, 	1,0,0,	0,1,0,
//							0,0,1,	1,0,1,	1,1,0,
//							0,1,1,	0.5,0.5,0.5, 	0.6, 0.8, 0.9
//
//};

//static GLushort indices[] = {	0,	1,	2,	3,	4,	5,	RST,
//								6,	7,	8,	9,	10,	11
//};

//static GLushort indices[] = {
//								3, 0, 4, 1, 5, 2,
//								RST,
//								6, 3, 7, 4, 8, 5
//};

//static GLushort indices[] = {
//								8, 0, 9, 1, 10, 2, 11, 3, 12, 4, 13, 5, 14, 6, 15, 7,
//								RST,
//								16, 8, 17, 9, 18, 10, 19, 11, 20, 12, 21, 13, 22, 14, 23, 15
//};
						//Puntos			  +
static GLushort indices[(POINT_PERIMETER * (2* SQUARES)) + (POINT_PERIMETER-1)];

static GLuint programId;
static GLuint va[1];
static GLuint bufferId[3];
static GLuint vertexPosLoc, vertexColLoc;

void keyPressed(unsigned char key, int x, int y) {
	//    printf("Se presion  tecla con c digo %d\n", key);
	if(key == 27) exit(0);
}

void specialKeyPressed(int key, int x, int y) {
	if(key == GLUT_KEY_F4 && glutGetModifiers() == GLUT_ACTIVE_ALT)
		exit(0);
}

static void initVertexes(){

	double increment = (2/Squares);
	int index = 0;

	for(double i = 1.0; i >= -1; i -= increment){
		for(double o = -1.0; o <= 1; o += increment){
			figDat[index] = o;
			index++;
			figDat[index] = i;
			index ++;
		}
	}

//	for(int i=0; i<(POINT_PERIMETER * POINT_PERIMETER) * 2; i+=2){
//		printf("%f, ", figDat[i]);
//		printf("%f \n", figDat[i+1]);
//	}
}

static double randomNum(void){
    return rand() / ((double) RAND_MAX);
}

static void initColors(){

	for(int i=0; i < ((POINT_PERIMETER * POINT_PERIMETER) * 3); i+= 3){
		figCol[i] = randomNum();
		figCol[i+1] = randomNum();
		figCol[i+2] = randomNum();
	}

}

static void initIndexes(){
	int index = 0;
	for(int i=1; i < POINT_PERIMETER; i++){
		for(int o=0; o < POINT_PERIMETER; o++){
			indices[index] = ( POINT_PERIMETER * i ) + o;
			index++;
			indices[index] = ( POINT_PERIMETER * (i-1) ) + o;
			index++;
		}
		indices[index] = RST;
		index++;
	}

		for(int i=0; i< (POINT_PERIMETER * (2* SQUARES)) + (POINT_PERIMETER-1); i+=2){
			printf("%d, ", indices[i]);
			printf("%d \n", indices[i+1]);
		}
}

static void init(){

	initVertexes();
	initColors();
	initIndexes();

	//Crear shaders
	GLuint vshId = compileShader("shaders/colorPosition4.vsh", GL_VERTEX_SHADER);
	GLuint fshId = compileShader("shaders/color4.fsh", GL_FRAGMENT_SHADER);
	if(!shaderCompiled(vshId)) return;
	if(!shaderCompiled(fshId)) return;

	printf("%d, %d\n", vshId, fshId);

	programId = glCreateProgram();

	glAttachShader(programId, fshId);
	glAttachShader(programId, vshId);
	glLinkProgram(programId);

	//Declarar y activar el vertex array
	glGenVertexArrays(1, va);
	glBindVertexArray(va[0]);

	//Alocar espacio
	glGenBuffers(3, bufferId);

	//Usar el arreglo de posiciones
	glBindBuffer(GL_ARRAY_BUFFER, bufferId[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(figDat), figDat, GL_STATIC_DRAW);
	vertexPosLoc = glGetAttribLocation(programId, "vPosition");
	glVertexAttribPointer(vertexPosLoc, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vertexPosLoc);

	//Usar el arreglo de colores
	glBindBuffer(GL_ARRAY_BUFFER, bufferId[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(figCol), figCol, GL_STATIC_DRAW);
	vertexColLoc = glGetAttribLocation(programId, "vColor");
	glVertexAttribPointer(vertexColLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vertexColLoc);

	//Reset
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glPrimitiveRestartIndex(RST);
	glEnable(GL_PRIMITIVE_RESTART);
}

static void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	//Activar programa
	glPointSize(9.0);
	glLineWidth(4.0);
	glUseProgram(programId);
	glBindVertexArray(va[0]);
	//glDrawArrays(GL_LINES, 0, 12+1);

	glDrawElements(GL_TRIANGLE_STRIP, (POINT_PERIMETER * POINT_PERIMETER) * 2, GL_UNSIGNED_SHORT, 0);

	glutSwapBuffers();
}

int main(int argc, char** argv){

	setbuf(stdout, NULL);
	glutInit(&argc, argv);
	int w = 1280, h = 720;
	int x = (glutGet(GLUT_SCREEN_WIDTH) - w) / 2;
	int y = (glutGet(GLUT_SCREEN_HEIGHT) - h) / 2;
	glutInitWindowSize(w, h);
	glutInitWindowPosition(x, y);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("Evaluacion Extraulica 4");
	glutKeyboardFunc(keyPressed);
	glutDisplayFunc(display);
	glewInit();
	glClearColor(0.0, 1.0, 1.0, 1.0);
	init();
	for(int i=0; i<(POINT_PERIMETER * POINT_PERIMETER) * 2; i+=2){
		printf("%f, ", figDat[i]);
		printf("%f \n", figDat[i+1]);
	}
	glutMainLoop();
	return 0;
}
