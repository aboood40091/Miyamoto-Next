#version 330 core

uniform vec4 uMVP[4];
uniform vec2 uTexTrans;
uniform vec2 uTexScale;
uniform float uTexRotate;

layout (location = 0) in vec3 aPosition;

out vec2 vTexCoord;

void main()
{
    vec4 pos = vec4(aPosition, 1.0);

    gl_Position = vec4(dot(uMVP[0], pos),
                       dot(uMVP[1], pos),
                       dot(uMVP[2], pos),
                       dot(uMVP[3], pos));

    float c = cos(uTexRotate);
    float s = sin(uTexRotate);
    vTexCoord = vec2( aPosition.x + uTexTrans.x,
                     -aPosition.y + uTexTrans.y);
    vTexCoord = vec2((vTexCoord.x * c - s * vTexCoord.y) * uTexScale.x + 0.5,
                     (vTexCoord.x * s + c * vTexCoord.y) * uTexScale.y + 0.5);
}
