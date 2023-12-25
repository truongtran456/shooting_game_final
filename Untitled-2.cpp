#ifdef _WIN32
#include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#define GL_SILENCE_DEPRECATION

#define XMAX 1200
#define YMAX 700
#define SPACESHIP_SPEED 20
#define TOP 0
#define RIGHT 1
#define BOTTOM 2
#define LEFT 3

float spaceshipRotation1 = 0.0f;
float spaceshipRotation2 = 0.0f;
float alienScaleRatio = 1.0f; // Ti le mac dinh la 1.0f -> phongto/thu nho

GLint m_viewport[4];
bool mButtonPressed = false;
float mouseX, mouseY; // toa do htai cua chuot
enum view
{
	INTRO,
	MENU,
	INSTRUCTIONS,
	GAME,
	GAMEOVER
};
view viewPage = INTRO; // initial value
bool keyStates[256] = {false};
bool direction[4] = {false};
bool laser1Dir[2] = {false};
bool laser2Dir[2] = {false};

int alienLife1 = 100;
int alienLife2 = 100;
bool gameOver = false;
float xOne = 500, yOne = 0;
float xTwo = 500, yTwo = 0;
bool laser1 = false, laser2 = false;

GLint CI = 0;
GLfloat a[][2] = {0, -50, 70, -50, 70, 70, -70, 70};
GLfloat LightColor[][3] = {1, 1, 0, 0, 1, 1, 0, 1, 0};
GLfloat AlienBody[][2] = {{-4, 9}, {-6, 0}, {0, 0}, {0.5, 9}, {0.15, 12}, {-14, 18}, {-19, 10}, {-20, 0}, {-6, 0}};
GLfloat AlienCollar[][2] = {{-9, 10.5}, {-6, 11}, {-5, 12}, {6, 18}, {10, 20}, {13, 23}, {16, 30}, {19, 39}, {16, 38}, {10, 37}, {-13, 39}, {-18, 41}, {-20, 43}, {-20.5, 42}, {-21, 30}, {-19.5, 23}, {-19, 20}, {-14, 16}, {-15, 17}, {-13, 13}, {-9, 10.5}};
GLfloat ALienFace[][2] = {{-6, 11}, {-4.5, 18}, {0.5, 20}, {0., 20.5}, {0.1, 19.5}, {1.8, 19}, {5, 20}, {7, 23}, {9, 29}, {6, 29.5}, {5, 28}, {7, 30}, {10, 38}, {11, 38}, {11, 40}, {11.5, 48}, {10, 50.5}, {8.5, 51}, {6, 52}, {1, 51}, {-3, 50}, {-1, 51}, {-3, 52}, {-5, 52.5}, {-6, 52}, {-9, 51}, {-10.5, 50}, {-12, 49}, {-12.5, 47}, {-12, 43}, {-13, 40}, {-12, 38.5}, {-13.5, 33}, {-15, 38}, {-14.5, 32}, {-14, 28}, {-13.5, 33}, {-14, 28}, {-13.8, 24}, {-13, 20}, {-11, 19}, {-10.5, 12}, {-6, 11}};
GLfloat ALienBeak[][2] = {{-6, 21.5}, {-6.5, 22}, {-9, 21}, {-11, 20.5}, {-20, 20}, {-14, 23}, {-9.5, 28}, {-7, 27}, {-6, 26.5}, {-4.5, 23}, {-4, 21}, {-6, 19.5}, {-8.5, 19}, {-10, 19.5}, {-11, 20.5}};

void displayRasterText(float x, float y, float z, char *stringToDisplay)
{ // dat vi tri rater trong 3D
	glRasterPos3f(x, y, z);
	for (char *c = stringToDisplay; *c != '\0'; c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0);
	glColor3f(1.0, 0.0, 0.0); // m�u ve
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(-1200, 1200, -700, 700); //<-----CHANGE THIS TO GET EXTRA SPACE
				      //  gluOrtho2D(-200,200,-200,200);
	glMatrixMode(GL_MODELVIEW);
}

