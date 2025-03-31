#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);


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

	// Window 생성
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

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
		glfwSwapBuffers(window);
		glfwPollEvents(); // 이벤트(키보드 입력, 마우스 이동)가 트리거 되는지 확인, window 상태 업데이트, (콜백 함수를 통해 등록 가능)
	}
	return 0;
}

// Window 크기 변경시 호출 되는 callback 함수
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}