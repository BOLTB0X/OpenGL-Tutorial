//
//  main.cpp
//  Tutorial
//
//  Created by KyungHeon Lee on 2024/05/21.
//

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// MARK: - framebuffer_size_callback
/// window 크기가 조정될 때마다 호출되는 창에 콜백 함수를 등록
/// user가 window 크기를 조정하는 순간 뷰포트도 조정되어야 함
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // MARK: view port
    /// 렌더링을 시작하기 전에 마지막으로 한 가지 작업을 수행해야 함 -> OpenGL에게 렌더링 창의 크기를 알려주어야함
    /// 1, 2번째 매개변수 왼쪽 하단 corner (x, y)
    /// 3, 4번째 rendering window의 width 와 height
    glViewport(0, 0, width, height);
}

// MARK: - processInput
// 사용자의 input을 받아서 GLFW를 control하기위해 callback함수
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// MARK: - main
int main(int argc, char* argv[]) {
    // MARK: glfw initialize and configure
    /// glfwInit -> 초기화
    /// glfwWindowHint -> 옵션 구성
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    
    /// GLFW에게 명시적으로 core-profile을 사용하고 싶다고 알림
    /// core-profile: 필요하지 않은 이전 버전과 호환되는 기능 없이 OpenGL 기능의 더 작은 하위 집합에 액세스할 수 있다는 의미
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    //
    
    // MARK: glfw window creation
    GLFWwindow* window = glfwCreateWindow(800, 600, "Learn OpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "GLFW window 생성 실패" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    /// GLFW에게 우리 Window의 컨텍스트를 현재 스레드의 기본 컨텍스트로 만들라고 지시하는 메서드
    glfwMakeContextCurrent(window);
    /// Window이 처음 표시될 때 glfwSetFramebufferSizeCallback의 반환이 Window 크기와 함께 호출 됨
    /// Window을 만든 후 렌더링 루프가 시작되기 전에 콜백 함수를 등록
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    // MARK: glad initialize
    /// OpenGL 함수를 호출하기 전에 GLAD를 초기화해야함
    /// OS에 특정한 OpenGL 함수 포인터의 주소를 로드하기 위해 함수를 GLAD에 전달해야 함 -> gladLoadGLLoader
    /// glfwGetProcAddress에 컴파일하는 OS에 따라 맞게 참조/정의하도록 함
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "GLAD 초기화 실패" << std::endl;
        return -1;
    }
    
    // MARK: Ready your engines
    /// application을 그리고 바로 window를 종료하지 않기 위해서는 사용자의 input을 기다리거나 명시적으로 그만하기를 요청할 때까지 window에 application을 계속 그리거나/나타내야 함
    /// -> render loop
    while (!glfwWindowShouldClose(window)) { // loop가 돌때마다 GLFW가 glfwWindowShouldClose을 통해 참/불인지 받았는지를 확인
        
        processInput(window); // input
        
        // rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // screen 색 설정
        glClear(GL_COLOR_BUFFER_BIT); // glClear를 호출하고 색상 버퍼를 지울 때마다 전체 색상 버퍼는 glClearColor에 의해 구성된 색상으로 채워짐
        
        /// GLFW window 각의 pixel의 색정보를 가지고 있는 커다란 2D buffer를 swap
        /// 이 loop에서 swap을 반복하면서 나중에 rendering할때 screen에 output을 나타내게될 것
        glfwSwapBuffers(window);
        
        glfwPollEvents(); // keyboard input 혹은 mouse movement event가 발생했는지를 확인
        
        /// cf. Double buffer
        /// application이 단일 버퍼에서 그림을 그리면 깜박임 현상이 발생할 수있음
        /// 이는 이미지가 즉시 표시되지 않고 왼쪽에서 오른쪽, 위에서 아래로 픽셀 단위로 그려지기 때문
        /// 이를 해결하기 위해 더블 버퍼링을 사용
        /// 최종 출력 이미지를 화면에 보여주는 프론트 버퍼와 렌더링 명령이 그려지는 백 버퍼를 사용
        /// 모든 렌더링 명령이 완료되면 백 버퍼와 프론트 버퍼를 교체하여, 렌더링 중인 이미지가 표시되지 않도록 함
    }
    
    glfwTerminate(); // 이전에 할당된 모든 GLFW 리소스를 지움
    return 0;
}