void introScreen()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 0.0, 0.0);
	displayRasterText(-500, 490, 0.0, "VKU University of Information and Communication Technology");
	glColor3f(1.0, 1.0, 1.0);
	displayRasterText(-300, 385, 0.0, "Software engineer - Computer science");
	glColor3f(0.0, 0.0, 1.0);
	displayRasterText(-180, 300, 0.0, "A MINI PROJECT ON ");
	glColor3f(1.0, 0.0, 1.0);
	displayRasterText(-185, 225, 0.0, " -- Computer Graphics -- ");
	glColor3f(1.0, 0.7, 0.8);
	displayRasterText(-75, 150, 0.0, "Created by");
	glColor3f(1.0, 1.0, 1.0);
	displayRasterText(-180, 80, 0.0, "TRAN QUOC TRUONG");
	glColor3f(1.0, 0.0, 0.0);
	displayRasterText(-800, -100, 0.0, "GROUP MEMBER");
	glColor3f(1.0, 1.0, 1.0);
	displayRasterText(-800, -200, 0.0, " Le Thi Dan Lien");
	displayRasterText(-800, -285, 0.0, " Tong Chinh Chung");
	glColor3f(1.0, 0.0, 0.0);
	displayRasterText(500, -100, 0.0, "Under the Guidance of");
	glColor3f(1.0, 1.0, 1.0);
	displayRasterText(500, -200, 0.0, "Prof X");
	glColor3f(1.0, 0.0, 0.0);
	displayRasterText(-250, -400, 0.0, "Academic Year 2023-2024");
	glColor3f(1.0, 1.0, 1.0);
	displayRasterText(-300, -550, 0.0, "Press ENTER to start the game");
	glFlush(); // day c�c l�nh ra b� d�m
	glutSwapBuffers();
}

void startScreenDisplay()
{
	glLineWidth(10);
	// SetDisplayMode(MENU_SCREEN);

	glColor3f(1, 0, 0);
	glBegin(GL_LINE_LOOP); // Border
	glVertex2f(-750, -500);
	glVertex2f(-750, 550);
	glVertex2f(750, 550);
	glVertex2f(750, -500);
	glEnd();

	glLineWidth(1);
	// ve 3 cai da gi�c chua start....
	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON); // START GAME PLOYGON
	glVertex2f(-200, 300);
	glVertex2f(-200, 400);
	glVertex2f(200, 400);
	glVertex2f(200, 300);
	glEnd();

	glBegin(GL_POLYGON); // INSTRUCTIONS POLYGON
	glVertex2f(-200, 50);
	glVertex2f(-200, 150);
	glVertex2f(200, 150);
	glVertex2f(200, 50);
	glEnd();

	glBegin(GL_POLYGON); // QUIT POLYGON
	glVertex2f(-200, -200);
	glVertex2f(-200, -100);
	glVertex2f(200, -100);
	glVertex2f(200, -200);
	glEnd();

	if (mouseX >= -100 && mouseX <= 100 && mouseY >= 150 && mouseY <= 200)
	{
		glColor3f(0, 0, 1); // xanh
		if (mButtonPressed)
		{ // nh�p chuot
			alienLife1 = alienLife2 = 100;
			viewPage = GAME; // chuyen d�n trang game
			mButtonPressed = false;
		}
	}
	else
		glColor3f(0, 0, 0); // den

	displayRasterText(-100, 340, 0.4, "Start Game");

	if (mouseX >= -100 && mouseX <= 100 && mouseY >= 30 && mouseY <= 80)
	{
		glColor3f(0, 0, 1);
		if (mButtonPressed)
		{
			viewPage = INSTRUCTIONS;
			printf("button pressed bitch\n");
			mButtonPressed = false;
		}
	}
	else
		glColor3f(0, 0, 0);
	displayRasterText(-120, 80, 0.4, "Instructions");

	if (mouseX >= -100 && mouseX <= 100 && mouseY >= -90 && mouseY <= -40)
	{
		glColor3f(0, 0, 1);
		if (mButtonPressed)
		{
			mButtonPressed = false;
			exit(0);
		}
	}
	else
		glColor3f(0, 0, 0);
	displayRasterText(-100, -170, 0.4, "    Quit");
	glutPostRedisplay();
}
// xu li nut back
void backButton()
{
	if (mouseX <= -450 && mouseX >= -500 && mouseY >= -275 && mouseY <= -250)
	{
		glColor3f(0, 0, 1); // xanh
		if (mButtonPressed)
		{
			viewPage = MENU; // chuyen den menu
			mButtonPressed = false;
			// instructionsGame = false;
			glutPostRedisplay();
		}
	}
	else
		glColor3f(1, 0, 0);
	displayRasterText(-1000, -550, 0, "Back");
}

void instructionsScreenDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// SetDisplayMode(MENU_SCREEN);
	// colorBackground();
	glColor3f(1, 0, 0);
	displayRasterText(-900, 550, 0.4, "INSTRUCTIONS");
	glColor3f(1, 0, 0);
	displayRasterText(-1000, 400, 0.4, "PLAYER 1");
	displayRasterText(200, 400, 0.4, "PLAYER 2");
	glColor3f(1, 1, 1);
	displayRasterText(-1100, 300, 0.4, "Key 'w' to move up.");
	displayRasterText(-1100, 200, 0.4, "Key 's' to move down.");
	displayRasterText(-1100, 100, 0.4, "Key 'd' to move right.");
	displayRasterText(-1100, 0, 0.4, "Key 'a' to move left.");
	displayRasterText(100, 300, 0.4, "Key 'i' to move up.");
	displayRasterText(100, 200, 0.4, "Key 'k' to move down.");
	displayRasterText(100, 100, 0.4, "Key 'j' to move right.");
	displayRasterText(100, 0, 0.4, "Key 'l' to move left.");
	displayRasterText(-1100, -100, 0.4, "Key 'c' to shoot, Use 'w' and 's' to change direction.");
	displayRasterText(100, -100, 0.4, "Key 'm' to shoot, Use 'i' and 'k' to change direction.");
	// displayRasterText(-1100 ,-100 ,0.4 ,"The packet can be placed only when 's' is pressed before.");
	displayRasterText(-1100, -300, 0.4, "The Objective is to kill your opponent.");
	displayRasterText(-1100, -370, 0.4, "Each time a player gets shot, LIFE decreases by 5 points.");
	backButton();
	// if(previousScreen)
	//	nextScreen = false ,previousScreen = false; //as set by backButton()
}

// ve co the cua alien=nguoi ngo�i h�nh tinh
void DrawAlienBody(bool isPlayer1)
{
	if (isPlayer1)
		glColor3f(0, 1, 0);
	else
		glColor3f(1, 1, 0); // BODY color
	glBegin(GL_POLYGON);
	for (int i = 0; i <= 8; i++)
		glVertex2fv(AlienBody[i]);
	glEnd();

	glColor3f(0, 0, 0); // BODY Outline
	glLineWidth(1);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= 8; i++)
		glVertex2fv(AlienBody[i]);
	glEnd();

	glBegin(GL_LINES); // BODY effect
	glVertex2f(-13, 11);
	glVertex2f(-15, 9);
	glEnd();
}
// ve tai
void DrawAlienCollar()
{
	glColor3f(1, 0, 0);		// COLLAR
	glBegin(GL_POLYGON);	// ve da gi�c
	for (int i = 0; i <= 20; i++) // lap qua 21 diem de xd dinh cua da gi�c
		glVertex2fv(AlienCollar[i]);
	glEnd(); // kthuc ve

	glColor3f(0, 0, 0);		// COLLAR outline
	glBegin(GL_LINE_STRIP);	// bat dau ve dg vien
	for (int i = 0; i <= 20; i++) // ve ca dinh cua da gi�c
		glVertex2fv(AlienCollar[i]);
	glEnd();
}

