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

//variables estaticas y constantes que controlan la funcionalidad del codigo
static int animationPeriod = 4;
static int isAnimate = 0;
//declarando variables de fact y rango
const int fact = 3;
const int x = 80;
const double DEG2RAD = 3.1415926535897932384 / 180;

static double w = 200;
static int flag = 0;
static int walk = 0;
//declarando variables
static int x_ = 2500;
int score = 0;

//funciones que da la sensacion de movimiento.
void animate(int value) {
	if (isAnimate) {

		glutPostRedisplay();
		glutTimerFunc(animationPeriod, animate, 1);
	}
}
//Funciones para el uso del teclado
void keyInput(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(0);
	case ' ':
		if (isAnimate) isAnimate = 0;
		else {
			isAnimate = 1;
			animate(1);
		}
		break;
	}
}
// funcion para detectar una colecion
bool collision(double len) {
	//Funcion para saber cuando choca
	if (abs(157 + x - (x_ + x + 50)) <= 100 + x) {
		if (5 * fact + w <= 650 * len)return 1;
		return 0;
	}
	return 0;
}
//funcion para saltar
void specialKeyInput(int key, int x, int y) {
	
	if (key == GLUT_KEY_UP && flag == 0 && w <= 200.0) {
		flag = 1;
	}
	glutPostRedisplay();
}
// Agregando Función de el Area de Intimpa
void draw_circle(double theta, double inner_radius, double outer_radius, int x, int y, int sin_sign = 1, int cos_sign = 1) {
	//Intimpa
	glBegin(GL_POINTS);
	glColor3f(0.5, 0.5, -0.5);
	for (double r = outer_radius; r >= inner_radius; r -= 8.0) {
		for (double i = 0; i < theta; i++) {
			double degInRad = i * DEG2RAD;
			glVertex2f(cos_sign * cos(degInRad) * r + x, sin_sign * sin(degInRad) * r + y);
		}
	}
	glEnd();
}

using namespace std;
// Dibujar un punto
void plot(int ix, int iy) {
	glBegin(GL_POINTS); // dibuja un punto
	glVertex2i(ix, iy); // en la posicion (ix, iy)
	glEnd(); // termina de dibujar el punto
}
// esta funcion 'swap' intercambia los valores de dos variables
void swap(int* ix, int* iy) {
	int temp = *ix;
	*ix = *iy;
	*iy = temp;
}
// esta funcion 'bresemham' dibuja una linea entre dos puntos
void bresemham(int x0, int y0, int x1, int y1) {
	int dy, x, y, error;
	int delta_x, delta_y;
	bool steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep) {
		swap(&x0, &y0);
		swap(&x1, &y1);
	}
	if (x0 > x1) {
		swap(&x0, &x1);
		swap(&y0, &y1);
	}
	if (y0 < y1) {
		dy = 1;
	}
	else {
		dy = -1;
	}
	delta_x = x1 - x0;
	delta_y = abs(y1 - y0);
	y = y0;
	error = 0;
	for (x = x0; x <= x1; x++) {
		if (steep) {
			plot(y, x);
		}
		else {
			plot(x, y);
		}
		error += delta_y;
		if (2 * error >= delta_x) {
			y += dy;
			error -= delta_x;
		}
	}
}

