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
uniform sampler2D tex_map1;

layout(location = 0) in vec4 PARAM_0;
layout(location = 1) in vec4 PARAM_1;
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
    RVar[0u] = PARAM_0;
    RVar[1u] = PARAM_1;
    RVar[2u] = PARAM_3;
    RVar[3u] = PARAM_4;
    if (stateVar == 0)
    {
        RVar[2u] = vec4(texture(tex_map0, vec4(RVar[2u].xy, 0.0, RVar[2u].x).xy).w, RVar[2u].y, RVar[2u].z, RVar[2u].w);
        RVar[3u] = vec4(texture(tex_map1, vec4(RVar[3u].xy, 0.0, RVar[3u].x).xy).w, RVar[3u].y, RVar[3u].z, RVar[3u].w);
    }
    if (stateVar == 0)
    {
        float _93 = RVar[2u].x;
        float _96 = (CBUFFER_1.values[4].w * _93) + uintBitsToFloat(0u);
        RVar[123u].x = _96;
        RVar[2u].w = uintBitsToFloat(1065353216u);
        float _131 = RVar[1u].z;
        float _133 = RVar[1u].z;
        RVar[127u].x = clamp(clamp(CBUFFER_1.values[4].x + uintBitsToFloat(0u), 0.0, 1.0) + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[127u].z = clamp(clamp(CBUFFER_1.values[4].z + uintBitsToFloat(0u), 0.0, 1.0) + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[127u].w = clamp(clamp(CBUFFER_1.values[4].y + uintBitsToFloat(0u), 0.0, 1.0) + uintBitsToFloat(0u), 0.0, 1.0);
        float _155 = RVar[3u].x;
        float _158 = (clamp(_96 + uintBitsToFloat(0u), 0.0, 1.0) * _155) + uintBitsToFloat(0u);
        RVar[127u].y = dot(vec4(RVar[1u].x, RVar[1u].y, _131 * _133, uintBitsToFloat(2147483648u)), vec4(RVar[1u].x, RVar[1u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[122u].x = _158;
        float _163 = RVar[0u].x;
        float _165 = RVar[127u].x;
        float _169 = RVar[0u].z;
        float _171 = RVar[127u].z;
        float _175 = RVar[0u].y;
        float _177 = RVar[127u].w;
        RVar[3u].w = clamp(_158 + uintBitsToFloat(0u), 0.0, 1.0);
        float _191 = RVar[0u].w;
        float _193 = RVar[127u].w;
        float _197 = RVar[0u].w;
        float _199 = RVar[127u].z;
        float _203 = RVar[127u].y;
        float _206 = inversesqrt(_203) * 0.5;
        RVar[3u].x = ((_163 + (-_165)) * RVar[0u].w) + RVar[127u].x;
        RVar[3u].y = ((_175 + (-_177)) * _191) + _193;
        RVar[3u].z = ((_169 + (-_171)) * _197) + _199;
        float _211 = RVar[1u].x;
        float _215 = (_211 * _206) + uintBitsToFloat(1056964608u);
        float _217 = RVar[1u].y;
        float _220 = (_217 * _206) + uintBitsToFloat(1056964608u);
        float _222 = RVar[1u].z;
        float _225 = (_222 * _206) + uintBitsToFloat(1056964608u);
        RVar[2u].x = _215;
        RVar[2u].y = _220;
        RVar[2u].z = _225;
        float _230 = RVar[2u].w;
        RVar[1u].x = _215;
        RVar[1u].y = _220;
        RVar[1u].z = _225;
        RVar[1u].w = _230;
        float _238 = RVar[3u].y;
        float _240 = RVar[3u].z;
        float _242 = RVar[3u].w;
        RVar[0u].x = RVar[3u].x;
        RVar[0u].y = _238;
        RVar[0u].z = _240;
        RVar[0u].w = _242;
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
    uint _318 = PS_PUSH.alphaFunc >> 8u;
    if (_318 == 1u)
    {
        _pixelTmp = vec4(1.0);
    }
    else
    {
        if (_318 == 2u)
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
    uint _346 = PS_PUSH.alphaFunc >> 8u;
    if (_346 == 1u)
    {
        _pixelTmp_1 = vec4(1.0);
    }
    else
    {
        if (_346 == 2u)
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