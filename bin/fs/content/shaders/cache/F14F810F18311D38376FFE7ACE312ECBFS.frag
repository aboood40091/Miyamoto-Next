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
uniform sampler2D tex_map2;

layout(location = 2) in vec4 PARAM_2;
layout(location = 0) in vec4 PARAM_0;
layout(location = 1) in vec4 PARAM_1;
layout(location = 3) in vec4 PARAM_3;
layout(location = 4) in vec4 PARAM_4;
layout(location = 5) in vec4 PARAM_5;
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
    RVar[4u] = PARAM_4;
    RVar[5u] = PARAM_5;
    if (stateVar == 0)
    {
        RVar[3u] = texture(tex_map0, vec4(RVar[3u].xy, 0.0, RVar[3u].x).xy);
        RVar[4u] = texture(tex_map1, vec4(RVar[4u].xy, 0.0, RVar[4u].x).xy);
        RVar[5u] = texture(tex_map2, vec4(RVar[5u].xy, 0.0, RVar[5u].x).xy);
    }
    if (stateVar == 0)
    {
        float _102 = RVar[3u].z;
        float _108 = RVar[3u].y;
        float _113 = RVar[3u].x;
        float _118 = RVar[0u].w;
        float _120 = RVar[3u].w;
        float _123 = (_118 * _120) + uintBitsToFloat(0u);
        float _125 = RVar[4u].x;
        RVar[123u].w = _123;
        RVar[127u].w = (-_125) + uintBitsToFloat(1065353216u);
        float _147 = (CBUFFER_1.values[5].z * ((-_102) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        float _152 = (CBUFFER_1.values[5].y * ((-_108) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        float _157 = (CBUFFER_1.values[5].x * ((-_113) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        float _159 = RVar[4u].y;
        RVar[127u].x = clamp(_123 + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[123u].y = _147;
        RVar[123u].z = _152;
        RVar[123u].w = _157;
        RVar[127u].z = (-_159) + uintBitsToFloat(1065353216u);
        float _172 = RVar[3u].x;
        float _175 = clamp((CBUFFER_1.values[4].x * _172) + _157, 0.0, 1.0);
        float _177 = RVar[4u].z;
        float _184 = RVar[3u].z;
        float _187 = clamp((CBUFFER_1.values[4].z * _184) + _147, 0.0, 1.0);
        float _191 = RVar[3u].y;
        float _194 = clamp((CBUFFER_1.values[4].y * _191) + _152, 0.0, 1.0);
        float _196 = RVar[0u].w;
        float _198 = RVar[4u].w;
        float _201 = (_196 * _198) + uintBitsToFloat(0u);
        RVar[123u].x = _175;
        RVar[123u].z = _187;
        RVar[123u].w = _194;
        RVar[122u].x = _201;
        float _208 = RVar[127u].w;
        float _211 = (_175 * _208) + uintBitsToFloat(0u);
        float _213 = RVar[127u].x;
        float _218 = (_187 * ((-_177) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        float _220 = RVar[127u].z;
        float _223 = (_194 * _220) + uintBitsToFloat(0u);
        float _225 = RVar[5u].x;
        RVar[123u].x = _211;
        RVar[126u].y = clamp(_213 + _201, 0.0, 1.0);
        RVar[123u].z = _218;
        RVar[123u].w = _223;
        RVar[127u].x = (-_225) + uintBitsToFloat(1065353216u);
        float _245 = RVar[4u].x;
        float _250 = RVar[5u].z;
        float _255 = RVar[5u].y;
        float _262 = RVar[4u].z;
        RVar[126u].x = clamp((CBUFFER_1.values[5].y * RVar[4u].y) + _223, 0.0, 1.0);
        RVar[127u].y = clamp((CBUFFER_1.values[5].x * _245) + _211, 0.0, 1.0);
        RVar[127u].w = clamp((CBUFFER_1.values[5].z * _262) + _218, 0.0, 1.0);
        float _273 = (CBUFFER_1.values[4].y * ((-_255) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        float _277 = RVar[127u].x;
        float _280 = (CBUFFER_1.values[4].x * _277) + uintBitsToFloat(0u);
        float _282 = RVar[126u].y;
        float _290 = (CBUFFER_1.values[4].z * ((-_250) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        RVar[123u].x = _273;
        RVar[123u].y = _280;
        RVar[123u].w = _290;
        RVar[4u].w = uintBitsToFloat(1065353216u);
        float _304 = RVar[126u].x;
        float _306 = RVar[5u].y;
        float _311 = RVar[127u].y;
        float _313 = RVar[5u].x;
        float _320 = RVar[126u].y;
        float _322 = (CBUFFER_1.values[4].w * ((-_282) + uintBitsToFloat(1065353216u))) + _320;
        float _324 = RVar[2u].z;
        float _326 = RVar[2u].z;
        RVar[126u].x = clamp((RVar[127u].w * RVar[5u].z) + _290, 0.0, 1.0);
        RVar[127u].y = clamp((_304 * _306) + _273, 0.0, 1.0);
        RVar[127u].z = clamp((_311 * _313) + _280, 0.0, 1.0);
        RVar[123u].w = _322;
        float _348 = RVar[126u].y;
        float _350 = RVar[5u].w;
        float _352 = (_348 * _350) + _322;
        RVar[126u].y = dot(vec4(RVar[2u].x, RVar[2u].y, _324 * _326, uintBitsToFloat(2147483648u)), vec4(RVar[2u].x, RVar[2u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[122u].x = _352;
        float _356 = RVar[1u].x;
        float _358 = RVar[127u].z;
        float _362 = RVar[1u].z;
        float _364 = RVar[126u].x;
        float _368 = RVar[1u].y;
        float _370 = RVar[127u].y;
        RVar[5u].w = clamp(_352 + (-uintBitsToFloat(1056964608u)), 0.0, 1.0);
        float _386 = RVar[1u].w;
        float _388 = RVar[127u].y;
        float _392 = RVar[1u].w;
        float _394 = RVar[126u].x;
        float _398 = RVar[126u].y;
        float _401 = inversesqrt(_398) * 0.5;
        RVar[5u].x = ((_356 + (-_358)) * RVar[1u].w) + RVar[127u].z;
        RVar[5u].y = ((_368 + (-_370)) * _386) + _388;
        RVar[5u].z = ((_362 + (-_364)) * _392) + _394;
        float _406 = RVar[2u].x;
        float _409 = (_406 * _401) + uintBitsToFloat(1056964608u);
        float _411 = RVar[2u].y;
        float _414 = (_411 * _401) + uintBitsToFloat(1056964608u);
        float _416 = RVar[2u].z;
        float _419 = (_416 * _401) + uintBitsToFloat(1056964608u);
        RVar[4u].x = _409;
        RVar[4u].y = _414;
        RVar[4u].z = _419;
        float _424 = RVar[4u].w;
        RVar[1u].x = _409;
        RVar[1u].y = _414;
        RVar[1u].z = _419;
        RVar[1u].w = _424;
        float _432 = RVar[5u].y;
        float _434 = RVar[5u].z;
        float _436 = RVar[5u].w;
        RVar[0u].x = RVar[5u].x;
        RVar[0u].y = _432;
        RVar[0u].z = _434;
        RVar[0u].w = _436;
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
    uint _512 = PS_PUSH.alphaFunc >> 8u;
    if (_512 == 1u)
    {
        _pixelTmp = vec4(1.0);
    }
    else
    {
        if (_512 == 2u)
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
    uint _540 = PS_PUSH.alphaFunc >> 8u;
    if (_540 == 1u)
    {
        _pixelTmp_1 = vec4(1.0);
    }
    else
    {
        if (_540 == 2u)
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