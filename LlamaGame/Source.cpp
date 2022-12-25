#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <math.h>

//declarando variables
static int x_ = 2500;
int score = 0;
using namespace std;

//Contador y suelo
void render(void) {

	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(2);
	glBegin(GL_POINTS);
	//pasto
	glColor3f(0.0, 1.0, 0.0);

	for (int i = 0; i < 100; i++) {
		glVertex2f(rand() % 2000, 200);
		glVertex2f((rand() + 31) % 2000, 150);
	}
	glEnd();

	if (x_ >= 0)
		x_ -= 5;
	else {
		x_ = 2000 + rand() % 400;
	}
	glLineWidth(2);
	glBegin(GL_LINES);
	//linea del suelo
	glColor4f(0.647059, 0.164706, 0.164706, 1);
	glVertex2f(0, 250);
	glVertex2f(2000, 250);
	glEnd();

	glLineWidth(10);
	glBegin(GL_LINES);
	//dinosaurio
	glColor4f(0, 0, 0, 1);

	glFlush();
	glEnd();
	// condicion de puntos
	score++;
	// imprimiendo el socore en pantalla
	glColor3f(1.000, 0.000, 0.000);
	glRasterPos2f(0, 0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'S');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'C');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'O');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'R');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'E');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ':');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, score / 1000 + 48);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, score / 100 % 10 + 48);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, score / 10 % 10 + 48);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, score % 10 + 48);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');

	glFlush();

}

void setup(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 2000, 0.0, 2000);
}

//Ventana
int main(int argc, char** argv) {
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(1230, 650);
	glutInitWindowPosition(50, 0);
	glutCreateWindow("Llama Game");
	setup();

	glutMainLoop();
}
