# Element Buffer Objects

정점을 렌더링할 때 마지막으로 논의하고 싶은 것이 하나 있는데, 그것은 EBO로 축약되는 요소 버퍼 객체

> 요소 버퍼 객체의 작동 방식을 설명하려면 예를 들어 보는 것이 가장 좋음
> 삼각형 대신 직사각형을 그리고 싶다고 가정한다면 두 개의 삼각형을 사용하여 직사각형을 그릴 수 있음(OpenGL은 주로 삼각형을 사용하여 작동) 그러면 다음과 같은 정점 세트가 생성 됨

```cpp
float vertices[] = {
    // first triangle
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f,  0.5f, 0.0f,  // top left
    // second triangle
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left
};
```

지정된 정점에 일부 겹치는 부분이 존재

오른쪽 하단과 왼쪽 상단을 두 번 지정, 동일한 직사각형을 6개가 아닌 4개의 꼭지점으로만 지정할 수 있기 때문에 이는 50%의 오버헤드

이는 1000개가 넘는 삼각형을 가진 더 복잡한 모델이 생기면 더 악화될 것

중복 더 나은 해결책은 고유한 정점만 저장한 다음 이러한 정점을 그릴 순서를 지정하는 것

이 경우 직사각형에 대해 4개의 정점만 저장, 요소 버퍼 개체는 정확히 그와 같이 작동함

EBO는 정점 버퍼 객체와 마찬가지로 OpenGL이 그릴 정점을 결정하는 데 사용하는 인덱스를 저장하는 버퍼인 것

소위 색인화된 도면이라고 불리는 것을 (고유한) 정점과 이를 직사각형으로 그리는 인덱스를 지정해야 함

```cpp
float vertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left
};
unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};
```

인덱스를 사용할 때 꼭지점은 6개가 아닌 4개만 필요하다는 것을 알 수 있음 다음으로 요소 버퍼 개체를 만들어야 함

```cpp
unsigned int EBO;
glGenBuffers(1, &EBO);
```

VBO와 유사하게 EBO를 바인딩하고 glBufferData를 사용하여 인덱스를 버퍼에 복사함

또한 VBO와 마찬가지로 바인드 호출과 바인드 해제 호출 사이에 해당 호출을 배치하려고 함 단, 이번에는 버퍼 유형으로 GL_ELEMENT_ARRAY_BUFFER를 지정

```cpp
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
```

이제 GL_ELEMENT_ARRAY_BUFFER를 버퍼 대상으로 제공하고 있음

glDrawArrays 호출을 glDrawElements로 대체하여 인덱스 버퍼에서 삼각형을 렌더링한다는 것을 나타냄

glDrawElements를 사용할 때 현재 바인딩된 요소 버퍼 개체에 제공된 인덱스를 사용하여 그리는 것

```cpp
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
```

- 첫 번째 argument glDrawArrays와 유사하게 그리려는 모드를 지정
  <br/>

- 두 번째 argument 그리려는 요소의 개수(6개의 인덱스를 지정했기 때문에 총 6개의 정점)
  <br/>

- 세 번째 argument GL_UNSIGNED_INT 유형인 인덱스 유형입
  <br/>

- 마지막 argument 사용하면 EBO에서 오프셋을 지정(또는 인덱스 배열을 전달하지만 요소 버퍼 개체를 사용하지 않는 경우 0)
  <br/>

glDrawElements 함수는 현재 GL_ELEMENT_ARRAY_BUFFER 타겟에 바인딩된 EBO에서 인덱스를 가져옴

이는 인덱스가 있는 객체를 렌더링할 때마다 해당 EBO를 바인딩해야 한다는 것을 의미

꼭짓점 배열 개체도 요소 버퍼 개체 바인딩을 추적하는 일이 발생하며 VAO가 바인딩되는 동안 바인딩되는 마지막 요소 버퍼 개체는 VAO의 요소 버퍼 개체로 저장

VAO에 바인딩하면 해당 EBO도 자동으로 바인딩

glDrawElements 함수는 현재 GL_ELEMENT_ARRAY_BUFFER 타겟에 바인딩된 EBO에서 인덱스를 가져옴

이는 인덱스가 있는 객체를 렌더링할 때마다 해당 EBO를 바인딩해야 한다는 것을 의미 -> 꼭짓점 배열 개체도 요소 버퍼 개체 바인딩을 추적하는 일이 발생

VAO가 바인딩되는 동안 바인딩되는 마지막 요소 버퍼 개체는 VAO의 요소 버퍼 개체로 저장

VAO에 바인딩하면 해당 EBO도 자동으로 바인딩

![VAO](https://learnopengl.com/img/getting-started/vertex_array_objects_ebo.png)

> VAO는 대상이 GL_ELEMENT_ARRAY_BUFFER일 때 glBindBuffer 호출을 저장
> 이는 또한 바인딩 해제 호출을 저장하므로 VAO 바인딩을 해제하기 전에 요소 배열 버퍼를 바인딩 해제하지 않도록 해야 함 그렇지 않으면 EBO가 구성되지 않음

<br/>

```cpp
// ..:: Initialization code :: ..
// 1. bind Vertex Array Object
glBindVertexArray(VAO);
// 2. copy our vertices array in a vertex buffer for OpenGL to use
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
// 3. copy our index array in a element buffer for OpenGL to use
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
// 4. then set the vertex attributes pointers
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);

//[...]

// ..:: Drawing code (in render loop) :: ..
glUseProgram(shaderProgram);
glBindVertexArray(VAO);
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
glBindVertexArray(0);
```
