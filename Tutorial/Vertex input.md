# Vertex input

> OpenGL은 3D 그래픽 라이브러리이므로 OpenGL에서 지정하는 모든 좌표는 3D(x, y 및 z 좌표)
> OpenGL은 단순히 모든 3D 좌표를 화면의 2D 픽셀로 변환하지 않음

무언가를 그리기 시작하려면 먼저 OpenGL에 입력 정점 데이터를 제공해야 함

OpenGL은 3개 축(x, y 및 z) 모두에서 -1.0과 1.0 사이의 특정 범위에 있는 경우에만 3D 좌표를 처리함

소위 정규화된 장치 좌표 범위 내의 모든 좌표는 결국 screen에 표시(이 영역 외부의 모든 좌표는 표시되지 X)

우리는 단일 삼각형을 렌더링하기를 원하기 때문에 각 정점이 3D 위치를 갖는 총 3개의 정점(vertex)을 지정해야 함

```cpp
float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};
```

- 부동 배열의 정규화된 장치 좌표(OpenGL의 가시 영역)에서 이를 정의
  <br/>

- 단일 삼각형을 렌더링하기를 원하기 때문에 각 정점(vertex)이 3D 위치를 갖는 총 3개의 정점(vertex)을 지정
  <br/>

- 부동 배열의 정규화된 장치 좌표(OpenGL의 가시 영역)로 정의
  <br/>

- OpenGL은 3D 공간에서 작동하기 때문에 각 꼭지점의 z 좌표가 0.0인 2D 삼각형을 렌더링함
  <br/>

- 이렇게 하면 삼각형의 깊이가 동일하게 유지되어 2D처럼 보임
  <br/>

- **Normalized Device Coordinates (NDC)**
  ![NDC1](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FJhv4V%2FbtqAsTf1Q09%2FwqAg7Q1ehXJ7XBoVgeofPK%2Fimg.png)

  - 정규화 된 좌표계로 플레이어는 모니터로 게임/영상의 화면을 봄, 따라서 결국 user가 보는 화면은 2D인 2차원
    <br/>
  - 공간이 3D여도 결국 랜더링을 통해 2D로 변환 되는데, 이러한 변환을 투영이라 함
    <br/>

  - OpenGL에서는 왼손 좌표계를 사용
    <br/>

  ![NDC2](https://learnopengl.com/img/getting-started/ndc.png)

  - 정점 셰이더에서 정점 좌표가 처리되면 x, y 및 z 값이 -1.0에서 1.0까지 변하는 작은 공간인 정규화된 장치 좌표에 있어야 함
    <br/>

  - 이 범위를 벗어나는 모든 좌표는 삭제되거나 잘려지고 화면에 표시되지 않음
    <br/>

  - 아래에서는 정규화된 장치 좌표 내에서 지정한 삼각형을 볼 수 있음(z축 무시)
    <br/>

  **NDC 좌표계는 뷰포트 transform(glViewport)을 통해 screen-space 좌표계으로 바꿈**
  <br/>

  **즉 바뀐 좌표계가 fragment shader를 거쳐 fragments로 바뀌게 되는 것**

Vertex data를 그래픽 파이프의 첫번째 단계 vertex shader로 보냄

GPU에 정점들을 위한 메모리를 할당해야하고 OpenGL이 이 메모리를 어떻게 해석해야 하는지 configure 해주고 그래픽 카드로 data를 어떻게 보낼 것인지 specify하면 최종적으로 vertex shader가 메모리의 정점들을 process해야 함

Vertex Buffer Objects(VBO)로 이 메모리를 관리함

- glGenBuffers

  - 많은 수의 vertices를 gpu 메모리안에 저장할 수 있음
    <br/>

  - 이 버퍼의 사용으로 큰 data batch를 한번에 그래픽 카드로 보낼 수 있고 메모리에 유지되도록 하는데 그 이유는 좌표를 하나씩 보낼 필요가 없는 것  
    <br/>

  - CPU에서 data를 그래픽 카드에게 보내는 것은 매우 느리기 때문에 가능한 한번에 많은 data를 보내야 함
    <br/>

  - 그렇게 data가 그래픽 카드 메모리에 도착하면 vertex shader가 거의 즉시 vertices에게 극도로 빠른 속도로 접근할 수 있게 되는 것
    <br/>

  - 이 buffer는 첫 챕터에서 말했던 그 object, unique ID가 존재하며 glGenBuffers 함수로 만들 수 있음
    <br/>

  ```cpp
  unsigned int VBO;
  glGenBuffers(1, &VBO);
  ```

   <br/>

- glBindBuffer

  - OpenGL은 많은 종류의 buffer objects가 있는데 그중 vertex buffer object의 type은 GL_ARRAY_BUFFER
    <br/>

  - glBindBuffer는 여러 buffer를 bind
    <br/>

  ```cpp
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  ```

  <br/>

- glBufferData(GL_ARRAY_BUFFER, VBO)

  - currently bound buffer, VBO버퍼를 GL_ARRAY_BUFFER target과 bind시킴
    <br/>

  - glBufferData function 으로 이전에 정의했던 vertex를 buffer memory로 복사
    <br/>

    ```cpp
    glBufferData(GL_ARRAY_BUFFER, VBO)
    ```

    <br/>

- glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW)

  ```cpp
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  ```

  > glBufferData는 사용자가 정의한 data를 currently bound buffer로 복사하는 역할을 한다.

    <br/>

  - 1번째 인자는 data를 복사해서 가져다 두고 싶은 buffer의 타입 2번째 인자는 전달하려는 data의 크기(bytes)
    <br/>

  - 3번째 인자는 보내려고 하는 실제 데이터의 주소이고 4번째 인자는 그래픽 카드가 이 데이터를 어떻게 사용하는지에 대한 configuration
    <br/>

  - GL_STREAM_DRAW : data가 딱 한번 set되고 GPU에 의해 가끔 사용됨
    <br/>

  - GL_STATIC_DRAW : data가 딱 한번 set되고 GPU에 의해 자주 사용됨
    <br/>

  - GL_DYNAMIC_DRAW : data가 빈번하게 set되고 GPU에 의해 자주 사용됨
    <br/>

  - 삼각형의 위치에 대한 data가 변하지 않고 자주 사용될 것이기 때문에 GL_STATIC_DRAW가 가장 알음
    <br/>

  - GL_DYNAMIC_DRAW를 사용하면 graphics card의 write 작업이 매우 빠르게 되도록 할 수 있음
    <br/>

  - VBO 라는 이름의 vertex buffer object로 vertex data를 그래픽카드 메모리에 저장했다면, 이제 정점(Vertex)와 fragment shader를 생성해야 함

## 참고

[원본](https://learnopengl.com/Getting-started/Hello-Triangle)

[블로그 참고 - 1](https://jsdysw.tistory.com/83)

[블로그 참고 - 2](https://sonagi87174.tistory.com/26)
