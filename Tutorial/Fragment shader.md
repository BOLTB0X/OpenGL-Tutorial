# Fragment shader

> 프래그먼트 셰이더는 삼각형을 렌더링하기 위해 생성할 두 번째이자 마지막 셰이더
> 프래그먼트 셰이더는 픽셀의 색상 출력을 계산하는 것, 튜토리얼이므로 작업을 단순하게 유지하기 위해 프래그먼트 셰이더는 항상 주황색 색상을 출력

**cf**

> 컴퓨터 그래픽의 색상은 빨간색, 녹색, 파란색 및 알파(불투명도) 구성 요소의 4가지 값 배열로 표시되며 일반적으로 RGBA로 축약이 됌
> OpenGL 또는 GLSL에서 색상을 정의할 때 각 구성 요소의 강도를 0.0에서 1.0 사이의 값으로 설정
> 예를 들어 빨간색을 1.0으로 설정하고 녹색을 1.0으로 설정하면 두 색상이 혼합되어 노란색이 되며 이러한 3가지 색상 구성 요소를 고려하면 1,600만 개가 넘는 다양한 색상을 생성할 수 있음

```cpp
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
```

- 프래그먼트 셰이더에는 하나의 출력 변수만 필요하며 이는 우리가 직접 계산해야 하는 최종 색상 출력을 정의하는 크기 4의 벡터
  <br/>
- 여기서는 FragColor라는 이름을 즉시 사용하는 out 키워드를 사용하여 출력 값을 선언할 수 있음
  <br/>
- 다음으로 vec4를 알파 값 1.0(1.0은 완전히 불투명함)의 주황색으로 색상 출력에 할당
  <br/>

```cpp
unsigned int fragmentShader;
fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // 1
glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
glCompileShader(fragmentShader);
```

1. 프래그먼트 셰이더를 컴파일하는 프로세스는 정점 셰이더와 유사하지만 이번에는 셰이더 타입으로 GL_FRAGMENT_SHADER 상수를 사용
   <br/>

2. 이제 두 셰이더가 모두 컴파일되었으며 남은 작업은 두 셰이더 개체를 렌더링에 사용할 수 있는 셰이더 프로그램에 연결하는 것이 남음
   <br/>

3. 여기에서도 컴파일 오류가 있는지 확인해야 함
   <br/>

## Shader program

> 셰이더 프로그램 개체는 여러 셰이더가 결합된 최종 링크 버전 최근에 컴파일된 셰이더를 사용하려면 이를 셰이더 프로그램 개체에 연결한 다음 개체를 렌더링할 때 이 셰이더 프로그램을 활성화해야 함
> 활성화된 셰이더 프로그램의 셰이더는 렌더링 호출을 실행할 때 사용이 됌
> 셰이더를 프로그램에 연결하면 각 셰이더의 출력이 다음 셰이더의 입력에 연결되고 출력과 입력이 일치하지 않는 경우 연결 오류가 발생하는 곳이기도 함

```cpp
unsigned int shaderProgram;
shaderProgram = glCreateProgram();
```

- glCreateProgram 함수: 프로그램을 생성하고 새로 생성된 프로그램 개체에 대한 ID 참조를 반환
  <br/>

```cpp
glAttachShader(shaderProgram, vertexShader);
glAttachShader(shaderProgram, fragmentShader);
glLinkProgram(shaderProgram);
```

- 셰이더를 프로그램에 연결하고 glLinkProgram을 통해 연결
  <br/>

**cf.**

> 셰이더 컴파일과 마찬가지로 셰이더 프로그램 연결이 실패했는지 확인하고 해당 로그를 검색할 수도 있음
> 그러나 glGetShaderiv 및 glGetShaderInfoLog를 사용하는 대신 아래의 코드를 사용

```cpp
glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

if(!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    // ...
}
```

> 결과는 새로 생성된 프로그램 개체를 인수로 사용하여 glUseProgram을 호출하여 활성화할 수 있는 프로그램 개체

```cpp
glUseProgram(shaderProgram);
```

- glUseProgram 이후의 모든 셰이더 및 렌더링 호출은 이제 이 프로그램 개체(및 셰이더)를 사용
  <br/>

- 셰이더 개체를 프로그램 개체에 연결한 후에는 셰이더 개체를 삭제하는 것 필수(더이상 필요 X)
  <br/>

```cpp
glDeleteShader(vertexShader);
glDeleteShader(fragmentShader);
```

지금까지 튜토리얼은 입력 정점 데이터를 GPU로 보내고 GPU가 정점 및 프라그먼트 셰이더 내에서 정점 데이터를 처리하는 방법을 GPU에 지시하는 가정을 다룸

OpenGL은 메모리의 정점 데이터를 어떻게 해석해야 하는지, 정점 데이터를 정점 셰이더의 속성에 어떻게 연결해야 하는지는 다음에 계속

## 참고

[원본](https://learnopengl.com/Getting-started/Hello-Triangle)

[블로그 참고](https://jsdysw.tistory.com/83)
