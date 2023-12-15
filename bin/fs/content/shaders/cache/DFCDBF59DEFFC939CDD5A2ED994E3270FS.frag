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
        vec4 _68 = texture(tex_map1, vec4(RVar[4u].xy, 0.0, RVar[4u].x).xy);
        RVar[4u] = vec4(_68.x, RVar[4u].y, RVar[4u].z, _68.w);
    }
    if (stateVar == 0)
    {
        float _88 = (CBUFFER_1.values[4].x * uintBitsToFloat(1065353216u)) + uintBitsToFloat(0u);
        float _92 = RVar[4u].w;
        float _96 = _92 + (-uintBitsToFloat(1056964608u));
        float _98 = RVar[4u].x;
        RVar[123u].x = _88;
        RVar[4u].y = uintBitsToFloat(0u);
        RVar[4u].w = _98 + (-uintBitsToFloat(1056964608u));
        RVar[8u].w = uintBitsToFloat(1065353216u);
        float _127 = RVar[2u].z;
        float _129 = RVar[2u].z;
        RVar[4u].x = _96 * CBUFFER_1.values[11].y;
        RVar[0u].y = _96 * CBUFFER_1.values[11].x;
        RVar[0u].z = (CBUFFER_1.values[4].y * uintBitsToFloat(1065353216u)) + uintBitsToFloat(0u);
        RVar[2u].w = clamp(_88 + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[0u].x = _127 * _129;
    }
    if (stateVar == 0)
    {
        vec4 _157 = intBitsToFloat(ivec4(ivec3(textureSize(tex_map0, floatBitsToInt(vec4(RVar[4u].yy, 0.0, RVar[4u].y).x)), 1), textureQueryLevels(tex_map0)));
        RVar[6u] = vec4(_157.x, _157.y, RVar[6u].z, RVar[6u].w);
        vec4 _174 = intBitsToFloat(ivec4(ivec3(textureSize(tex_map2, floatBitsToInt(vec4(RVar[4u].yy, 0.0, RVar[4u].y).x)), 1), textureQueryLevels(tex_map2)));
        RVar[7u] = vec4(_174.x, _174.y, RVar[7u].z, RVar[7u].w);
    }
    if (stateVar == 0)
    {
        float _188 = (CBUFFER_1.values[4].z * uintBitsToFloat(1065353216u)) + uintBitsToFloat(0u);
        float _190 = RVar[0u].z;
        float _195 = RVar[4u].w;
        float _199 = RVar[4u].x;
        float _201 = (_195 * CBUFFER_1.values[11].w) + _199;
        float _203 = RVar[4u].w;
        float _207 = RVar[0u].y;
        float _209 = (_203 * CBUFFER_1.values[11].z) + _207;
        float _211 = RVar[6u].x;
        RVar[123u].x = _188;
        RVar[126u].y = clamp(_190 + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[123u].z = _201;
        RVar[123u].w = _209;
        RVar[127u].y = float(floatBitsToInt(_211));
        float _222 = RVar[4u].w;
        float _227 = (_222 * CBUFFER_1.values[12].y) + _201;
        float _229 = RVar[4u].w;
        float _233 = (_229 * CBUFFER_1.values[12].x) + _209;
        float _238 = RVar[2u].w;
        float _243 = RVar[6u].y;
        RVar[123u].x = _227;
        RVar[123u].y = _233;
        RVar[127u].w = clamp(_238 + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[127u].x = float(floatBitsToInt(_243));
        float _251 = RVar[126u].y;
        float _254 = clamp(_251 + uintBitsToFloat(0u), 0.0, 1.0);
        float _262 = _233 * uintBitsToFloat(1132396544u);
        float _264 = RVar[127u].y;
        RVar[126u].x = _254;
        RVar[125u].y = clamp(clamp(_188 + uintBitsToFloat(0u), 0.0, 1.0) + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[126u].z = _227 * uintBitsToFloat(1132396544u);
        RVar[125u].w = _262;
        float _272 = RVar[2u].y;
        float _274 = RVar[2u].y;
        float _276 = RVar[0u].x;
        float _278 = (_272 * _274) + _276;
        float _280 = RVar[1u].x;
        float _282 = RVar[127u].w;
        float _286 = RVar[1u].y;
        float _291 = RVar[127u].x;
        RVar[123u].x = _278;
        RVar[127u].y = _280 + (-_282);
        RVar[127u].z = _286 + (-_254);
        float _300 = RVar[2u].x;
        float _302 = RVar[2u].x;
        float _306 = RVar[126u].z;
        float _309 = RVar[1u].z;
        float _311 = RVar[125u].y;
        float _315 = RVar[7u].x;
        RVar[0u].x = RVar[3u].x + (_262 * (1.0 / _264));
        RVar[124u].y = (_300 * _302) + _278;
        RVar[126u].w = _309 + (-_311);
        RVar[126u].y = float(floatBitsToInt(_315));
        float _332 = RVar[3u].y;
        float _335 = RVar[7u].y;
        RVar[3u].x = (RVar[127u].y * RVar[1u].w) + RVar[127u].w;
        RVar[0u].y = _332 + (_306 * (1.0 / _291));
        RVar[127u].w = float(floatBitsToInt(_335));
        float _350 = RVar[126u].w;
        float _352 = RVar[1u].w;
        float _354 = RVar[125u].y;
        float _358 = RVar[126u].y;
        RVar[3u].y = (RVar[127u].z * RVar[1u].w) + RVar[126u].x;
        RVar[3u].z = (_350 * _352) + _354;
        float _366 = RVar[127u].w;
        float _372 = RVar[126u].z;
        float _375 = RVar[124u].y;
        float _378 = inversesqrt(_375) * 0.5;
        RVar[1u].x = RVar[5u].x + (RVar[125u].w * (1.0 / _358));
        float _386 = RVar[5u].y;
        float _389 = RVar[2u].z;
        float _394 = RVar[2u].y;
        RVar[8u].x = (RVar[2u].x * _378) + uintBitsToFloat(1056964608u);
        RVar[1u].y = _386 + (_372 * (1.0 / _366));
        RVar[8u].z = (_389 * _378) + uintBitsToFloat(1056964608u);
        RVar[8u].y = (_394 * _378) + uintBitsToFloat(1056964608u);
    }
    if (stateVar == 0)
    {
        RVar[0u] = vec4(texture(tex_map0, vec4(RVar[0u].xy, 0.0, RVar[0u].x).xy).w, RVar[0u].y, RVar[0u].z, RVar[0u].w);
        RVar[1u] = vec4(texture(tex_map2, vec4(RVar[1u].xy, 0.0, RVar[1u].x).xy).w, RVar[1u].y, RVar[1u].z, RVar[1u].w);
    }
    if (stateVar == 0)
    {
        float _446 = RVar[0u].w;
        float _448 = RVar[0u].x;
        float _451 = (_446 * _448) + uintBitsToFloat(0u);
        RVar[124u].y = (RVar[0u].w * RVar[1u].x) + uintBitsToFloat(0u);
        RVar[123u].w = _451;
        RVar[3u].w = clamp((clamp((_451 + uintBitsToFloat(0u)) * 0.5, 0.0, 1.0) + RVar[124u].y) * 0.5, 0.0, 1.0);
        float _467 = RVar[8u].y;
        float _469 = RVar[8u].z;
        float _471 = RVar[8u].w;
        RVar[1u].x = RVar[8u].x;
        RVar[1u].y = _467;
        RVar[1u].z = _469;
        RVar[1u].w = _471;
        float _479 = RVar[3u].y;
        float _481 = RVar[3u].z;
        float _483 = RVar[3u].w;
        RVar[0u].x = RVar[3u].x;
        RVar[0u].y = _479;
        RVar[0u].z = _481;
        RVar[0u].w = _483;
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
    uint _558 = PS_PUSH.alphaFunc >> 8u;
    if (_558 == 1u)
    {
        _pixelTmp = vec4(1.0);
    }
    else
    {
        if (_558 == 2u)
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
    uint _586 = PS_PUSH.alphaFunc >> 8u;
    if (_586 == 1u)
    {
        _pixelTmp_1 = vec4(1.0);
    }
    else
    {
        if (_586 == 2u)
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