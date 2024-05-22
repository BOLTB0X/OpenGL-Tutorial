# Creating a window

> 그래픽을 만들기 전에 가장 먼저 해야 할 일은 OpenGL context와 그릴 application 프로그램 window를 만드는 것
> 이러한 작업은 운영 체제마다 다르며 OpenGL은 의도적으로 이러한 작업에서 자체를 추상화해야함

## package 설치

1. GLFW

   - OpenGL만을 위해 C로 만든 라이브러리
     <br/>

   - OpenGL context를 생성하고 window parameters를 정의하고 user input을 다룰 수 있도록 해줌
     <br/>

   - 터미널 -> brew install glfw 입략
     <br/>

2. CMake

   - 프로젝트, 솔루션 파일을 만들어주는 프로그램
     <br/>

   - 터미널 -> brew install cmake
     <br/>

3. GLAD

   > OpenGL의 버전을 정의하고 해당 버전에 따라 모든 관련된 OpenGL 함수를 정의하고 로드 할 수 있는 웹 서비스를 제공

   - OpenGL은 어디까지나 표준사양
     <br/>

   - 어떤 OpenGL드라이버를 그래픽카드에 탑재 하였는지는 제조사의 결정
     <br/>

   - 개발자 입장에서는 특정 그래픽 카드의 드라이버 사양에 맞는 함수를 런타임에서 찾게 되고 따라서 시간이 소요 됌
     <br/>

   - [.dav1d.de](https://glad.dav1d.de/) 에서 생성 후 프로젝트에 복사

## Xcode Setting

1. Linking

   - 프로젝트는 glfw3.lib가 존재하는 directory를 설정
     <br/>

   - OpenGL 프레임워크 추가
     <br/>

   - Build Phases 에 glad.c 설정

<img width="766" alt="linking" src="https://github.com/BOLTB0X/BOLTB0X/assets/83914919/467e7366-ec9d-4d20-8bef-5b33fa8e1d52">

<img width="765" alt="searchPath" src="https://github.com/BOLTB0X/BOLTB0X/assets/83914919/1bfe00c0-c81d-4d83-8af9-ba8776757391">

<img width="769" alt="glad" src="https://github.com/BOLTB0X/BOLTB0X/assets/83914919/6804f206-3143-4931-a480-125d81f28f85">
