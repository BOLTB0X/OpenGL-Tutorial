#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <common/shader_s.h>

#include <iostream>
//#include <cmath>

// Utils
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// Check
//void checkShaderCompiler(GLuint shader, const std::string& type);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//const char* vertexShaderSource = "#version 330 core\n"
//	"layout (location = 0) in vec3 aPos;\n"
//	"layout (location = 1) in vec3 aColor;\n"
//	//"out vec4 vertexColor;\n"
//	"out vec3 ourColor;\n"
//	"void main()\n"
//	"{\n"
//	"	gl_Position = vec4(aPos, 1.0);\n"
//	//"	vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
//	"	ourColor = aColor;\n"
//	"}\0";
//
//const char* fragmentShaderSource = "#version 330 core\n"
//	"out vec4 FragColor;\n"
//	"in vec3 ourColor;\n"
//	//"in vec4 vertexColor;\n"
//	"void main()\n"
//	"{\n"
//	"	FragColor = vec4(ourColor, 1.0f);\n"
//	//"	FragColor = ourColor;\n"
//	//"	FragColor = vertexColor;\n"
//	"}\n\0";

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

	// Shader program 빌드 && 컴파일
	// ----------------------------
	// Vertex shader
	//unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//glCompileShader(vertexShader);

	//// Fragment shader
	//unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//glCompileShader(fragmentShader);

	//// link shaders
	//unsigned int shaderProgram = glCreateProgram();
	//glAttachShader(shaderProgram, vertexShader);
	//glAttachShader(shaderProgram, fragmentShader);
	//glLinkProgram(shaderProgram);

	//checkShaderCompiler(vertexShader, "VERTEX");
	//checkShaderCompiler(fragmentShader, "FRAGMENT");
	//checkShaderCompiler(shaderProgram, "LINKING");

	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);

	// Vertex 데이터 (and buffer(s)) 셋업 and configure Vertex attributes
	// ------------------------------------------------------------------

	//float vertices[] = {
	//	 0.5f, -0.5f, 0.0f,  // bottom right
	//	-0.5f, -0.5f, 0.0f,  // bottom left
	//	 0.0f,  0.5f, 0.0f   // top
	//};

	Shader ourShader("3_exercise03.vs", "3_exercise03.fs");

	float vertices[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
	};

	// VBO, VAO: GPU 메모리에 정점 데이터를 저장하고 관리하는 데 사용되는 객체
	unsigned int VBO, VAO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	//glBindVertexArray(VAO);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	//glBindVertexArray(0);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// as we only have a single shader, we could also just activate our shader once beforehand if we want to 
	//glUseProgram(shaderProgram);

	// Render Loop
	// ------------
	while (!glfwWindowShouldClose(window)) {
		// input
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw
		// ----

		//double timeValue = glfwGetTime();
		//float greenValue = static_cast<float>(sin(timeValue) / 2.0 + 0.5);
		//int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		
		// render the triangle
		ourShader.use();
		//ourShader.setFloat("xOffset", 0.5f);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Optional: de-allocate
	// ----------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//glDeleteProgram(shaderProgram);

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

// 쉐이더 컴파일러 확인
//void checkShaderCompiler(GLuint shader, const std::string& type) {
//	int success;
//	char infoLog[512];
//
//	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
//	if (!success) {
//		glGetShaderInfoLog(shader, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::" << type << "::COMPILATION_FAILED\n"
//			<< infoLog << std::endl;
//	}
//}
