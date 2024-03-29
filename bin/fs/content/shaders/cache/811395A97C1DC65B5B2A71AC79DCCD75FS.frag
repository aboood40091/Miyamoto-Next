#version 430

layout(std140) uniform Mat
{
    vec4 values[41];
} CBUFFER_1;

struct PS_PUSH_DATA
{
    uint alphaFunc;
    float alphaRef;
    uint needsPremultiply; uint uItemID; int uIsSelected;
};

uniform PS_PUSH_DATA PS_PUSH;

uniform sampler2D tex_map1;
uniform sampler2D tex_map0;

layout(location = 2) in vec4 PARAM_2;
layout(location = 1) in vec4 PARAM_1;
layout(location = 0) in vec4 PARAM_0;
layout(location = 3) in vec4 PARAM_3;
layout(location = 4) in vec4 PARAM_4;
layout(location = 0) out vec4 PIXEL_0;
layout(location = 1) out vec4 PIXEL_1;
layout (location = 2) out uint ItemID;
int stackIdxVar;
int stateVar;
vec4 RVar[128];
vec4 _pixelTmp;
vec4 _pixelTmp_1;

void main()
{
    stackIdxVar = 0;
    stateVar = 0;
    RVar[0u] = PARAM_2;
    RVar[1u] = PARAM_1;
    RVar[2u] = PARAM_0;
    RVar[3u] = PARAM_3;
    RVar[4u] = PARAM_4;
    if (stateVar == 0)
    {
        vec4 _64 = texture(tex_map1, vec4(RVar[4u].xy, 0.0, RVar[4u].x).xy);
        RVar[4u] = vec4(_64.x, _64.y, _64.z, RVar[4u].w);
        RVar[3u] = texture(tex_map0, vec4(RVar[3u].xy, 0.0, RVar[3u].x).xy);
    }
    if (stateVar == 0)
    {
        float _87 = RVar[0u].y;
        float _93 = RVar[0u].x;
        float _98 = RVar[0u].w;
        float _104 = RVar[0u].z;
        RVar[0u].w = uintBitsToFloat(1065353216u);
        float _120 = (CBUFFER_1.values[10].w * ((-_104) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        float _125 = (CBUFFER_1.values[10].w * ((-_87) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        float _130 = (CBUFFER_1.values[10].w * ((-_93) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        float _132 = RVar[3u].w;
        float _135 = (clamp(_98 + uintBitsToFloat(0u), 0.0, 1.0) * _132) + uintBitsToFloat(0u);
        float _137 = RVar[2u].z;
        float _139 = RVar[2u].z;
        RVar[123u].x = _120;
        RVar[123u].y = _125;
        RVar[123u].z = _130;
        RVar[123u].w = _135;
        float _147 = RVar[2u].y;
        float _149 = RVar[2u].y;
        float _151 = (_147 * _149) + (_137 * _139);
        float _153 = RVar[4u].z;
        float _158 = RVar[4u].y;
        float _163 = RVar[4u].x;
        RVar[123u].x = _151;
        RVar[4u].w = clamp(_135 + uintBitsToFloat(0u), 0.0, 1.0);
        float _173 = RVar[2u].x;
        float _175 = RVar[2u].x;
        float _177 = (_173 * _175) + _151;
        float _179 = RVar[3u].z;
        float _182 = (clamp(_153 + (-_120), 0.0, 1.0) * _179) + uintBitsToFloat(0u);
        float _184 = RVar[3u].y;
        float _187 = (clamp(_158 + (-_125), 0.0, 1.0) * _184) + uintBitsToFloat(0u);
        float _189 = RVar[3u].x;
        float _192 = (clamp(_163 + (-_130), 0.0, 1.0) * _189) + uintBitsToFloat(0u);
        RVar[123u].x = _177;
        RVar[123u].y = _182;
        RVar[123u].z = _187;
        RVar[123u].w = _192;
        float _199 = clamp(_192 + uintBitsToFloat(0u), 0.0, 1.0);
        float _202 = clamp(_182 + uintBitsToFloat(0u), 0.0, 1.0);
        float _205 = clamp(_187 + uintBitsToFloat(0u), 0.0, 1.0);
        float _208 = inversesqrt(_177) * 0.5;
        RVar[127u].x = _199;
        RVar[127u].z = _202;
        RVar[127u].w = _205;
        RVar[126u].x = _208;
        float _216 = RVar[1u].x;
        float _226 = RVar[1u].z;
        float _230 = RVar[1u].y;
        float _234 = RVar[2u].x;
        RVar[0u].y = (RVar[2u].y * _208) + uintBitsToFloat(1056964608u);
        RVar[0u].x = (_234 * _208) + uintBitsToFloat(1056964608u);
        float _247 = RVar[1u].w;
        float _249 = RVar[127u].w;
        float _253 = RVar[1u].w;
        float _255 = RVar[127u].z;
        float _259 = RVar[2u].z;
        float _261 = RVar[126u].x;
        float _264 = (_259 * _261) + uintBitsToFloat(1056964608u);
        RVar[4u].x = ((_216 + (-_199)) * RVar[1u].w) + RVar[127u].x;
        RVar[4u].y = ((_230 + (-_205)) * _247) + _249;
        RVar[4u].z = ((_226 + (-_202)) * _253) + _255;
        RVar[0u].z = _264;
        float _272 = RVar[0u].y;
        float _274 = RVar[0u].w;
        RVar[1u].x = RVar[0u].x;
        RVar[1u].y = _272;
        RVar[1u].z = _264;
        RVar[1u].w = _274;
        float _282 = RVar[4u].y;
        float _284 = RVar[4u].z;
        float _286 = RVar[4u].w;
        RVar[0u].x = RVar[4u].x;
        RVar[0u].y = _282;
        RVar[0u].z = _284;
        RVar[0u].w = _286;
    }
    switch (PS_PUSH.alphaFunc & 255u)
    {
        case 0u:
        {
            discard;
        }
        case 1u:
        {
            if (!(RVar[0u].w < PS_PUSH.alphaRef))
            {
                discard;
            }
            break;
        }
        case 2u:
        {
            if (abs(RVar[0u].w - PS_PUSH.alphaRef) > 9.9999997473787516355514526367188e-05)
            {
                discard;
            }
            break;
        }
        case 3u:
        {
            if (!(RVar[0u].w <= PS_PUSH.alphaRef))
            {
                discard;
            }
            break;
        }
        case 4u:
        {
            if (!(RVar[0u].w > PS_PUSH.alphaRef))
            {
                discard;
            }
            break;
        }
        case 5u:
        {
            if (abs(RVar[0u].w - PS_PUSH.alphaRef) <= 9.9999997473787516355514526367188e-05)
            {
                discard;
            }
            break;
        }
        case 6u:
        {
            if (!(RVar[0u].w >= PS_PUSH.alphaRef))
            {
                discard;
            }
            break;
        }
    }
    _pixelTmp = RVar[0u];
    uint _362 = PS_PUSH.alphaFunc >> 8u;
    if (_362 == 1u)
    {
        _pixelTmp = vec4(1.0);
    }
    else
    {
        if (_362 == 2u)
        {
            _pixelTmp = vec4(0.0);
        }
    }
    if ((PS_PUSH.needsPremultiply & 1u) != 0u)
    {
        _pixelTmp *= vec4(_pixelTmp.www, 1.0);
    }
    if (PS_PUSH.uIsSelected != 0) PIXEL_0 = vec4(_pixelTmp.rgb * 0.5f + vec3(1.0f, 0.25f, 0.25f) * 0.5f, _pixelTmp.a); else PIXEL_0 = _pixelTmp; ItemID = PS_PUSH.uItemID;
    _pixelTmp_1 = RVar[1u];
    uint _390 = PS_PUSH.alphaFunc >> 8u;
    if (_390 == 1u)
    {
        _pixelTmp_1 = vec4(1.0);
    }
    else
    {
        if (_390 == 2u)
        {
            _pixelTmp_1 = vec4(0.0);
        }
    }
    if ((PS_PUSH.needsPremultiply & 2u) != 0u)
    {
        _pixelTmp_1 *= vec4(_pixelTmp_1.www, 1.0);
    }
    PIXEL_1 = _pixelTmp_1;
}

 