// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) CGV TU Dresden - All Rights Reserved

#include "Smoothing.h"

#include <random>
#include <iostream>
void SmoothUniformLaplacian(HEMesh& m, float lambda, unsigned int iterations)
{
	/*Task 1.2.4*/
	for (int i=0;i< iterations;i++) {
		for (auto v : m.vertices())
		{
			
			//std::cout << m.point(v) << std::endl;
			OpenMesh::Vec3f n;
			m.calc_vertex_normal_correct(v, n);
			m.point(v) = m.point(v) + lambda * n;

			//std::cout << m.point(v) << std::endl;
			
		}
	}

}

void AddNoise(HEMesh& m)
{
	std::mt19937 rnd;
	std::normal_distribution<float> dist;

	for (auto v : m.vertices())
	{
		OpenMesh::Vec3f n;
		m.calc_vertex_normal_correct(v, n); //normal scales with area
		float areaScale = n.norm();
		float lengthScale = sqrt(areaScale);
		n = lengthScale / areaScale * n;

		m.point(v) += 0.1f * dist(rnd) * n;
	}
}