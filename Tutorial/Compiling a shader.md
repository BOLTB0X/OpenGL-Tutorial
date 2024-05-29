# Compiling a shader

> 정점 셰이더의 소스 코드를 가져와 지금은 코드 파일 상단에 있는 const C 문자열에 저장

```cpp
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
```

OpenGL이 셰이더를 사용하려면 런타임에 소스 코드에서 셰이더를 동적으로 컴파일해야 함

가장 먼저 해야 할 일은 다시 ID로 참조되는 셰이더 개체를 만드는 것, 즉 정점 셰이더를 **unsigned int**로 저장하고 **glCreateShader**를 사용하여 셰이더를 생성함

```cpp
unsigned int vertexShader;
vertexShader = glCreateShader(GL_VERTEX_SHADER);
```

**glCreateShader**에 대한 인수로 생성하려는 셰이더 유형을 제공하고 정점 셰이더를 생성 중이므로 **GL_VERTEX_SHADER**를 전달

```cpp
// 셰이더 소스 코드를 셰이더 객체에 연결하고 셰이더를 컴파일
glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
glCompileShader(vertexShader);
```

- **glShaderSource 함수**
  - 컴파일할 셰이더 개체를 첫 번째 인수로 사용
    <br/>
  - 두 번째 인수는 소스 코드로 전달하는 문자열 수를 지정
    <br/>
  - 세 번째 매개변수는 정점 셰이더의 실제 소스 코드
    <br/>
  - 네 번째 매개변수는 NULL로 남겨둘 수 있음
    <br/>

**cf. glCompileShader를 호출한 후 컴파일이 성공했는지 확인하고 그렇지 않은 경우**

> 어떤 오류가 발견되었으므로 이를 수정할 수 있습니다. 컴파일 타임 오류 확인은 다음과 같이 수행

```cpp
int  success;
char infoLog[512];
glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
```

> 먼저 성공을 나타내는 정수와 오류 메시지(있는 경우)에 대한 저장 컨테이너를 정의
> 그런 다음 glGetShaderiv를 사용하여 컴파일이 성공했는지 확인, 컴파일이 실패하면 glGetShaderInfoLog를 사용하여 오류 메시지를 검색하고 오류 메시지를 print

```cpp
if(!success)
{
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
}
```

정점 셰이더를 컴파일하는 동안 오류가 감지되지 않으면 이제 컴파일
