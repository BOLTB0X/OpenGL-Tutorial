#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 ourPosition;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    ourPosition = aPos;
}

// 삼각형의 각 정점의 위치(aPos)를 색상 값으로 사용