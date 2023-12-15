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
uniform sampler2D tex_map3;
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
        RVar[4u] = vec4(_72.x, _72.y, _72.z, RVar[4u].w);
        vec4 _87 = texture(tex_map0, vec4(RVar[3u].xy, 0.0, RVar[3u].x).xy);
        RVar[3u] = vec4(_87.x, _87.y, _87.z, RVar[3u].w);
        vec4 _102 = texture(tex_map3, vec4(RVar[6u].xy, 0.0, RVar[6u].x).xy);
        RVar[6u] = vec4(_102.x, _102.y, _102.z, RVar[6u].w);
        vec4 _117 = texture(tex_map2, vec4(RVar[5u].xy, 0.0, RVar[5u].x).xy);
        RVar[5u] = vec4(_117.x, _117.y, _117.z, RVar[5u].w);
    }
    if (stateVar == 0)
    {
        float _133 = RVar[0u].z;
        float _135 = RVar[4u].z;
        float _138 = (_133 * _135) + uintBitsToFloat(0u);
        float _140 = RVar[0u].y;
        float _142 = RVar[4u].y;
        float _145 = (_140 * _142) + uintBitsToFloat(0u);
        float _147 = RVar[0u].x;
        float _149 = RVar[4u].x;
        float _152 = (_147 * _149) + uintBitsToFloat(0u);
        float _154 = RVar[6u].y;
        RVar[127u].x = (-RVar[6u].x) + uintBitsToFloat(1065353216u);
        RVar[123u].y = _138;
        RVar[123u].z = _145;
        RVar[123u].w = _152;
        RVar[127u].w = (-_154) + uintBitsToFloat(1065353216u);
        float _181 = RVar[6u].x;
        RVar[127u].z = (-RVar[6u].z) + uintBitsToFloat(1065353216u);
        RVar[126u].w = (_181 * uintBitsToFloat(1065353216u)) + uintBitsToFloat(0u);
        float _190 = RVar[3u].z;
        float _193 = (clamp(_138 + uintBitsToFloat(0u), 0.0, 1.0) * _190) + uintBitsToFloat(0u);
        float _195 = RVar[3u].y;
        float _198 = (clamp(_145 + uintBitsToFloat(0u), 0.0, 1.0) * _195) + uintBitsToFloat(0u);
        float _200 = RVar[3u].x;
        float _203 = (clamp(_152 + uintBitsToFloat(0u), 0.0, 1.0) * _200) + uintBitsToFloat(0u);
        float _205 = RVar[6u].y;
        float _211 = RVar[6u].z;
        RVar[123u].x = _193;
        RVar[123u].y = _198;
        RVar[123u].z = _203;
        RVar[125u].w = (_205 * uintBitsToFloat(1065353216u)) + uintBitsToFloat(0u);
        RVar[127u].y = (_211 * uintBitsToFloat(1065353216u)) + uintBitsToFloat(0u);
        float _231 = RVar[127u].x;
        float _234 = (CBUFFER_1.values[4].x * _231) + uintBitsToFloat(0u);
        float _247 = RVar[127u].w;
        RVar[123u].x = _234;
        RVar[126u].y = clamp(_193 + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[126u].z = clamp(_198 + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[127u].x = (CBUFFER_1.values[4].y * _247) + uintBitsToFloat(0u);
        float _256 = RVar[126u].w;
        float _261 = RVar[125u].w;
        float _266 = RVar[127u].y;
        float _273 = RVar[127u].z;
        float _276 = (CBUFFER_1.values[4].z * _273) + uintBitsToFloat(0u);
        float _278 = RVar[6u].x;
        RVar[123u].w = _276;
        RVar[127u].z = clamp((clamp(_203 + uintBitsToFloat(0u), 0.0, 1.0) * _278) + _234, 0.0, 1.0);
        float _285 = RVar[126u].y;
        float _287 = RVar[6u].z;
        float _290 = clamp((_285 * _287) + _276, 0.0, 1.0);
        float _292 = RVar[126u].z;
        float _294 = RVar[6u].y;
        float _296 = RVar[127u].x;
        float _299 = clamp((_292 * _294) + _296, 0.0, 1.0);
        float _301 = RVar[5u].x;
        float _304 = (clamp(_256 + uintBitsToFloat(0u), 0.0, 1.0) * _301) + uintBitsToFloat(0u);
        float _306 = RVar[5u].y;
        float _309 = (clamp(_261 + uintBitsToFloat(0u), 0.0, 1.0) * _306) + uintBitsToFloat(0u);
        float _311 = RVar[5u].z;
        float _314 = (clamp(_266 + uintBitsToFloat(0u), 0.0, 1.0) * _311) + uintBitsToFloat(0u);
        RVar[123u].x = _290;
        RVar[123u].y = _299;
        RVar[123u].z = _304;
        RVar[123u].w = _309;
        RVar[122u].x = _314;
        float _322 = RVar[2u].z;
        float _324 = RVar[2u].z;
        float _331 = RVar[127u].z;
        float _333 = clamp(_331 + _304, 0.0, 1.0);
        RVar[126u].y = clamp(_290 + _314, 0.0, 1.0);
        RVar[127u].z = clamp(_299 + _309, 0.0, 1.0);
        RVar[126u].w = _333;
        RVar[6u].w = uintBitsToFloat(0u);
        float _355 = RVar[1u].x;
        RVar[127u].y = dot(vec4(RVar[2u].x, RVar[2u].y, _322 * _324, uintBitsToFloat(2147483648u)), vec4(RVar[2u].x, RVar[2u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        float _366 = RVar[1u].z;
        float _368 = RVar[126u].y;
        float _372 = RVar[1u].y;
        float _374 = RVar[127u].z;
        RVar[6u].x = ((_355 + (-_333)) * RVar[1u].w) + RVar[126u].w;
        RVar[5u].w = uintBitsToFloat(1065353216u);
        float _387 = RVar[1u].w;
        float _389 = RVar[126u].y;
        float _393 = RVar[127u].y;
        float _396 = inversesqrt(_393) * 0.5;
        RVar[6u].y = ((_372 + (-_374)) * RVar[1u].w) + RVar[127u].z;
        RVar[6u].z = ((_366 + (-_368)) * _387) + _389;
        float _400 = RVar[2u].x;
        float _404 = (_400 * _396) + uintBitsToFloat(1056964608u);
        float _406 = RVar[2u].y;
        float _409 = (_406 * _396) + uintBitsToFloat(1056964608u);
        float _411 = RVar[2u].z;
        float _414 = (_411 * _396) + uintBitsToFloat(1056964608u);
        RVar[5u].x = _404;
        RVar[5u].y = _409;
        RVar[5u].z = _414;
        float _419 = RVar[5u].w;
        RVar[1u].x = _404;
        RVar[1u].y = _409;
        RVar[1u].z = _414;
        RVar[1u].w = _419;
        float _427 = RVar[6u].y;
        float _429 = RVar[6u].z;
        float _431 = RVar[6u].w;
        RVar[0u].x = RVar[6u].x;
        RVar[0u].y = _427;
        RVar[0u].z = _429;
        RVar[0u].w = _431;
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
    uint _507 = PS_PUSH.alphaFunc >> 8u;
    if (_507 == 1u)
    {
        _pixelTmp = vec4(1.0);
    }
    else
    {
        if (_507 == 2u)
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
    uint _535 = PS_PUSH.alphaFunc >> 8u;
    if (_535 == 1u)
    {
        _pixelTmp_1 = vec4(1.0);
    }
    else
    {
        if (_535 == 2u)
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