//Funcion para recetar el juego
void reset() {
	w = 200;
	flag = 0;
	walk = 0;
	x_ = 2500;
	animationPeriod = 4;
	isAnimate = 0;
}
void generate_tree(int x_, double len) {
	int x = 30;
	//Intimpa
	//Tronco Intimpa
	glColor3f(0.5, 0.5, -0.5);
	glBegin(GL_POLYGON);
	glVertex2f(x_ - 10, 250 * len);
	glVertex2f(x_ + 10, 250 * len);
	glVertex2f(x_ + 10, 650 * len);
	glVertex2f(x_ - 10, 650 * len);
	glEnd();
	
	// Creando Hojas Intimpa
	draw_circle(180.0, -5.0, 90, x_, 350 * len, -1, -1);
	draw_circle(180.0, 0.8, 85, x_, 400 * len, -1, -1);
	draw_circle(180.0, -5.0, 80, x_, 450 * len, -1, -1);
	draw_circle(180.0, 0.0, 75, x_, 500 * len, -1, -1);
	draw_circle(180.0, -5.0, 70, x_, 550 * len, -1, -1);
	draw_circle(180.0, 0.0, 60, x_, 600 * len, -1, -1);
	draw_circle(180.0, -5.0, 40, x_, 650 * len, -1, -1);
}

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
	
	generate_tree(x_, 1.0);

	if (x_ >= 0)
		x_ -= 5;
	else {
		x_ = 2000 + rand() % 400;
	}
	glLineWidth(2);
	glBegin(GL_LINES);
	//linea del suelo
	glColor4f(0.647059, 0.164706, 0.164706, 1);
	bresemham(0, 250, 2000, 250);
	glEnd();

	glLineWidth(10);
	glBegin(GL_LINES);
	/****** Drawing ::: Begin ******/
	glColor3f(0.5, 0.35, 0.05);
	//glPointSize(5.0);

	// cuerpo trasero
	bresemham(40 + x, 35 * fact + w, 40 + x, 55 * fact + w);
	bresemham(40+x, 57 * fact + w, 38 + x, 55 * fact + w);
	bresemham(36+x, 57 * fact + w, 38 + x, 60 * fact + w);
	bresemham(36+x, 60 * fact + w, 80 + x, 60 * fact + w);
	// pata llama 1 left
	bresemham(40+x, 5 * fact + w, 40 + x, 35 * fact + w);
	bresemham(40+x, 5 * fact + w, 45 + x, 5 * fact + w);
	bresemham(45 + x, 5 * fact + w, 45 + x, 35 * fact + w);
	// pata llama 2 left
	bresemham(50 + x, 5 * fact + w, 50 + x, 35 * fact + w);
	bresemham(50 + x, 5 * fact + w, 55 + x, 5 * fact + w);
	bresemham(55 + x, 5 * fact + w, 55 + x, 35 * fact + w);
	// pata llama 1 right
	bresemham(70 + x, 5 * fact + w, 70 + x, 35 * fact + w);
	bresemham(70 + x, 5 * fact + w, 75 + x, 5 * fact + w);
	bresemham(75 + x, 5 * fact + w, 75 + x, 35 * fact + w);
	// pata llama 2 right
	bresemham(80 + x, 5 * fact + w, 80 + x, 35 * fact + w);
	bresemham(80 + x, 5 * fact + w, 85 + x, 5 * fact + w);
	bresemham(85 + x, 5 * fact + w, 85 + x, 35 * fact + w);
	// ombligo
	bresemham(55 + x, 35 * fact + w, 70 + x, 35 * fact + w);
	// cuello curveado
	bresemham(85 + x, 35 * fact + w, 90 + x, 50 * fact + w);
	// cuello hacia la cabeza
	bresemham(90 + x, 50 * fact + w, 90 + x, 85 * fact + w);// por la parte del frente
	bresemham(80 + x, 60 * fact + w, 80 + x, 100 * fact + w); // por la parte de la espalda
	// oido de mi iama
	bresemham(80 + x, 100 * fact + w, 75 + x, 107 * fact + w); // linea hhacia atras
	bresemham(75 + x, 107 * fact + w, 85 + x, 100 * fact + w);
	// cabeza
	bresemham(85 + x, 100 * fact + w, 90 + x, 100 * fact + w);
	bresemham(90 + x, 100 * fact + w, 100 + x, 93 * fact + w); // perfil de la nariz
	bresemham(100 + x, 93 * fact + w, 100 + x, 85 * fact + w); // boca
	bresemham(90 + x, 85 * fact + w, 100 + x, 85 * fact + w); // quijada
	//ojo
	glBegin(GL_POINTS);
	glVertex2i(88 + x, 94 * fact + w);
	glEnd();
	/****** Drawing ::: END ******/

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
	//condicion si es que choca o no el dino con el cactus
	if (collision(1.0)) {
		score = 0;
		reset();
	}
	else if (collision(0)) {
		score++;
	}
	if (w <= 200) {
		if (walk == -20)
			walk = 20;
		else {
			walk = -20;
		}
	}
	else {
		walk = 0;
	}

	if (flag == 1) {
		if (w <= 1000) {
			w = w + 8;
		}
		else {
			flag = 0;
		}
	}
	else if (w >= 200)
		w = w - 8;
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
	glutDisplayFunc(render);
	
	glutKeyboardFunc(keyInput);
	glutSpecialFunc(specialKeyInput);
	
	glutMainLoop();
}
