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
uniform sampler2D tex_map2;

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
        RVar[3u] = texture(tex_map1, vec4(RVar[3u].xy, 0.0, RVar[3u].x).xy);
        vec4 _77 = texture(tex_map0, vec4(RVar[2u].xy, 0.0, RVar[2u].x).xy);
        RVar[2u] = vec4(_77.x, _77.y, _77.z, RVar[2u].w);
        RVar[4u] = texture(tex_map2, vec4(RVar[4u].xy, 0.0, RVar[4u].x).xy);
    }
    if (stateVar == 0)
    {
        float _100 = RVar[3u].x;
        float _105 = (_100 * uintBitsToFloat(1065353216u)) + uintBitsToFloat(0u);
        float _118 = RVar[3u].z;
        float _122 = (_118 * uintBitsToFloat(1065353216u)) + uintBitsToFloat(0u);
        float _124 = RVar[3u].y;
        float _128 = (_124 * uintBitsToFloat(1065353216u)) + uintBitsToFloat(0u);
        float _130 = RVar[2u].x;
        RVar[123u].x = _105;
        RVar[127u].y = (-CBUFFER_1.values[7].w) + uintBitsToFloat(1065353216u);
        RVar[123u].z = _122;
        RVar[123u].w = _128;
        RVar[126u].y = (-_130) + uintBitsToFloat(1065353216u);
        float _143 = RVar[2u].y;
        float _155 = RVar[2u].z;
        RVar[125u].y = clamp(_105 + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[127u].z = clamp(_128 + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[126u].w = (-_155) + uintBitsToFloat(1065353216u);
        RVar[127u].w = clamp(_122 + uintBitsToFloat(0u), 0.0, 1.0);
        float _176 = RVar[4u].z;
        float _178 = RVar[127u].y;
        float _181 = (_176 * _178) + uintBitsToFloat(0u);
        float _183 = RVar[4u].y;
        float _185 = RVar[127u].y;
        float _188 = (_183 * _185) + uintBitsToFloat(0u);
        float _190 = RVar[4u].x;
        float _192 = RVar[127u].y;
        float _195 = (_190 * _192) + uintBitsToFloat(0u);
        RVar[127u].x = (CBUFFER_1.values[5].x * RVar[126u].y) + uintBitsToFloat(0u);
        RVar[123u].y = _181;
        RVar[123u].z = _188;
        RVar[123u].w = _195;
        RVar[127u].y = (CBUFFER_1.values[5].y * ((-_143) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        float _216 = RVar[126u].w;
        float _219 = (CBUFFER_1.values[5].z * _216) + uintBitsToFloat(0u);
        float _221 = RVar[127u].w;
        float _228 = RVar[127u].z;
        float _235 = RVar[3u].w;
        float _239 = (_235 * uintBitsToFloat(1065353216u)) + uintBitsToFloat(0u);
        RVar[126u].x = clamp((RVar[125u].y * CBUFFER_1.values[7].w) + _195, 0.0, 1.0);
        RVar[123u].y = _219;
        RVar[127u].z = clamp((_221 * CBUFFER_1.values[7].w) + _181, 0.0, 1.0);
        RVar[127u].w = clamp((_228 * CBUFFER_1.values[7].w) + _188, 0.0, 1.0);
        RVar[122u].x = _239;
        float _260 = RVar[2u].y;
        float _262 = RVar[127u].y;
        float _269 = RVar[2u].x;
        float _271 = RVar[127u].x;
        float _276 = RVar[4u].w;
        float _280 = (_276 * uintBitsToFloat(1065353216u)) + uintBitsToFloat(0u);
        RVar[127u].y = clamp((CBUFFER_1.values[4].z * RVar[2u].z) + _219, 0.0, 1.0);
        RVar[126u].z = clamp((CBUFFER_1.values[4].y * _260) + _262, 0.0, 1.0);
        RVar[126u].w = clamp((CBUFFER_1.values[4].x * _269) + _271, 0.0, 1.0);
        RVar[122u].x = _280;
        float _290 = RVar[127u].z;
        float _293 = (CBUFFER_1.values[7].z * _290) + uintBitsToFloat(0u);
        float _297 = RVar[127u].w;
        float _300 = (CBUFFER_1.values[7].y * _297) + uintBitsToFloat(0u);
        float _304 = RVar[126u].x;
        float _307 = (CBUFFER_1.values[7].x * _304) + uintBitsToFloat(0u);
        RVar[123u].y = _293;
        RVar[123u].z = _300;
        RVar[123u].w = _307;
        RVar[2u].w = uintBitsToFloat(1065353216u);
        float _314 = RVar[126u].w;
        float _316 = clamp(_314 + _307, 0.0, 1.0);
        float _323 = RVar[127u].y;
        float _327 = RVar[126u].z;
        float _331 = RVar[1u].z;
        float _333 = RVar[1u].z;
        RVar[126u].x = _316;
        RVar[127u].y = (CBUFFER_1.values[4].w * clamp(clamp(_239 + uintBitsToFloat(0u), 0.0, 1.0) + _280, 0.0, 1.0)) + uintBitsToFloat(0u);
        RVar[126u].z = clamp(_323 + _293, 0.0, 1.0);
        RVar[126u].w = clamp(_327 + _300, 0.0, 1.0);
        float _355 = RVar[0u].x;
        RVar[125u].y = dot(vec4(RVar[1u].x, RVar[1u].y, _331 * _333, uintBitsToFloat(2147483648u)), vec4(RVar[1u].x, RVar[1u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        float _366 = RVar[0u].z;
        float _368 = RVar[126u].z;
        float _372 = RVar[0u].y;
        float _374 = RVar[126u].w;
        float _380 = RVar[127u].y;
        RVar[4u].x = ((_355 + (-_316)) * RVar[0u].w) + RVar[126u].x;
        RVar[4u].w = clamp(CBUFFER_1.values[5].w + _380, 0.0, 1.0);
        float _392 = RVar[0u].w;
        float _394 = RVar[126u].z;
        float _398 = RVar[125u].y;
        float _401 = inversesqrt(_398) * 0.5;
        RVar[4u].y = ((_372 + (-_374)) * RVar[0u].w) + RVar[126u].w;
        RVar[4u].z = ((_366 + (-_368)) * _392) + _394;
        float _405 = RVar[1u].x;
        float _409 = (_405 * _401) + uintBitsToFloat(1056964608u);
        float _411 = RVar[1u].y;
        float _414 = (_411 * _401) + uintBitsToFloat(1056964608u);
        float _416 = RVar[1u].z;
        float _419 = (_416 * _401) + uintBitsToFloat(1056964608u);
        RVar[2u].x = _409;
        RVar[2u].y = _414;
        RVar[2u].z = _419;
        float _424 = RVar[2u].w;
        RVar[1u].x = _409;
        RVar[1u].y = _414;
        RVar[1u].z = _419;
        RVar[1u].w = _424;
        float _432 = RVar[4u].y;
        float _434 = RVar[4u].z;
        float _436 = RVar[4u].w;
        RVar[0u].x = RVar[4u].x;
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