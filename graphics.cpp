//============================================================================
// Name        : SmartDraw
// Author      : Muhammad Usman
// Copyright   : (c) Reserved
//============================================================================
#ifndef GRAPHICS_CPP
#define GRAPHICS_CPP
#define HEIGHT 700
#include "smartdraw.h"
#include <cmath>
#include <sys/wait.h>
#include <sys/types.h>
#include <stack>
using namespace std;
void SetCanvasSize(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode( GL_MODELVIEW);
	glLoadIdentity();
}
stack<List<Shape> > History;
List<Shape> shapes;
List<string> Names;
int x, y;
int mode, index = 0;
string inp;
int end1 = -1;
void Display()
{
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT); //Update the colors
	if (end1 != -1)
		cout << (shapes[end1].edges.size()) << endl;
	DrawString(465, 680, "Vertex", colors[BLUE]);
	DrawString(590, 680, "Edge", colors[BLUE]);
	DrawString(200, 680, "AddObject", colors[BLUE]);
	DrawString(350, 680, "Objects", colors[BLUE]);
	DrawString(590, 680, "Add Rectangle", colors[BLUE]);
	for (int i = 0; i < shapes.size(); ++i)
	{
		shapes[i].display();
	}
	DrawString(200, 660, inp.c_str(), colors[ORANGE]);
	glutSwapBuffers();

}

void NonPrintableKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/)
	{

	}
	else if (key == GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/)
	{

	}
	else if (key == GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/)
	{
	}

	else if (key == GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/)
	{

	}

}
void PrintableKeys(unsigned char key, int x, int y)
{
	if (((key > 64 && key < 91) || (key > 96 && key < 123)
			|| (key > 47 && key < 58) || key == 95) && mode == 0)
		inp += key;
	else if (mode == 0 && key == 13)
	{
		end1++;
		Shape s;
		shapes.push_back(s);
		Names.push_back(inp);
		inp.clear();
	}
	else if (key == 'b')
	{
		if (History.size() > 0)
		{
			shapes = History.top();
			History.pop();
		}
	}
	else if(key=='s')
	{
        writecode(shapes);
	}
	else if(key=='w')
	{
	    readcode(shapes);
	}
}
my_pair<int, int> last_vertex(-1, -1);
bool first_time = false;
void MouseClicked(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) // dealing only with left button
	{
		::x = x;
		::y = y;
		if (HEIGHT - y > 680 && x > 200 && x < 639)
			switchmode(x, mode, first_time);
		else if (mode == 2)
		{
			draw(mode, x, HEIGHT - y, index, shapes);
			History.push(shapes);
		}
		else if (mode == 3)
			last_vertex = get_least_dis(x, HEIGHT - y, shapes);
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (mode == 3 && first_time == false)
		{
			my_pair<int, int> p = get_least_dis(x, HEIGHT - y, shapes);
			if (!(p == last_vertex))
			{
				Edge E(last_vertex.second, p.second);
				shapes[last_vertex.first].AddEdge(E);
			}
			History.push(shapes);
		}
		first_time = false;
	}
	else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
	{

	}
}
/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m)
{

// implement your functionality here
	glutPostRedisplay();
// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(1000.0 / FPS, Timer, 0);
}

int main(int argc, char*argv[])
{

	glutInit(&argc, argv); // initialize the graphics library...
	int width = 1300, height = 700;
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("SmartDraw"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...
	glutDisplayFunc(Display); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	glutMouseFunc(MouseClicked);
	glutTimerFunc(1000.0 / FPS, Timer, 0);
	glutMainLoop();
	return 1;
}
#endif /* PACMAN_CPP_ */
