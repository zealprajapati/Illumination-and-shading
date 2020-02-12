//
//  data.h
//  IM project 3
//
//  Created by cpsfaculty on 10/25/14.
//  Copyright (c) 2014 ___Ju Shen___. All rights reserved.
//

#ifndef IM_project_3_data_h
#define IM_project_3_data_h


#endif

#include <iostream>
#ifdef WIN32
#include <windows.h>
#endif

#include <stdlib.h>
#include <iostream>
#include <fstream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#endif





struct Color {
	GLfloat channel[3];
};

struct Vertex {
	float x;
	float y;
	float z;

	Color c;

	float uni_x; //store the normalized value of this vector (for cos_theta and cross product use
	float uni_y;
	float uni_z;

	/*Normalize the vertex's vector to make the length equal to 1 and store it in uni_x,y,z*/
	void normalize()
	{
		float len = x * x + y * y + z * z;
		uni_x = x / sqrt(len);
		uni_y = y / sqrt(len);
		uni_z = z / sqrt(len);
	}

	/*Reload dot product */
	const float operator * (const Vertex& right) const
	{
		float result;

		/*implement here*/
		result = x * right.x+ y* right.y + z* right.z;

		return result;
	}


	/*Reload - operator*/
	const Vertex operator - (const Vertex& right) const
	{
		Vertex result;

		/*implement here*/
		result.x = x - right.x;
		result.y = y - right.y;
		result.z = z - right.z;

		return result;
	}




	float normDot(const Vertex& right) const
	{
		float result = uni_x * right.uni_x + uni_y * right.uni_y + uni_z * right.uni_z;
		return result;
	}
	/*The cross-product */
	Vertex cross(const Vertex& right)
	{
		Vertex result;

		/*implement here*/
		result.x = y * right.z - z * right.y;
		result.y = z * right.x - x * right.z;
		result.z = x * right.y - y * right.x;

		result.normalize();
		return result;
	}
};

struct Triangle {
	int v_idx[3];
	Color c[3];
};

/* Here you need to implement some operations for 4-by-1 vector*/
struct Vec {
	float elem[4];


};

/* Here you need to implement a 4-by-4 matrix */
struct Mat {
	float elem[4][4];


	/*Normalize the matrix*/
	void eye()
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (i == j)
					elem[i][j] = 1.0f;
				else
					elem[i][j] = 0.0f;
			}
		}
	}

	/*This function is to reload the multipliation operator for matrix products*/
	const Mat operator * (const Mat& right) const
	{
		Mat result;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				result.elem[i][j] = 0;
				for (int k = 0; k < 4; k++)
				{
					result.elem[i][j] += elem[i][k] * right.elem[k][j];
				}
			}
		}

		return result;
	}

	/*This function is to reload the multipliation operator for matrix times a 4-by-1 vector*/
	const Vec operator * (const Vec& vec) const
	{
		Vec result;

		for (int i = 0; i < 4; i++)
		{

			result.elem[i] = 0;
			for (int k = 0; k < 4; k++)
			{
				result.elem[i] += elem[i][k] * vec.elem[k];
			}

		}

		return result;
	}

	void printMat()
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				printf("%.5f, ", elem[i][j]);
			}
			printf("\n");
		}
	}
};


vector<Vertex> vertice_list;
vector<Triangle> triangles_list;

/*Define the light and colors*/
Vertex light;
Color ambient_color;
Color bunny_color;
Color phong_color;
Vertex view_pos;



float p = 50;
/*Parameter control the rotation*/
float theta_x = .0f;
float theta_y = .0f;
float theta_z = .0f;

/*Parameter control the translation*/
float translate_x = .0f;
float translate_y = .0f;
float translate_z = .0f;


int mesh_only = 0; //control whether a mesh triangle or plane is drawn
int shading_type = 0; //0 - no shading; 1 - flat shading; 2 - Gauround Shading


/*For the mouse control use*/
/* Define data */
int mouse_down = 0; //Represent the left mouse key is clicked down
int change_mode = 0; //0 means rotation; 1 means translation
int current_x = 0, current_y = 0;
