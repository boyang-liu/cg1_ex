// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) CGV TU Dresden - All Rights Reserved

#include "SurfaceArea.h"

#include <iostream>

float ComputeSurfaceArea(const HEMesh& m)
{
	float area = 0;
	/* Task 1.2.2 */
	//std::cout << "Area computation is not implemented." << std::endl;
	HEMesh::FaceIter f_it,f_end(m.faces_end());
	//HEMesh::FaceHalfedgeIter fh_it;
	HEMesh::FaceVertexIter fv_it;
	const HEMesh::Point P;
	std::vector<HEMesh::Point> xPoints;


	for (f_it = m.faces_begin(); f_it != f_end; ++f_it){
		
		xPoints.clear();
		for (fv_it = m.cfv_iter(f_it); fv_it.is_valid(); ++fv_it) {
			const HEMesh::Point& Q = m.point(fv_it); 
			xPoints.push_back(Q);
			if(xPoints.size()>2)
			{
				const HEMesh::Point& A = xPoints[0];
				const HEMesh::Point& B = xPoints[xPoints.size() - 1];
				const HEMesh::Point& C = xPoints[xPoints.size() - 2];
				area += ((B - A) % (C - A)).norm() * 0.5f ;
				
			}					
		}			
	}	
	return area;
	
}