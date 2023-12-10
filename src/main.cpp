#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

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

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

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
		0, 0, 1, 0, 1, 1, 0, 1,
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
	Shader shader("../shaders/lit.vs", "../shaders/lit.fs");
	Texture2D tex("../textures/cool.png");

	glm::mat4 model = glm::mat4(1.0);

	glm::mat4 view = glm::mat4(1.0);
	view = glm::translate(view, glm::vec3(0, 0, -5));

	glm::mat4 projection = glm::perspective(glm::radians(45.0), 800.0/600.0, 0.1, 1000.0);

	glm::vec3 position(0, 0, 0);
	glm::vec3 rotation(0, 0, 0);
	glm::vec3 scale(1, 1, 1);
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		{
			ImGui::Begin("Window");

			ImGui::SliderFloat3("Position", glm::value_ptr(position), -10, 10);
			ImGui::SliderFloat3("Rotation", glm::value_ptr(rotation), 0, 360);
			ImGui::SliderFloat3("Scale", glm::value_ptr(scale), 0, 1);

			ImGui::End();
		}

		ImGui::Render();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		model = glm::mat4(1.0);
		model = glm::translate(model, position);
		glm::mat4 rotMatrix = glm::mat4(0.0);
		model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0, 0.0, 0.0));
		model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0, 1.0, 0.0));
		model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0, 0.0, 1.0));
		model = glm::scale(model, scale);

		tex.Bind();
		shader.AddMat4("u_model", model);
		shader.AddMat4("u_view", view);
		shader.AddMat4("u_projection", projection);
		shader.AddVec3("u_albedo", glm::vec3(1, 1, 1));
		shader.AddVec3("u_lightColor", glm::vec3(1, 1, 1));
		shader.AddVec3("u_lightPosition", glm::vec3(0, 4, 0));
		mesh.Draw(shader);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
	}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
}
