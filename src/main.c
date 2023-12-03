#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include <stdio.h>
#include "mesh.h"

int main(void) {
	GLFWwindow* window;

	if (!glfwInit()) return 1;

	glfwWindowHint(GLFW_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(800, 600, "Window", NULL, NULL);
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) return 1;

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	glViewport(0, 0, 800, 600);

	float vertices[] = {
		// FRONT
		-1, -1,  1,
		-1,  1,  1,
		 1, -1,  1,
		 1,  1,  1,
		// RIGHT
		 1, -1, -1,
		 1,  1, -1,
		// BACK
		-1, -1, -1,
		-1,  1, -1,
	};
	int indices[] = {
		// FRONT
		0, 1, 2,
		2, 1, 3,
		// RIGHT
		2, 3, 4,
		4, 3, 5,
		// BACK
		4, 5, 6,
		6, 5, 7,
		// LEFT
		6, 7, 0,
		0, 7, 1,
		// TOP
		1, 7, 3,
		3, 7, 5,
		// BOTTOM
		6, 0, 4,
		4, 0, 2
	};
	
	Shader shader = ShaderInit("../shaders/unlit.vert", "../shaders/unlit.frag");
	Mesh mesh = MeshInit(shader, vertices, sizeof(vertices), indices, sizeof(indices));

	mat4 model;
	glm_mat4_identity(model);
	glm_scale(model, (vec3){0.5, 0.5, 0.5});

	mat4 view;
	glm_mat4_identity(view);
	glm_translate(view, (vec3){0, 0, -3});

	mat4 projection;
	glm_perspective(glm_rad(45), 800.0/600.0, 0.1, 100.0, projection);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glm_rotate(model, glm_rad(1), (vec3){1, 0, 0});

		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0/255.0, 128/255.0, 128/255.0, 1.0);

		ShaderAddColor(shader, "u_tint", 1.0, 1.0, 1.0);
		ShaderAddMat4(shader, "u_model", model);
		ShaderAddMat4(shader, "u_view", view);
		ShaderAddMat4(shader, "u_projection", projection);
		MeshDraw(mesh);

		glfwSwapBuffers(window);
	}
	glfwTerminate();
}