// ve face ng ngo�i h�nh tinh
void DrawAlienFace(bool isPlayer1)
{
	glColor3f(0.6, 0.0, 0.286); // FACE
	glColor3f(0.8, 0.2, 0.1);
	glColor3f(0, 0.5, 1);
	if (isPlayer1)
		glColor3f(0, 0, 1);
	else
		glColor3f(0, 1, 0);

	glBegin(GL_POLYGON);
	for (int i = 0; i <= 42; i++)
		glVertex2fv(ALienFace[i]);
	glEnd();

	glColor3f(0, 0, 0); // FACE outline
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= 42; i++)
		glVertex2fv(ALienFace[i]);
	glEnd();

	glBegin(GL_LINE_STRIP); // EAR effect
	glVertex2f(3.3, 22);
	glVertex2f(4.4, 23.5);
	glVertex2f(6.3, 26);
	glEnd();
}

// ve mieng
void DrawAlienBeak()
{
	glColor3f(1, 1, 0); // BEAK color
	glBegin(GL_POLYGON);
	for (int i = 0; i <= 14; i++)
		glVertex2fv(ALienBeak[i]); // th�m ddiem v�o da giac
	glEnd();

	glColor3f(0, 0, 0); // BEAK outline
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= 14; i++)
		glVertex2fv(ALienBeak[i]);
	glEnd();
}

// ve mat'
void DrawAlienEyes(bool isPlayer1)
{
	if (isPlayer1)
		glColor3f(0, 1, 1);
	else
		glColor3f(0, 0, 0);

	glPushMatrix();
	glRotated(-10, 0, 0, 1);
	glTranslated(-6, 32.5, 0); // Left eye
	glScalef(2.5, 4, 0);
	glutSolidSphere(1, 20, 30);
	glPopMatrix();

	glPushMatrix();
	glRotated(-1, 0, 0, 1);
	glTranslated(-8, 36, 0); // Right eye
	glScalef(2.5, 4, 0);
	glutSolidSphere(1, 100, 100);
	glPopMatrix();
}

// ve nguoi ngo�i h�nh tinh dua v�o n~ dd n�y h
void DrawAlien(bool isPlayer1)
{
	glPushMatrix();

	DrawAlienBody(isPlayer1); // body
	DrawAlienCollar();	      // tai
	DrawAlienFace(isPlayer1); // face
	DrawAlienBeak();	      // mieng
	DrawAlienEyes(isPlayer1); // mat

	glPopMatrix();
}

