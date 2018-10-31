#include "stdafx.h"
#include "JGN_SolidSphere.h"


void JGN_SolidSphere(float radius, int numStacks, int numSides)
{
	//numStacks = 2;
	//numSides = 3;


	//glScalef(0.2*radius / CONST_COE, 0.2*radius / CONST_COE, 0.2*radius / CONST_COE);

	//    vec3 points[sides * (sides-1)];
	GLfloat curRadius, curTheta, curRho, deltaTheta, deltaRho, curX, curY, curZ;
	int curStack, curSlice;
	const int numVerts = (numStacks - 1)*numSides;
	float v[3];
	int curVert = 0;
	int t;

	deltaTheta = (2 * M_PI) / numSides;
	deltaRho = M_PI / numStacks;

	for (curStack = 1; curStack < numStacks; curStack++)
	{
		curRho = (3.141 / 2.0) - curStack * deltaRho;
		curY = sin(curRho) * radius;
		curRadius = cos(curRho) * radius;
		for (curSlice = 0; curSlice < numSides; curSlice++)
		{
			curTheta = curSlice * deltaTheta;
			curX = curRadius * cos(curTheta);
			curZ = -curRadius * sin(curTheta);
			points[curVert++] = vec3{ curX,curY,curZ };
		}
	}
	// option 1 - points only
	/*
	glBegin(GL_POINTS);
	glNormal3d(0,1,0);
	glVertex3d(0,radius,0);
	for (t=0; t<numVerts; t++)
	{
	curX = points[t].x;
	curY = points[t].y;
	curZ = points[t].z;
	glNormal3d(curX, curY, curZ);
	glVertex3d(curX, curY, curZ);
	}
	glNormal3d(0,-1,0);
	glVertex3d(0,-radius,0);
	glEnd();
	*/

	///////////////////////////////
	// option 2 - solid
	///////////////////////////////
	// part A - draw the top 'lid' (tris)
	//glBegin(GL_POLYGON);

	glBegin(GL_TRIANGLE_FAN);

	glNormal3d(0, 1, 0);
	glVertex3d(0, radius, 0);

	for (int t = 0; t < numSides; t++)
	{
		v[0] = points[t].x;
		v[1] = points[t].y;
		v[2] = points[t].z;
		glNormal3dv(v);
		glVertex3dv(v);
	}
	v[0] = points[0].x;
	v[1] = points[0].y;
	v[2] = points[0].z;
	glNormal3dv(v);
	glVertex3dv(v);
	glEnd();

	// part B - draw the 'sides' (quads)
	int vertIndex;
	for (int curStack = 0; curStack < numStacks - 2; curStack++)
	{
		vertIndex = curStack * numSides;
		glBegin(GL_QUAD_STRIP);

		for (int curSlice = 0; curSlice < numSides; curSlice++)
		{
			v[0] = points[vertIndex + curSlice].x;
			v[1] = points[vertIndex + curSlice].y;
			v[2] = points[vertIndex + curSlice].z;
			glNormal3dv((GLdouble*)v);
			glVertex3dv(v);

			v[0] = points[vertIndex + numSides + curSlice].x;
			v[1] = points[vertIndex + numSides + curSlice].y;
			v[2] = points[vertIndex + numSides + curSlice].z;

			glNormal3dv((GLdouble*)v);
			glVertex3dv(v);
		}
		glNormal3d(points[vertIndex].x, points[vertIndex].y, points[vertIndex].z);
		glVertex3d(points[vertIndex].x, points[vertIndex].y, points[vertIndex].z);
		glNormal3d(points[vertIndex + numSides].x, points[vertIndex + numSides].y, points[vertIndex + numSides].z);
		glVertex3d(points[vertIndex + numSides].x, points[vertIndex + numSides].y, points[vertIndex + numSides].z);
		glEnd();
	}

	// part C - draw the bottom 'lid' (tris)
	glBegin(GL_TRIANGLE_FAN);
	//glBegin(GL_POLYGON);
	glNormal3d(0, -1, 0);
	glVertex3d(0, -radius, 0);


	for (int t = 0; t < numSides - 1; t++)
		//		for (t = 0; t<8; t++)

	{

		curX = points[numVerts - 1 - t].x;
		curY = points[numVerts - 1 - t].y;
		curZ = points[numVerts - 1 - t].z;
		glNormal3d(curX, curY, curZ);
		glVertex3d(curX, curY, curZ);

	}

	glNormal3d(points[(numStacks - 2)*numSides].x, points[(numStacks - 2)*numSides].y, points[(numStacks - 2)*numSides].z);
	glVertex3d(points[(numStacks - 2)*numSides].x, points[(numStacks - 2)*numSides].y, points[(numStacks - 2)*numSides].z);


	curX = points[numVerts - 1].x;
	curY = points[numVerts - 1].y;
	curZ = points[numVerts - 1].z;
	glNormal3d(curX, curY, curZ);
	glVertex3d(curX, curY, curZ);
	glEnd();

	//glScalef(5 * CONST_COE / radius, 5 * CONST_COE / radius, 5 * CONST_COE / radius);

}

/////////////////////////////////////////////////



void JGN_SolidSphereFpsCalibration()
{
	if (cl_duration.count() > 2)
	{

		sphStacks -= 100;
		sphSides -= 100;

		int c = 0;

		if (sphStacks < 2)
		{
			sphStacks = 2;
			c++;
		}
		if (sphSides < 3)
		{
			sphSides = 3;
			c++;
		}
		if (c == 2)
		{
			sph_pnt_flag++;
			if (sph_pnt_flag >= 2)
			{
				shperes_on = 0;
				glDisable(GL_LIGHTING);
			}

			return;
		}

		JGN_QRedisplay();

	}
	else if (cl_duration.count() > 0.5)
	{

		sphStacks -= 60;
		sphSides -= 60;


		int c = 0;

		if (sphStacks < 2)
		{
			sphStacks = 2;
			c++;
		}
		if (sphSides < 3)
		{
			sphSides = 3;
			c++;
		}
		if (c == 2)
		{
			sph_pnt_flag++;
			if (sph_pnt_flag >= 2)
			{
				shperes_on = 0;
				glDisable(GL_LIGHTING);
			}


			return;
		}

		JGN_QRedisplay();

	}
	else if (cl_duration.count() > 0.06)
	{

		sphStacks -= 30;
		sphSides -= 30;


		int c = 0;

		if (sphStacks < 2)
		{
			sphStacks = 2;
			c++;
		}
		if (sphSides < 3)
		{
			sphSides = 3;
			c++;
		}
		if (c == 2)
		{
			sph_pnt_flag++;
			if (sph_pnt_flag >= 2)
			{
				shperes_on = 0;
				glDisable(GL_LIGHTING);
			}

			return;
		}

		JGN_QRedisplay();

	}
	else if (cl_duration.count() < 0.03)
	{

		if (shperes_on == 0 && cl_duration.count() < 0.015)
		{
			shperes_on = 1;
			sphStacks = 2;
			sphSides = 3;
			glEnable(GL_LIGHTING);

		}
		else
		{
			sph_pnt_flag = 0;
			(sphStacks < sphSides) ? sphStacks++ : sphSides++;

			if (sphStacks > 100)
			{
				sphStacks = 100;
				return;

			}
			if (sphSides > 100)
			{
				sphSides = 100;
				return;

			}
		}

		//JGN_QRedisplay();

	}
}