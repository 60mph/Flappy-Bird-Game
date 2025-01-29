#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
#pragma comment (lib, "winmm.lib")
#include <mmsystem.h>
#include <random>
#include "OpenGl/glut.h"
#include <math.h>
#include <ctime>

int WinWidth = 900;
int WinHeight = 900;

//Parameters:
float gravity = 0.0025;
float speed = 1.0;
float speedUp = 0.001;
float startSpeed = 0.01;
float startCloudSpeed = 0.003;
float startCitySpeed = 0.002;
float dist = 0.9;
float light = 1;

int moveAngle = 0;
bool gameStop = false;
bool gamePause = false;
bool jump = false;
bool firstStart = true;
int counter = 0;
int BestScore = 0;

struct TPipe {
	float x, h;
};

struct TBird {
	float x, y;
	float dx, dy;
	float r;
};

struct TCloud {
	float x, y;
	float r;
};

struct TCity {
	float x, y;
	float r;
};

TBird bird;
TPipe pipe2;
TPipe pipe;
TCloud cloud[10];
TCity house[20];

void TBirdInit(TBird* obj, float x1, float y1, float dx1, float dy1, float r1) {
	obj->x = x1;
	obj->dx = dx1;
	obj->y = y1;
	obj->dy = dy1;
	obj->r = r1;
}

void DrawBird() {
	float cnt = 100;
	float x = 0, y = 0;
	float a = 3.145 * 2 / cnt;
	float startRad = 0.8;
	glLineWidth(3);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.8, 0.8, 0.0);
	glVertex2f(x, y);
	for (int i = 0; i <= cnt; ++i)
	{
		x = sin(a * i) * 0.75;
		y = cos(a * i) * 0.65;
		glVertex2f(x, y);
	}
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(0, 0, 0);
	glVertex2f(x, y);
	for (int i = 0; i <= cnt; ++i)
	{
		x = sin(a * i) * 0.75;
		y = cos(a * i) * 0.65;
		glVertex2f(x, y);
	}
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.9, 0.9, 0.9);
	glVertex2f(0.45, 0);
	for (int i = 0; i <= 10; ++i)
	{
		x = sin(3.145 * 2 / 10 * i) * 0.3 + 0.43;
		y = cos(3.145 * 2 / 10 * i) * 0.4 + 0.1;
		glVertex2f(x, y);
	}
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(0, 0, 0);
	//glVertex2f(0.45, 0);
	for (int i = 0; i <= 10; ++i)
	{
		x = sin(3.145 * 2 / 10 * i) * 0.3 + 0.43;
		y = cos(3.145 * 2 / 10 * i) * 0.4 + 0.1;
		glVertex2f(x, y);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0, 0, 0);
	/*glVertex2f(0.4, 0.0);
	glVertex2f(0.7, 0.0);
	glVertex2f(0.7, 0.5);
	glVertex2f(0.4, 0.5);*/
	glVertex2f(0.53, 0.17);
	for (int i = 0; i <= 8; ++i)
	{
		x = sin(3.145 * 2 / 10 * i) * 0.1 + 0.53;
		y = cos(3.145 * 2 / 10 * i) * 0.15 + 0.17;
		glVertex2f(x, y);
	}
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 0.5, 0);
	glVertex2f(0.0, 0.0);
	glVertex2f(1.0, 0.0);
	glVertex2f(1.0, -0.3);
	glVertex2f(0.0, -0.3);
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 0.5, 0);
	glVertex2f(0.1, -0.30);
	glVertex2f(0.75, -0.30);
	glVertex2f(0.75, -0.45);
	glVertex2f(0.1, -0.45);
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.9, 0.9, 0.9);
	glVertex2f(-1, 0.3);
	for (int i = 0; i <= 10; ++i)
	{
		x = sin(3.145 * 2 / 10 * i) * 0.25 - 0.4;
		y = cos(3.145 * 2 / 10 * i) * 0.35;
		glVertex2f(x, y);
	}
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(0, 0, 0);
	glVertex2f(0.0, 0.0);
	glVertex2f(1.0, 0.0);
	glVertex2f(1.0, -0.3);
	glVertex2f(0.0, -0.3);
	glEnd();


	glBegin(GL_LINE_LOOP);
	glColor3f(0, 0, 0);
	glVertex2f(0.1, -0.30);
	glVertex2f(0.75, -0.30);
	glVertex2f(0.75, -0.45);
	glVertex2f(0.1, -0.45);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(0, 0, 0);
	glVertex2f(-1, 0.3);
	for (int i = 0; i <= 6; ++i)
	{
		x = sin(3.145 * 2 / 10 * i) * 0.25 - 0.4;
		y = cos(3.145 * 2 / 10 * i) * 0.35;
		glVertex2f(x, y);
	}
	glEnd();

}

