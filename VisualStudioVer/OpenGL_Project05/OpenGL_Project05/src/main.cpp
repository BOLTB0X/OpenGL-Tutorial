#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <common/shader_s.h>
#include <common/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

// Utils
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float mixValue = 0.2f;

int main(void) {
	// glfw: initialize and configure
	// --------------------------------

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initailize GLAD" << std::endl;
		return -1;
	}

	Shader ourShader("glsl/vertex_shader.vs", "glsl/fragment_shader.fs");

	float vertices[] = {
		// positions          // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
	};

	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	// VBO, VAO: GPU 메모리에 정점 데이터를 저장하고 관리하는 데 사용되는 객체
	unsigned int VBO, VAO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// load and create a texture 
	// -------------------------
	unsigned int texture1, texture2;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1); // 이제 모든 예정된 GL_TEXTURE_2D 작업이 이 텍스처 개체에 적용 됌
	// texture 래핑 매개변수 설정
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // 텍스처 래핑을 GL_REPEAT(기본 래핑 방법)로 설정
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// texture 필터링 매개변수 설정
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // stb_image.h에 로드된 텍스처를 y축을 기준으로 반전하라고 지시

	unsigned char* data = stbi_load("resources/container.jpg", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	// texture 2
	// ---------
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2); // 이제 모든 예정된 GL_TEXTURE_2D 작업이 이 텍스처 개체에 적용 됌
	// texture 래핑 매개변수 설정
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // 텍스처 래핑을 GL_REPEAT(기본 래핑 방법)로 설정
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// texture 필터링 매개변수 설정
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load image, create texture and generate mipmaps
	data = stbi_load("resources/awesomeface.png", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	// 각 샘플러가 속하는 텍스처 단위를 OpenGL에 알림(한 번만 수행하면 됨)
	// -------------------------------------------------------------------------------------------
	ourShader.use(); // 유니폼을 설정하기 전에 셰이더를 활성화/사용하는 것을 잊지 말길
	ourShader.setInt("texture1", 0);
	ourShader.setInt("texture2", 1);

	// Render Loop
	// ------------
	while (!glfwWindowShouldClose(window)) {
		// input
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// bind textures on corresponding texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		//glm::mat4 trans = glm::mat4(1.0f);
		//trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
		//trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

		glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
		transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

		// render the container
		ourShader.use();
		unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
		//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));


		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Optional: de-allocate
	// ----------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	// glfw: 종료하고 이전에 할당된 모든 GLFW 리소스를 해제
	// -------------------------------------------------
	glfwTerminate();
	return 0;
}

//  GLFW 라이브러리를 사용하여 특정 키 입력을 감지하고 그에 따라 반응하는 함수
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}


// Window 크기 변경시 호출 되는 callback 함수
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
