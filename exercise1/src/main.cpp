// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) CGV TU Dresden - All Rights Reserved



//#include <GLFW/glfw3.h>
#include"Viewer.h"
#include <util/GLDebug.h>
#include<iostream>

int main(void)
{
	nanogui::init();

	{
		nanogui::ref<Viewer> viewer = new Viewer();
		viewer->setVisible(true);

		nse::util::GLDebug::SetupDebugCallback();
		nse::util::GLDebug::IgnoreGLError(131185); //buffer usage info

		try
		{
			nanogui::mainloop(16);
		}
		catch (std::runtime_error& e)
		{
			std::cerr << e.what() << std::endl;
		}

	}

	nanogui::shutdown();

	return 0;


	//GLFWwindow* window;
	////std::cout << "aaa";
	///* Initialize the library */
	//if (!glfwInit())
	//	return -1;

	///* Create a windowed mode window and its OpenGL context */
	//window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	///*Viewer::Viewer mesh_view;
	//mesh_view.drawContents();*/

	//if (!window)
	//{
	//	glfwTerminate();
	//	return -1;
	//}

	///* Make the window's context current */
	//glfwMakeContextCurrent(window);

	///* Loop until the user closes the window */
	//while (!glfwWindowShouldClose(window))
	//{
	//	/* Render here */
	//	glClear(GL_COLOR_BUFFER_BIT);

	//	/* Swap front and back buffers */
	//	glfwSwapBuffers(window);

	//	/* Poll for and process events */
	//	glfwPollEvents();
	//}
	//
	//glfwTerminate();
	//return 0;
}