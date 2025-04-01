#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main(void) {
	// glfw: initialize and configure
	// --------------------------------

	glfwInit(); // GLFW initialize
	// GLFW configure
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Window 생성
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// GLFW에 이 함수를 등록하여 창 크기가 조정될 때마다 호출하도록 알려주는 함수
	glfwMakeContextCurrent(window);
	// GLFW 지원 메서드 glfwSetFramebufferSizeCallback 
	// framebuffer_size_callback 함수 포인터로 내가 지정한 크기로 변경
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// GLAD 초기화: OpenGL 함수 포인터 관련
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initailize GLAD" << std::endl;
		return -1;
	}

	// Render Loop
	// ------------
	while (!glfwWindowShouldClose(window)) { // glfwWindowShouldClose 함수 : 각 루프 반복의 시작 부분에서 GLFW가 닫히도록 지시되었는지 확인
		
		// input
		processInput(window);

		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glfwSwapBuffers(window); // 렌더 반복 중에 렌더링하는 데 사용되는 색상 버퍼(GLFW 창의 각 픽셀에 대한 색상 값이 포함된 대형 2D 버퍼)를 스왑하여 화면에 출력으로 표시하는 함수
		glfwPollEvents(); // 이벤트(키보드 입력, 마우스 이동)가 트리거 되는지 확인, window 상태 업데이트, (콜백 함수를 통해 등록 가능)
	}

	// glfw: 종료하고 이전에 할당된 모든 GLFW 리소스를 해제
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