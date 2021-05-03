#version 330
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) CGV TU Dresden - All Rights Reserved



out vec4 color;
in vec3 normal;
uniform vec3 cameraPos;

in float coord_y;
uniform sampler2D background;
uniform vec2 screenSize;
in vec2 our_tex_coords;
uniform sampler2D diffuseTexture;//grass
uniform sampler2D diffuseTexture_2;//rockTexture
uniform sampler2D diffuseTexture_3;//roadColorTexture
uniform sampler2D diffuseTexture_4;//alphaMap
uniform sampler2D diffuseTexture_5;//roadSpecularMap
uniform sampler2D diffuseTexture_6;//roadNormalMap

in vec3 bitangent;
in vec3 tangent;

const vec3 dirToLight = normalize(vec3(1, 3, 1));	

//Calculates the visible surface color based on the Blinn-Phong illumination model
vec4 calculateLighting(vec4 materialColor, float specularIntensity, vec3 normalizedNormal, vec3 directionToViewer)
{
	vec4 color = materialColor;
	vec3 h = normalize(dirToLight + directionToViewer);
	color.xyz *= 0.9 * max(dot(normalizedNormal, dirToLight), 0) + 0.1;
	color.xyz += specularIntensity * pow(max(dot(h, normalizedNormal), 0), 50);
	return color;
}

vec4 getBackgroundColor()
{
	return texture(background, gl_FragCoord.xy / screenSize);
}

void main()
{
	//surface geometry 
	vec3 n = normalize(normal);
	
	
	//vec3 n = vec3(0, 1, 0);
	
	vec3 dirToViewer = vec3(0, 1, 0);
	//vec3 dirToViewer = normalize(normal);
	float specular = 0;

	
	int tex_x,tex_y;
	for(int u1=0;u1<10;u1++)
	{
	if((our_tex_coords.x-u1*25.5)<=0)
	{tex_x=u1-1;
	break;
	}
	
	}
	for(int u2=0;u2<10;u2++)
	{
	if((our_tex_coords.y-u2*25.5)<=0)
	{tex_y=u2-1;
	break;
	}
	
	}
	//tex coordinate for grass
	vec2 n2=vec2((our_tex_coords.x-tex_x*25.5)/25.5,(our_tex_coords.y-tex_y*25.5)/25.5);//texture coordinate
	//material properties	
		
	vec3 norm1=vec3(0,1,0);
	vec3 sin=cross(n,norm1);
	//tex coordinate for road
	vec2 n3=vec2(our_tex_coords.x/255,our_tex_coords.y/255);
	color = texture(diffuseTexture_4, n3);

	//alphaMap while color black
	if(color.x<0.2)
	{

	//grass and rock
	
	if((sin.x*sin.x+sin.y*sin.y+sin.z*sin.z)>0.25){
	//smooth between rock and grass
	if ((sin.x*sin.x+sin.y*sin.y+sin.z*sin.z)>0.4)
	{
	vec4 color1 = texture(diffuseTexture_2, n2);
	vec4 color2 = texture(diffuseTexture, n2);
	//color = mix(color1, color2, sin.x*sin.x+sin.y*sin.y+sin.z*sin.z);
	color =color1;
	}else {
	vec4 color1 = texture(diffuseTexture_2, n2);
	vec4 color2 = texture(diffuseTexture, n2);
	color = mix(color2,color1 , ((sin.x*sin.x+sin.y*sin.y+sin.z*sin.z)-0.25)*6.5);
	}



	}else{color = texture(diffuseTexture, n2);}

	}else{
	//roadcolor ,specular and normal
	

	vec4 color3 = texture(diffuseTexture, n2);
	vec4 color4=texture(diffuseTexture_3, n2);
	color = mix(color3,color4,color.x);
	//color=color4;
	
	vec4 color5=texture(diffuseTexture_5, n2);
	specular = color5.x;
	dirToViewer=cameraPos-vec3(our_tex_coords.x,coord_y,our_tex_coords.y);
	
	
	mat3 tangentSpaceToViewSpace = mat3(tangent, bitangent, n);
	vec3 mapNormal = texture(diffuseTexture_6, n2).xyz*2-1; 
	n = normalize(tangentSpaceToViewSpace * mapNormal);
	
	
	
	}

	
	

	
	
	
	
	

	
	
	
	
	//Calculate light
	color = calculateLighting(color, specular, n, dirToViewer);

	
}