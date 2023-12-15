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
        float _210 = RVar[6u].z;
        float _215 = RVar[4u].w;
        float _219 = RVar[6u].x;
        float _221 = (_215 * CBUFFER_1.values[11].w) + _219;
        float _223 = RVar[4u].w;
        float _227 = RVar[6u].y;
        float _229 = (_223 * CBUFFER_1.values[11].z) + _227;
        float _231 = RVar[5u].x;
        RVar[0u].x = clamp((RVar[0u].w + uintBitsToFloat(0u)) * 0.5, 0.0, 1.0);
        RVar[0u].y = clamp(_210 + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[123u].z = _221;
        RVar[123u].w = _229;
        RVar[127u].w = float(floatBitsToInt(_231));
        float _241 = RVar[4u].w;
        float _246 = (_241 * CBUFFER_1.values[12].y) + _221;
        float _248 = RVar[4u].w;
        float _252 = (_248 * CBUFFER_1.values[12].x) + _229;
        float _254 = RVar[2u].z;
        float _256 = RVar[2u].z;
        float _261 = RVar[5u].y;
        RVar[123u].x = _246;
        RVar[123u].y = _252;
        RVar[4u].w = uintBitsToFloat(1065353216u);
        RVar[127u].z = float(floatBitsToInt(_261));
        float _272 = RVar[2u].y;
        float _274 = RVar[2u].y;
        float _276 = (_272 * _274) + (_254 * _256);
        float _280 = RVar[127u].w;
        RVar[127u].x = _246 * uintBitsToFloat(1132396544u);
        RVar[123u].y = _276;
        float _285 = RVar[2u].x;
        float _287 = RVar[2u].x;
        float _289 = (_285 * _287) + _276;
        float _292 = RVar[127u].z;
        RVar[123u].y = _289;
        float _299 = RVar[127u].x;
        float _302 = inversesqrt(_289) * 0.5;
        RVar[5u].x = RVar[3u].x + ((_252 * uintBitsToFloat(1132396544u)) * (1.0 / _280));
        float _310 = RVar[3u].y;
        float _313 = RVar[2u].z;
        float _318 = RVar[2u].y;
        RVar[4u].x = (RVar[2u].x * _302) + uintBitsToFloat(1056964608u);
        RVar[5u].y = _310 + (_299 * (1.0 / _292));
        RVar[4u].z = (_313 * _302) + uintBitsToFloat(1056964608u);
        RVar[4u].y = (_318 * _302) + uintBitsToFloat(1056964608u);
    }
    if (stateVar == 0)
    {
        RVar[5u] = texture(tex_map0, vec4(RVar[5u].xy, 0.0, RVar[5u].x).xy);
    }
    if (stateVar == 0)
    {
        float _347 = RVar[0u].x;
        float _349 = RVar[5u].w;
        float _352 = (_347 * _349) + uintBitsToFloat(0u);
        float _354 = RVar[0u].y;
        float _356 = RVar[5u].z;
        float _359 = (_354 * _356) + uintBitsToFloat(0u);
        float _361 = RVar[3u].z;
        float _363 = RVar[5u].y;
        float _366 = (_361 * _363) + uintBitsToFloat(0u);
        float _368 = RVar[2u].w;
        float _370 = RVar[5u].x;
        float _373 = (_368 * _370) + uintBitsToFloat(0u);
        RVar[123u].x = _352;
        RVar[123u].y = _359;
        RVar[123u].z = _366;
        RVar[123u].w = _373;
        float _391 = RVar[7u].w;
        float _394 = (clamp(_352 + uintBitsToFloat(0u), 0.0, 1.0) * _391) + uintBitsToFloat(0u);
        float _396 = RVar[7u].z;
        float _399 = (clamp(_359 + uintBitsToFloat(0u), 0.0, 1.0) * _396) + uintBitsToFloat(0u);
        float _401 = RVar[7u].y;
        float _404 = (clamp(_366 + uintBitsToFloat(0u), 0.0, 1.0) * _401) + uintBitsToFloat(0u);
        float _406 = RVar[7u].x;
        float _409 = (clamp(_373 + uintBitsToFloat(0u), 0.0, 1.0) * _406) + uintBitsToFloat(0u);
        RVar[123u].x = _394;
        RVar[123u].y = _399;
        RVar[123u].z = _404;
        RVar[123u].w = _409;
        float _418 = clamp(CBUFFER_1.values[7].x + _409, 0.0, 1.0);
        float _422 = clamp(CBUFFER_1.values[7].z + _399, 0.0, 1.0);
        float _426 = clamp(CBUFFER_1.values[7].y + _404, 0.0, 1.0);
        RVar[127u].x = _418;
        RVar[127u].z = _422;
        RVar[127u].w = _426;
        RVar[7u].w = clamp((_394 + uintBitsToFloat(0u)) * 0.5, 0.0, 1.0);
        float _440 = RVar[1u].z;
        float _444 = RVar[1u].y;
        float _454 = RVar[1u].w;
        float _456 = RVar[127u].w;
        float _460 = RVar[1u].w;
        float _462 = RVar[127u].z;
        RVar[7u].x = ((RVar[1u].x + (-_418)) * RVar[1u].w) + RVar[127u].x;
        RVar[7u].y = ((_444 + (-_426)) * _454) + _456;
        RVar[7u].z = ((_440 + (-_422)) * _460) + _462;
        float _471 = RVar[4u].y;
        float _473 = RVar[4u].z;
        float _475 = RVar[4u].w;
        RVar[1u].x = RVar[4u].x;
        RVar[1u].y = _471;
        RVar[1u].z = _473;
        RVar[1u].w = _475;
        float _483 = RVar[7u].y;
        float _485 = RVar[7u].z;
        float _487 = RVar[7u].w;
        RVar[0u].x = RVar[7u].x;
        RVar[0u].y = _483;
        RVar[0u].z = _485;
        RVar[0u].w = _487;
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
    uint _563 = PS_PUSH.alphaFunc >> 8u;
    if (_563 == 1u)
    {
        _pixelTmp = vec4(1.0);
    }
    else
    {
        if (_563 == 2u)
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
    uint _591 = PS_PUSH.alphaFunc >> 8u;
    if (_591 == 1u)
    {
        _pixelTmp_1 = vec4(1.0);
    }
    else
    {
        if (_591 == 2u)
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