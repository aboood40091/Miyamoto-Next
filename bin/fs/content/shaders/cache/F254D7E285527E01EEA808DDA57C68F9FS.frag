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
uniform sampler2D tex_map3;

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
        vec4 _102 = texture(tex_map2, vec4(RVar[5u].xy, 0.0, RVar[5u].x).xy);
        RVar[5u] = vec4(_102.x, _102.y, _102.z, RVar[5u].w);
        vec4 _117 = texture(tex_map3, vec4(RVar[6u].xy, 0.0, RVar[6u].x).xy);
        RVar[6u] = vec4(_117.x, _117.y, _117.z, RVar[6u].w);
    }
    if (stateVar == 0)
    {
        float _127 = RVar[0u].x;
        float _129 = RVar[4u].x;
        float _132 = (_127 * _129) + uintBitsToFloat(0u);
        float _134 = RVar[0u].x;
        float _136 = RVar[5u].x;
        float _141 = RVar[0u].z;
        float _143 = RVar[4u].z;
        float _146 = (_141 * _143) + uintBitsToFloat(0u);
        float _148 = RVar[0u].y;
        float _150 = RVar[4u].y;
        float _153 = (_148 * _150) + uintBitsToFloat(0u);
        float _155 = RVar[0u].y;
        float _157 = RVar[5u].y;
        RVar[123u].x = _132;
        RVar[126u].y = (_134 * _136) + uintBitsToFloat(0u);
        RVar[123u].z = _146;
        RVar[123u].w = _153;
        RVar[127u].z = (_155 * _157) + uintBitsToFloat(0u);
        float _187 = RVar[6u].x;
        RVar[126u].z = (RVar[0u].z * RVar[5u].z) + uintBitsToFloat(0u);
        RVar[127u].y = (-_187) + uintBitsToFloat(1065353216u);
        float _195 = RVar[3u].z;
        float _198 = (clamp(_146 + uintBitsToFloat(0u), 0.0, 1.0) * _195) + uintBitsToFloat(0u);
        float _200 = RVar[3u].y;
        float _203 = (clamp(_153 + uintBitsToFloat(0u), 0.0, 1.0) * _200) + uintBitsToFloat(0u);
        float _205 = RVar[3u].x;
        float _208 = (clamp(_132 + uintBitsToFloat(0u), 0.0, 1.0) * _205) + uintBitsToFloat(0u);
        float _210 = RVar[6u].y;
        float _215 = RVar[6u].z;
        RVar[123u].x = _198;
        RVar[123u].y = _203;
        RVar[123u].z = _208;
        RVar[127u].w = (-_210) + uintBitsToFloat(1065353216u);
        RVar[126u].w = (-_215) + uintBitsToFloat(1065353216u);
        float _247 = RVar[127u].y;
        RVar[127u].x = clamp(RVar[0u].w + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[125u].z = (CBUFFER_1.values[4].x * _247) + uintBitsToFloat(0u);
        float _255 = RVar[126u].y;
        float _261 = RVar[127u].w;
        float _264 = (CBUFFER_1.values[4].y * _261) + uintBitsToFloat(0u);
        float _266 = RVar[126u].z;
        float _270 = RVar[127u].z;
        float _276 = RVar[126u].w;
        float _279 = (CBUFFER_1.values[4].z * _276) + uintBitsToFloat(0u);
        RVar[123u].y = _264;
        RVar[122u].x = _279;
        float _284 = RVar[127u].x;
        float _294 = RVar[6u].y;
        float _299 = RVar[6u].x;
        float _301 = RVar[125u].z;
        RVar[126u].y = clamp((clamp(clamp(_198 + uintBitsToFloat(0u), 0.0, 1.0) + _266, 0.0, 1.0) * RVar[6u].z) + _279, 0.0, 1.0);
        RVar[125u].z = clamp((clamp(clamp(_203 + uintBitsToFloat(0u), 0.0, 1.0) + _270, 0.0, 1.0) * _294) + _264, 0.0, 1.0);
        RVar[127u].w = clamp((clamp(clamp(_208 + uintBitsToFloat(0u), 0.0, 1.0) + _255, 0.0, 1.0) * _299) + _301, 0.0, 1.0);
        RVar[6u].w = uintBitsToFloat(1065353216u);
        RVar[127u].y = dot(vec4(RVar[2u].x, RVar[2u].y, RVar[2u].z, uintBitsToFloat(2147483648u)), vec4(RVar[2u].x, RVar[2u].y, RVar[2u].z, uintBitsToFloat(0u)));
        float _333 = RVar[1u].x;
        float _335 = RVar[127u].w;
        float _339 = RVar[1u].z;
        float _341 = RVar[126u].y;
        float _345 = RVar[1u].y;
        float _347 = RVar[125u].z;
        RVar[0u].w = clamp(clamp(clamp(_284 + uintBitsToFloat(0u), 0.0, 1.0) + uintBitsToFloat(0u), 0.0, 1.0) + uintBitsToFloat(0u), 0.0, 1.0);
        float _361 = RVar[1u].w;
        float _363 = RVar[125u].z;
        float _367 = RVar[1u].w;
        float _369 = RVar[126u].y;
        float _373 = RVar[127u].y;
        float _376 = inversesqrt(_373) * 0.5;
        RVar[0u].x = ((_333 + (-_335)) * RVar[1u].w) + RVar[127u].w;
        RVar[0u].y = ((_345 + (-_347)) * _361) + _363;
        RVar[0u].z = ((_339 + (-_341)) * _367) + _369;
        float _381 = RVar[2u].x;
        float _385 = (_381 * _376) + uintBitsToFloat(1056964608u);
        float _387 = RVar[2u].y;
        float _390 = (_387 * _376) + uintBitsToFloat(1056964608u);
        float _392 = RVar[2u].z;
        float _395 = (_392 * _376) + uintBitsToFloat(1056964608u);
        RVar[6u].x = _385;
        RVar[6u].y = _390;
        RVar[6u].z = _395;
        float _400 = RVar[6u].w;
        RVar[2u].x = _385;
        RVar[2u].y = _390;
        RVar[2u].z = _395;
        RVar[2u].w = _400;
        float _408 = RVar[0u].y;
        float _410 = RVar[0u].z;
        float _412 = RVar[0u].w;
        RVar[1u].x = RVar[0u].x;
        RVar[1u].y = _408;
        RVar[1u].z = _410;
        RVar[1u].w = _412;
    }
    switch (PS_PUSH.alphaFunc & 255u)
    {
        case 0u:
        {
            discard;
        }
        case 1u:
        {
            if (!(RVar[1u].w < PS_PUSH.alphaRef))
            {
                discard;
            }
            break;
        }
        case 2u:
        {
            if (abs(RVar[1u].w - PS_PUSH.alphaRef) > 9.9999997473787516355514526367188e-05)
            {
                discard;
            }
            break;
        }
        case 3u:
        {
            if (!(RVar[1u].w <= PS_PUSH.alphaRef))
            {
                discard;
            }
            break;
        }
        case 4u:
        {
            if (!(RVar[1u].w > PS_PUSH.alphaRef))
            {
                discard;
            }
            break;
        }
        case 5u:
        {
            if (abs(RVar[1u].w - PS_PUSH.alphaRef) <= 9.9999997473787516355514526367188e-05)
            {
                discard;
            }
            break;
        }
        case 6u:
        {
            if (!(RVar[1u].w >= PS_PUSH.alphaRef))
            {
                discard;
            }
            break;
        }
    }
    _pixelTmp = RVar[1u];
    uint _488 = PS_PUSH.alphaFunc >> 8u;
    if (_488 == 1u)
    {
        _pixelTmp = vec4(1.0);
    }
    else
    {
        if (_488 == 2u)
        {
            _pixelTmp = vec4(0.0);
        }
    }
    if ((PS_PUSH.needsPremultiply & 1u) != 0u)
    {
        _pixelTmp *= vec4(_pixelTmp.www, 1.0);
    }
    if (PS_PUSH.uIsSelected != 0) PIXEL_0 = vec4(_pixelTmp.rgb * 0.5f + vec3(1.0f, 0.25f, 0.25f) * 0.5f, _pixelTmp.a); else PIXEL_0 = _pixelTmp; ItemID = PS_PUSH.uItemID;
    _pixelTmp_1 = RVar[2u];
    uint _516 = PS_PUSH.alphaFunc >> 8u;
    if (_516 == 1u)
    {
        _pixelTmp_1 = vec4(1.0);
    }
    else
    {
        if (_516 == 2u)
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