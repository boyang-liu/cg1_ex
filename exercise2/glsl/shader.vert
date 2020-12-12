#version 130
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) CGV TU Dresden - All Rights Reserved

 in vec3 in_position;
 in vec3 in_color;
out vec3 fragment_color;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
void main(void)
{	
	
	gl_Position =projectionMatrix*modelViewMatrix  *vec4(in_position,1.0);
	fragment_color = in_color;
	
	/* - 2.2.2 (b)
	 * Declare a new "in" variable with the name "in_color". Instead of setting
	 * "fragment_color" to the position, set it to "in_color. */

	/* - 2.2.4 (a)
	 * Declare two new "uniform" variables with the type "mat4" (above the main function)
	 * that store the modelview and projection matrix. To apply the transformations
	 * multiply the value of "in_position" before setting "gl_Position". */

	/* - 2.2.5
	 * The algorithm to calculate the julia fractal needs a position as input.
	 * Declare another "out" variable and set it to the untransformed input
	 * position. */






}