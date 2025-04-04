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


- [전체 프로젝트 코드(C++)](https://github.com/BOLTB0X/OpenGL-Study/tree/main/VisualStudioVer/OpenGL_Project01)


</details>

<details>
<summary> Hello Triangle</summary>

**Practice**

<p align="center">
  <table style="width:100%; text-align:center; border-spacing:5px;">
    <tr>
      <td style="text-align:center; vertical-align:middle;">
        <p align="center">
        <img src="https://github.com/BOLTB0X/OpenGL-Study/blob/main/Img/%EC%B2%AB%EC%82%BC%EA%B0%81%ED%98%95.jpg?raw=true" alt="Example Image" width="70%"/>
        </p>
      </td>
      <td style="text-align:center; vertical-align:middle;">
        <p align="center">
        <img src="https://github.com/BOLTB0X/OpenGL-Study/blob/main/Img/%EC%B2%AB%EC%82%AC%EA%B0%81%ED%98%95.jpg?raw=true" alt="Example Image" width="70%"/>
        </p>
      </td>
      <td style="text-align:center; vertical-align:middle;">
        <p align="center">
        <img src="https://github.com/BOLTB0X/OpenGL-Study/blob/main/Img/%EC%B2%AB%EC%82%AC%EA%B0%81%ED%98%95-%EC%99%80%EC%9D%B4%EC%96%B4%ED%94%84%EB%A0%88%EC%9E%84%EB%AA%A8%EB%93%9C.jpg?raw=true" alt="Example Image" width="70%"/>
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
      
  </details>

  <details>
  <summary> Wire Frame </summary>

  ```cpp
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  ```
  </details>
    <br/>

**Exercises**

<p align="center">
  <table style="width:100%; text-align:center; border-spacing:5px;">
    <tr>
      <td style="text-align:center; vertical-align:middle;">
        <p align="center">
        <img src="https://github.com/BOLTB0X/OpenGL-Study/blob/main/Img/2-2-Exercise01.jpg?raw=true" alt="Example Image" width="70%"/>
        </p>
      </td>
      <td style="text-align:center; vertical-align:middle;">
        <p align="center">
        <img src="https://github.com/BOLTB0X/OpenGL-Study/blob/main/Img/2-2-Exercise03.jpg?raw=true" alt="Example Image" width="70%"/>
        </p>
      </td>
    </tr>
    <tr>
      <td style="text-align:center; font-size:14px; font-weight:bold;">
      <p align="center">
      e01, e02
      </p>
      </td>
      <td style="text-align:center; font-size:14px; font-weight:bold;">
      <p align="center">
      e03
      </p>
      </td>
    </tr>
  </table>
</p>

- Solution

   <details>
   <summary> Exercises 01 sol  </summary>
   
     `glDrawArrays`를 사용하여 데이터에 더 많은 정점을 추가하여 나란히 2개의 삼각형을 그려라

    ```cpp
    float twinTriangleVertices[] = {
		  // 1
		  -0.9f, -0.5f, 0.0f,  // left 
		  -0.0f, -0.5f, 0.0f,  // right
		  -0.45f, 0.5f, 0.0f,  // top 
		  // 2
		  0.0f, -0.5f, 0.0f,  // left
		  0.9f, -0.5f, 0.0f,  // right
		  0.45f, 0.5f, 0.0f   // top
	  };
    ```

    ```cpp
    // ....

    while (!glfwWindowShouldClose(window)) {
        // ...

        glDrawArrays(GL_TRIANGLES, 0, 6);

        // ...
    }

    // ..
    ```

   </details>

   <details>
   <summary> Exercises 02 sol </summary>

   서로 다른 두 개의 `VAO`와 `VBO`를 사용하여 동일한 두 개의 삼각형을 만드세요

   ```cpp
   float oneTriangle[] = {
		  -0.9f, -0.5f, 0.0f,  // left 
		  -0.0f, -0.5f, 0.0f,  // right
		  -0.45f, 0.5f, 0.0f,  // top 
   };

	 float twoTriangle[] = {
		  0.0f, -0.5f, 0.0f,  // left
		  0.9f, -0.5f, 0.0f,  // right
		  0.45f, 0.5f, 0.0f   // top 
	 };
   ```

   ```cpp
   unsigned int VBOs[2], VAOs[2];
	 glGenVertexArrays(2, VAOs);
	 glGenBuffers(2, VBOs);

	 // 1
	 glBindVertexArray(VAOs[0]);
	 glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	 glBufferData(GL_ARRAY_BUFFER, sizeof(oneTriangle), oneTriangle, GL_STATIC_DRAW);
	 glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	 glEnableVertexAttribArray(0);

	 // 2
	 glBindVertexArray(VAOs[1]);
	 glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	 glBufferData(GL_ARRAY_BUFFER, sizeof(twoTriangle), twoTriangle, GL_STATIC_DRAW);
	 glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	 glEnableVertexAttribArray(0);
   ```

   ```cpp
   while (!glfwWindowShouldClose(window)) {
      // ...
		  glUseProgram(shaderProgram1);
		  glBindVertexArray(VAOs[0]);
		  glDrawArrays(GL_TRIANGLES, 0, 3);

		  glUseProgram(shaderProgram2);
		  glBindVertexArray(VAOs[1]);
		  glDrawArrays(GL_TRIANGLES, 0, 3);
      // ...
   }
   ```

   </details>

   <details>
   <summary> Exercises 03 sol </summary>

   노란색을 출력하는 **Shader** 를 사용하는 두 개의 **Shader** 을 만드세요

   ```cpp
   const char* fragmentShader1Source = "#version 330 core\n"
	 "out vec4 FragColor;\n"
	 "void main()\n"
	 "{\n"
	 "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	 "}\n\0";

   const char* fragmentShader2Source = "#version 330 core\n"
	 "out vec4 FragColor;\n"
	 "void main()\n"
	 "{\n"
	 "   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
	 "}\n\0";
   ```

   ```cpp
   // Shader program 빌드 && 컴파일
	 // ----------------------------
	 // Vertex shader
	 unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	 glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	 glCompileShader(vertexShader);

	 // Fragment shader
	 unsigned int fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
	 glShaderSource(fragmentShader1, 1, &fragmentShader1Source, NULL);
	 glCompileShader(fragmentShader1);

	 unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	 glShaderSource(fragmentShader2, 1, &fragmentShader2Source, NULL);
	 glCompileShader(fragmentShader2);

	 // link shaders
	 unsigned int shaderProgram1 = glCreateProgram();
	 unsigned int shaderProgram2 = glCreateProgram();

	 glAttachShader(shaderProgram1, vertexShader);
	 glAttachShader(shaderProgram1, fragmentShader1);
	 glLinkProgram(shaderProgram1);

	 glAttachShader(shaderProgram2, vertexShader);
	 glAttachShader(shaderProgram2, fragmentShader2);
	 glLinkProgram(shaderProgram2);

	 checkShaderCompiler(vertexShader, "VERTEX");

	 checkShaderCompiler(fragmentShader1, "FRAGMENT");
	 checkShaderCompiler(fragmentShader2, "FRAGMENT");

	 checkShaderCompiler(shaderProgram1, "LINKING");
	 checkShaderCompiler(shaderProgram2, "LINKING");

	 glDeleteShader(vertexShader);
	 glDeleteShader(fragmentShader1);
	 glDeleteShader(fragmentShader2);
   ```

   </details>
      <br/>

[전체 프로젝트 코드(C++)](https://github.com/BOLTB0X/OpenGL-Study/blob/main/VisualStudioVer/OpenGL_Project02/OpenGL_Project02/src/main.cpp)
  
</details>

<details>
<summary> Shaders </summary>

**Practice**

<p align="center">
  <table style="width:100%; text-align:center; border-spacing:5px;">
    <tr>
      <td style="text-align:center; vertical-align:middle;">
        <p align="center">
        <img src="https://github.com/BOLTB0X/OpenGL-Study/blob/main/Img/shader-%EB%B2%84%ED%85%8D%EC%8A%A4%EB%A1%9C%20%EC%83%89%EC%A0%84%EB%8B%AC.jpg?raw=true" alt="Example Image" width="70%"/>
        </p>
      </td>
      <td style="text-align:center; vertical-align:middle;">
        <p align="center">
        <img src="https://github.com/BOLTB0X/OpenGL-Study/blob/main/Img/shader-%EC%9C%A0%EB%8B%88%ED%8F%BC%EC%A0%81%EC%9A%A9.gif?raw=true" alt="Example Image" width="70%"/>
        </p>
      </td>
      <td style="text-align:center; vertical-align:middle;">
        <p align="center">
        <img src="https://github.com/BOLTB0X/OpenGL-Study/blob/main/Img/shader-Attributes%20%EC%B6%94%EA%B0%80.jpg?raw=true" alt="Example Image" width="70%"/>
        </p>
      </td>
    </tr>
    <tr>
      <td style="text-align:center; font-size:14px; font-weight:bold;">
      <p align="center">
      정점으로 Color
      </p>
      </td>
      <td style="text-align:center; font-size:14px; font-weight:bold;">
      <p align="center">
      Uniforms 
      </p>
      </td>
      <td style="text-align:center; font-size:14px; font-weight:bold;">
      <p align="center">
      Attributes
      </p>
      </td>
    </tr>
  </table>
</p>

- Shader Code

   <details>
   <summary> 정점으로 Color 로 변경 </summary>

   ```cpp
   const char* vertexShaderSource = "#version 330 core\n"
	 "layout (location = 0) in vec3 aPos;\n"
   "out vec4 vertexColor;\n"
	 "void main()\n"
   "{\n"
	 "	gl_Position = vec4(aPos, 1.0);\n"
   "	vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"

   "}\0";

   const char* fragmentShaderSource = "#version 330 core\n"
   "out vec4 FragColor;\n"
   "in vec4 vertexColor;\n"
   "void main()\n"
   "{\n"
   "	FragColor = vertexColor;\n"
   "}\n\0";
   ```

   </details>

   <details>
   <summary> Uniforms </summary>

   ```cpp
   const char* vertexShaderSource = "#version 330 core\n"
	 "layout (location = 0) in vec3 aPos;\n"
   "out vec3 ourColor;\n"
	 "void main()\n"
   "{\n"
	 "	gl_Position = vec4(aPos, 1.0);\n"
   "	ourColor = aColor;\n"
   "}\0";

   const char* fragmentShaderSource = "#version 330 core\n"
   "out vec4 FragColor;\n"
   "uniform vec4 ourColor;\n"
   "void main()\n"
   "{\n"
   "	FragColor = ourColor;\n"
   "}\n\0";
   ```

   ```cpp
   while (!glfwWindowShouldClose(window)) {
      // ...

	    double timeValue = glfwGetTime();
	    float greenValue = static_cast<float>(sin(timeValue) / 2.0 + 0.5);
	    int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

	    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

      // ..
   }
   ```

   </details>

   <details>
   <summary> Attributes 로 전달 </summary>

   ```cpp
   // 정점 수정
   float vertices[] = {
      // positions         // colors
      0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
      -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
      0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
   }; 
   ```

   ```cpp
   const char* vertexShaderSource = "#version 330 core\n"
	 "layout (location = 0) in vec3 aPos;\n"
   "layout (location = 1) in vec3 aColor;\n"
   "out vec3 ourColor;\n"
	 "void main()\n"
   "{\n"
	 "	gl_Position = vec4(aPos, 1.0);\n"
   "	ourColor = aColor;\n"
   "}\0";

   const char* fragmentShaderSource = "#version 330 core\n"
   "out vec4 FragColor;\n"
   "in vec3 ourColor;\n"
   "void main()\n"
   "{\n"
   "	FragColor = vec4(ourColor, 1.0f);\n"
   "}\n\0";
   ```

   - 다른 **정점 속성(Attributes)** 을 추가하고 **VBO** 의 메모리를 업데이트했기 때문에 정점 속성 포인터를 다시 구성해야 함

   - **VBO** 의 메모리에 업데이트된 데이터는 이제 다음과 같음
   
   <p align="center">
      <img src="https://learnopengl.com/img/getting-started/vertex_attribute_pointer_interleaved.png" alt="Example Image" width="80%">
      <br/>
      이미지 출처: learnopengl.com
   </p>

   - 현재 레이아웃을 알고 있으면 `glVertexAttribPointer`로 정점 형식을 업데이트할 수 있음

   ```cpp
   // position attribute
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
   glEnableVertexAttribArray(0);
   // color attribute
   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
   glEnableVertexAttribArray(1);
   ```

   </details>
   <br/>

- Custom Shader Class

   <details>
   <summary> Code </summary>
   
   ```cpp
   #ifndef SHADER_H
   #define SHADER_H

   #include <glad/glad.h>

   #include <string>
   #include <fstream>
   #include <sstream>
   #include <iostream>

   class Shader
   {
   public:
       unsigned int ID;
       // constructor generates the shader on the fly
       // ------------------------------------------------------------------------
       Shader(const char* vertexPath, const char* fragmentPath)
       {
           // 1. retrieve the vertex/fragment source code from filePath
           std::string vertexCode;
           std::string fragmentCode;
           std::ifstream vShaderFile;
           std::ifstream fShaderFile;
           // ensure ifstream objects can throw exceptions:
           vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
           fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
           try 
           {
               // open files
               vShaderFile.open(vertexPath);
               fShaderFile.open(fragmentPath);
               std::stringstream vShaderStream, fShaderStream;
               // read file's buffer contents into streams
               vShaderStream << vShaderFile.rdbuf();
               fShaderStream << fShaderFile.rdbuf();
               // close file handlers
               vShaderFile.close();
               fShaderFile.close();
               // convert stream into string
               vertexCode   = vShaderStream.str();
               fragmentCode = fShaderStream.str();
           }
           catch (std::ifstream::failure& e)
           {
               std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
           }
           const char* vShaderCode = vertexCode.c_str();
           const char * fShaderCode = fragmentCode.c_str();
           // 2. compile shaders
           unsigned int vertex, fragment;
           // vertex shader
           vertex = glCreateShader(GL_VERTEX_SHADER);
           glShaderSource(vertex, 1, &vShaderCode, NULL);
           glCompileShader(vertex);
           checkCompileErrors(vertex, "VERTEX");
           // fragment Shader
           fragment = glCreateShader(GL_FRAGMENT_SHADER);
           glShaderSource(fragment, 1, &fShaderCode, NULL);
           glCompileShader(fragment);
           checkCompileErrors(fragment, "FRAGMENT");
           // shader Program
           ID = glCreateProgram();
           glAttachShader(ID, vertex);
           glAttachShader(ID, fragment);
           glLinkProgram(ID);
           checkCompileErrors(ID, "PROGRAM");
           // delete the shaders as they're linked into our program now and no longer necessary
           glDeleteShader(vertex);
           glDeleteShader(fragment);
       }
       // activate the shader
       // ------------------------------------------------------------------------
       void use() 
       { 
           glUseProgram(ID); 
       }
       // utility uniform functions
       // ------------------------------------------------------------------------
       void setBool(const std::string &name, bool value) const
       {         
           glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
       }
       // ------------------------------------------------------------------------
       void setInt(const std::string &name, int value) const
       { 
           glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
       }
       // ------------------------------------------------------------------------
       void setFloat(const std::string &name, float value) const
       { 
           glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
       }
       
    private:
       // utility function for checking shader compilation/linking errors.
       // ------------------------------------------------------------------------
       void checkCompileErrors(unsigned int shader, std::string type)
       {
           int success;
           char infoLog[1024];
           if (type != "PROGRAM")
           {
               glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
               if (!success)
               {
                   glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                   std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
               }
           }
           else
           {
               glGetProgramiv(shader, GL_LINK_STATUS, &success);
               if (!success)
               {
                   glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                   std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
               }
           }
       }
   };
   ```

   ```cpp
   int main(void) {
      // ...

      Shader ourShader("vertex_shader.vs", "fragment_shader.fs");

      // ...

      while (!glfwWindowShouldClose(window)) {
          // ...
          ourShader.use();
		      glBindVertexArray(VAO);
		      glDrawArrays(GL_TRIANGLES, 0, 3);
          // ...
      }

      // ...
   }
   ```

   </details>
   <br/>

**Exercises**

<p align="center">
  <table style="width:100%; text-align:center; border-spacing:5px;">
    <tr>
      <td style="text-align:center; vertical-align:middle;">
        <p align="center">
        <img src="https://github.com/BOLTB0X/OpenGL-Study/blob/main/Img/3-Exercise01.jpg?raw=true" alt="Example Image" width="70%"/>
        </p>
      </td>
      <td style="text-align:center; vertical-align:middle;">
        <p align="center">
        <img src="https://github.com/BOLTB0X/OpenGL-Study/blob/main/Img/3-Exercise02.jpg?raw=true" alt="Example Image" width="70%"/>
        </p>
      </td>
      <td style="text-align:center; vertical-align:middle;">
        <p align="center">
        <img src="https://github.com/BOLTB0X/OpenGL-Study/blob/main/Img/3-Exercise03.jpg?raw=true" alt="Example Image" width="70%"/>
        </p>
      </td>
    </tr>
    <tr>
      <td style="text-align:center; font-size:14px; font-weight:bold;">
      <p align="center">
      e01
      </p>
      </td>
      <td style="text-align:center; font-size:14px; font-weight:bold;">
      <p align="center">
      e02 
      </p>
      </td>
      <td style="text-align:center; font-size:14px; font-weight:bold;">
      <p align="center">
      e03
      </p>
      </td>
    </tr>
  </table>
</p>

- Solution

   <details>
   <summary> Exercises 01 sol  </summary>
   
     삼각형이 거꾸로 되도록 Vertex Shader를 조정하라

    ```cpp
    #version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aColor;

    out vec3 ourColor;

    void main()
    {
       gl_Position = vec4(aPos.x, -aPos.y, aPos.z, 1.0);
       ourColor = aColor;
    }
    ```
   </details>

   <details>
   <summary> Exercises 02 sol </summary>

   균일한 값을 통해 수평 `offset`을 지정하고 이 `offset` 값을 사용하여 정점 셰이더에서 삼각형을 화면 오른쪽으로 이동시켜라

   ```cpp
   #version 330 core
   layout (location = 0) in vec3 aPos;
   layout (location = 1) in vec3 aColor;

   out vec3 ourColor;

   uniform float xOffset;

   void main()
   {
       gl_Position = vec4(aPos.x + xOffset, aPos.y, aPos.z, 1.0);
       ourColor = aColor;
   }
   ```

   ```cpp
   while (!glfwWindowShouldClose(window)) {
      // ...
		  ourShader.setFloat("xOffset", 0.5f);
      // ...
   }
   ```

   </details>

   <details>
   <summary> Exercises 03 sol </summary>

   `out` 키워드를 사용하여 정점 위치를 fragment Shader에 출력하고 fragment의 색상을 이 정점 위치와 같게 설정합니다(정점 위치 값이 삼각형 전체에 걸쳐 보간되는 방식을 확인하세요). 
   
   이렇게 하는 데 성공했다면 다음 질문에 답해보세요: 왜 삼각형의 왼쪽 아래 면이 검은색일까요?

   ```cpp
   #version 330 core
   out vec4 FragColor;

   in vec3 ourPosition;

   void main()
   {
       FragColor = vec4(ourPosition, 1.0f);
   }
   ```

   ```cpp
   #version 330 core
   layout (location = 0) in vec3 aPos;

   out vec3 ourPosition;

   void main()
   {
       gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
       ourPosition = aPos;
   }
   ```

   **정점 위치(`aPos`)가 색상 값으로 쓰이면서 음수 좌표는 검은색으로 표현되기 때문**

   - `aPos` = `(0.5, -0.5, 0.0)` -> 빨간색 `(1.0, 0.0, 0.0)`

   - `aPos` = `(-0.5, -0.5, 0.0)` -> 검은색 `(0.0, 0.0, 0.0)`

   - `aPos` = `(0.0, 0.5, 0.0)` -> 파란색 `(0.0, 0.0, 1.0)`

   삼각형의 왼쪽 아래 정점이 `(0,0,0)` 이라 검은색이 되고, 나머지 부분이 부드럽게 보간되면서 자연스럽게 색상이 변함

   </details>
   <br/>

[전체 프로젝트 코드(C++)](https://github.com/BOLTB0X/OpenGL-Study/tree/main/VisualStudioVer/OpenGL_Project03)
  

</details>

<details>
<summary> Textures </summary>

**Practice**

<p align="center">
  <table style="width:100%; text-align:center; border-spacing:5px;">
    <tr>
      <td style="text-align:center; vertical-align:middle;">
        <p align="center">
        <img src="https://github.com/BOLTB0X/OpenGL-Study/blob/main/Img/4-1-Texture-wall.jpg?raw=true" alt="Example Image" width="70%"/>
        </p>
      </td>
      <td style="text-align:center; vertical-align:middle;">
        <p align="center">
        <img src="https://github.com/BOLTB0X/OpenGL-Study/blob/main/Img/4-2-Texture-container.jpg?raw=true" alt="Example Image" width="70%"/>
        </p>
      </td>
    </tr>
    <tr>
      <td style="text-align:center; font-size:14px; font-weight:bold;">
      <p align="center">
      Wall
      </p>
      </td>
      <td style="text-align:center; font-size:14px; font-weight:bold;">
      <p align="center">
      Container 
      </p>
      </td>
    </tr>
  </table>
</p>

<p align="center">
  <table style="width:100%; text-align:center; border-spacing:5px;">
    <tr>
      <td style="text-align:center; vertical-align:middle;">
        <p align="center">
        <img src="https://github.com/BOLTB0X/OpenGL-Study/blob/main/Img/4-3-Texture-mix.jpg?raw=true" alt="Example Image" width="70%"/>
        </p>
      </td>
      <td style="text-align:center; vertical-align:middle;">
        <p align="center">
        <img src="https://github.com/BOLTB0X/OpenGL-Study/blob/main/Img/4-4-Texture-mix-face.jpg?raw=true" alt="Example Image" width="70%"/>
        </p>
      </td>
      <td style="text-align:center; vertical-align:middle;">
        <p align="center">
        <img src="https://github.com/BOLTB0X/OpenGL-Study/blob/main/Img/4-5-Texture-mix-face-y.jpg?raw=true" alt="Example Image" width="70%"/>
        </p>
      </td>
    </tr>
    <tr>
      <td style="text-align:center; font-size:14px; font-weight:bold;">
      <p align="center">
      Mix Color
      </p>
      </td>
      <td style="text-align:center; font-size:14px; font-weight:bold;">
      <p align="center">
      Mix 텍스처 1 
      </p>
      </td>
      <td style="text-align:center; font-size:14px; font-weight:bold;">
      <p align="center">
      Mix 텍스처 2
      </p>
      </td>
    </tr>
  </table>
</p>

- 텍스처 로드

   <details>
   <summary> Wall , Container </summary>

   ```cpp
   // wall : 정점 좌표
   float vertices[] = {
    // positions         // colors          // texture coords
      0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   1.0f, 0.0f,   // bottom right
	   -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   0.0f, 0.0f,   // bottom left
	    0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   0.5f, 1.0f    // top
	 };
   ```

   ```cpp
   float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	 };

	 unsigned int indices[] = {
		 0, 1, 3, // first triangle
		 1, 2, 3  // second triangle
	 };
   ```

   ```cpp
   unsigned int texture;
   glGenTextures(1, &texture);
   glBindTexture(GL_TEXTURE_2D, texture);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   int width, height, nrChannels;
   unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
   if (data) {
       glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
       glGenerateMipmap(GL_TEXTURE_2D);
   } else {
       std::cout << "Failed to load texture" << std::endl;
   }
   stbi_image_free(data);
   ```

   ```cpp
	 // Render Loop
	 // ------------
	 while (!glfwWindowShouldClose(window)) {
      // ...
       
      glBindTexture(GL_TEXTURE_2D, texture);
      glBindVertexArray(VAO);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

      // ...
   }
   ```
   
   </details>

   <details>
   <summary> Mix </summary>

   ```cpp
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
	 } else {
		 std::cout << "Failed to load texture" << std::endl;
	 }
	 stbi_image_free(data);

	 // 각 샘플러가 속하는 텍스처 단위를 OpenGL에 알림(한 번만 수행하면 됨)
	 // -------------------------------------------------------------------------------------------
	 ourShader.use(); // 유니폼을 설정하기 전에 셰이더를 활성화/사용하는 것을 잊지 말길
	 glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
	 ourShader.setInt("texture2", 1);
   ```

   ```cpp
	 // Render Loop
	 // ------------
	 while (!glfwWindowShouldClose(window)) {
      // ...

      glActiveTexture(GL_TEXTURE0);
		  glBindTexture(GL_TEXTURE_2D, texture1);
		  glActiveTexture(GL_TEXTURE1);
		  glBindTexture(GL_TEXTURE_2D, texture2);

      // ...
   }
   ```

   ```cpp
   // 대칭
   stbi_set_flip_vertically_on_load(true);
   ```

   </details>
   <br/>

- GLSL

   <details>
   <summary> Wall , Container </summary>

   ```cpp
   // Vertex Shader
   #version 330 core
   layout (location = 0) in vec3 aPos;
   layout (location = 1) in vec3 aColor;
   layout (location = 2) in vec2 aTexCoord;
   
   out vec3 ourColor;
   out vec2 TexCoord;
   
   void main()
   {
       gl_Position = vec4(aPos, 1.0);
       ourColor = aColor;
       TexCoord = vec2(aTexCoord.x, aTexCoord.y);
   }
   ```

   ```cpp
   // Fragment Shader
   #version 330 core
   out vec4 FragColor;
  
   in vec3 ourColor;
   in vec2 TexCoord;

   uniform sampler2D ourTexture;

   void main()
   {
       FragColor = texture(ourTexture, TexCoord);
   }
   ```

   </details>

   <details>
   <summary> Mix </summary>

   ```cpp
   // Color Mix
   // Fragment Shader
   FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);
   ```

   ```cpp
   // 텍스처 2개
   // Fragment Shader
   #version 330 core
   out vec4 FragColor;
  
   in vec3 ourColor;
   in vec2 TexCoord;

   uniform sampler2D texture1;
   uniform sampler2D texture2;

   void main()
   {
       FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
   }
   ```
   </details>
   <br/>

**Exercises**

<p align="center">
  <table style="width:100%; text-align:center; border-spacing:5px;">
    <tr>
      <td style="text-align:center; vertical-align:middle;">
        <p align="center">
        <img src="https://github.com/BOLTB0X/OpenGL-Study/blob/main/Img/4-Exercise01.jpg?raw=true" alt="Example Image" width="70%"/>
        </p>
      </td>
      <td style="text-align:center; vertical-align:middle;">
        <p align="center">
        <img src="https://github.com/BOLTB0X/OpenGL-Study/blob/main/Img/4-Exercise02.jpg?raw=true" alt="Example Image" width="70%"/>
        </p>
      </td>
    </tr>
    <tr>
      <td style="text-align:center; font-size:14px; font-weight:bold;">
      <p align="center">
      e01
      </p>
      </td>
      <td style="text-align:center; font-size:14px; font-weight:bold;">
      <p align="center">
      e02
      </p>
      </td>
    </tr>
  </table>
</p>

<p align="center">
  <table style="width:100%; text-align:center; border-spacing:5px;">
    <tr>
      <td style="text-align:center; vertical-align:middle;">
        <p align="center">
        <img src="https://github.com/BOLTB0X/OpenGL-Study/blob/main/Img/4-Exercise03.jpg?raw=true" alt="Example Image" width="70%"/>
        </p>
      </td>
      <td style="text-align:center; vertical-align:middle;">
        <p align="center">
        <img src="https://github.com/BOLTB0X/OpenGL-Study/blob/main/Img/4-Exercise04.gif?raw=true" alt="Example Image" width="70%"/>
        </p>
      </td>
    </tr>
    <tr>
      <td style="text-align:center; font-size:14px; font-weight:bold;">
      <p align="center">
      e03
      </p>
      </td>
      <td style="text-align:center; font-size:14px; font-weight:bold;">
      <p align="center">
      e04
      </p>
      </td>
    </tr>
  </table>
</p>

- Solution

   <details>
   <summary> Exercises 01 sol  </summary>
   
    fragment shader 를 변경하여 행복한 얼굴만 반대 방향/반대 방향을 바라보도록 수정해라

    ```cpp
    #version 330 core
    out vec4 FragColor;
    in vec3 ourColor;
    in vec2 TexCoord;
    
    uniform sampler2D texture1;
    uniform sampler2D texture2;

    void main()
    {
       FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(1.0 - TexCoord.x, TexCoord.y)), 0.2);
    }
    ```

   </details>

   <details>
   <summary> Exercises 02 sol </summary>
   
   `0.0f ~ 1.0f` 대신 `0.0f ~ 2.0f` 범위의 텍스처 좌표를 지정하여 다양한 텍스처 래핑 방법을 실험해 보세요.
   
   가장자리에 고정된 단일 컨테이너 이미지에 4개의 스마일리 얼굴을 표시할 수 있는지 확인해 보세요

   ```cpp
   // ...

   glGenTextures(1, &texture1);
   glBindTexture(GL_TEXTURE_2D, texture1);
   // set the texture wrapping parameters
   
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // 수정
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   // ...
   ```

   ```cpp
   // ...

   glGenTextures(1, &texture2);
   glBindTexture(GL_TEXTURE_2D, texture2);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// 수정
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   // ...
   ```

   </details>

   <details>
   <summary> Exercises 03 sol </summary>

   텍스처 이미지의 중앙 픽셀만 직사각형에 표시하여 텍스처 좌표를 변경하여 개별 픽셀이 보이도록 하세요. 텍스처 필터링 방법을 `GL_NEAREST` 로 설정하여 픽셀을 더 명확하게 해보세요

   ```cpp
   // ...
   glGenTextures(1, &texture1);
   glBindTexture(GL_TEXTURE_2D, texture1);
   
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // GL_CLAMP_TO_EDGE
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   
   // set texture filtering parameters
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // set texture filtering to nearest neighbor to clearly see the texels/pixels
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   ```

   </details>

   <details>
   <summary> Exercises 04 sol </summary>
   
   두 텍스처가 보이는 양을 변경하려면 믹스 함수의 세 번째 매개변수로 균일한 변수를 사용합니다. 
   
   
   위쪽 및 아래쪽 화살표 키를 사용하여 컨테이너 또는 스마일리 얼굴이 보이는 양을 변경해보세요

   ```cpp
   void processInput(GLFWwindow *window) {
      if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
          glfwSetWindowShouldClose(window, true);

      if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
      {
          mixValue += 0.01f;
          if(mixValue >= 1.0f)
              mixValue = 1.0f;
      }
      if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
      {
          mixValue -= 0.01f;
          if (mixValue <= 0.0f)
            mixValue = 0.0f;
      }
   }
   ```

   ```cpp
   while (!glfwWindowShouldClose(window)) {
      // ...
      ourShader.setFloat("mixValue", mixValue);
      // ...
   }
   ```

   ```cpp
   #version 330 core
   out vec4 FragColor;
  
   in vec3 ourColor;
   in vec2 TexCoord;

   uniform float mixValue;

   uniform sampler2D texture1;
   uniform sampler2D texture2;

   void main()
   {
       FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixValue);
   }
   ```

   </details>
      <br/>

[전체 프로젝트 코드(C++)](https://github.com/BOLTB0X/OpenGL-Study/blob/main/VisualStudioVer/OpenGL_Project02/OpenGL_Project02/src/main.cpp)

</details>

## 참고

- [Learn OpenGL](https://learnopengl.com/)

- [티스토리-꽉퓨타의 SW 이야기(OpenGL - 윈도우에 개발환경 구축하기)](https://kwak-story.tistory.com/3)