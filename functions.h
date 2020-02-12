//
//  functions.h
//  IM project 3
//
//  Created by cpsfaculty on 10/25/14.
//  Copyright (c) 2014 ___Ju Shen___. All rights reserved.
//

#ifndef IM_project_3_functions_h
#define IM_project_3_functions_h


#endif

#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

inline double to_int(std::string const& str) {
	std::istringstream ss(str);

	int d;
	ss >> d;

	/* eat up trailing whitespace if there was a double read, and ensure
	 * there is no character left. the eof bit is set in the case that
	 * `std::ws` tried to read beyond the stream. */
	if (!(ss && (ss >> std::ws).eof()))
		exit(1);

	return d;
}

inline float to_float(std::string const& str) {
	std::istringstream ss(str);

	float f;
	ss >> f;

	/* eat up trailing whitespace if there was a double read, and ensure
	 * there is no character left. the eof bit is set in the case that
	 * `std::ws` tried to read beyond the stream. */
	if (!(ss && (ss >> std::ws).eof()))
		exit(1);

	return f;
}


inline char* to_char(string s)
{
	char *a = new char[s.size() + 1];
	a[s.size()] = 0;
	memcpy(a, s.c_str(), s.size());
	return a;
}


void transformTriangles()
{
	/*Initialize the rotation matrix*/
	Mat Rx, Ry, Rz;
	Mat T;

	/*Initially set all the matrix to */
	Rx.eye();
	Ry.eye();
	Rz.eye();
	T.eye();

	/*rotation matrix about x axis */
	Rx.elem[1][1] = cos(theta_x);
	Rx.elem[1][2] = -sin(theta_x);
	Rx.elem[2][1] = sin(theta_x);
	Rx.elem[2][2] = cos(theta_x);


	/*rotation matrix about y axis */
	Ry.elem[0][0] = cos(theta_y);
	Ry.elem[0][2] = sin(theta_y);
	Ry.elem[2][0] = -sin(theta_y);
	Ry.elem[2][2] = cos(theta_y);

	/* transaltion matrix*/
	T.elem[0][3] = translate_x;
	T.elem[1][3] = translate_y;


	/*Final transformation matrix P*/
	Mat P = T * Rx * Ry;

	/* Go through each vertex*/
	for (int i = 0; i < vertice_list.size(); i++)
	{
		Vec cur_pt, updated_pt;
		cur_pt.elem[0] = vertice_list[i].x;
		cur_pt.elem[1] = vertice_list[i].y;
		cur_pt.elem[2] = vertice_list[i].z;
		cur_pt.elem[3] = 1.0f;
		updated_pt = P * cur_pt;
		vertice_list[i].x = updated_pt.elem[0] / updated_pt.elem[3];
		vertice_list[i].y = updated_pt.elem[1] / updated_pt.elem[3];
		vertice_list[i].z = updated_pt.elem[2] / updated_pt.elem[3];

		vertice_list[i].normalize();
	}

	/*Reset the angles and translations */
	theta_x = 0;
	theta_y = 0;
	theta_z = 0;
	translate_x = 0;
	translate_y = 0;
	translate_z = 0;
}

void normalComputation()
{

}


