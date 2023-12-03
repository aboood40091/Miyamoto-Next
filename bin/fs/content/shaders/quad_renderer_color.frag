#version 330 core

uniform vec4 uColor;

uniform uint uItemID;
uniform bool uIsSelected;

layout (location = 0) out vec4 FragColor;
layout (location = 2) out uint ItemID;

void main()
{
    if (uIsSelected)
        FragColor = vec4(uColor.rgb * 0.5f + vec3(1.0f, 0.25f, 0.25f) * 0.5f, uColor.a);
    else
        FragColor = uColor;

    ItemID = uItemID;
}
