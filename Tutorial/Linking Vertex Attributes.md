# Linking Vertex Attributes

> 꼭짓점 셰이더를 사용하면 원하는 입력을 꼭짓점 속성의 형태로 지정이 가능

이는 유연성이 뛰어나지만 입력 데이터의 어느 부분이 꼭짓점 셰이더의 어느 꼭짓점 속성에 전달되는지 수동으로 지정해야 함을 의미

**즉 이는 렌더링하기 전에 OpenGL이 정점 데이터를 해석하는 방법을 지정해야 함을 의미**

_정점 버퍼 데이터의 형식은 다음과 같음_

![Vertex Attributes](https://learnopengl.com/img/getting-started/vertex_attribute_pointer.png)

- 위치 데이터는 32비트(4바이트) 부동 소수점 값으로 저장이 됌
  <br/>

- 각 위치는 해당 값 중 3개로 구성
  <br/>

- 각 3개 값 세트 사이에는 공백(또는 다른 값)이 없고 값은 배열에 빽빽하게 들어있음
  <br/>

- data의 첫 번째 값은 버퍼의 시작 부분에 있음
  <br/>

이러한 지식을 바탕으로 우리는 OpenGL이 glVertexAttribPointer를 사용하여 정점 데이터(정점 속성별)를 어떻게 해석해야 하는지 알 수 있음

```cpp
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
```

glVertexAttribPointer 함수에는 꽤 많은 매개변수가 존재

1. 매개변수는 구성하려는 정점 속성을 지정
   레이아웃(위치 = 0)을 사용하여 정점 셰이더에서 위치 정점 속성의 위치를 ​​지정
   <br/>

   이는 정점 속성의 위치를 ​​0으로 설정하고 이 정점 속성에 데이터를 전달하려고 하므로 0을 전달
   <br/>

2. 다음 argument 정점 속성의 크기를 지정: vertex 속성은 vec3이므로 3개의 값으로 구성
   <br/>

3. argument는 GL_FLOAT(GLSL의 vec\*는 부동 소수점 값으로 구성됨)인 데이터 유형을 지정
   <br/>

4. argument는 데이터를 정규화할지 여부를 지정 정수 데이터 유형(int, byte)을 입력
   <br/>

   이를 GL_TRUE로 설정한 경우 정수 데이터는 0(또는 부호 있는 데이터의 경우 -1)으로 정규화되고 부동 소수점으로 변환되면 1로 정규화되는 것
   <br/>

   이는 우리와 관련이 없으므로 GL_FALSE로 두겠음
   <br/>

5. argument는 보폭(stride)으로 알려져 있으며 연속적인 정점 속성 사이의 공간을 알려줌
   <br/>

   다음 위치 데이터 세트는 플로트 크기의 정확히 3배에 위치하므로 해당 값을 보폭으로 지정
   <br/>

   배열이 빡빡하게 패킹되어 있다는 것을 알고 있으므로(다음 정점 속성 값 사이에 공백이 없음) OpenGL이 스트라이드를 결정하도록 보폭을 0으로 지정이 가능(이것은 값이 촘촘하게 패킹된 경우에만 작동)
   <br/>

   더 많은 정점 속성이 있을 때마다 각 정점 속성 사이의 간격을 신중하게 정의해야 하지만 나중에 이에 대한 더 많은 예를 보게 될 것
   <br/>

6. 매개변수는 void\* 유형이므로 이상한 캐스트가 필요, 버퍼에서 위치 데이터가 시작되는 offset
   <br/>

   위치 데이터는 데이터 배열의 시작 부분에 있으므로 이 값은 0으로 설정

<br/>

> 각 정점 속성은 VBO가 관리하는 메모리에서 데이터를 가져오고 데이터를 가져오는 VBO(여러 VBO를 가질 수 있음)는 **glVertexAttribPointer**를 호출할 때 현재 GL_ARRAY_BUFFER에 바인딩된 VBO에 의해 결정
> 이전에 정의된 VBO는 **glVertexAttribPointer**를 호출하기 전에 여전히 바인딩되어 있으므로 정점 속성 0은 이제 해당 정점 데이터와 연결

이제 OpenGL이 정점 데이터를 해석하는 방법을 지정했으므로 정점 속성 위치를 인수로 제공하는 **glEnableVertexAttribArray**를 사용하여 정점 속성을 활성화해야 함

정점 속성은 기본적으로 비활성화되어 있음, 그 시점부터 우리는 모든 것을 설정했었음

정점 버퍼 개체를 사용하여 버퍼의 정점 데이터를 초기화하고 정점 및 조각 셰이더를 설정하고

정점 데이터를 정점 셰이더의 정점 속성에 연결하는 방법을 OpenGL에 지시했으며 OpenGL에서 객체를 그리는 것은 이제 다음과 같이 나타냄

```cpp
// 0. copy our vertices array in a buffer for OpenGL to use
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
// 1. then set the vertex attributes pointers
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
// 2. use our shader program when we want to render an object
glUseProgram(shaderProgram);
// 3. now draw the object
someOpenGLFunctionThatDrawsOurTriangle();
```

개발자는 객체를 그리고 싶을 때마다 이 과정을 반복해야 하는 단점이 존재

적절한 버퍼 객체를 바인딩하고 각 객체에 대한 모든 정점 속성을 구성하는 것은 빠르게 번거로운 프로세스가 됌

이러한 모든 상태 구성을 객체에 저장하고 간단히 이 객체를 바인딩하여 상태를 복원할 수 있는 방법이 **Vertex Array Object**

## Vertex Array Object

정점 배열 객체(VAO라고도 함)는 정점 버퍼 객체처럼 바인딩될 수 있으며 해당 지점의 모든 후속 정점 속성 호출은 VAO 내부에 저장이 됌

이는 정점 속성 포인터를 구성할 때 해당 호출을 한 번만 수행하면 되며 객체를 그리고 싶을 때마다 해당 VAO를 바인딩하면 된다는 장점인 것

이를 통해 다른 VAO를 바인딩하는 것처럼 쉽게 다른 정점 데이터와 속성 구성 간을 전환이 가능(설정한 모든 상태는 VAO 내부에 저장 가능)

> Core OpenGL에서는 정점 입력으로 무엇을 해야 할지 알 수 있도록 VAO를 사용해야 함
> VAO 바인딩에 실패하면 OpenGL은 아무것도 그리기를 거부할 가능성이 높음

꼭짓점 배열 객체는 다음을 저장

- **glEnableVertexAttribArray** Or **glDisableVertexAttribArray**를 호출
  <br/>

- **glVertexAttribPointer**를 통한 정점 속성 구성
  <br/>

- **glVertexAttribPointer**를 호출하여 정점 속성과 연결된 정점 버퍼 개체

![vertex array ](https://learnopengl.com/img/getting-started/vertex_array_objects.png)

VAO를 생성하는 프로세스는 VBO의 프로세스와 유사

```cpp
unsigned int VAO;
glGenVertexArrays(1, &VAO);
```

VAO를 사용하려면 glBindVertexArray를 사용하여 VAO를 바인딩

그 시점부터 해당 VBO 및 속성 포인터를 바인딩/구성한 다음 나중에 사용할 수 있도록 VAO 바인딩을 해제해야 함

객체를 그리고 싶으면 객체를 그리기 전에 선호하는 설정으로 VAO를 바인딩

코드에서는 다음과 같음

```cpp
// ..:: Initialization code (done once (unless your object frequently changes)) :: ..
// 1. bind Vertex Array Object
glBindVertexArray(VAO);
// 2. copy our vertices array in a buffer for OpenGL to use
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
// 3. then set our vertex attributes pointers
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);

// ...

// ..:: Drawing code (in render loop) :: ..
// 4. draw the object
glUseProgram(shaderProgram);
glBindVertexArray(VAO);
someOpenGLFunctionThatDrawsOurTriangle();
```

우리가 수행한 모든 작업은 정점 속성 구성과 사용할 VBO를 저장하는 VAO인 이 순간까지 이어졌음

일반적으로 그리려는 개체가 여러 개인 경우 먼저 모든 VAO(따라서 필수 VBO 및 속성 포인터)를 생성/구성하고 나중에 사용할 수 있도록 저장

객체 중 하나를 그리려는 순간 해당 VAO를 가져와 바인딩한 다음 객체를 그리고 VAO 바인딩을 다시 해제

```cpp
glUseProgram(shaderProgram);
glBindVertexArray(VAO);
glDrawArrays(GL_TRIANGLES, 0, 3);
```

glDrawArrays 함수는 우리가 그리려는 OpenGL 기본 유형을 첫 번째 인수로 사용

처음에 우리는 삼각형을 그리고 싶다고 말했고 거짓말을 하고 싶지 않기 때문에 GL_TRIANGLES를 전달

두 번째 인수는 우리가 그리려는 정점 배열의 시작 인덱스를 지정합니다. 이것을 0으로 그대로 둠

마지막 인수는 우리가 그리고 싶은 정점 수를 지정함(데이터에서 정확히 3개의 정점 길이인 1개의 삼각형만 렌더링)

## 참고

[원본](https://learnopengl.com/Getting-started/Hello-Triangle)

[블로그 참고](https://jsdysw.tistory.com/83)
