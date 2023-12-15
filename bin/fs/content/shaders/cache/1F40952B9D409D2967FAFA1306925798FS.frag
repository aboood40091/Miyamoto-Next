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
uniform sampler2D tex_map3;
uniform sampler2D tex_map0;
uniform sampler2D tex_map2;

layout(location = 2) in vec4 PARAM_2;
layout(location = 1) in vec4 PARAM_1;
layout(location = 0) in vec4 PARAM_0;
layout(location = 3) in vec4 PARAM_3;
layout(location = 4) in vec4 PARAM_4;
layout(location = 5) in vec4 PARAM_5;
layout(location = 6) in vec4 PARAM_6;
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
    RVar[5u] = PARAM_5;
    RVar[6u] = PARAM_6;
    if (stateVar == 0)
    {
        vec4 _72 = texture(tex_map1, vec4(RVar[4u].xy, 0.0, RVar[4u].x).xy);
        RVar[4u] = vec4(_72.x, RVar[4u].y, RVar[4u].z, _72.w);
        vec4 _87 = texture(tex_map3, vec4(RVar[6u].xy, 0.0, RVar[6u].x).xy);
        RVar[6u] = vec4(_87.x, RVar[6u].y, RVar[6u].z, _87.w);
    }
    if (stateVar == 0)
    {
        float _104 = RVar[4u].w;
        float _107 = _104 + (-uintBitsToFloat(1056964608u));
        float _109 = RVar[6u].w;
        float _112 = _109 + (-uintBitsToFloat(1056964608u));
        float _114 = RVar[6u].x;
        RVar[6u].x = RVar[4u].x + (-uintBitsToFloat(1056964608u));
        RVar[6u].y = uintBitsToFloat(0u);
        RVar[7u].x = _114 + (-uintBitsToFloat(1056964608u));
        RVar[4u].x = _112 * CBUFFER_1.values[13].y;
        RVar[4u].y = _107 * CBUFFER_1.values[11].x;
        RVar[0u].z = _112 * CBUFFER_1.values[13].x;
        RVar[4u].w = _107 * CBUFFER_1.values[11].y;
        RVar[9u].w = uintBitsToFloat(1065353216u);
    }
    if (stateVar == 0)
    {
        vec4 _170 = intBitsToFloat(ivec4(ivec3(textureSize(tex_map0, floatBitsToInt(vec4(RVar[6u].yy, 0.0, RVar[6u].y).x)), 1), textureQueryLevels(tex_map0)));
        RVar[0u] = vec4(_170.x, _170.y, RVar[0u].z, RVar[0u].w);
        vec4 _186 = intBitsToFloat(ivec4(ivec3(textureSize(tex_map2, floatBitsToInt(vec4(RVar[6u].yy, 0.0, RVar[6u].y).x)), 1), textureQueryLevels(tex_map2)));
        RVar[8u] = vec4(_186.x, _186.y, RVar[8u].z, RVar[8u].w);
    }
    if (stateVar == 0)
    {
        float _196 = RVar[6u].x;
        float _200 = RVar[4u].y;
        float _202 = (_196 * CBUFFER_1.values[11].z) + _200;
        float _204 = RVar[7u].x;
        float _208 = RVar[0u].z;
        float _210 = (_204 * CBUFFER_1.values[13].z) + _208;
        float _212 = RVar[6u].x;
        float _216 = RVar[4u].w;
        float _218 = (_212 * CBUFFER_1.values[11].w) + _216;
        float _220 = RVar[7u].x;
        float _224 = RVar[4u].x;
        float _226 = (_220 * CBUFFER_1.values[13].w) + _224;
        float _228 = RVar[0u].y;
        RVar[123u].x = _202;
        RVar[123u].y = _210;
        RVar[123u].z = _218;
        RVar[123u].w = _226;
        RVar[127u].y = float(floatBitsToInt(_228));
        float _239 = RVar[7u].x;
        float _244 = (_239 * CBUFFER_1.values[14].y) + _226;
        float _246 = RVar[6u].x;
        float _251 = (_246 * CBUFFER_1.values[12].x) + _202;
        float _253 = RVar[7u].x;
        float _257 = (_253 * CBUFFER_1.values[14].x) + _210;
        float _259 = RVar[6u].x;
        float _263 = (_259 * CBUFFER_1.values[12].y) + _218;
        float _265 = RVar[0u].x;
        RVar[123u].x = _244;
        RVar[123u].y = _251;
        RVar[123u].z = _257;
        RVar[123u].w = _263;
        RVar[126u].x = _257 * uintBitsToFloat(1132396544u);
        RVar[126u].y = _263 * uintBitsToFloat(1132396544u);
        RVar[126u].w = _244 * uintBitsToFloat(1132396544u);
        float _292 = (CBUFFER_1.values[4].x * uintBitsToFloat(1065353216u)) + uintBitsToFloat(0u);
        float _298 = (CBUFFER_1.values[4].y * uintBitsToFloat(1065353216u)) + uintBitsToFloat(0u);
        float _307 = RVar[127u].y;
        RVar[123u].x = _292;
        RVar[123u].y = _298;
        RVar[127u].w = (CBUFFER_1.values[4].z * uintBitsToFloat(1065353216u)) + uintBitsToFloat(0u);
        float _323 = RVar[126u].y;
        float _326 = RVar[8u].x;
        RVar[0u].x = RVar[3u].x + ((_251 * uintBitsToFloat(1132396544u)) * (1.0 / float(floatBitsToInt(_265))));
        RVar[127u].x = float(floatBitsToInt(_326));
        float _332 = RVar[127u].w;
        float _346 = RVar[8u].y;
        RVar[0u].y = RVar[3u].y + (_323 * (1.0 / _307));
        RVar[126u].y = float(floatBitsToInt(_346));
        float _353 = clamp(clamp(clamp(_292 + uintBitsToFloat(0u), 0.0, 1.0) + uintBitsToFloat(0u), 0.0, 1.0) + uintBitsToFloat(0u), 0.0, 1.0);
        float _358 = RVar[2u].z;
        float _360 = RVar[2u].z;
        float _366 = RVar[127u].x;
        RVar[127u].x = _353;
        RVar[8u].y = clamp(clamp(clamp(_298 + uintBitsToFloat(0u), 0.0, 1.0) + uintBitsToFloat(0u), 0.0, 1.0) + uintBitsToFloat(0u), 0.0, 1.0);
        float _371 = RVar[2u].y;
        float _373 = RVar[2u].y;
        float _375 = (_371 * _373) + (_358 * _360);
        float _377 = RVar[1u].x;
        float _382 = clamp(clamp(clamp(_332 + uintBitsToFloat(0u), 0.0, 1.0) + uintBitsToFloat(0u), 0.0, 1.0) + uintBitsToFloat(0u), 0.0, 1.0);
        float _384 = RVar[126u].x;
        float _387 = RVar[126u].y;
        RVar[123u].x = _375;
        RVar[126u].y = _377 + (-_353);
        RVar[127u].z = _382;
        float _396 = RVar[2u].x;
        float _398 = RVar[2u].x;
        float _400 = (_396 * _398) + _375;
        float _402 = RVar[126u].w;
        float _405 = RVar[1u].y;
        float _407 = RVar[8u].y;
        float _411 = RVar[1u].z;
        RVar[3u].x = RVar[5u].x + (_384 * (1.0 / _366));
        RVar[123u].y = _400;
        RVar[4u].w = _405 + (-_407);
        float _426 = RVar[5u].y;
        float _429 = RVar[1u].w;
        float _431 = RVar[127u].z;
        RVar[6u].x = (RVar[126u].y * RVar[1u].w) + RVar[127u].x;
        RVar[3u].y = _426 + (_402 * (1.0 / _387));
        RVar[6u].z = ((_411 + (-_382)) * _429) + _431;
        RVar[5u].x = inversesqrt(_400) * 0.5;
    }
    if (stateVar == 0)
    {
        RVar[0u] = vec4(texture(tex_map0, vec4(RVar[0u].xy, 0.0, RVar[0u].x).xy).w, RVar[0u].y, RVar[0u].z, RVar[0u].w);
        RVar[3u] = vec4(texture(tex_map2, vec4(RVar[3u].xy, 0.0, RVar[3u].x).xy).w, RVar[3u].y, RVar[3u].z, RVar[3u].w);
    }
    if (stateVar == 0)
    {
        float _486 = RVar[0u].w;
        float _488 = RVar[3u].x;
        float _493 = RVar[0u].w;
        float _495 = RVar[0u].x;
        float _498 = (_493 * _495) + uintBitsToFloat(0u);
        float _500 = RVar[2u].y;
        float _502 = RVar[5u].x;
        RVar[6u].y = (RVar[4u].w * RVar[1u].w) + RVar[8u].y;
        RVar[127u].z = (_486 * _488) + uintBitsToFloat(0u);
        RVar[123u].w = _498;
        RVar[9u].y = (_500 * _502) + uintBitsToFloat(1056964608u);
        float _521 = RVar[2u].z;
        float _523 = RVar[5u].x;
        RVar[9u].x = (RVar[2u].x * RVar[5u].x) + uintBitsToFloat(1056964608u);
        RVar[9u].z = (_521 * _523) + uintBitsToFloat(1056964608u);
        float _530 = RVar[127u].z;
        float _537 = (CBUFFER_1.values[4].w * clamp(clamp(_498 + uintBitsToFloat(0u), 0.0, 1.0) + _530, 0.0, 1.0)) + uintBitsToFloat(0u);
        RVar[123u].y = _537;
        RVar[6u].w = clamp(_537 + uintBitsToFloat(0u), 0.0, 1.0);
        float _546 = RVar[9u].y;
        float _548 = RVar[9u].z;
        float _550 = RVar[9u].w;
        RVar[1u].x = RVar[9u].x;
        RVar[1u].y = _546;
        RVar[1u].z = _548;
        RVar[1u].w = _550;
        float _558 = RVar[6u].y;
        float _560 = RVar[6u].z;
        float _562 = RVar[6u].w;
        RVar[0u].x = RVar[6u].x;
        RVar[0u].y = _558;
        RVar[0u].z = _560;
        RVar[0u].w = _562;
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
    uint _637 = PS_PUSH.alphaFunc >> 8u;
    if (_637 == 1u)
    {
        _pixelTmp = vec4(1.0);
    }
    else
    {
        if (_637 == 2u)
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
    uint _665 = PS_PUSH.alphaFunc >> 8u;
    if (_665 == 1u)
    {
        _pixelTmp_1 = vec4(1.0);
    }
    else
    {
        if (_665 == 2u)
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