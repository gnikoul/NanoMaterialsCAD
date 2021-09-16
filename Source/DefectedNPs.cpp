#include "stdafx.h"
#include "VSystem.h"
#include "DefectedNPs.h"

Group Icosahedral(float lattice_constant, int noshells)
{
	Group groupInit;
	groupInit.N_atoms = 0;

	lattice_constant = 1;
	noshells = 6;

	if (noshells < 1)
		return groupInit;

	int t = 0.5 + sqrt(5.0) / 2.0;

	jgn::vec3 verticies[12];
	verticies[0].x = t; verticies[0].y = 0.0; verticies[0].z = 1.0;
	verticies[1].x = t; verticies[1].y = 0.0; verticies[1].z = -1.0;
	verticies[2].x = -t; verticies[2].y = 0.0; verticies[2].z = 1.0;
	verticies[3].x = -t; verticies[3].y = 0.0; verticies[3].z = -1.0;
	verticies[4].x = 1; verticies[4].y = t; verticies[4].z = 0.0;
	verticies[5].x = -1; verticies[5].y = t; verticies[5].z = 0.0;
	verticies[6].x = 1; verticies[6].y = -t; verticies[6].z = 0.0;
	verticies[7].x = -1; verticies[7].y = -t; verticies[7].z = 0.0;
	verticies[8].x = 0; verticies[8].y = 1; verticies[8].z = t;
	verticies[9].x = 0; verticies[9].y = -1; verticies[9].z = t;
	verticies[10].x = 0; verticies[10].y = 1; verticies[10].z = -t;
	verticies[11].x = 0; verticies[11].y = -1; verticies[11].z = -t;



	for (int s = 1; s < noshells; s++)
	{
		//Construct square edges(6)
		for (int i = 0; i < 12; i = i + 2)
		{
			jgn::vec3 v1 = verticies[i];
			jgn::vec3 v2 = verticies[i + 1];
			for (int j = 0; j < s + 1; j++)
			{
				jgn::vec3 newpos = v1 * j + v2 * (s - j);
				groupInit.position.push_back(newpos);
				groupInit.N_atoms++;
			}
		}
		// Construct triangle planes(12)
		if (s > 1)
		{
			int map[12][2];
			map[0][0] = 8; map[0][1] = 9;
			map[1][0] = 10; map[1][1] = 11;
			map[2][0] = 8; map[2][1] = 9;
			map[3][0] = 10; map[3][1] = 11;
			map[4][0] = 0; map[4][1] = 1;
			map[5][0] = 2; map[5][1] = 3;
			map[6][0] = 0; map[6][1] = 1;
			map[7][0] = 2; map[7][1] = 3;
			map[8][0] = 4; map[8][1] = 5;
			map[9][0] = 6; map[9][1] = 7;
			map[10][0] = 4; map[10][1] = 5;
			map[11][0] = 6; map[11][1] = 7;
			for (int i = 0; i < 12; i++)
			{
				jgn::vec3 v0 = verticies[i] * s;
				jgn::vec3 v1 = verticies[map[i][0]] - verticies[i];
				jgn::vec3 v2 = verticies[map[i][1]] - verticies[i];
				for (int j = 0; j < s; j++)
				{
					for (int k = 0; k < s - j; k++)
					{
						if (j == 0 && k == 0)
							continue;
						jgn::vec3 newpos = v0 + v1 * j + v2 * k;
						groupInit.position.push_back(newpos);
						groupInit.N_atoms++;
					}
				}
			}
		}
		// Fill missing triangle planes(8)
		if (s > 2)
		{
			int map[4][4];
			map[0][0] = 9; map[0][1] = 6; map[0][2] = 8; map[0][3] = 4;
			map[1][0] = 11; map[1][1] = 6; map[1][2] = 10; map[1][3] = 4;
			map[2][0] = 9; map[2][1] = 7; map[2][2] = 8; map[2][3] = 5;
			map[3][0] = 11; map[3][1] = 7; map[3][2] = 10; map[3][3] = 5;
			for (i = 0; i < 4; i++)
			{
				jgn::vec3 v0 = verticies[i];
				jgn::vec3 v1 = verticies[map[i][0]] - verticies[i];
				jgn::vec3 v2 = verticies[map[i][1]] - verticies[i];
				jgn::vec3 v3 = verticies[map[i][2]] - verticies[i];
				jgn::vec3 v4 = verticies[map[i][3]] - verticies[i];
				for (j = 1; j < s; j++)
				{
					for (k = 1; k < s - j; k++)
					{
						jgn::vec3 newpos = v0 + v1 * j + v2 * k;
						groupInit.position.push_back(newpos);
						groupInit.N_atoms++;
						newpos = v0 + v3 * j + v4 * k;
						groupInit.position.push_back(newpos);
						groupInit.N_atoms++;
					}
				}
			}
		}
	}
	// Scale the positions
	float scaling_factor = lattice_constant / sqrt(2.0 * (1.0 + pow(t, 2)));
	for (int i = 0; i < groupInit.N_atoms; i++)
	{
		groupInit.position[i] = groupInit.position[i] * scaling_factor;
		std::cout << groupInit.position[i] << std::endl;
	}

	return groupInit;
}