void ShowBird(TBird obj) {

	glPushMatrix();
	glTranslatef(obj.x, obj.y, 0);
	glScalef(obj.r, obj.r, 0);
	glRotatef((obj.dy * 360 * 2) + 10, 0, 0, 1);
	DrawBird();
	glPopMatrix();
}

void TPipeInit(TPipe *obj, float x1, float h1) {
	obj->x = x1;
	obj->h = h1;
}

void DrawPipe() {
	glLineWidth(2);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0, 0.3, 0);
	glVertex2f(-0.2, -0.35);
	glVertex2f(0.2, -0.35);
	glVertex2f(0.2, -2);
	glVertex2f(-0.2, -2);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3f(0, 0, 0);
	glVertex2f(-0.2, -0.35);
	glVertex2f(0.2, -0.35);
	//glVertex2f(0.2, -2);
	//glVertex2f(-0.2, -2);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0, 0.3, 0);
	glVertex2f(-0.2, 0.35);
	glVertex2f(0.2, 0.35);
	glVertex2f(0.2, 2);
	glVertex2f(-0.2, 2);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3f(0, 0, 0);
	glVertex2f(-0.2, 0.35);
	glVertex2f(0.2, 0.35);
	glVertex2f(0.2, 2);
	glVertex2f(-0.2, 2);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0, 0.25, 0);
	glVertex2f(-0.25, -0.35);
	glVertex2f(0.25, -0.35);
	glVertex2f(0.25, -0.5);
	glVertex2f(-0.25, -0.5);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3f(1, 1, 1);
	glVertex2f(-0.25, -0.35);
	glVertex2f(0.25, -0.35);
	//glVertex2f(0.25, -0.5);
	//glVertex2f(-0.25, -0.5);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0, 0.25, 0);
	glVertex2f(-0.25, 0.35);
	glVertex2f(0.25, 0.35);
	glVertex2f(0.25, 0.5);
	glVertex2f(-0.25, 0.5);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(0, 0, 0);
	glVertex2f(-0.25, 0.35);
	glVertex2f(0.25, 0.35);
	glVertex2f(0.25, 0.5);
	glVertex2f(-0.25, 0.5);
	glEnd();
}

void ShowPipe(TPipe obj) {

	glPushMatrix();
	glTranslatef(obj.x, obj.h, 0);
	DrawPipe();
	glPopMatrix();
}

void TCloudInit(TCloud* obj, float x1, float y1, float r1) {
	obj->x = x1;
	obj->y = y1;
	obj->r = r1;
}

void TCityInit(TCity* obj, float x1, float y1, float r1) {
	obj->x = x1;
	obj->y = y1;
	obj->r = r1;
}

void DrawCity() {
	glLineWidth(2);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.5, 0.5, 0.5);
	glVertex2f(-0.05, 0);
	glVertex2f(0.05, 0);
	glVertex2f(0.05, -2);
	glVertex2f(-0.05, -2);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3f(0.8, 0.8, 0.8);
	glVertex2f(-0.05, 0);
	glVertex2f(0.05, 0);
	glVertex2f(0.05, -2);
	glVertex2f(-0.05, -2);
	glEnd();

	for (int i = 0; i > -10; --i)
	{
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(0.3, 0.5, 1);
		glVertex2f(-0.04, 0.03* i - 0.01);
		glVertex2f(-0.005, 0.03 * i - 0.01);
		glVertex2f(-0.005, 0.03 * i - 0.03);
		glVertex2f(-0.04, 0.03 * i - 0.03);
		glEnd();
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(0.3, 0.5, 1);
		glVertex2f(0.04, 0.03 * i - 0.01);
		glVertex2f(0.005, 0.03 * i - 0.01);
		glVertex2f(0.005, 0.03 * i - 0.03);
		glVertex2f(0.04, 0.03 * i - 0.03);
		glEnd();
		glLineWidth(1);
		glBegin(GL_LINE_LOOP);
		glColor3f(0.7, 0.7, 0.7);
		glVertex2f(-0.04, 0.03 * i - 0.01);
		glVertex2f(-0.005, 0.03 * i - 0.01);
		glVertex2f(-0.005, 0.03 * i - 0.03);
		glVertex2f(-0.04, 0.03 * i - 0.03);
		glEnd();
		glBegin(GL_LINE_LOOP);
		glColor3f(0.7, 0.7, 0.7);
		glVertex2f(0.04, 0.03 * i - 0.01);
		glVertex2f(0.005, 0.03 * i - 0.01);
		glVertex2f(0.005, 0.03 * i - 0.03);
		glVertex2f(0.04, 0.03 * i - 0.03);
		glEnd();
	}
}

