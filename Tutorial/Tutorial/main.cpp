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
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // MARK: view port
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
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    // MARK: glfw window creation
    GLFWwindow* window = glfwCreateWindow(800, 600, "Learn OpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "GLFW window 생성 실패" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    // MARK: glad initialize
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "GLAD 초기화 실패" << std::endl;
        return -1;
    }
    
    // MARK: Ready your engines
    while (!glfwWindowShouldClose(window)) {
        
        processInput(window); // input
        
        // rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glfwSwapBuffers(window);
        
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}
