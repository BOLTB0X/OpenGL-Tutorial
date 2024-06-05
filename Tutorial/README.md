# Hello Triangle

> OpenGL에서는 모든 것이 3D 공간에 있지만 화면이나 창은 픽셀의 2D 배열이므로 OpenGL 작업의 대부분은 모든 3D 좌표를 화면에 맞는 2D 픽셀로 변환하는 것

OpenGL에서는 3D 좌표를 2D 픽셀로 변환하는 프로세스는 OpenGL의 graphics pipeline에 의해 관리함

파이프라인은 두 개의 큰 부분으로 나눌 수 있음

- 3D 좌표를 2D 좌표로 변환 부분
  <br/>

- 2D 좌표를 실제 색상 픽셀로 변환 부분
  <br/>

Graphics pipeline은 여러 단계로 나눌 수 있으며, 각 단계에는 이전 단계의 출력이 입력으로 필요

이러한 모든 단계는 매우 전문적이며(하나의 특정 기능을 가짐) 병렬로 쉽게 실행할 수 있음

병렬 특성으로 인해 오늘날의 그래픽 카드에는 그래픽 파이프라인 내에서 data를 신속하게 처리할 수 있는 수천 개의 작은 processing cores가 존재

Processing cores는 pipeline의 각 단계마다 GPU에서 작은 프로그램을 실행하는데 이러한 작은 프로그램이 **shader**

shader 중 일부는 개발자가 구성이 가능, 기존 기본 shader를 대체하기 위해 자체 shader를 작성할 수 있음

이를 통해 파이프라인의 특정 부분을 훨씬 더 세밀하게 제어할 수 있으며 GPU에서 실행되므로 CPU 시간도 절약할 수 있음

GLSL(OpenGL Shading Language) 작성

## Graphics pipeline

> 렌더링하는 과정을 여러 단계로 나누어 처리하는 방식

아래 그림이 pipeline의 단계들에 대한 추상적 표현

blue section이 개발자가 직접 configure한 shader를 넣을 수 있는 영역

![graphics pipeline](https://learnopengl.com/img/getting-started/pipeline.png)

1. **Vertex Data**

   - 맨 처음 전달하는 3D coordinate list를 Vertex Data 이 좌표들이 삼각형의 vertices
     <br/>

   - 튜토리얼에선 각각의 vertex는 3D coordinates와 color value를 가지고 있다고 생각하라고 함
     <br/>

   - 그다음으로 이 점들을 가지고 어떤 형태를 rendering할 것인지 OpenGL에게 hint가 필요
     <br/>

   - 단순히 점을 그릴 것인지? 삼각형을 그릴 것인지? 아니면 직선을 그릴 것인지? 와 같이 미리 알려주는 내용을 _'primitives'_
     <br/>

2. **Vetex Shader**

   - vertex shader는 single vertex를 input으로 받음
     <br/>

   - vertex shader는 3D coordinate을 다른 종류의 3D coordinate으로 바꿔줌
     <br/>

   - vertex attribute의 기본적인 processing을 수행함
     <br/>

3. **Primitive assembly**

   - vertext shader로부터 모든 vertices좌표를 input으로 받음
     <br/>

   - primitive대로 vertices를 합쳐줌
     <br/>

4. **Geometry shader**

   - 이전 단계에서의 output인 primitive를 구성하는 collection of vertices를 input으로 받음
     <br/>

   - 이 단계에서 새로운 vertex를 추가해서 새로운 primitive를 만들 수 있게 해줌
     <br/>

5. **Rasterization stage**

   - 이전 단계의 output을 input으로 받음
     <br/>

   - 이 단계에선 resulting primitives를 최종 화면(screen)에 pixel로 대응하는 작업이 수행되는 것
     <br/>

   - 이어서 fragment shader가 사용할 수 있게 fragments를 만들어냄
     <br/>

6. **Fragments**

   - OpenGL이 single pixel을 rendering하기 위해 필요한 모든 data
     <br/>

   - fragment shader단계로 진입하기 전에 clipping이라는 작업이 진행되는데 이는 화면 밖으로 나간 fragments들을 버리는 작업
     <br/>

   - 성능 향상을 위해 수행되는 동작(화면에 보이지 않음)
     <br/>

7. **Fragment shader**

   - 픽셀의 최종 색을 계산을 함
     <br/>

   - 이때 3D scene의 모든 정보(그림자, 빛, 빛의 색)를 고려해서 pixel color를 칠하게 됨
     <br/>

   - 이렇게 모든 픽셀 color가 결정되면 alpha test and blending stage로 넘어가게 됌
     <br/>

   - 이 단계에서는 fragment의 depth value와 alpha value(투명도)를 계산하게 되는 것이 **입체감을 주는 단계** 임
     <br/>

   - 결국 fragment shader에서 계산된 pixel color가 반드시 최종 결과와 일치하는 것은 아님
     <br/>

   - 위의 간략히 살펴본 단계 외에도 tessellation, transform feedback loop 등과 같은 단계들이 더 존재
     <br/>

   - moden OpenGL에서는 최소한으로 vertex와 fragment shader만큼은 직접 정의하도록 하고 있음

## [Vertex input](https://github.com/BOLTB0X/OpenGL-Tutorial/blob/Hello-Triangle/Tutorial/Vertex%20input.md)

## [Vertex shader](https://github.com/BOLTB0X/OpenGL-Tutorial/blob/Hello-Triangle/Tutorial/Vertex%20shader.md)

## [Compiling a shader](https://github.com/BOLTB0X/OpenGL-Tutorial/blob/Hello-Triangle/Tutorial/Compiling%20a%20shader.md)

## [Fragment shader](https://github.com/BOLTB0X/OpenGL-Tutorial/blob/Hello-Triangle/Tutorial/Fragment%20shader.md)

## [Linking Vertex Attributes](https://github.com/BOLTB0X/OpenGL-Tutorial/blob/Hello-Triangle/Tutorial/Linking%20Vertex%20Attributes.md)

## [Element Buffer Objects](https://github.com/BOLTB0X/OpenGL-Tutorial/blob/Hello-Triangle/Tutorial/Element%20Buffer%20Objects.md)