void DrawGround() {
	glLineWidth(2);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.2, 0.5, 0.2);
	glVertex2f(-1, 0);
	glVertex2f(1, 0);
	glVertex2f(1, -2);
	glVertex2f(-1, -2);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3f(0, 0, 0);
	glVertex2f(-1, 0);
	glVertex2f(1, 0);
	glVertex2f(1, -2);
	glVertex2f(-1, -2);
	glEnd();
}

void ShowGround() {
	glPushMatrix();
	glTranslatef(0, -0.95, 0);
	DrawGround();
	glPopMatrix();
}

void ShowCity(TCity obj) {
	glPushMatrix();
	glTranslatef(obj.x, obj.y, 0);
	glScalef(obj.r, obj.r, 0);
	DrawCity();
	glPopMatrix();
}

void CityMove(TCity* obj) {
	if (!gameStop && !gamePause) {
		obj->x -= startCitySpeed * speed;
	}
}

void DrawCloud() {
	float cnt = 100;
	float x = 0, y = 0;
	float a = 3.145 * 2 / cnt;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 1, 1);
	glVertex2f(x, y);
	for (int i = 0; i <= cnt; ++i)
	{
		x = sin(a * i) * 0.55;
		y = cos(a * i) * 0.35;
		glVertex2f(x, y);
	}
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 1, 1);
	glVertex2f(0.6, -0.1);
	for (int i = 0; i <= cnt; ++i)
	{
		x = sin(a * i) * 0.65 + 0.6;
		y = cos(a * i) * 0.15 - 0.1;
		glVertex2f(x, y);
	}
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 1, 1);
	glVertex2f(-0.7, -0.3);
	for (int i = 0; i <= cnt; ++i)
	{
		x = sin(a * i) * 0.75 - 0.7;
		y = cos(a * i) * 0.2 - 0.3;
		glVertex2f(x, y);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 1, 1);
	glVertex2f(-0.1, -0.1);
	for (int i = 0; i <= cnt; ++i)
	{
		x = sin(a * i) * 0.85 - 0.1;
		y = cos(a * i) * 0.3 -0.1;
		glVertex2f(x, y);
	}
	glEnd();
}

void ShowCloud(TCloud obj) {
	glPushMatrix();
	glTranslatef(obj.x, obj.y, 0);
	glScalef(obj.r, obj.r, 0);
	DrawCloud();
	glPopMatrix();
}

void CloudMove(TCloud *obj) {
	if (!gameStop && !gamePause) {
		obj->x -= startCloudSpeed * speed;
	}
}

void InBest() {
	std::ifstream data("AppData.txt");
	data >> BestScore;
	data.close();
}

void OutBest() {
	std::ofstream data("AppData.txt");
	data << counter;
	data.close();
}

void Startout(GLfloat red, GLfloat green, GLfloat blue)
{
	std::string score = "Press P to Start";
	glColor3f(red, green, blue);
	int i = 0;
	for (int i = 0; i < score.size(); ++i)
	{
		glRasterPos2f(i * 0.02, 0);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, score[i]);
	}
}

void ShowStartout() {
	glPushMatrix();
	glTranslatef(-0.45, -0.2, 0);
	glScalef(3, 3, 0);
	Startout(0, 0, 0);
	glPopMatrix();
}

void Restartout(GLfloat red, GLfloat green, GLfloat blue)
{
	std::string score = "Press R to Restart";
	glColor3f(red, green, blue);
	int i = 0;
	for (int i = 0; i < score.size(); ++i)
	{
		glRasterPos2f(i * 0.02, 0);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, score[i]);
	}
}

void ShowRetartout() {
	glPushMatrix();
	glTranslatef(-0.45, -0.2, 0);
	glScalef(3, 3, 0);
	Restartout(0, 0, 0);
	glPopMatrix();
}

void Scoreout(std::string& str, GLfloat red, GLfloat green, GLfloat blue)
{
	std::string score = "SCORE: ";
	glColor3f(red, green, blue);
	int i = 0;
	for (int i = 0; i < str.size() + score.size(); ++i)
	{
		glRasterPos2f(i * 0.02, 0);
		if (i < score.size())
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, score[i]);
		else
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i-score.size()]);
	}
	
}

