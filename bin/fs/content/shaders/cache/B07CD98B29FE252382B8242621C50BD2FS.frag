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

uniform sampler2D tex_map0;

layout(location = 0) in vec4 PARAM_0;
layout(location = 1) in vec4 PARAM_1;
layout(location = 2) in vec4 PARAM_2;
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
    RVar[0u] = PARAM_0;
    RVar[1u] = PARAM_1;
    RVar[2u] = PARAM_2;
    if (stateVar == 0)
    {
        vec4 _56 = texture(tex_map0, vec4(RVar[2u].xy, 0.0, RVar[2u].x).xy);
        RVar[2u] = vec4(_56.x, _56.y, _56.z, RVar[2u].w);
    }
    if (stateVar == 0)
    {
        float _74 = RVar[2u].z;
        float _77 = (CBUFFER_1.values[5].z * _74) + uintBitsToFloat(0u);
        float _81 = RVar[2u].y;
        float _84 = (CBUFFER_1.values[5].y * _81) + uintBitsToFloat(0u);
        float _88 = RVar[2u].x;
        float _91 = (CBUFFER_1.values[5].x * _88) + uintBitsToFloat(0u);
        RVar[123u].x = _77;
        RVar[123u].y = _84;
        RVar[123u].z = _91;
        RVar[3u].w = uintBitsToFloat(0u);
        RVar[2u].w = uintBitsToFloat(1065353216u);
        float _103 = RVar[1u].z;
        float _105 = RVar[1u].z;
        float _116 = clamp(_91 + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[127u].y = clamp(_77 + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[127u].z = clamp(_84 + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[127u].w = _116;
        float _122 = RVar[1u].x;
        float _124 = RVar[1u].y;
        float _129 = RVar[1u].x;
        float _131 = RVar[1u].y;
        float _147 = RVar[0u].z;
        float _149 = RVar[127u].y;
        float _153 = RVar[0u].y;
        float _155 = RVar[127u].z;
        float _160 = inversesqrt(dot(vec4(_122, _124, _103 * _105, uintBitsToFloat(2147483648u)), vec4(_129, _131, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)))) * 0.5;
        RVar[3u].x = ((RVar[0u].x + (-_116)) * RVar[0u].w) + RVar[127u].w;
        RVar[127u].x = _160;
        float _170 = RVar[0u].w;
        float _172 = RVar[127u].z;
        float _176 = RVar[0u].w;
        float _178 = RVar[127u].y;
        float _182 = RVar[1u].y;
        RVar[2u].x = (RVar[1u].x * _160) + uintBitsToFloat(1056964608u);
        RVar[3u].y = ((_153 + (-_155)) * _170) + _172;
        RVar[3u].z = ((_147 + (-_149)) * _176) + _178;
        RVar[2u].y = (_182 * _160) + uintBitsToFloat(1056964608u);
        float _191 = RVar[1u].z;
        float _193 = RVar[127u].x;
        float _196 = (_191 * _193) + uintBitsToFloat(1056964608u);
        RVar[2u].z = _196;
        float _201 = RVar[2u].y;
        float _203 = RVar[2u].w;
        RVar[1u].x = RVar[2u].x;
        RVar[1u].y = _201;
        RVar[1u].z = _196;
        RVar[1u].w = _203;
        float _211 = RVar[3u].y;
        float _213 = RVar[3u].z;
        float _215 = RVar[3u].w;
        RVar[0u].x = RVar[3u].x;
        RVar[0u].y = _211;
        RVar[0u].z = _213;
        RVar[0u].w = _215;
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
    uint _291 = PS_PUSH.alphaFunc >> 8u;
    if (_291 == 1u)
    {
        _pixelTmp = vec4(1.0);
    }
    else
    {
        if (_291 == 2u)
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
    uint _319 = PS_PUSH.alphaFunc >> 8u;
    if (_319 == 1u)
    {
        _pixelTmp_1 = vec4(1.0);
    }
    else
    {
        if (_319 == 2u)
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