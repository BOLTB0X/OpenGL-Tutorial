#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

// Utils
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// Check
void checkShaderCompiler(GLuint shader, const std::string& type);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\n\0";

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
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Fragment shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// link shaders
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	checkShaderCompiler(vertexShader, "VERTEX");
	checkShaderCompiler(fragmentShader, "FRAGMENT");
	checkShaderCompiler(shaderProgram, "LINKING");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	// Vertex 데이터 (and buffer(s)) 셋업 and configure Vertex attributes
	// ------------------------------------------------------------------
	float triangleVertices[] = {
		-0.5f, -0.5f, 0.0f, // left  
		 0.5f, -0.5f, 0.0f, // right 
		 0.0f,  0.5f, 0.0f  // top   
	};

	float vertices[] = {
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};

	unsigned int indices[] = {
			0, 1, 3,   // 1 triangle
			1, 2, 3    // 2 triangle
	};

	// VBO, VAO: GPU 메모리에 정점 데이터를 저장하고 관리하는 데 사용되는 객체
	// VBO: Vertex 데이터(Vertex 좌표, UV 좌표, 색상, 법선 )를 GPU의 메모리에 저장하는 버퍼
	// VAO: 여러 개의 VBO와 속성(Attribute) 설정을 저장하는 객체
	// EBO: 인덱스 버퍼
	unsigned int VBO, VAO, EBO;

	glGenVertexArrays(1, &VAO); // OpenGL에 Vertex 속성(좌표, 색상, 법선 등)이 어디에 있는지 지정해야 하는데, VAO가 이 역할을 대신해 줌
	glGenBuffers(1, &VBO); // 저장하는 버퍼
	glGenBuffers(1, &EBO); 

	// 1. bind Vertex Array Object
	// VAO를 먼저 바인딩, 바인딩하면 그 이후의 설정이 해당 VAO에 저장됨
	glBindVertexArray(VAO);

	// 2. copy our vertices array in a vertex buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 3. copy our index array in a element buffer for OpenGL to use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 4. then set the vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// glVertexAttribPointer에 대한 호출은 VBO를 정점 속성의 바인딩된 정점 버퍼 객체로 등록하므로 나중에 안전하게 바인딩을 해제할 수 있음
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// 나중에 VAO를 언바인딩하여 다른 VAO 호출이 실수로 이 VAO를 수정하지 않도록 할 수 있지만, 이런 일은 거의 발생하지 않음
	// VAO를 수정하려면 어차피 glBindVertexArray를 호출해야 하므로 직접적으로 필요하지 않을 때는 일반적으로 VAO(또는 VBO)를 언바인딩하지 않음
	glBindVertexArray(0);

	// Render Loop
	// ------------
	while (!glfwWindowShouldClose(window)) { // glfwWindowShouldClose 함수 : 각 루프 반복의 시작 부분에서 GLFW가 닫히도록 지시되었는지 확인

		// input
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 와이어프레임 모드
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window); // 렌더 반복 중에 렌더링하는 데 사용되는 색상 버퍼(GLFW 창의 각 픽셀에 대한 색상 값이 포함된 대형 2D 버퍼)를 스왑하여 화면에 출력으로 표시하는 함수
		glfwPollEvents(); // 이벤트(키보드 입력, 마우스 이동)가 트리거 되는지 확인, window 상태 업데이트, (콜백 함수를 통해 등록 가능)
	}

	// Optional: de-allocate
	// ----------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

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
void checkShaderCompiler(GLuint shader, const std::string& type) {
	int success;
	char infoLog[512];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::" << type << "::COMPILATION_FAILED\n"
			<< infoLog << std::endl;
	}
}
