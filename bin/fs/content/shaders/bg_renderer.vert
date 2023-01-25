#version 330 core

layout (location = 0) in vec3 Vertex;
layout (location = 1) in vec2 TexCoord0;

uniform vec4 mvp[4];

out vec2 vTexCoord0;

void main()
{
    vec4 pos = vec4(Vertex, 1.0);

    gl_Position = vec4(
        dot(mvp[0], pos),
        dot(mvp[1], pos),
        dot(mvp[2], pos),
        dot(mvp[3], pos)
    );

    vTexCoord0 = TexCoord0;
}
