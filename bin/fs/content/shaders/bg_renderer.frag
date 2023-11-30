#version 330 core

uniform sampler2D texture0;

in vec2 vTexCoord0;
flat in uint vItemID;

layout (location = 0) out vec4 FragColor;
layout (location = 2) out uint ItemID;

void main()
{
    vec4 color = texture(texture0, vTexCoord0);
    if (color.a < 0.0625)
        discard;

    FragColor = color;
    ItemID = vItemID;
}
