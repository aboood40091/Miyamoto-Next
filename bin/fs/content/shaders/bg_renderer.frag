#version 330 core

uniform sampler2D texture0;

in vec2      vTexCoord0;
flat in uint vItemID;
flat in int  vIsSelected;

layout (location = 0) out vec4 FragColor;
layout (location = 2) out uint ItemID;

void main()
{
    vec4 color = texture(texture0, vTexCoord0);
    if (color.a < 0.0625)
        discard;

    if (vIsSelected != 0)
        FragColor = vec4(color.rgb * 0.5f + vec3(1.0f, 0.25f, 0.25f) * 0.5f, 1.0f);
    else
        FragColor = color;

    ItemID = vItemID;
}
