// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) CGV TU Dresden - All Rights Reserved

#include "Volume.h"

#include <iostream>






float ComputeVolume(const HEMesh& m)
{
	float vol = 0;
	/*Task 1.2.2*/
	//std::cout << "Volume calculation is not implemented." << std::endl;



	
	HEMesh::FaceIter f_it, f_end(m.faces_end());	
	HEMesh::FaceVertexIter fv_it;
	const HEMesh::Point P;
	std::vector<HEMesh::Point> xPoints;
	HEMesh::Normal N;
	int aa = 0;
	for (f_it = m.faces_begin(); f_it != f_end; ++f_it) {
		xPoints.clear();
		
		
		HEMesh::FaceHandle fn = m.face_handle(aa);	
		N = m.calc_face_normal(fn);
		//std::cout << N << std::endl;
		aa++;
		
		
		for (fv_it = m.cfv_iter(f_it); fv_it.is_valid(); ++fv_it) {
			const HEMesh::Point& Q = m.point(fv_it);
			xPoints.push_back(Q);

			


			if (xPoints.size() > 2)
			{	
				float area = 0;
				float h = 0;
				const HEMesh::Point& A = xPoints[0];
				const HEMesh::Point& B = xPoints[xPoints.size() - 1];
				const HEMesh::Point& C = xPoints[xPoints.size() - 2];
				area = ((B - A) % (C - A)).norm() * 0.5f;
				h = (N | A);
				
				
			
				vol += h*area/3;
				
			}
		}
	}





	return vol;
}