#version 330 core

uniform sampler2D sTexture;

uniform uint uItemID;
uniform bool uIsSelected;

in vec2 vTexCoord;

layout (location = 0) out vec4 FragColor;
layout (location = 2) out uint ItemID;

void main()
{
    vec4 color = texture(sTexture, vTexCoord);
    if (color.a < 0.0625)
        discard;

    if (uIsSelected)
        FragColor = vec4(color.rgb * 0.5f + vec3(1.0f, 0.25f, 0.25f) * 0.5f, color.a);
    else
        FragColor = color;

    ItemID = uItemID;
}