// ve dia bay - eclip midpoint
void DrawSpaceshipBody(bool isPlayer1)
{

	float centerX = 0; // toa do center
	float centerY = 0;
	float radiusX = 70; // r theo ngang doc
	float radiusY = 18;
	if (isPlayer1)
		glColor3f(1, 0, 0); // M�u d? cho BASE
	else
		glColor3f(0.5, 0, 0.5); // M�u t�m cho BASE

	glBegin(GL_POLYGON); // S? d?ng GL_POLYGON thay v� GL_POINTS
	float x = 0;
	float y = radiusY;
	float p = pow(radiusY, 2) - pow(radiusX, 2) * radiusY + 0.25 * pow(radiusX, 2);
	while (2 * pow(radiusY, 2) * x < 2 * pow(radiusX, 2) * y)
	{
		x++;
		if (p < 0)
		{
			p = p + 2 * pow(radiusY, 2) * x + pow(radiusY, 2);
		}
		else
		{
			y--;
			p = p + 2 * pow(radiusY, 2) * x - 2 * pow(radiusX, 2) * y + pow(radiusY, 2);
		}
		// T� m�u ph�a b�n trong c?a ellipse
		glVertex2f(centerX + x, centerY - y);
		glVertex2f(centerX - x, centerY - y);
		glVertex2f(centerX + x, centerY + y);
		glVertex2f(centerX - x, centerY + y);
	}
	p = pow(radiusY, 2) * pow((x + 0.5), 2) + pow(radiusX, 2) * pow((y - 1), 2) - pow(radiusX, 2) * pow(radiusY, 2);
	while (y > 0)
	{
		y--;
		if (p > 0)
		{
			p = p - 2 * pow(radiusX, 2) * y + pow(radiusX, 2);
		}
		else
		{
			x++;
			p = p + 2 * pow(radiusY, 2) * x - 2 * pow(radiusX, 2) * y + pow(radiusX, 2);
		}
		// T� m�u ph�a b�n trong c?a ellipse
		glVertex2f(centerX + x, centerY - y);
		glVertex2f(centerX - x, centerY - y);
		glVertex2f(centerX + x, centerY + y);
		glVertex2f(centerX - x, centerY + y);
	}
	glEnd();
	// may cai nut nho phia' trong hinh eclipse
	glPushMatrix(); // LIGHTS
	glScalef(3, 3, 1);
	glTranslated(-20, 0, 0); // 1
	glColor3fv(LightColor[(CI + 0) % 3]);
	glutSolidSphere(1, 1000, 1000);
	glTranslated(5, 0, 0); // 2
	glColor3fv(LightColor[(CI + 1) % 3]);
	glutSolidSphere(1, 1000, 1000);
	glTranslated(5, 0, 0); // 3
	glColor3fv(LightColor[(CI + 2) % 3]);
	glutSolidSphere(1, 1000, 1000);
	glTranslated(5, 0, 0); // 4
	glColor3fv(LightColor[(CI + 0) % 3]);
	glutSolidSphere(1, 1000, 1000);

	glTranslated(5, 0, 0); // Di chuy?n d?n v? tr� mong mu?n
	glColor3fv(LightColor[(CI + 1) % 3]);

	const float scale_factor = 3.0f; // Tang k�ch thu?c l�n 2 l?n

	glScalef(scale_factor, scale_factor, scale_factor); // Tang k�ch thu?c
	glutSolidSphere(1, 1000, 1000);		  // V? qu? c?u

	glScalef(1.0f / scale_factor, 1.0f / scale_factor, 1.0f / scale_factor); // Kh�i ph?c k�ch thu?c ban d?u

	glTranslated(5, 0, 0); // 6
	glColor3fv(LightColor[(CI + 2) % 3]);
	glutSolidSphere(1, 1000, 1000);
	glTranslated(5, 0, 0); // 7
	glColor3fv(LightColor[(CI + 0) % 3]);
	glutSolidSphere(1, 1000, 1000);
	glTranslated(5, 0, 0); // 8
	glColor3fv(LightColor[(CI + 1) % 3]);
	glutSolidSphere(1, 1000, 1000);
	glTranslated(5, 0, 0); // 9
	glColor3fv(LightColor[(CI + 2) % 3]);
	glutSolidSphere(1, 1000, 1000);

	glPopMatrix();
}
// ve cai' b�nh l�i duong d�y(phai phong to moi th�y dg d�y) -> c�i v� lang l�i �
void DrawSteeringWheel()
{
	glPushMatrix();	        // day ma tran vao ngan xep ma tran
	glLineWidth(3);	        // do rong ve dg day 3pixel
	glColor3f(0.20, 0., 0.20);  // mau den vs 1 t� do
	glScalef(7, 4, 1);	        // kthuoc
	glTranslated(-1.9, 5.5, 0); // dich chuyen vi tri'
	glutWireSphere(1, 8, 8);    // ve hinh cau vs r=1 va su dung 8 doc va ngang de tao dduong d�y
	glPopMatrix();	        // lay ma tran tu ngan xep
}

