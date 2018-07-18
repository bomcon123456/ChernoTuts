#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error Glew_INIT" << std::endl;
	}
	{
		float verticies[] = {
			-0.5f, -0.5f, 0.0f, 0.0f,
			 0.5f, -0.5f, 1.0f, 0.0f,
			 0.5f, 0.5f, 1.0f, 1.0f,
			 -0.5f, 0.5f, 0.0f, 1.0f
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		VertexArray vao;
		VertexBuffer vbo(verticies, 4 * 4 * sizeof(float));
		VertexBufferLayout layout;

		layout.Push<float>(2);
		layout.Push<float>(2);
		vao.AddBuffer(vbo, layout);

		IndexBuffer ibo(indices, 6);

		/*
		 * Basically because our window is 640x480 ~ 4:3
		 * Those params * 2 => 4:3
		 * Create sth has a distance of 3 units (top-bottom) and 4 units (left-right)
		 * Essentialy we're creating the boundaries for the window, e.g if we set params -4.0,4.0,-3.0,3.0, the picture will be twice as smaller
		 */
		glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);

		Shader shader("res/shaders/Basic.shader");
		shader.Bind();
		shader.SetUniform4f("u_Color", 0.1f, 0.6f, 0.9f,1.0f);
		shader.SetUniformMat4f("u_MVP", proj);

		Texture texture("res/textures/agave.png");
		texture.Bind(0);
		shader.SetUniform1i("u_Texture",0);

		vao.Unbind();
		shader.Unbind();
		vbo.Unbind();
		ibo.Unbind();

		Renderer renderer;

		float r = 0.0f;
		float increment = 0.05f;
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			renderer.Clear();

			shader.Bind();
			shader.SetUniform4f("u_Color", r, 0.3f, 1.0f, 1.0f);

			renderer.Draw(vao, ibo, shader);

			if (r > 1.0f)
			{
				increment = -0.05f;
			}
			else if (r < 0.05f)
			{
				increment = 0.05f;
			}
			r += increment;
			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}
	glfwTerminate();
	return 0;
}
