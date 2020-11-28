// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) CGV TU Dresden - All Rights Reserved

#include "Smoothing.h"

#include <random>
#include <iostream>
void SmoothUniformLaplacian(HEMesh& m, float lambda, unsigned int iterations)
{
	/*Task 1.2.4*/
	//for (int i=0;i< iterations;i++) {}
	for (int iter = 0; iter < iterations; iter++) {
		
		std::vector<OpenMesh::Vec3f> v_new;

		int qqq = 0;
		

		for (auto v : m.vertices())
		{
			if (qqq<3){
			

				std::vector<HEMesh::VertexHandle> v_vh;
				//std::cout << m.point(v) << std::endl;
				std::vector<HEMesh::HalfedgeHandle> v_hh;
				GetNeighborVertices(m, v, v_vh, v_hh);
				//std::cout << v_vh.size() << std::endl;
				float Ai = 0;
				OpenMesh::Vec3f sum2(0.0, 0.0, 0.0);
				OpenMesh::Vec3f sum;
				for (int i = 0; i < v_vh.size(); i++)
				{
					OpenMesh::Vec3f pij = m.point(v) - m.point(v_vh[i]);
					float pij_L = pij.length()*pij.length();

					HEMesh::HalfedgeHandle hh1, hh2, hh3, hh4;
					hh1 = m.prev_halfedge_handle(v_hh[i]);
					hh2 = m.opposite_halfedge_handle(hh1);
					hh3 = m.opposite_halfedge_handle(v_hh[i]);
					hh4 = m.next_halfedge_handle(hh3);
					int a, b;
					for (int j = 0; j < v_vh.size(); j++)
					{

						if (hh4.idx() == v_hh[j].idx())
						{
							a = j;
						}
						if (hh2.idx() == v_hh[j].idx())
						{
							b = j;
						}

					}
					

					HEMesh::Point vi = m.point(v);
					HEMesh::Point vj = m.point(v_vh[i]);
					HEMesh::Point v1 = m.point(v_vh[a]);
					HEMesh::Point v2 = m.point(v_vh[b]);
					float cosaij = ((vj - v1) | (vi - v1)) / ((vj - v1).length()*(vi - v1).length());
					float sinaij = ((vj - v1) % (vi - v1)).length() / ((vj - v1).length()*(vi - v1).length());
					float cotaij = cosaij / sinaij;

					float cosbij = ((vj - v2) | (vi - v2)) / ((vj - v2).length()*(vi - v2).length());
					float sinbij = ((vj - v2) % (vi - v2)).length() / ((vj - v2).length()*(vi - v2).length());
					float cotbij = cosbij / sinbij;
					

					std::cout << "cotaij:" << cotaij << std::endl;
					std::cout << "cotbij:" << cotbij << std::endl;

					
					Ai = Ai + (cotaij + cotbij)*pij_L;
					sum2 = sum2 +((cotaij + cotbij)* (vj - vi));

					std::cout << "(cotaij + cotbij)*pij_L:" << (cotaij + cotbij)*pij_L << std::endl;
					std::cout << "(cotaij + cotbij)*(vj - vi):" << (cotaij + cotbij)*(vj - vi) << std::endl;
					std::cout << "vi:" << vi << std::endl;
					std::cout << "vj:" << vj << std::endl;
					


				}
				std::cout << "==========" << std::endl;
				Ai = Ai * 0.125;
				std::cout << "sum2:" << sum2 << std::endl;
				std::cout << "(2 * Ai):" << (2 * Ai) << std::endl;
				sum = sum2 / (2 * Ai);

				v_new.push_back(lambda * sum);
				
				std::cout << "Ai:" << Ai << std::endl;
				std::cout << "sum:" << sum2 << std::endl;
				std::cout << "sfi:" << sum << std::endl;
				std::cout << "lambdasfi:" << v_new[v_new.size()-1] << std::endl;
				//std::cout << cotbij << std::endl;
				//std::cout << v.idx()<< std::endl;
				std::cout << "----------" << std::endl;
			qqq++;
		}
		
		}
		int k = 0;
		
		for (auto v : m.vertices()){
			if(qqq!=0){
			//std::cout << m.point(v) << std::endl;
			m.point(v) = m.point(v)+ v_new[k];
			k++;
			std::cout << "newpos:" << m.point(v) << std::endl;
			qqq--;
			}
		}
	}
	


}
void GetNeighborVertices(HEMesh& m,HEMesh::VertexHandle vh,std::vector<HEMesh::VertexHandle> &v_vh, std::vector<HEMesh::HalfedgeHandle> &v_hh) {

	
	
	for (auto h : m.halfedges()) 
	{
		if (h.from() == vh)//||v.from() == vh
		{
			
			v_vh.push_back(h.to());
			v_hh.push_back(h);
			
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