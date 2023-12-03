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

	mat4 view;
	glm_mat4_identity(view);
	glm_translate(view, (vec3){0, 0, -3});

	mat4 projection;
	glm_perspective(glm_rad(45), 800.0/600.0, 0.1, 100.0, projection);

	vec3 cameraPos = { 0,  0, 3 };
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
			vec3 right;
			glm_cross(direction, (vec3){ 0, 1, 0}, right);
			glm_normalize(right);
			glm_vec3_mul(right, (vec3){ dt * 2, dt * 2, dt * 2 }, speed);
			glm_vec3_sub(cameraPos, speed, cameraPos);
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			vec3 speed;
			vec3 right;
			glm_cross(direction, (vec3){ 0, 1, 0}, right);
			glm_normalize(right);
			glm_vec3_mul(right, (vec3){ dt * MOVE_SPEED, dt * 2, dt * 2 }, speed);
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
		glClearColor(0/255.0, 128/255.0, 128/255.0, 1.0);

		ShaderAddFloat(shader, "u_time", glfwGetTime());
		ShaderAddMat4(shader, "u_view", view);
		ShaderAddMat4(shader, "u_projection", projection);

		glm_mat4_identity(model);
		glm_translate(model, (vec3){ -0.7, 0, 0 });
		glm_scale(model, (vec3){ 0.5, 0.5, 0.5 });
		ShaderAddVec3(shader, "u_tint", (vec3){ 255/255.0, 206/255.0, 11/255.0 });
		ShaderAddMat4(shader, "u_model", model);
		MeshDraw(mesh);

		glm_mat4_identity(model);
		glm_translate(model, (vec3){ 0.7, 0, 0 });
		glm_scale(model, (vec3){ 0.5, 0.5, 0.5 });
		ShaderAddVec3(shader, "u_tint", (vec3){ 171/255.0, 62/255.0, 143/255.0 });
		ShaderAddMat4(shader, "u_model", model);
		MeshDraw(mesh);

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