/*Do the shading on each triangle*/
void trianglesShading()
{
	if (shading_type == 0)
	{
		/*Make all the triangles the same color*/
		for (int i = 0; i < triangles_list.size(); i++) //triangle index
		{
			for (int j = 0; j < 3; j++) //vertex index
			{
				for (int k = 0; k < 3; k++) //color channel index
				{
					triangles_list[i].c[j].channel[k] = 0.5;

				}
			}
		}
	}
	else if (shading_type == 1) //flat shading without phong term
	{
		for (int i = 0; i < triangles_list.size(); i++)
		{
			Vertex vec1 = vertice_list[triangles_list[i].v_idx[1]] - vertice_list[triangles_list[i].v_idx[0]];
			Vertex vec2 = vertice_list[triangles_list[i].v_idx[2]] - vertice_list[triangles_list[i].v_idx[0]];
			Vertex n = vec1.cross(vec2);
			n.normalize();
			Vertex l = light - vertice_list[triangles_list[i].v_idx[0]];
			l.normalize();
			float cos_theta = n.normDot(l);

			

			if (cos_theta < 0.0f)
				cos_theta = 0.0f;

		triangles_list[i].c[0].channel[0] =  light.c.channel[0] * bunny_color.channel[0] * cos_theta + ambient_color.channel[0] * bunny_color.channel[0];
		triangles_list[i].c[0].channel[1] = light.c.channel[1] * bunny_color.channel[1] * cos_theta + ambient_color.channel[1] * bunny_color.channel[1];
		triangles_list[i].c[0].channel[2] = light.c.channel[2] * bunny_color.channel[2] * cos_theta + ambient_color.channel[2] * bunny_color.channel[2];

		l = light - vertice_list[triangles_list[i].v_idx[1]];
		l.normalize();
		 cos_theta = n.normDot(l);

		 

		if (cos_theta < 0.0f)
			cos_theta = 0.0f;

		triangles_list[i].c[1].channel[0] = light.c.channel[0] * bunny_color.channel[0] * cos_theta + ambient_color.channel[0] * bunny_color.channel[0];
		triangles_list[i].c[1].channel[1] = light.c.channel[1] * bunny_color.channel[1] * cos_theta + ambient_color.channel[1] * bunny_color.channel[1];
		triangles_list[i].c[1].channel[2] = light.c.channel[2] * bunny_color.channel[2] * cos_theta + ambient_color.channel[2] * bunny_color.channel[2];
		
		
		l = light - vertice_list[triangles_list[i].v_idx[2]];
		l.normalize();
	 cos_theta = n.normDot(l);

		 

		if (cos_theta < 0.0f)
			cos_theta = 0.0f;

		triangles_list[i].c[2].channel[0] = light.c.channel[0] * bunny_color.channel[0] * cos_theta + ambient_color.channel[0] * bunny_color.channel[0];
		triangles_list[i].c[2].channel[1] = light.c.channel[1] * bunny_color.channel[1] * cos_theta + ambient_color.channel[1] * bunny_color.channel[1];
		triangles_list[i].c[2].channel[2] = light.c.channel[2] * bunny_color.channel[2] * cos_theta + ambient_color.channel[2] * bunny_color.channel[2];

		
		}
	}
	else if (shading_type == 2) //flat shading with phong term
	{
	for (int i = 0; i < triangles_list.size(); i++)
	{
		Vertex vec1 = vertice_list[triangles_list[i].v_idx[1]] - vertice_list[triangles_list[i].v_idx[0]];
		Vertex vec2 = vertice_list[triangles_list[i].v_idx[2]] - vertice_list[triangles_list[i].v_idx[0]];
		Vertex n = vec1.cross(vec2);
		n.normalize();
		Vertex l = light - vertice_list[triangles_list[i].v_idx[0]];
		l.normalize();
		float cos_theta = n.normDot(l);

	Vertex v = view_pos - vertice_list[triangles_list[i].v_idx[0]];
	
		
		v.normalize();


		Vertex r;
		r.x = n.x * 2.0f * cos_theta - l.x;
		r.y = n.y* 2.0f * cos_theta - l.y;
		r.z = n.z * 2.0f * cos_theta - l.z;
		r.normalize();

		float cos_beta= 0.0;
		float cos_alpha=0.0;
		if (l.normDot(n) > 0)
		{
			cos_theta = l.normDot(n);
		}
		if (v.normDot(r) > 0)
		{
			cos_alpha= v.normDot(r);
		}
		cos_alpha= pow(cos_alpha, p);


		 

		triangles_list[i].c[0].channel[0] = bunny_color.channel[0] * ambient_color.channel[0] +  bunny_color.channel[0] * cos_beta + phong_color.channel[0] * cos_alpha;
		triangles_list[i].c[0].channel[1] = bunny_color.channel[1] * ambient_color.channel[1] +  bunny_color.channel[1] * cos_beta + phong_color.channel[1] * cos_alpha;
		triangles_list[i].c[0].channel[2] = bunny_color.channel[2] * ambient_color.channel[2] +  bunny_color.channel[2] * cos_beta + phong_color.channel[2] * cos_alpha;

		l = light - vertice_list[triangles_list[i].v_idx[1]];
		l.normalize();
		 cos_theta = n.normDot(l);

		 v = view_pos - vertice_list[triangles_list[i].v_idx[1]];
		v.normalize();
	

		
		r.x = n.x * 2.0f * cos_theta - l.x;
		r.y = n.y * 2.0f * cos_theta - l.y;
		r.z = n.z* 2.0f * cos_theta - l.z;
		r.normalize();

		
		if (l.normDot(n) > 0)
		{
			cos_beta = l.normDot(n);
		}
		if (v.normDot(r) > 0)
		{
			cos_alpha = v.normDot(r);
		}
		cos_alpha = pow(cos_alpha, p);
		triangles_list[i].c[1].channel[0] = bunny_color.channel[0] * ambient_color.channel[0] +  bunny_color.channel[0] * cos_beta + phong_color.channel[0] * cos_alpha;
		triangles_list[i].c[1].channel[1] = bunny_color.channel[1] * ambient_color.channel[1] +  bunny_color.channel[1] * cos_beta + phong_color.channel[1] * cos_alpha;
		triangles_list[i].c[1].channel[2] = bunny_color.channel[2] * ambient_color.channel[2] +  bunny_color.channel[2] * cos_beta + phong_color.channel[2] * cos_alpha;


		l = light - vertice_list[triangles_list[i].v_idx[2]];
		l.normalize();
		 cos_theta = n.normDot(l);

		 v = view_pos - vertice_list[triangles_list[i].v_idx[2]];
		v.normalize();


		
		r.x = n.x * 2.0f * cos_theta - l.x;
		r.y = n.y* 2.0f * cos_theta - l.y;
		r.z = n.z * 2.0f * cos_theta - l.z;
		r.normalize();

		if (l.normDot(n) > 0)
		{
			cos_beta= l.normDot(n);
		}
		if (v.normDot(r) > 0)
		{
			cos_alpha = v.normDot(r);
		}
		cos_alpha = pow(cos_alpha, p);
		triangles_list[i].c[1].channel[0] = bunny_color.channel[0] * ambient_color.channel[0] +  bunny_color.channel[0] * cos_beta + phong_color.channel[0] * cos_alpha;
		triangles_list[i].c[1].channel[1] = bunny_color.channel[1] * ambient_color.channel[1] + bunny_color.channel[1] * cos_beta+ phong_color.channel[1] * cos_alpha;
		triangles_list[i].c[1].channel[2] = bunny_color.channel[2] * ambient_color.channel[2] +  bunny_color.channel[2] * cos_beta + phong_color.channel[2] * cos_alpha;

	

	}
	}
}

