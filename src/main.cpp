#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "mesh.h"
#include "shader.h"
#include "texture.h"

int main(void) {
	GLFWwindow* window;

	if (!glfwInit()) return 1;

	glfwWindowHint(GLFW_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

	window = glfwCreateWindow(800, 600, "Window", NULL, NULL);
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) return 1;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	glViewport(0, 0, 800, 600);

	float vertices[] = {
		-1, -1, -1,
		 1, -1, -1,
		 1,  1, -1,
		-1,  1, -1,
		-1, -1,  1,
		 1, -1,  1,
		 1,  1,  1,
		-1,  1,  1
	};

	float texCoords[] = {
		0, 0,
		1, 0,
		1, 1,
		0, 1
	};
	
	float normals[] = {
		-1, -1, -1,
		 1, -1, -1,
		 1,  1, -1,
		-1,  1, -1,
		-1, -1,  1,
		 1, -1,  1,
		 1,  1,  1,
		-1,  1,  1
	};

	int indices[] = {
		0, 1, 3, 3, 1, 2,
		1, 5, 2, 2, 5, 6,
		5, 4, 6, 6, 4, 7,
		4, 0, 7, 7, 0, 3,
		3, 2, 7, 7, 2, 6,
		4, 5, 0, 0, 5, 1
	};

	Mesh mesh(vertices, sizeof(vertices), indices, sizeof(indices), texCoords, sizeof(texCoords), normals, sizeof(normals));
	Shader shader("../shaders/unlit.vs", "../shaders/unlit.fs");
	Texture2D tex("../textures/cool.png");

	glm::mat4 model = glm::mat4(1.0);
	model = glm::scale(model, glm::vec3(0.5, 0.5, 0.5));

	glm::mat4 view = glm::mat4(1.0);
	view = glm::translate(view, glm::vec3(0, 0, -5));

	glm::mat4 projection = glm::perspective(glm::radians(45.0), 800.0/600.0, 0.1, 1000.0);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		model = glm::rotate(model, glm::radians(1.0f), glm::vec3(0.0, 1.0, 0.0));

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.AddMat4("u_model", model);
		shader.AddMat4("u_view", view);
		shader.AddMat4("u_projection", projection);
		shader.AddVec3("u_tint", glm::vec3(1.0, 1.0, 1.0));
		tex.Bind();
		mesh.Draw(shader);

		glfwSwapBuffers(window);
	}
	glfwTerminate();
}
