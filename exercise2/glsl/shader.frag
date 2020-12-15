#version 130
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) CGV TU Dresden - All Rights Reserved

in vec3 fragment_color;
in vec4 point_p;
out vec4 color;
in vec3 julia_parameter;

in vec3 centr;
in float fractalmode;
void main(void)
{
	//color = vec4(fragment_color,1.0); //* 0.5+vec4(0.5) 
	
	 /**** Begin of tasks ***
	 - 2.2.5
	 Implement the pseudo-code for calculating the julia fractal at a point.
	 To get the point you can declare a new "in" variable which contains the
	 position and just use the X- and Y- value. 

	 *** End of tasks ***/
	vec2 c,z;
	float m=julia_parameter.z;




	//julia fractal
	if(fractalmode==0.0){
	c.x=julia_parameter.x;
	c.y=julia_parameter.y;
	z.x=(point_p.x)*m;
	z.y=(point_p.y)*m;
	
	}else {
	//the Mandelbrot fractal
	c.x=1.333*(point_p.x-0.5)*m-centr.x;
	c.y=(point_p.y-0.5)*m-centr.y;
	z.x=1.333*(point_p.x-0.5)*m-centr.x;
	z.y=(point_p.y-0.5)*m-centr.y;
	}
	
	

	float X,Y;
	
	

	int imax=200;
	int i;
    for(i=0; i<imax; i++) {
	X=(z.x*z.x-z.y*z.y)+c.x;
	Y=(z.y*z.x+z.x*z.y)+c.y;
	if((X*X+Y*Y)>4.0)
	{break;}
	z.x=X;
	z.y=Y;
	}
	float alpha=0.0;
	if(i<imax)
	{
	alpha=float(i)/float(imax);
	}
	color=vec4(alpha)*10.0*vec4(fragment_color,1.0);
}