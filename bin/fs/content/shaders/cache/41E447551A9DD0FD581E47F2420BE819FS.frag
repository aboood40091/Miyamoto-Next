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
uniform sampler2D tex_map2;
uniform sampler2D tex_map0;

layout(location = 0) in vec4 PARAM_0;
layout(location = 1) in vec4 PARAM_1;
layout(location = 2) in vec4 PARAM_2;
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
    RVar[2u] = PARAM_2;
    RVar[3u] = PARAM_3;
    RVar[4u] = PARAM_4;
    if (stateVar == 0)
    {
        vec4 _64 = texture(tex_map1, vec4(RVar[3u].xy, 0.0, RVar[3u].x).xy);
        RVar[3u] = vec4(_64.x, RVar[3u].y, RVar[3u].z, _64.w);
        vec4 _79 = texture(tex_map2, vec4(RVar[4u].xy, 0.0, RVar[4u].x).xy);
        RVar[6u] = vec4(_79.x, _79.y, _79.z, RVar[6u].w);
    }
    if (stateVar == 0)
    {
        float _90 = RVar[1u].z;
        float _92 = RVar[1u].z;
        float _96 = RVar[3u].w;
        float _100 = _96 + (-uintBitsToFloat(1056964608u));
        float _102 = RVar[3u].x;
        RVar[4u].y = uintBitsToFloat(0u);
        RVar[3u].w = _102 + (-uintBitsToFloat(1056964608u));
        RVar[7u].w = uintBitsToFloat(1065353216u);
        float _125 = RVar[1u].y;
        float _127 = RVar[1u].y;
        RVar[3u].x = _100 * CBUFFER_1.values[11].y;
        RVar[3u].y = _100 * CBUFFER_1.values[11].x;
        RVar[5u].x = (_125 * _127) + (_90 * _92);
    }
    if (stateVar == 0)
    {
        vec4 _155 = intBitsToFloat(ivec4(ivec3(textureSize(tex_map0, floatBitsToInt(vec4(RVar[4u].yy, 0.0, RVar[4u].y).x)), 1), textureQueryLevels(tex_map0)));
        RVar[4u] = vec4(_155.x, _155.y, RVar[4u].z, RVar[4u].w);
    }
    if (stateVar == 0)
    {
        float _164 = RVar[3u].w;
        float _168 = RVar[3u].x;
        float _170 = (_164 * CBUFFER_1.values[11].w) + _168;
        float _172 = RVar[3u].w;
        float _176 = RVar[3u].y;
        float _178 = (_172 * CBUFFER_1.values[11].z) + _176;
        float _180 = RVar[4u].x;
        RVar[123u].z = _170;
        RVar[123u].w = _178;
        RVar[127u].w = float(floatBitsToInt(_180));
        float _189 = RVar[3u].w;
        float _194 = (_189 * CBUFFER_1.values[12].y) + _170;
        float _196 = RVar[3u].w;
        float _200 = (_196 * CBUFFER_1.values[12].x) + _178;
        float _202 = RVar[1u].x;
        float _204 = RVar[1u].x;
        float _206 = RVar[5u].x;
        float _210 = RVar[4u].y;
        RVar[123u].x = _194;
        RVar[123u].y = _200;
        RVar[126u].z = (_202 * _204) + _206;
        RVar[127u].y = float(floatBitsToInt(_210));
        float _224 = RVar[127u].w;
        RVar[127u].z = _194 * uintBitsToFloat(1132396544u);
        float _229 = RVar[127u].y;
        float _235 = RVar[127u].z;
        float _238 = RVar[126u].z;
        float _242 = inversesqrt(_238) * 0.5;
        RVar[4u].x = RVar[2u].x + ((_200 * uintBitsToFloat(1132396544u)) * (1.0 / _224));
        float _250 = RVar[2u].y;
        float _253 = RVar[1u].z;
        float _258 = RVar[1u].y;
        RVar[7u].x = (RVar[1u].x * _242) + uintBitsToFloat(1056964608u);
        RVar[4u].y = _250 + (_235 * (1.0 / _229));
        RVar[7u].z = (_253 * _242) + uintBitsToFloat(1056964608u);
        RVar[7u].y = (_258 * _242) + uintBitsToFloat(1056964608u);
    }
    if (stateVar == 0)
    {
        RVar[4u] = texture(tex_map0, vec4(RVar[4u].xy, 0.0, RVar[4u].x).xy);
    }
    if (stateVar == 0)
    {
        float _287 = RVar[4u].y;
        float _292 = RVar[4u].x;
        float _297 = RVar[4u].w;
        float _301 = (_297 * uintBitsToFloat(1065353216u)) + uintBitsToFloat(0u);
        float _303 = RVar[4u].z;
        RVar[123u].z = _301;
        float _313 = (CBUFFER_1.values[5].z * ((-_303) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        float _318 = (CBUFFER_1.values[5].y * ((-_287) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        float _323 = (CBUFFER_1.values[5].x * ((-_292) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        RVar[123u].x = _313;
        RVar[123u].y = _318;
        RVar[123u].z = _323;
        float _333 = (clamp(_301 + uintBitsToFloat(0u), 0.0, 1.0) * uintBitsToFloat(1065353216u)) + uintBitsToFloat(0u);
        float _338 = RVar[4u].z;
        float _341 = clamp((CBUFFER_1.values[4].z * _338) + _313, 0.0, 1.0);
        float _345 = RVar[4u].y;
        float _348 = clamp((CBUFFER_1.values[4].y * _345) + _318, 0.0, 1.0);
        float _352 = RVar[4u].x;
        float _355 = clamp((CBUFFER_1.values[4].x * _352) + _323, 0.0, 1.0);
        RVar[123u].x = _333;
        RVar[123u].y = _341;
        RVar[123u].z = _348;
        RVar[123u].w = _355;
        float _361 = RVar[6u].z;
        float _364 = (_341 * _361) + uintBitsToFloat(0u);
        float _366 = RVar[6u].y;
        float _369 = (_348 * _366) + uintBitsToFloat(0u);
        float _371 = RVar[6u].x;
        float _374 = (_355 * _371) + uintBitsToFloat(0u);
        RVar[123u].y = _364;
        RVar[123u].z = _369;
        RVar[123u].w = _374;
        RVar[6u].w = clamp(_333 + uintBitsToFloat(0u), 0.0, 1.0);
        float _384 = clamp(_374 + uintBitsToFloat(0u), 0.0, 1.0);
        float _387 = clamp(_364 + uintBitsToFloat(0u), 0.0, 1.0);
        float _390 = clamp(_369 + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[127u].x = _384;
        RVar[127u].z = _387;
        RVar[127u].w = _390;
        float _399 = RVar[0u].z;
        float _403 = RVar[0u].y;
        float _413 = RVar[0u].w;
        float _415 = RVar[127u].w;
        float _419 = RVar[0u].w;
        float _421 = RVar[127u].z;
        RVar[6u].x = ((RVar[0u].x + (-_384)) * RVar[0u].w) + RVar[127u].x;
        RVar[6u].y = ((_403 + (-_390)) * _413) + _415;
        RVar[6u].z = ((_399 + (-_387)) * _419) + _421;
        float _430 = RVar[7u].y;
        float _432 = RVar[7u].z;
        float _434 = RVar[7u].w;
        RVar[1u].x = RVar[7u].x;
        RVar[1u].y = _430;
        RVar[1u].z = _432;
        RVar[1u].w = _434;
        float _442 = RVar[6u].y;
        float _444 = RVar[6u].z;
        float _446 = RVar[6u].w;
        RVar[0u].x = RVar[6u].x;
        RVar[0u].y = _442;
        RVar[0u].z = _444;
        RVar[0u].w = _446;
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
    uint _522 = PS_PUSH.alphaFunc >> 8u;
    if (_522 == 1u)
    {
        _pixelTmp = vec4(1.0);
    }
    else
    {
        if (_522 == 2u)
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
    uint _550 = PS_PUSH.alphaFunc >> 8u;
    if (_550 == 1u)
    {
        _pixelTmp_1 = vec4(1.0);
    }
    else
    {
        if (_550 == 2u)
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