void BestScoreout(std::string& str, GLfloat red, GLfloat green, GLfloat blue)
{
	std::string score = "BEST SCORE: ";
	glColor3f(red, green, blue);
	int i = 0;
	for (int i = 0; i < str.size() + score.size(); ++i)
	{
		glRasterPos2f(i * 0.02, 0);
		if (i < score.size())
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, score[i]);
		else
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i - score.size()]);
	}

}

void ShowScore(std::string& str)
{
	glPushMatrix();
	glTranslatef(-0.9, 0.9, 0);
	glScalef(2, 2, 0);
	
	Scoreout(str, 0, 0, 0);
	glPopMatrix();
}

void ShowBestScore(std::string& str)
{
	glPushMatrix();
	glTranslatef(-0.9, 0.8, 0);
	glScalef(2, 2, 0);
	BestScoreout(str, 0, 0, 0);
	glPopMatrix();
}

void BuildNewPipe(TPipe *pipe) {
	//light *= 0.95;
	srand(time(0)*16);
	int countrand = rand();
	srand(countrand);
	float randY = float(abs(rand() % 100)) / 50 - 1;
	//std::cout << randY << std::endl;
	TPipeInit(pipe, 1.6 * dist, randY * 0.6);
}

void BuildNewCloud(TCloud* cloud, float x, float randCount){
	srand(time(0) * randCount);
	float random = float(abs(rand() % 100)) / 100;
	TCloudInit(cloud, 0.5 * (x - 4), random, 0.25 * (0.8 * random + 0.2));
}

void BuildNewCity(TCity* house, float x, float randCount) {
	srand(time(0) * randCount);
	float random = float(abs(rand() % 100)) / 100;
	TCityInit(house, 0.1 * (x - 10) + 0.1, (random*0.3) - 1.0, 0.3 * random + 0.7);
}

void Counter() {
	if (!gameStop)
	{
		counter++;
		std::cout << counter << std::endl;
	}
	if (counter > BestScore) {
		OutBest();
		InBest();
	}

}

void BirdJump(TBird* obj) {
	//if(GetKeyState(left))
		//
	//float oldy = 0;
	if (jump) {
		//oldy = obj->y;
		//std::cout << obj->dy << std::endl;
		//if (obj->dy < -0.01) {
			obj->dy *= -0.2;
			obj->dy += 0.035;
			jump = false;
		//}
		jump = false;
	}
}

void BirdMove(TBird* obj) {
	//obj->x += obj->dx;
	if (!gameStop && !gamePause) {
		obj->dy -= gravity;
		obj->y += obj->dy;
		BirdJump(obj);
	}
}

void PipeMove(TPipe* obj) {
	//obj->x += obj->dx;
	if (!gameStop && !gamePause) {
		obj->x -= startSpeed * speed;
	}
}

void FailCheck(TBird* obj)
{
	if (abs(obj->y ) > 1.2 - obj->r)
		gameStop = true;
}

//bool mouseButton(int button, int state, int x, int y) {
//
//	// только при начале движения, если нажата левая кнопка
//	if (button == GLUT_LEFT_BUTTON) {
//
//		// когда кнопка отпущена
//		if (state == GLUT_DOWN) {
//			return 1;
//		}
//		else {// state = GLUT_DOWN
//			return 0;
//		}
//	}
//}

//void GameInit() {
//	//TBirdInit(&bird, 0, 0, 0, 0, 0.1);
//	//TPipeInit(&pipe, 1, 1.6);
//}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	//glPointSize(10);
	//glLineWidth(10);
	glFlush();
}

void Start() {
	gameStop = false;
	gamePause = true;
}

void StartPos() {
	Start();
	firstStart = true;
	light = 1.0;
	speed = 1.0;
	counter = 0;
	TPipeInit(&pipe, 1.6, 0);
	TPipeInit(&pipe2, 3.2, 0);
	TBirdInit(&bird, 0, 0, 0, 0, 0.1);
	for (int i = 0; i < 10; ++i)
	{
		BuildNewCloud(&cloud[i], i, i);
	}
	for (int i = 0; i < 20; ++i)
	{
		BuildNewCity(&house[i], i, i);
	}
	PlaySound(TEXT("Song.wav"), NULL, SND_ASYNC | SND_LOOP);
}

