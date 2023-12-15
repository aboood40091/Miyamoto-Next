#version 430

struct PS_PUSH_DATA
{
    uint alphaFunc;
    float alphaRef;
    uint needsPremultiply; uint uItemID; int uIsSelected;
};

uniform PS_PUSH_DATA PS_PUSH;

uniform sampler2D tex_map0;

layout(location = 2) in vec4 PARAM_2;
layout(location = 0) in vec4 PARAM_0;
layout(location = 1) in vec4 PARAM_1;
layout(location = 3) in vec4 PARAM_3;
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
    RVar[1u] = PARAM_0;
    RVar[2u] = PARAM_1;
    RVar[3u] = PARAM_3;
    if (stateVar == 0)
    {
        RVar[3u] = texture(tex_map0, vec4(RVar[3u].xy, 0.0, RVar[3u].x).xy);
    }
    if (stateVar == 0)
    {
        float _68 = RVar[0u].w;
        float _70 = RVar[3u].w;
        float _73 = (_68 * _70) + uintBitsToFloat(0u);
        float _75 = RVar[0u].z;
        float _77 = RVar[3u].z;
        float _80 = (_75 * _77) + uintBitsToFloat(0u);
        float _82 = RVar[0u].y;
        float _84 = RVar[3u].y;
        float _87 = (_82 * _84) + uintBitsToFloat(0u);
        float _89 = RVar[0u].x;
        float _91 = RVar[3u].x;
        float _94 = (_89 * _91) + uintBitsToFloat(0u);
        RVar[123u].x = _73;
        RVar[123u].y = _80;
        RVar[123u].z = _87;
        RVar[123u].w = _94;
        RVar[0u].w = uintBitsToFloat(1065353216u);
        float _106 = clamp(_94 + uintBitsToFloat(0u), 0.0, 1.0);
        float _108 = RVar[2u].z;
        float _110 = RVar[2u].z;
        RVar[127u].x = _106;
        RVar[127u].z = clamp(_80 + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[127u].w = clamp(_87 + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[3u].w = clamp(_73 + uintBitsToFloat(0u), 0.0, 1.0);
        float _127 = RVar[2u].x;
        float _129 = RVar[2u].y;
        float _134 = RVar[2u].x;
        float _136 = RVar[2u].y;
        float _152 = RVar[1u].z;
        float _154 = RVar[127u].z;
        float _158 = RVar[1u].y;
        float _160 = RVar[127u].w;
        float _165 = inversesqrt(dot(vec4(_127, _129, _108 * _110, uintBitsToFloat(2147483648u)), vec4(_134, _136, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)))) * 0.5;
        RVar[3u].x = ((RVar[1u].x + (-_106)) * RVar[1u].w) + RVar[127u].x;
        RVar[127u].x = _165;
        float _175 = RVar[1u].w;
        float _177 = RVar[127u].w;
        float _181 = RVar[1u].w;
        float _183 = RVar[127u].z;
        float _187 = RVar[2u].y;
        RVar[0u].x = (RVar[2u].x * _165) + uintBitsToFloat(1056964608u);
        RVar[3u].y = ((_158 + (-_160)) * _175) + _177;
        RVar[3u].z = ((_152 + (-_154)) * _181) + _183;
        RVar[0u].y = (_187 * _165) + uintBitsToFloat(1056964608u);
        float _196 = RVar[2u].z;
        float _198 = RVar[127u].x;
        float _201 = (_196 * _198) + uintBitsToFloat(1056964608u);
        RVar[0u].z = _201;
        float _206 = RVar[0u].y;
        float _208 = RVar[0u].w;
        RVar[1u].x = RVar[0u].x;
        RVar[1u].y = _206;
        RVar[1u].z = _201;
        RVar[1u].w = _208;
        float _216 = RVar[3u].y;
        float _218 = RVar[3u].z;
        float _220 = RVar[3u].w;
        RVar[0u].x = RVar[3u].x;
        RVar[0u].y = _216;
        RVar[0u].z = _218;
        RVar[0u].w = _220;
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
    uint _296 = PS_PUSH.alphaFunc >> 8u;
    if (_296 == 1u)
    {
        _pixelTmp = vec4(1.0);
    }
    else
    {
        if (_296 == 2u)
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
    uint _324 = PS_PUSH.alphaFunc >> 8u;
    if (_324 == 1u)
    {
        _pixelTmp_1 = vec4(1.0);
    }
    else
    {
        if (_324 == 2u)
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