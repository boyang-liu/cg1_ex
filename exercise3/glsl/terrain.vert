#version 330
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) CGV TU Dresden - All Rights Reserved

in vec4 position;


//in vec2 tex_coords;
out vec2 our_tex_coords;
out float coord_y;
uniform mat4 mvp;

//Returns the height of the procedural terrain at a given xz position
float getTerrainHeight(vec2 p);

out vec3 bitangent;
out vec3 tangent;

out vec3 normal;

void main()
{
	
	vec2 m;
	m.x=position.x;
	m.y=position.z;
	float height_y;
	height_y=getTerrainHeight(m);
	vec4 newposition;
	newposition=vec4(position.x,height_y,position.z,1.0);
	vec3 pos=vec3(newposition.x,newposition.y,newposition.z);
	gl_Position = mvp * newposition;
	

	our_tex_coords=vec2 (newposition.x,newposition.z);
	coord_y=height_y;
	
	
	vec2 m_diff_x2=vec2((newposition.x+1),newposition.z);
	vec2 m_diff_z2=vec2(newposition.x,(newposition.z+1));


	float height_y_mz,height_y_mx;
	height_y_mz=getTerrainHeight(m_diff_z2);
	height_y_mx=getTerrainHeight(m_diff_x2);

	vec3 m_diff_x=vec3(1,(height_y_mx-height_y),0);
	vec3 m_diff_z=vec3(0,(height_y_mz-height_y),1);

	//tangent=normalize(m_diff_x);
	//bitangent=normalize(m_diff_z);
	tangent=m_diff_x;
	bitangent=m_diff_z;


	//vec3 m_diff_x=vec3(1,0,0);
	//vec3 m_diff_z=vec3(0,0,1);


	float a,b,c;
	a=(m_diff_x.y*m_diff_z.z)-(m_diff_z.y*m_diff_x.z);
	b=(m_diff_x.z*m_diff_z.x)-(m_diff_x.x*m_diff_z.z);
	c=(m_diff_x.x*m_diff_z.y)-(m_diff_x.y*m_diff_z.x);
	//vec3 nor=cross(m_diff_x,m_diff_z);

	normal=vec3(a,-b,c);
	//normal=normalize(nor);
	//normal=vec3(normal.x,-normal.y,normal.z);
	/*
	vec2 m1=vec2(newposition.x,(newposition.z+0.01));
	vec2 m2=vec2((newposition.x+0.01),newposition.z);
	vec3 a1=vec3(newposition.x,newposition.y,(newposition.z+0.1));
	vec3 a2=vec3((newposition.x+0.1),newposition.y,newposition.z);
	vec3 n1 = cross(a1-pos,a2-pos );*/
	

	
}

//source: https://gist.github.com/patriciogonzalezvivo/670c22f3966e662d2f83
float rand(vec2 c)
{
	return 2 * fract(sin(dot(c.xy ,vec2(12.9898,78.233))) * 43758.5453) - 1;
}

float perlinNoise(vec2 p )
{
	vec2 ij = floor(p);
	vec2 xy = p - ij;
	//xy = 3.*xy*xy-2.*xy*xy*xy;
	xy = .5*(1.-cos(3.1415926 * xy));
	float a = rand((ij+vec2(0.,0.)));
	float b = rand((ij+vec2(1.,0.)));
	float c = rand((ij+vec2(0.,1.)));
	float d = rand((ij+vec2(1.,1.)));
	float x1 = mix(a, b, xy.x);
	float x2 = mix(c, d, xy.x);
	return mix(x1, x2, xy.y);
}

//based on https://www.seedofandromeda.com/blogs/58-procedural-heightmap-terrain-generation
float getTerrainHeight(vec2 p)
{
	float total = 0.0;
	float maxAmplitude = 0.0;
	float amplitude = 1.0;
	float frequency = 0.02;
	for (int i = 0; i < 11; i++) 
	{
		total +=  ((1.0 - abs(perlinNoise(p * frequency))) * 2.0 - 1.0) * amplitude;
		frequency *= 2.0;
		maxAmplitude += amplitude;
		amplitude *= 0.45;
	}
	return 15 * total / maxAmplitude;
}