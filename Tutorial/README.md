# Hello window

창(window)를 띄울려면 헤더파일을 추가해야 함

```cpp
#include <glad/glad.h>
#include <GLFW/glfw3.h>
```

glad에서 glfw의 일부분의 내용을 포함하고 있기 때문에 glad.h를 glfw3.h보다 먼저 include

## GLFW initialize and configure

```cpp
int main() {
    glfwInit(); // 1
    // 2
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    return 0;
}
```

1. glfwInit(): GLFW 초기화
   <br/>

2. glfwWindowHint: GLFW 옵션 구성

   - major, minor 버전에 3.3을 사용할 것 이라고 GLFW에게 선언
     <br/>

   - OpenGL 3.3 혹은 이상이 설치되어있어야 함
     <br/>

   - GLFW에게 명시적으로 core-profile을 사용하고 싶다고 알림
     <br/>

   - core-profile: 필요하지 않은 이전 버전과 호환되는 기능 없이 OpenGL 기능의 더 작은 하위 집합에 액세스할 수 있다는 의미
     <br/>

   - Mac OS X 에서는 glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 추가
     <br/>

## GLFW window creation

```cpp
GLFWwindow* window = glfwCreateWindow(800, 600, "Learn OpenGL", NULL, NULL);
if (window == NULL) {
    std::cout << "GLFW window 생성 실패" << std::endl;
    glfwTerminate();
    return -1;
}
```

object를 반환하며 context 생성(그림을 그리게 되는 것)

1. glfwCreateWindow(): window object 생성

   - window width와 height, window name, monitor, share
     <br/>

2. glfwTerminate(): glfw 종료

## GLAD

```cpp
if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "GLAD 초기화 실패" << std::endl;
    return -1;
}
```

OpenGL 함수를 호출하기 전에 GLAD를 초기화해야함

1. gladLoadGLLoader: OS에 특정한 OpenGL 함수 포인터의 주소를 로드하기 위해 함수를 GLAD에 전달
   <br/>

2. glfwGetProcAddress: 컴파일하는 OS에 따라 맞게 참조/정의하도록 함

## Viewport

렌더링을 시작하기 전에 마지막으로 한 가지 작업을 수행해야 함 -> OpenGL에게 렌더링 창의 크기를 알려주어야함

```cpp
glViewport(0, 0, width, height);
```

- 1, 2번째 매개변수 왼쪽 하단 corner (x, y)
  <br/>

- 3, 4번째 rendering window의 width 와 height

## framebuffer_size_callback

window 크기가 조정될 때마다 호출되는 창에 콜백 함수를 등록, user가 window 크기를 조정하는 순간 뷰포트도 조정되어야 함

```cpp
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
   glViewport(0, 0, width, height);
}

// ...

glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
```

- GLFW window가 resize될 때마다, callback 함수를 호출을 알림
  <br/>

- 창(window) 생성하고 render loop가 initiate되기 전에 callback함수 등록

## Ready your engines

pplication을 그리고 바로 window를 종료하지 않기 위해서는 사용자의 input을 기다리거나 명시적으로 그만하기를 요청할 때까지

window에 application을 계속 그리거나/나타내야 함 -> render loop

```cpp
while(!glfwWindowShouldClose(window)) {
   glfwSwapBuffers(window);
   glfwPollEvents();
}
```

1. glfwWindowShouldClose()

   - loop가 돌때마다 GLFW가 close명령을 받았는지를 확인
     <br/>

   - true를 return하면 rendering 종료
     <br/>

2. The glfwPollEvents()

   - keyboard input or mouse movement event 발생여부 확인
     <br/>

3. glfwSwapBuffers()

   - GLFW window 각의 pixel의 색정보를 가지고 있는 커다란 2D buffer를 swap
     <br/>

   - 이 loop에서 swap을 반복하면서 나중에 rendering할때 screen에 output을 나타내게될 것

## Double buffer

application이 단일 버퍼에서 그림을 그리면 깜박임 현상이 발생할 수있음

이는 이미지가 즉시 표시되지 않고 왼쪽에서 오른쪽, 위에서 아래로 픽셀 단위로 그려지기 때문

이를 해결하기 위해 더블 버퍼링을 사용

최종 출력 이미지를 화면에 보여주는 프론트 버퍼와 렌더링 명령이 그려지는 백 버퍼를 사용

모든 렌더링 명령이 완료되면 백 버퍼와 프론트 버퍼를 교체하여, 렌더링 중인 이미지가 표시되지 않도록 함

## Input

```cpp
void processInput(GLFWwindow *window) {
   if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
     glfwSetWindowShouldClose(window, true);
}
```

- 사용자의 input을 받아서 GLFW를 control하기위해 callback함수
  <br/>

- glfwGetKey(): user가 escape key를 눌렀는지 검사

```cpp
while (!glfwWindowShouldClose(window)) {
   processInput(window);
   glfwSwapBuffers(window);
   glfwPollEvents();
}
```

- render loop == frame

## Ready your engines(Rendering)

여기 command는 loop에 frame마다 실행

```cpp
// render loop
while(!glfwWindowShouldClose(window)) {
   // input
   processInput(window);

   // rendering commands here
   glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

   glClear(GL_COLOR_BUFFER_BIT);

   // check and call events and swap the buffers
   glfwPollEvents();
   glfwSwapBuffers(window);
}
```

- 먼저 frame의 시작에 screen을 clear 그러지 않을경우 이전에 그렸던 내용이 남아 있음
  <br/>

- glClearColor(): state-setting 함수

  - screen의 color buffer를 clear할 수 있음
    <br/>

  - screen의 color buffer를 clear할때 다시 채울 color의 configuration을 setting
    <br/>

  - glCearColor로 state를 set하면 glClear가 호출될때 그 state로 color buffer를 clear

- glClear(): current state을 가져오는 state-using함수

  - glClear는 어느 특정 버퍼를 선택해서 clear 가능
    <br/>

  - clear하고자 하는 버퍼를 bit로 선택
    <br/>

  - (GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT, GL_STENCIL_BUFFER_BIT.)
    <br/>

  - color buffer만을 비울것 이기 때문에 위와 같이 선택

## 실행 화면

<img width="788" alt="window" src="https://github.com/BOLTB0X/OpenGL-Tutorial/assets/83914919/07b85be6-fc47-4e3d-84a7-ea6cdd417515">

## 원본

[Hello Window](https://learnopengl.com/Getting-started/Hello-Window)
