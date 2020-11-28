// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) CGV TU Dresden - All Rights Reserved

#include "Stripification.h"

#include <random>
#include "sample_set.h"
#include <chrono>
#include <iostream>


unsigned int ExtractTriStrips(HEMesh& mesh, OpenMesh::FPropHandleT<int> perFaceStripIdProperty, unsigned int nTrials)
{
	//prepare random engine
	int nStrips = 0;
	std::mt19937 eng;
	int k = 5;
	//initialize strip index to -1 for each face
	int total = 0;
	for (auto f : mesh.faces())
	{
		mesh.property(perFaceStripIdProperty, f) = -1;
		total++;
	}
	/*Task 1.2.5*/
	sample_set<int> my_set;
	my_set.reserve(total);
	for (int i = 0; i < total; i++)
	{
		my_set.insert(i);
	}

	int length=0;
	int length_new=0;
	std::vector<int> face_id;
	std::vector<int> face_id_new;
	int total_num = 0;
	int mesh_property = 0;
//my_set.remove(rand_elem1);
	while (my_set.size()!=0)
	{

	
	for(int i=0;i<k;i++)
	{
			int rand_elem1 = my_set.sample(eng);
		
			auto f = mesh.face_handle(rand_elem1);			
			HEMesh::FaceIter f_it= mesh.faces_begin(), f_end(mesh.faces_end());;
			for (int ii = 0; ii < rand_elem1; ii++)
			{
				f_it++;
			}		
			HEMesh::FaceHalfedgeIter fh_it;
			fh_it = mesh.fh_iter(f_it);	
			HEMesh::HalfedgeHandle& e = fh_it.handle();
			HEMesh::HalfedgeHandle& e211 = fh_it.handle();
			HEMesh::HalfedgeHandle& e2 = mesh.next_halfedge_handle(e211);
			HEMesh::HalfedgeHandle& e311 = fh_it.handle();
			HEMesh::HalfedgeHandle& e3 = mesh.next_halfedge_handle(e311);
			HEMesh::FaceHandle& first = mesh.face_handle(e);
			length_new++;
			face_id_new.push_back(first.idx());

			for(int m=0;m<20;m++)
			{
				HEMesh::HalfedgeHandle& e_next_1=mesh.next_halfedge_handle(e2);
				HEMesh::HalfedgeHandle& e_inv_1 = mesh.opposite_halfedge_handle(e_next_1);
				if (mesh.is_boundary(e_inv_1))
					break;
				HEMesh::FaceHandle& f_next_1 = mesh.face_handle(e_inv_1);
				if (mesh.property(perFaceStripIdProperty, f_next_1) != -1)
					break;
				else
				{
				length_new++;
				face_id_new.push_back(f_next_1.idx());
				}

				

				e2 = e_inv_1;


				HEMesh::HalfedgeHandle& e_next_2 = mesh.next_halfedge_handle(e2);
				HEMesh::HalfedgeHandle& e_next_21 = mesh.next_halfedge_handle(e_next_2);
				HEMesh::HalfedgeHandle& e_inv_2 = mesh.opposite_halfedge_handle(e_next_21);
				if (mesh.is_boundary(e_inv_2))
					break;
				HEMesh::FaceHandle& f_next_2 = mesh.face_handle(e_inv_2);
				if (mesh.property(perFaceStripIdProperty, f_next_2) != -1)
					break;
				else
				{
					length_new++;
					face_id_new.push_back(f_next_2.idx());
				}
				e2 = e_inv_2;

			}

			
			for (int m = 0; m < 20; m++)
			{
				HEMesh::HalfedgeHandle& e_inv_3 = mesh.opposite_halfedge_handle(e3);
				if (mesh.is_boundary(e_inv_3))
					break;
				HEMesh::HalfedgeHandle& e_next_3 = mesh.next_halfedge_handle(e_inv_3);
				HEMesh::FaceHandle& f_next_3 = mesh.face_handle(e_next_3);
				if (mesh.property(perFaceStripIdProperty, f_next_3) != -1)
					break;
				else
				{
					length_new++;
					face_id_new.push_back(f_next_3.idx());
				}
				e3 = e_next_3;
				HEMesh::HalfedgeHandle& e_inv_4 = mesh.opposite_halfedge_handle(e3);
				if (mesh.is_boundary(e_inv_4))
					break;
				HEMesh::HalfedgeHandle& e_next_4 = mesh.next_halfedge_handle(e_inv_4);
				HEMesh::HalfedgeHandle& e_next_41 = mesh.next_halfedge_handle(e_next_4);
				HEMesh::FaceHandle& f_next_4 = mesh.face_handle(e_next_41);
				if (mesh.property(perFaceStripIdProperty, f_next_4) != -1)
					break;
				else
				{
					length_new++;
					face_id_new.push_back(f_next_4.idx());
				}
				e3 = e_next_41;


			}
			
			

			if (length < length_new) 
			{
				length = length_new;
				face_id = face_id_new;
			}
			//std::cout << length << std::endl;
			length_new = 0;
			face_id_new.clear();
			
		


	}
	for (int i = 0; i < face_id.size(); i++)
	{	
		auto f = mesh.face_handle(face_id[i]);
		mesh.property(perFaceStripIdProperty, f) = mesh_property;
		
		my_set.remove(face_id[i]);
		total_num = total_num + 1;
	}
	mesh_property++;
	
	length = 0;
	length_new = 0;
	face_id.clear();
	face_id_new.clear();
	
	nStrips += 1;

	}
	std::cout << total_num << std::endl;
	std::cout << total << std::endl;
	std::cout<<my_set.size()<<std::endl;

	return nStrips;
}