// c�i h�nh tr�m nguoi no'- bresenham eclip
void DrawSpaceshipDoom()
{
	glPushMatrix();
	float centerX = 0;
	float centerY = 30;
	float radiusX = 35;
	float radiusY = 50;
	glColor4f(0.7, 1, 1, 0.0011); // �at m�u cho nen cua h�nh
	glBegin(GL_POLYGON);	// Su dung GL_POLYGON thay v� GL_POINTS
	int rx = radiusX;
	int ry = radiusY;
	int rx2 = rx * rx;
	int ry2 = ry * ry;
	int twoRx2 = 2 * rx2;
	int twoRy2 = 2 * ry2;
	int p;
	int x = 0;
	int y = ry;
	int px = 0;
	int py = twoRx2 * y;
	// V�ng 1
	glVertex2f(centerX + x, centerY - y);
	glVertex2f(centerX - x, centerY - y);
	glVertex2f(centerX + x, centerY + y);
	glVertex2f(centerX - x, centerY + y);
	// V�ng 1
	p = round(ry2 - rx2 * ry + 0.25 * rx2);
	while (px < py)
	{
		x++;
		px += twoRy2;
		if (p < 0)
		{
			p += ry2 + px;
		}
		else
		{
			y--;
			py -= twoRx2;
			p += ry2 + px - py;
		}
		// T� m�u ph�a b�n trong c?a ellipse
		glVertex2f(centerX + x, centerY - y);
		glVertex2f(centerX - x, centerY - y);
		glVertex2f(centerX + x, centerY + y);
		glVertex2f(centerX - x, centerY + y);
	}
	// V�ng 2
	p = round(ry2 * (x + 0.5) * (x + 0.5) + rx2 * (y - 1) * (y - 1) - rx2 * ry2);
	while (y > 0)
	{
		y--;
		py -= twoRx2;
		if (p > 0)
		{
			p += rx2 - py;
		}
		else
		{
			x++;
			px += twoRy2;
			p += rx2 - py + px;
		}
		// T� m�u ph�a b�n trong c?a ellipse
		glVertex2f(centerX + x, centerY - y);
		glVertex2f(centerX - x, centerY - y);
		glVertex2f(centerX + x, centerY + y);
		glVertex2f(centerX - x, centerY + y);
	}

	glEnd();

	glPopMatrix();
}

// ve tia laze - bresenham duong thang
void DrawLaser(int x1, int y1, bool dir[])
{
	int x2 = -XMAX, y2 = y1;
	if (dir[0])
	{
		y2 = YMAX;
	}
	else if (dir[1])
	{
		y2 = -YMAX;
	}
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int x, y;
	int p = 2 * dy - dx;
	if (x1 > x2)
	{
		x = x2;
		y = y2;
		x2 = x1;
	}
	else
	{
		x = x1;
		y = y1;
	}
	// Set color and line width
	glLineWidth(5);
	glColor3f(1, 0, 0);
	glBegin(GL_POINTS);
	// Draw the first point
	glVertex2i(x, y);
	// Use Bresenham's algorithm to draw the line
	while (x < x2)
	{
		x++;
		if (p < 0)
		{
			p += 2 * dy;
		}
		else
		{
			y++;
			p += 2 * (dy - dx);
		}
		glVertex2i(x, y);
	}
	glEnd();
}

// ve con tau
void SpaceshipCreate(int x, int y, bool isPlayer1)
{
	glPushMatrix();
	glTranslated(x, y, 0);
	if (isPlayer1)
	{
		glRotatef(spaceshipRotation1, 0, 0, 1); // Quay Spaceship 1
	}
	else
	{
		glRotatef(spaceshipRotation2, 0, 0, 1); // Quay Spaceship 2
	}
	// if(!checkIfSpaceShipIsSafe() && alienLife1 ){
	// 	alienLife1-=10;
	// 	xStart -= 23;
	// }
	DrawSpaceshipDoom();
	glPushMatrix();
	glTranslated(4, 19, 0);
	DrawAlien(isPlayer1); // ve ng ngo�i h�nh tinh
	glPopMatrix();
	DrawSteeringWheel();	// ve b�nh l�i t�u
	DrawSpaceshipBody(isPlayer1); // goi ham ve phan body tau'
	// DrawSpaceShipLazer();
	// if(mButtonPressed) {
	// 	DrawLazerBeam();
	// }
	glEnd();
	glPopMatrix();
}
//
void DisplayHealthBar1()
{
	char temp1[40];
	glColor3f(1, 1, 1);
	sprintf(temp1, "  LIFE = %d", alienLife1);
	displayRasterText(-1100, 600, 0.4, temp1);
	glColor3f(1, 0, 0);
}

// ve hien thi Life=m�u
void DisplayHealthBar2()
{
	char temp2[40];
	glColor3f(1, 1, 1);
	sprintf(temp2, "  LIFE = %d", alienLife2);
	displayRasterText(800, 600, 0.4, temp2);
	glColor3f(1, 0, 0);
}

