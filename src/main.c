#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include <stdio.h>
#include "mesh.h"

#define MOVE_SPEED 3
#define SENSITIVITY 5

int main(void) {
	GLFWwindow* window;

	if (!glfwInit()) return 1;

	glfwWindowHint(GLFW_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(800, 600, "Window", NULL, NULL);
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) return 1;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	glViewport(0, 0, 800, 600);

	float cubeVertices[] = {
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
	int cubeIndices[] = {
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
	float cubeNormals[] = {
		// FRONT
		 0,  0,  1,
		 0,  0,  1,
		 0,  0,  1,
		 0,  0,  1,
		// RIGHT
		 1,  0,  0,
		 1,  0,  0,
		 1,  0,  0,
		 1,  0,  0,
		// BACK
		 0,  0, -1,
		 0,  0, -1,
		 0,  0, -1,
		 0,  0, -1,
		// LEFT
		-1,  0,  0,
		-1,  0,  0,
		-1,  0,  0,
		-1,  0,  0,
		// TOP
		 0,  1,  0,
		 0,  1,  0,
		 0,  1,  0,
		 0,  1,  0,
		// BOTTOM
		 0, -1,  0,
		 0, -1,  0,
		 0, -1,  0,
		 0, -1,  0,
	};
	
	float planeVertices[] = {
		 1, 0, -1,
		 1, 0,  1,
		-1, 0, -1,
		-1, 0,  1
	};
	int planeIndices[] = {
		0, 1, 2,
		2, 1, 3
	};
	float planeNormals[] = {
		0, 1, 0,
		0, 1, 0,
		0, 1, 0,
		0, 1, 0
	};

	Shader lit = ShaderInit("../shaders/lit.vs", "../shaders/lit.fs");
	Shader unlit = ShaderInit("../shaders/unlit.vs", "../shaders/unlit.fs");
	Mesh cube = MeshInit(lit, cubeVertices, sizeof(cubeVertices), cubeIndices, sizeof(cubeIndices), cubeNormals, sizeof(cubeNormals));
	Mesh light = MeshInit(unlit, cubeVertices, sizeof(cubeVertices), cubeIndices, sizeof(cubeIndices), cubeNormals, sizeof(cubeNormals));

	mat4 model;
	glm_mat4_identity(model);
	glm_scale(model, (vec3){ 0.4, 0.2, 0.4 });

	vec3 lightPos = { 0, 1, 1 };
	mat4 lightModel;
	glm_mat4_identity(lightModel);
	glm_translate(lightModel, lightPos);
	glm_scale(lightModel, (vec3){ 0.2, 0.2, 0.2 });

	mat4 view;
	glm_mat4_identity(view);
	glm_translate(view, (vec3){0, 0, -3});

	mat4 projection;
	glm_perspective(glm_rad(45), 800.0/600.0, 0.1, 100.0, projection);

	vec3 cameraPos = { 0,  2, 3 };
	vec3 cameraUp = { 0, 1, 0 };
	vec3 cameraRight = { 1, 0, 0 };
	float pitch = 0, yaw = -90;
	double dt = 0;
	double lastTime = 0;

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	double lastMouseX = 0, lastMouseY = 0;
	double mouseXDelta = 0;
	double mouseYDelta = 0;

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		vec3 direction;
		direction[0] = cos(glm_rad(yaw)) * cos(glm_rad(pitch));
		direction[1] = sin(glm_rad(pitch));
		direction[2] = sin(glm_rad(yaw)) * cos(glm_rad(pitch));

		glm_cross(direction, cameraUp, cameraRight);
		glm_normalize(cameraRight);

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			vec3 speed;
			glm_vec3_mul(direction, (vec3){ dt * 2, dt * 2, dt * 2 }, speed);
			glm_vec3_add(cameraPos, speed, cameraPos);
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			vec3 speed;
			glm_vec3_mul(direction, (vec3){ dt * 2, dt * 2, dt * 2 }, speed);
			glm_vec3_sub(cameraPos, speed, cameraPos);
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			vec3 speed;
			glm_vec3_mul(cameraRight, (vec3){ dt * 2, dt * 2, dt * 2 }, speed);
			glm_vec3_sub(cameraPos, speed, cameraPos);
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			vec3 speed;
			vec3 right;
			glm_cross(direction, (vec3){ 0, 1, 0}, right);
			glm_normalize(right);
			glm_vec3_mul(cameraRight, (vec3){ dt * MOVE_SPEED, dt * 2, dt * 2 }, speed);
			glm_vec3_add(cameraPos, speed, cameraPos);
		}

		yaw += mouseXDelta * dt * SENSITIVITY;
		pitch -= mouseYDelta * dt * SENSITIVITY;

		pitch = glm_min(pitch, 89.9);
		pitch = glm_max(pitch, -89.9);

		vec3 forward;
		glm_vec3_add(cameraPos, direction, forward);
		glm_lookat(cameraPos, forward, (vec3){ 0, 1, 0 }, view);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0, 0.0, 0.0, 1.0);

		MeshDraw(cube);
		ShaderAddMat4(lit, "u_model", model);
		ShaderAddMat4(lit, "u_projection", projection);
		ShaderAddMat4(lit, "u_view", view);
		ShaderAddVec3(lit, "u_albedo", (vec3){ 0.3, 0.6, 1.0 });
		ShaderAddVec3(lit, "u_lightColor", (vec3){ 1.0, 1.0, 1.0 });
		ShaderAddVec3(lit, "u_lightPosition", lightPos);

		MeshDraw(light);
		ShaderAddVec3(unlit, "u_tint", (vec3){ 1.0, 1.0, 1.0 });
		ShaderAddMat4(unlit, "u_model", lightModel);
		ShaderAddMat4(unlit, "u_view", view);
		ShaderAddMat4(unlit, "u_projection", projection);

		glfwSwapBuffers(window);

		dt = glfwGetTime() - lastTime;
		lastTime = glfwGetTime();

		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);
		mouseXDelta = mouseX - lastMouseX;
		mouseYDelta = mouseY - lastMouseY;
		lastMouseX = mouseX;
		lastMouseY = mouseY;
	}
	glfwTerminate();
}
