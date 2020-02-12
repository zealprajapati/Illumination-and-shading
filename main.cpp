//
//  main.cpp
//  IM project 3
//
//  Created by cpsfaculty on 10/25/14.
//  Copyright (c) 2014 ___Ju Shen___. All rights reserved.
//

#include <iostream>
#ifdef WIN32
#include <windows.h>
#endif

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#endif

using namespace std;

#include "data.h"
#include "functions.h"
#include "callbackFunctions.h"

int main(int argc, char * argv[]) {
	

	


	/*Initialize glut stuff*/
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("Bunny");
	loadObjFiles("bunny_low.obj", vertice_list, triangles_list);
	initialize();



	/*Initialize gl stuff*/
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-0.4, 0.4, -0.4 * .48 / .64, 0.4 * .48 / .64, 2, 10); //parallel projection
	gluLookAt(0, 0, 5, 0, 0.2, 0, 0, 1, 0);


	/*Register GL stuff with the GLUT*/
	glutDisplayFunc(onDisplay);
	glutMouseFunc(onMouse);
	glutMotionFunc(onMouseMotion);
	glutKeyboardFunc(onKeyboard);



	/*debug use */
	Mat a, b;
	Vec v1, v2;
	a.elem[0][0] = 3;
	a.elem[0][1] = 2;
	a.elem[0][2] = 4;
	a.elem[0][3] = 7;

	a.elem[1][0] = 2;
	a.elem[1][1] = 1;
	a.elem[1][2] = 5;
	a.elem[1][3] = 2;


	a.elem[2][0] = -2;
	a.elem[2][1] = 9;
	a.elem[2][2] = 12;
	a.elem[2][3] = 11;


	a.elem[3][0] = 33;
	a.elem[3][1] = 44;
	a.elem[3][2] = 55;
	a.elem[3][3] = 66;


	v1.elem[0] = 8;
	v1.elem[1] = 2;
	v1.elem[2] = 9;
	v1.elem[3] = 10;



	v2 = a * v1;




	/*Initialize the loop*/
	glutMainLoop();




	return 0;
}