// ktra laze tr�ng kh
void checkLaserContact(int x, int y, bool dir[], int xp, int yp, bool player1)
{
	int xend = -XMAX, yend = y;
	xp += 8;
	yp += 8; // moving circle slightly up to fix laser issue
	if (dir[0])
		yend = YMAX;
	else if (dir[1])
		yend = -YMAX;

	// Here we find out if the laser(line) intersects with spaceship(circle)
	// by solving the equations for the same and finding the discriminant of the
	// quadratic equation obtained
	float m = (float)(yend - y) / (float)(xend - x);
	float k = y - m * x;
	int r = 50; // approx radius of the spaceship

	// calculating value of b, a, and c needed to find discriminant
	float b = 2 * xp - 2 * m * (k - yp);
	float a = 1 + m * m;
	float c = xp * xp + (k - yp) * (k - yp) - r * r;

	float d = (b * b - 4 * a * c); // discriminant for the equation
	printf("\nDisc: %f x: %d, y: %d, xp: %d, yp: %d", d, x, y, xp, yp);
	if (d >= 0)
	{
		if (player1)
			alienLife1 -= 5;
		else
			alienLife2 -= 5;

		printf("%d %d\n", alienLife1, alienLife2);
	}
}

void gameScreenDisplay()
{
	DisplayHealthBar1();
	DisplayHealthBar2();
	glScalef(2, 2, 0);

	glPushMatrix();				// phongto/thunho
	glScalef(alienScaleRatio, alienScaleRatio, 1.0f); // phongto/thunho

	if (alienLife1 > 0)
	{
		SpaceshipCreate(xOne, yOne, true);
		if (laser1)
		{
			DrawLaser(xOne, yOne, laser1Dir);
			checkLaserContact(xOne, yOne, laser1Dir, -xTwo, yTwo, true);
		}
	}
	else
	{
		viewPage = GAMEOVER;
	}

	if (alienLife2 > 0)
	{
		glPushMatrix();
		glScalef(-1, 1, 1);
		SpaceshipCreate(xTwo, yTwo, false);
		if (laser2)
		{
			DrawLaser(xTwo, yTwo, laser2Dir);
			checkLaserContact(xTwo, yTwo, laser2Dir, -xOne, yOne, false);
		}
		glPopMatrix();
	}
	else
	{
		viewPage = GAMEOVER;
	}
	glPopMatrix(); // Huy bo scaling �p dung cho vat the Alien

	if (viewPage == GAMEOVER)
	{
		xOne = xTwo = 500;
		yOne = yTwo = 0;
	}
}

// an n�t mui t�n l�n xu�ng ph�ng to/thu nho
void specialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		// Ph�ng to vat the Alien
		alienScaleRatio += 0.1f;
		break;
	case GLUT_KEY_DOWN:
		// Thu nho vat the Alien
		alienScaleRatio -= 0.1f;
		if (alienScaleRatio < 0.1f) // Dat gioi han toi thieu cho ty le
			alienScaleRatio = 0.1f;
		break;
	}

	// Kiem tra xem dang o trong trang thai GAME de ap dung ty le phong to/thu nho cho vat the Alien
	if (viewPage == GAME)
	{
		glutPostRedisplay();
	}
}

// hthi ai win
void displayGameOverMessage()
{
	glColor3f(1, 1, 0);
	char *message;
	if (alienLife1 > 0)
		message = "Game Over! Player 1 won the game";
	else
		message = "Game Over! Player 2 won the game";

	displayRasterText(-350, 600, 0.4, message);
}

