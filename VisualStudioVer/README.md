# OpenGL Study In Visual Studio

![으으아](https://mblogthumb-phinf.pstatic.net/MjAyMTA5MDdfNzEg/MDAxNjMwOTQyMjQ3MzQ1.LsRXGVtVjbUNBIBwq3qAynvSUpm6iRsPN7xFUzijrAcg.hoJ2o9kw7MuqMRTy4-9YmlMI7_QtpmaBKT25j57oWygg.GIF.playkit/DownrightGlossyFoxhound-size_restricted.gif?type=w800)

> 그래픽 및 이미지를 조작하는 데 사용할 수 있는 많은 기능들을 제공하는 API

| 항목         | 내용 |
|-------------|---------------------------------|
| 학습 자료 | [Learn OpenGL](https://learnopengl.com/) |
| 개발 환경 | Visual Studio 2022 , GLFW, glad |
| 사용 기술 | OpenGL, GLSL, Shader Programming, C++ |

## Getting started

<details>
<summary> Create Window </summary>

> **GLFW** , **GLAD** 은 OpenGL을 쉽게 사용하도록 도와주는 라이브러리

- [GLFW](https://www.glfw.org/download.html) : 창 생성을 위해

- [CMake](https://cmake.org/download/) : OS와 개발환경에 빌드 시스템을 더 쉽게 관리, 맞는 프로젝트 파일을 생성을 위해

- [GLAD](https://glad.dav1d.de/) : 확장 기능 로드

- [GLM](https://github.com/g-truc/glm) : 벡터, 행렬 등을 다루는 함수와 클래스를 제공

```cpp
#include <glad/glad.h>
#include <GLFW/glfw3.h>
```

<br/>

</details>

<details>
<summary> Hello Window</summary>

<p align="center">
  <table style="width:100%; text-align:center;">
    <tr>
      <td style="text-align:center; vertical-align:middle;">
        <p align="center">
        <img src="https://github.com/BOLTB0X/OpenGL-Study/blob/main/Img/window.jpg?raw=true" alt="Example Image" width="70%"/>
        </p>
      </td>
      <td style="text-align:center; vertical-align:middle;">
        <p align="center">
        <img src="https://github.com/BOLTB0X/OpenGL-Study/blob/main/Img/window2.jpg?raw=true" alt="Example Image" width="70%"/>
        </p>
      </td>
    </tr>
    <tr>
      <td style="text-align:center; font-size:14px; font-weight:bold;">
      <p align="center">
      Window 1
      </p>
      </td>
      <td style="text-align:center; font-size:14px; font-weight:bold;">
      <p align="center">
      Window 2
      </p>
      </td>
    </tr>
  </table>
</p>

- **init**

  ```cpp
  // 1
  glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  #ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  #endif

	glfwMakeContextCurrent(window); // 2
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // 3
  ```

    1. GLFW initialize 및 configure

    2. `glfwMakeContextCurrent` : GLFW에 이 함수를 등록하여 창 크기가 조정될 때마다 호출하도록 알려주는 함수

    3. `glfwSetFramebufferSizeCallback` : `framebuffer_size_callback` 함수 포인터로 내가 지정한 크기로 변경

  <br/>

- **Utils**

  ```cpp
  void processInput(GLFWwindow* window) {
	  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, true);
  }

  void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	  glViewport(0, 0, width, height);
  }
  ```

    1. `processInput` : GLFW 라이브러리를 사용하여 특정 키 입력을 감지하고 그에 따라 반응하는 함수

    2. `framebuffer_size_callback` : Window 크기 변경시 호출 되는 **callback** 함수

    <br/>

- **Render Loop**

   ```cpp
   while (!glfwWindowShouldClose(window)) { // 1
		
		   // input
		   processInput(window);

		   // render
		   glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		   glClear(GL_COLOR_BUFFER_BIT);
		
		   glfwSwapBuffers(window); // 2
		   glfwPollEvents(); // 3
	 }
   ```

    1. `glfwWindowShouldClose`: 각 루프 반복의 시작 부분에서 GLFW가 닫히도록 지시되었는지 확인

    2. `glfwSwapBuffers` : 렌더 반복 중에 렌더링하는 데 사용되는 색상 버퍼(GLFW 창의 각 픽셀에 대한 색상 값이 포함된 대형 2D 버퍼)를 스왑하여 화면에 출력으로 표시하는 함수

    3. `glfwPollEvents` : 이벤트(키보드 입력, 마우스 이동)가 트리거 되는지 확인, window 상태 업데이트, (콜백 함수를 통해 등록 가능)

    <br/>

- [전체 프로젝트 코드(C++)](https://github.com/BOLTB0X/OpenGL-Study/tree/main/VisualStudioVer/OpenGL_Project01)

<br/>

</details>

<details>
<summary> Hello Triangle</summary>

<p align="center">
  <table style="width:100%; text-align:center; border-spacing:5px;">
    <tr>
      <td style="text-align:center; vertical-align:middle;">
        <p align="center">
        <img src="https://github.com/BOLTB0X/OpenGL-Study/blob/main/Img/%EC%B2%AB%EC%82%BC%EA%B0%81%ED%98%95.jpg?raw=true" alt="Example Image" width="60%"/>
        </p>
      </td>
      <td style="text-align:center; vertical-align:middle;">
        <p align="center">
        <img src="https://github.com/BOLTB0X/OpenGL-Study/blob/main/Img/%EC%B2%AB%EC%82%AC%EA%B0%81%ED%98%95.jpg?raw=true" alt="Example Image" width="60%"/>
        </p>
      </td>
      <td style="text-align:center; vertical-align:middle;">
        <p align="center">
        <img src="https://github.com/BOLTB0X/OpenGL-Study/blob/main/Img/%EC%B2%AB%EC%82%AC%EA%B0%81%ED%98%95-%EC%99%80%EC%9D%B4%EC%96%B4%ED%94%84%EB%A0%88%EC%9E%84%EB%AA%A8%EB%93%9C.jpg?raw=true" alt="Example Image" width="60%"/>
        </p>
      </td>
    </tr>
    <tr>
      <td style="text-align:center; font-size:14px; font-weight:bold;">
      <p align="center">
      Triangle
      </p>
      </td>
      <td style="text-align:center; font-size:14px; font-weight:bold;">
      <p align="center">
      Rectangle
      </p>
      </td>
      <td style="text-align:center; font-size:14px; font-weight:bold;">
      <p align="center">
      Wire Frame
      </p>
      </td>
    </tr>
  </table>
</p>

- **Shader program 빌드 && 컴파일**

   <details>
   <summary> Shader </summary>
   
    ```cpp
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
    ```

   </details>

   <details>
   <summary> Shader 컴파일 in main </summary>

   ```cpp
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
   ```

    <br/>

   </details>


   <details>
   <summary> Shader 컴파일 함수 </summary>

   ```cpp
   void checkShaderCompiler(GLuint shader, const std::string& type) {
	   int success;
	   char infoLog[512];

	   glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	   if (!success) {
		   glGetShaderInfoLog(shader, 512, NULL, infoLog);
		   std::cout << "ERROR::SHADER::" << type << "::COMPILATION_FAILED\n" << infoLog << std::endl;
	  }
   }
   ```

   </details>
       <br/>

- **Vertex 데이터 (and 버퍼) 셋업**

   <details>
   <summary> Vertex 정의 </summary>

   ```cpp
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
   ```

    <br/>

   </details>

   <details>
   <summary> VBO , VAO , EBO </summary>

    VBO, VAO: GPU 메모리에 정점 데이터를 저장하고 관리하는 데 사용되는 객체

    - **VBO** : Vertex 데이터(Vertex 좌표, UV 좌표, 색상, 법선 )를 GPU의 메모리에 저장하는 버퍼
    
    - **VAO** : 여러 개의 VBO와 속성(Attribute) 설정을 저장하는 객체
      
    - **EBO** : 인덱스 버퍼

    ```cpp
	  unsigned int VBO, VAO, EBO;

	  glGenVertexArrays(1, &VAO); // 1
	  glGenBuffers(1, &VBO); // 2
	  glGenBuffers(1, &EBO); 
    ```
    
    1. `glGenVertexArrays` :  OpenGL에 Vertex 속성(좌표, 색상, 법선 등)이 어디에 있는지 지정해야 하는데, VAO가 이 역할을 대신해 줌

    2. `glGenBuffers` : 저장하는 버퍼

    <br/>

    ```cpp
    glBindVertexArray(VAO); // 1

    // 2
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 3
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 4
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // 5
    glBindBuffer(GL_ARRAY_BUFFER, 0);

	  // 6
	  glBindVertexArray(0);
    ```

    1. bind Vertex Array Object
       `glBindVertexArray` : VAO를 먼저 바인딩, 바인딩하면 그 이후의 설정이 해당 VAO에 저장됨

    2. copy our vertices array in a vertex buffer for OpenGL to use

    3. copy our index array in a element buffer for OpenGL to use

    4. then set the vertex attributes pointers

    5. `glBindBuffer` : `glVertexAttribPointer` 에 대한 호출은 VBO를 정점 속성의 바인딩된 정점 버퍼 객체로 등록하므로 나중에 안전하게 바인딩을 해제할 수 있음

    6. `glBindVertexArray` :  나중에 VAO를 언바인딩하여 다른 VAO 호출이 실수로 이 VAO를 수정하지 않도록 할 수 있지만, 이런 일은 거의 발생하지 않음
	  
       VAO를 수정하려면 어차피 `glBindVertexArray`를 호출해야 하므로 직접적으로 필요하지 않을 때는 일반적으로 VAO(또는 VBO)를 언바인딩하지 않음
       
   </details>
      <br/>

- **draw**

  <details>
  <summary> Triangle </summary>

  ```cpp
  glUseProgram(shaderProgram); // 1
  glBindVertexArray(VAO); // 2
  glDrawArrays(GL_TRIANGLES, 0, 3); // 3
  
  glfwSwapBuffers(window); // 4
  glfwPollEvents(); // 5
  ```

  1. `glUseProgram` : 현재 사용할 셰이더 프로그램을 설정하는 함수

  2. `glBindVertexArray` : 렌더링할 객체(Vertex VAO)를 바인딩하는 함수

  3. `glDrawArrays` : 현재 바인딩된 VAO에 저장된 버텍스 데이터를 사용하여 삼각형을 그림

  4. `glfwSwapBuffers` : 렌더 반복 중에 렌더링하는 데 사용되는 색상 버퍼(GLFW 창의 각 픽셀에 대한 색상 값이 포함된 대형 2D 버퍼)를 스왑하여 화면에 출력으로 표시하는 함수

  5. `glfwPollEvents` : 이벤트(키보드 입력, 마우스 이동)가 트리거 되는지 확인, window 상태 업데이트, (콜백 함수를 통해 등록 가능)
      
      <br/>

  </details>

  <details>
  <summary> Wire Frame </summary>

  ```cpp
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  ```
  </details>

    <br/>

- [전체 프로젝트 코드(C++)](https://github.com/BOLTB0X/OpenGL-Study/blob/main/VisualStudioVer/OpenGL_Project02/OpenGL_Project02/src/main.cpp)
  
   <br/>

</details>

<details>
<summary> Shaders </summary>
</details>

## 참고

- [Learn OpenGL](https://learnopengl.com/)

- [티스토리-꽉퓨타의 SW 이야기(OpenGL - 윈도우에 개발환경 구축하기)](https://kwak-story.tistory.com/3)