void processNormalKeys(unsigned char key, int x, int y) {
	if (key == 32) {
		jump = true;
		//std::cout << "SP" << std::endl;
	}
	else jump = false;
	if (key == 27) {
		exit(0);
		//std::cout << "SP" << std::endl;
	}
	if (key == 'r') {
		if (firstStart)
			firstStart = 0;
		StartPos();
	}
	
	if (key == 'p') {
		if (!gamePause)
			gamePause = 1;
		else
			gamePause = 0;
		if (firstStart)
			firstStart = 0;
	}

	/*else if (key == 'r') {
		int mod = glutGetModifiers();
		if (mod == GLUT_ACTIVE_ALT)
			cout << ""
		else
			red = 1.0;
	}*/
}

void Timer(int)
{
	//moveAngle++;
	//glRotatef(10, 0, 0, 0);
	/*if (y > r)
	{
		y = y - 0.1 * sqrt(1.004 * y * y);
	}
	else y = 2;*/
	//ShowBird(bird);
	
	glutPostRedisplay();
	glClearColor(0.5 * light, 0.7 * light, 1 * light, 1);
	std::string str = std::to_string(counter);
	std::string Bstr = std::to_string(BestScore);
	
	FailCheck(&bird);
	//std::cout << pipe.x << " " << pipe.h << " " << bird.y << std::endl;
	//std::cout << pipe.x << " " << pipe.h << " " << bird.y << std::endl;
	if (abs(pipe.x) < (0.25 + bird.r))
	{
		if (bird.y > pipe.h + (0.2 + bird.r) || bird.y < pipe.h - (0.2 + bird.r))
		{
			//std::cout << "Game over" << std::endl;
			gameStop = true;
			//std::cout << pipe.x << " " << pipe.h << " " << bird.y << std::endl;
		}
	}
	if (abs(pipe2.x) < 0.25 + bird.r)
	{
		if (bird.y > pipe2.h + (0.2 + bird.r) || bird.y < pipe2.h - (0.2 + bird.r))
		{
			//std::cout << "Game over" << std::endl;
			gameStop = true;
			//std::cout << "PIPE1: " << pipe.x << " " << pipe.h << " " << " PIPE2: " << pipe2.x << " " << pipe2.h << " BIRD: " << bird.y << std::endl;
		}
	}
	if (abs(pipe.x) <= 0.005 * speed) {
		BuildNewPipe(&pipe2);
		//Counter();
	}
	if (abs(pipe2.x) <= 0.005 * speed) {
		BuildNewPipe(&pipe);
		//Counter();
	}
	if (pipe.x < -1.6 * dist) {
		BuildNewPipe(&pipe);
		//Counter();
	}
	if (pipe2.x < -1.6 * dist)
		BuildNewPipe(&pipe2);
	if (abs(pipe.x) <= 0.005 * speed || abs(pipe2.x) <= 0.005 * speed)
		Counter();

	for (int i = 0; i < 10; ++i)
	{
		if (cloud[i].x < -1.3 * (cloud[i].r + 0.8)) {
			BuildNewCloud(&cloud[i], 10, i);
		}
		ShowCloud(cloud[i]);
		CloudMove(&cloud[i]);
	}
	for (int i = 0; i < 20; ++i)
	{
		if (house[i].x < -1.1) {
			BuildNewCity(&house[i], 20, i);
		}
		ShowCity(house[i]);
		CityMove(&house[i]);
	}
	ShowGround();
	BirdMove(&bird);
	PipeMove(&pipe);
	PipeMove(&pipe2);
	glutKeyboardFunc(processNormalKeys);
	
	ShowBird(bird);
	ShowPipe(pipe);
	ShowPipe(pipe2);
	ShowScore(str);
	ShowBestScore(Bstr);
	if (firstStart)
		ShowStartout();
	else if (gameStop)
		ShowRetartout();
	glutSwapBuffers();
	if(!gameStop && !gamePause)
	speed += speedUp;
	//light = cos(speed);
	glutTimerFunc(10, Timer, 100);
	
}

int main(int argc, char**argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WinWidth, WinHeight);
	glutInitWindowPosition(480, 100);
	glutCreateWindow("FlappyBird");
	glClearColor(0.5, 0.7, 1, 1);
	//glClearColor(0.0, 0.5, 1, 0.1);
	InBest();
	
	//GameInit();
	gluOrtho2D(-1, 1, -1, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glutDisplayFunc(display);
	StartPos();
	
	glutTimerFunc(10, Timer, 0);
	
	glutMainLoop();
	return 0;
}