// xu li cac n�t
void keyOperations()
{
	if (keyStates[13] == true && viewPage == INTRO)
	{
		viewPage = MENU;
		printf("view value changed to %d", viewPage);
		printf("enter key pressed\n");
	}
	if (viewPage == GAME)
	{
		laser1Dir[0] = laser1Dir[1] = false;
		laser2Dir[0] = laser2Dir[1] = false;
		if (keyStates['c'] == true)
		{
			laser2 = true;
			if (keyStates['w'] == true)
				laser2Dir[0] = true;
			if (keyStates['s'] == true)
				laser2Dir[1] = true;
		}
		else
		{
			laser2 = false;
			if (keyStates['d'] == true)
				xTwo -= SPACESHIP_SPEED;
			if (keyStates['a'] == true)
				xTwo += SPACESHIP_SPEED;
			if (keyStates['w'] == true)
				yTwo += SPACESHIP_SPEED;
			if (keyStates['s'] == true)
				yTwo -= SPACESHIP_SPEED;
		}

		if (keyStates['m'] == true)
		{
			laser1 = true;
			if (keyStates['i'] == true)
				laser1Dir[0] = true;
			if (keyStates['k'] == true)
				laser1Dir[1] = true;
		}
		else
		{
			laser1 = false;
			if (keyStates['l'] == true)
				xOne += SPACESHIP_SPEED;
			if (keyStates['j'] == true)
				xOne -= SPACESHIP_SPEED;
			if (keyStates['i'] == true)
				yOne += SPACESHIP_SPEED;
			if (keyStates['k'] == true)
				yOne -= SPACESHIP_SPEED;
		}
	}
}

void display()
{
	// glClearColor(, 0 , 0, 1);
	keyOperations();
	glClear(GL_COLOR_BUFFER_BIT);

	switch (viewPage)
	{
	case INTRO:
		introScreen();
		break;
	case MENU:
		startScreenDisplay();
		break;
	case INSTRUCTIONS:
		instructionsScreenDisplay();
		break;
	case GAME:
		gameScreenDisplay();
		// reset scaling values
		glScalef(1 / 2, 1 / 2, 0);
		break;
	case GAMEOVER:
		displayGameOverMessage();
		startScreenDisplay();
		break;
	}

	glFlush();
	glLoadIdentity();
	glutSwapBuffers();
}

// void reshape(GLint w, GLint h)
// {
// 	glViewport(0, 0, w, h);
// 	glMatrixMode(GL_PROJECTION);
// 	glLoadIdentity();
// 	if(h>w)
// 	{
// 		gluOrtho2D(0, 500, ((float)h/(float)w)*(0), ((float)h/(float)w)*500);
// 	}
// 	else
// 	{
// 		gluOrtho2D(((float)w/(float)h)*(0), ((float)w/(float)h)*(500), 0, 500);
// 	}
// 	glMatrixMode(GL_MODELVIEW);
// 	glutPostRedisplay();
// }

void passiveMotionFunc(int x, int y)
{

	// when mouse not clicked
	mouseX = float(x) / (m_viewport[2] / 1200.0) - 600.0; // converting screen resolution to ortho 2d spec
	mouseY = -(float(y) / (m_viewport[3] / 700.0) - 350.0);

	// Do calculations to find value of LaserAngle
	// somethingMovedRecalculateLaserAngle();
	glutPostRedisplay();
}

void mouseClick(int buttonPressed, int state, int x, int y)
{

	if (buttonPressed == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		mButtonPressed = true;
	else
		mButtonPressed = false;
	glutPostRedisplay();
}

void keyPressed(unsigned char key, int x, int y)
{
	keyStates[key] = true;

	switch (key)
	{
	case 'q':
		spaceshipRotation2 -= 5.0f; // Quay Spaceship 1 sang tr�i
		break;
	case 'e':
		spaceshipRotation2 += 5.0f; // Quay Spaceship 1 sang ph?i
		break;
	case 'u':
		spaceshipRotation1 += 5.0f; // Quay Spaceship 2 sang tr�i
		break;
	case 'o':
		spaceshipRotation1 -= 5.0f; // Quay Spaceship 2 sang ph?i
		break;
	}

	glutPostRedisplay();
}

void refresh()
{
	glutPostRedisplay();
}

void keyReleased(unsigned char key, int x, int y)
{
	keyStates[key] = false;
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1200, 600);
	glutCreateWindow("Space Shooter");
	init();
	// glutReshapeFunc(reshape);
	glutIdleFunc(refresh);
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyReleased);
	glutMouseFunc(mouseClick);
	glutPassiveMotionFunc(passiveMotionFunc);
	glutSpecialFunc(specialKeys); // �ang k� h�m specialKeys xu l� ph�m mui t�n
	glGetIntegerv(GL_VIEWPORT, m_viewport);
	glutDisplayFunc(display);
	glutMainLoop();
}