void initialize()
{
	light.x = 0;
	light.y = 2;
	light.z = 5;
	light.c.channel[0] = 0.8;
	light.c.channel[1] = 0.8;
	light.c.channel[2] = 0.8;

	light.normalize();

	light.c.channel[0] = 0.9;
	light.c.channel[1] = 0.9;
	light.c.channel[2] = 0.9;

	ambient_color.channel[0] = 0.2;
	ambient_color.channel[1] = 0.2;
	ambient_color.channel[2] = 0.2;

	bunny_color.channel[0] = 0.5;
	bunny_color.channel[1] = 0.5;
	bunny_color.channel[2] = 0.5;

	phong_color.channel[0] = 0.9;
	phong_color.channel[0] = 0.7;
	phong_color.channel[0] = 0.1;

}

void loadObjFiles(const char *filename, vector<Vertex> &vertice_list, vector<Triangle> &triangles_list)
{
	ifstream myfile(filename);
	string line;
	string valueX, valueY, valueZ, v;
	string idx0, idx1, idx2, f;

	int n = 0;
	while (!myfile.eof())
	{
		getline(myfile, line);
		if (line[0] == 'v')
		{
			std::istringstream iss(line);
			iss >> v >> valueX >> valueY >> valueZ;
			Vertex v;
			v.x = (GLfloat)to_float(valueX);
			v.y = (GLfloat)to_float(valueY);
			v.z = (GLfloat)to_float(valueZ);
			// v.normalize();


			 /* By default, the initial colors for all the vertices are grey */
			for (int c = 0; c < 3; c++)
			{
				v.c.channel[c] = 0.5;
			}
			vertice_list.push_back(v);
		}
		if (line[0] == 'f')
		{
			std::istringstream iss(line);
			iss >> f >> idx0 >> idx1 >> idx2;
			int i0 = to_int(idx0) - 1;
			int i1 = to_int(idx1) - 1;
			int i2 = to_int(idx2) - 1;

			Triangle triangle;
			triangle.v_idx[0] = i0;
			triangle.v_idx[1] = i1;
			triangle.v_idx[2] = i2;

			triangle.c[0] = vertice_list[i0].c;
			triangle.c[1] = vertice_list[i1].c;
			triangle.c[2] = vertice_list[i2].c;
			triangles_list.push_back(triangle);
		}
	}


	/* Check what is the centroid value */
	float x = .0f;
	float y = .0f;
	float z = .0f;
	for (int i = 0; i < vertice_list.size(); i++)
	{
		x += vertice_list[i].x;
		y += vertice_list[i].y;
		z += vertice_list[i].z;
	}
	x /= (float)vertice_list.size();
	y /= (float)vertice_list.size();
	z /= (float)vertice_list.size();
	printf("center: %.5f, %.5f, %.5f\n", x, y, z);
}