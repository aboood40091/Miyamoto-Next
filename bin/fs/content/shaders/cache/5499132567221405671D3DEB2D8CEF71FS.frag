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
uniform sampler2D tex_map2;
uniform sampler2D tex_map0;

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
        RVar[6u] = vec4(_87.x, _87.y, _87.z, RVar[6u].w);
        RVar[7u] = texture(tex_map2, vec4(RVar[5u].xy, 0.0, RVar[5u].x).xy);
    }
    if (stateVar == 0)
    {
        float _111 = RVar[0u].x;
        float _113 = RVar[6u].x;
        float _116 = (_111 * _113) + uintBitsToFloat(0u);
        float _119 = RVar[4u].w;
        float _123 = _119 + (-uintBitsToFloat(1056964608u));
        float _125 = RVar[4u].x;
        float _130 = RVar[0u].y;
        float _132 = RVar[6u].y;
        float _135 = (_130 * _132) + uintBitsToFloat(0u);
        RVar[123u].x = _116;
        RVar[5u].y = uintBitsToFloat(0u);
        RVar[4u].w = _125 + (-uintBitsToFloat(1056964608u));
        RVar[122u].x = _135;
        float _155 = RVar[0u].z;
        float _157 = RVar[6u].z;
        RVar[6u].x = _123 * CBUFFER_1.values[11].y;
        RVar[6u].y = _123 * CBUFFER_1.values[11].x;
        RVar[6u].z = (_155 * _157) + uintBitsToFloat(0u);
        RVar[2u].w = clamp(_116 + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[3u].z = clamp(_135 + uintBitsToFloat(0u), 0.0, 1.0);
    }
    if (stateVar == 0)
    {
        vec4 _194 = intBitsToFloat(ivec4(ivec3(textureSize(tex_map0, floatBitsToInt(vec4(RVar[5u].yy, 0.0, RVar[5u].y).x)), 1), textureQueryLevels(tex_map0)));
        RVar[5u] = vec4(_194.x, _194.y, RVar[5u].z, RVar[5u].w);
    }
    if (stateVar == 0)
    {
        float _208 = RVar[6u].z;
        float _213 = RVar[4u].w;
        float _217 = RVar[6u].x;
        float _219 = (_213 * CBUFFER_1.values[11].w) + _217;
        float _221 = RVar[4u].w;
        float _225 = RVar[6u].y;
        float _227 = (_221 * CBUFFER_1.values[11].z) + _225;
        float _229 = RVar[5u].x;
        RVar[0u].x = clamp(RVar[0u].w + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[0u].y = clamp(_208 + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[123u].z = _219;
        RVar[123u].w = _227;
        RVar[127u].w = float(floatBitsToInt(_229));
        float _239 = RVar[4u].w;
        float _244 = (_239 * CBUFFER_1.values[12].y) + _219;
        float _246 = RVar[4u].w;
        float _250 = (_246 * CBUFFER_1.values[12].x) + _227;
        float _252 = RVar[2u].z;
        float _254 = RVar[2u].z;
        float _259 = RVar[5u].y;
        RVar[123u].x = _244;
        RVar[123u].y = _250;
        RVar[4u].w = uintBitsToFloat(1065353216u);
        RVar[127u].z = float(floatBitsToInt(_259));
        float _270 = RVar[2u].y;
        float _272 = RVar[2u].y;
        float _274 = (_270 * _272) + (_252 * _254);
        float _278 = RVar[127u].w;
        RVar[127u].x = _244 * uintBitsToFloat(1132396544u);
        RVar[123u].y = _274;
        float _283 = RVar[2u].x;
        float _285 = RVar[2u].x;
        float _287 = (_283 * _285) + _274;
        float _290 = RVar[127u].z;
        RVar[123u].y = _287;
        float _297 = RVar[127u].x;
        float _301 = inversesqrt(_287) * 0.5;
        RVar[5u].x = RVar[3u].x + ((_250 * uintBitsToFloat(1132396544u)) * (1.0 / _278));
        float _309 = RVar[3u].y;
        float _312 = RVar[2u].z;
        float _317 = RVar[2u].y;
        RVar[4u].x = (RVar[2u].x * _301) + uintBitsToFloat(1056964608u);
        RVar[5u].y = _309 + (_297 * (1.0 / _290));
        RVar[4u].z = (_312 * _301) + uintBitsToFloat(1056964608u);
        RVar[4u].y = (_317 * _301) + uintBitsToFloat(1056964608u);
    }
    if (stateVar == 0)
    {
        RVar[5u] = texture(tex_map0, vec4(RVar[5u].xy, 0.0, RVar[5u].x).xy);
    }
    if (stateVar == 0)
    {
        float _346 = RVar[0u].x;
        float _348 = RVar[5u].w;
        float _351 = (_346 * _348) + uintBitsToFloat(0u);
        float _353 = RVar[0u].y;
        float _355 = RVar[5u].z;
        float _358 = (_353 * _355) + uintBitsToFloat(0u);
        float _360 = RVar[3u].z;
        float _362 = RVar[5u].y;
        float _365 = (_360 * _362) + uintBitsToFloat(0u);
        float _367 = RVar[2u].w;
        float _369 = RVar[5u].x;
        float _372 = (_367 * _369) + uintBitsToFloat(0u);
        RVar[123u].x = _351;
        RVar[123u].y = _358;
        RVar[123u].z = _365;
        RVar[123u].w = _372;
        float _390 = RVar[7u].w;
        float _393 = (clamp(_351 + uintBitsToFloat(0u), 0.0, 1.0) * _390) + uintBitsToFloat(0u);
        float _395 = RVar[7u].z;
        float _398 = (clamp(_358 + uintBitsToFloat(0u), 0.0, 1.0) * _395) + uintBitsToFloat(0u);
        float _400 = RVar[7u].y;
        float _403 = (clamp(_365 + uintBitsToFloat(0u), 0.0, 1.0) * _400) + uintBitsToFloat(0u);
        float _405 = RVar[7u].x;
        float _408 = (clamp(_372 + uintBitsToFloat(0u), 0.0, 1.0) * _405) + uintBitsToFloat(0u);
        RVar[123u].x = _393;
        RVar[123u].y = _398;
        RVar[123u].z = _403;
        RVar[123u].w = _408;
        float _417 = clamp(CBUFFER_1.values[7].x + _408, 0.0, 1.0);
        float _421 = clamp(CBUFFER_1.values[7].z + _398, 0.0, 1.0);
        float _425 = clamp(CBUFFER_1.values[7].y + _403, 0.0, 1.0);
        RVar[127u].x = _417;
        RVar[127u].z = _421;
        RVar[127u].w = _425;
        RVar[7u].w = clamp((_393 + uintBitsToFloat(0u)) * 0.5, 0.0, 1.0);
        float _439 = RVar[1u].z;
        float _443 = RVar[1u].y;
        float _453 = RVar[1u].w;
        float _455 = RVar[127u].w;
        float _459 = RVar[1u].w;
        float _461 = RVar[127u].z;
        RVar[7u].x = ((RVar[1u].x + (-_417)) * RVar[1u].w) + RVar[127u].x;
        RVar[7u].y = ((_443 + (-_425)) * _453) + _455;
        RVar[7u].z = ((_439 + (-_421)) * _459) + _461;
        float _470 = RVar[4u].y;
        float _472 = RVar[4u].z;
        float _474 = RVar[4u].w;
        RVar[1u].x = RVar[4u].x;
        RVar[1u].y = _470;
        RVar[1u].z = _472;
        RVar[1u].w = _474;
        float _482 = RVar[7u].y;
        float _484 = RVar[7u].z;
        float _486 = RVar[7u].w;
        RVar[0u].x = RVar[7u].x;
        RVar[0u].y = _482;
        RVar[0u].z = _484;
        RVar[0u].w = _486;
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
    uint _562 = PS_PUSH.alphaFunc >> 8u;
    if (_562 == 1u)
    {
        _pixelTmp = vec4(1.0);
    }
    else
    {
        if (_562 == 2u)
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
    uint _590 = PS_PUSH.alphaFunc >> 8u;
    if (_590 == 1u)
    {
        _pixelTmp_1 = vec4(1.0);
    }
    else
    {
        if (_590 == 2u)
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