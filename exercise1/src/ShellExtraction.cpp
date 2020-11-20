// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) CGV TU Dresden - All Rights Reserved

#include "ShellExtraction.h"
#include "util/UnionFind.h"
#include <queue>
#include <iostream>
unsigned int ExtractShells(HEMesh& m, OpenMesh::FPropHandleT<int> perFaceShellIndex)
{
	//reset the shell indices to -1 for every face
	int count=1;
	nse::util::UnionFind U;
	for (auto f : m.faces())
	{
		m.property(perFaceShellIndex, f) = -1;
		U.AddItem();
	}
	
	
	for (auto f : m.faces()) {
		
		for (auto e : f.halfedges()) 
		{
			auto e2 = e.opp();
			auto f2 = e2.face();
			if (f2.idx() > f.idx()) 
			{
				U.Merge(f.idx(), f2.idx());
				
			}
		}	
	}
	std::vector<int> V;
	for (auto f : m.faces()) {
		if (f.idx()==0) 
		{
			m.property(perFaceShellIndex, f) = count;
		}
		else{
			if (U.GetRepresentative(f.idx()) == U.GetRepresentative(f.idx() - 1))
			{
				m.property(perFaceShellIndex, f) = count;
			}else{
				m.property(perFaceShellIndex, f) = count+1;
				count++;
			}
		}
		
	}

	//for (auto f : m.faces())
		std::cout << count << std::endl;
	/*Task 1.2.3*/
	return count;
}