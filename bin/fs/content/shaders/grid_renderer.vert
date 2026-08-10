#version 330 core

uniform vec4 uMVP[4];

layout (location = 0) in vec3 aPosition;

out vec2 vWorldPos;

void main()
{
    vec4 pos = vec4(aPosition, 1);

    vWorldPos = aPosition.xy;

    gl_Position = vec4(dot(uMVP[0], pos),
                       dot(uMVP[1], pos),
                       dot(uMVP[2], pos),
                       dot(uMVP[3], pos));
}
