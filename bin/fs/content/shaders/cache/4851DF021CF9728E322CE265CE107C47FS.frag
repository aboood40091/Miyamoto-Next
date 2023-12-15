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

layout(location = 1) in vec4 PARAM_1;
layout(location = 0) in vec4 PARAM_0;
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
    RVar[0u] = PARAM_1;
    RVar[1u] = PARAM_0;
    RVar[2u] = PARAM_3;
    RVar[3u] = PARAM_4;
    RVar[4u] = PARAM_5;
    if (stateVar == 0)
    {
        RVar[3u] = texture(tex_map1, vec4(RVar[3u].xy, 0.0, RVar[3u].x).xy);
        RVar[2u] = texture(tex_map0, vec4(RVar[2u].xy, 0.0, RVar[2u].x).xy);
        RVar[4u] = texture(tex_map2, vec4(RVar[4u].xy, 0.0, RVar[4u].x).xy);
    }
    if (stateVar == 0)
    {
        float _98 = RVar[3u].w;
        float _109 = (_98 * CBUFFER_1.values[10].w) + uintBitsToFloat(0u);
        float _111 = RVar[3u].z;
        float _117 = RVar[3u].y;
        float _122 = RVar[3u].x;
        float _127 = RVar[2u].x;
        RVar[123u].x = _109;
        RVar[127u].x = (-_127) + uintBitsToFloat(1065353216u);
        float _140 = (CBUFFER_1.values[5].x * ((-_122) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        float _144 = clamp(_109 + uintBitsToFloat(0u), 0.0, 1.0);
        float _149 = (CBUFFER_1.values[5].z * ((-_111) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        float _154 = (CBUFFER_1.values[5].y * ((-_117) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        float _156 = RVar[2u].y;
        RVar[123u].x = _140;
        RVar[127u].y = _144;
        RVar[123u].z = _149;
        RVar[123u].w = _154;
        RVar[127u].w = (-_156) + uintBitsToFloat(1065353216u);
        float _169 = RVar[3u].y;
        float _172 = clamp((CBUFFER_1.values[4].y * _169) + _154, 0.0, 1.0);
        float _176 = RVar[3u].x;
        float _179 = clamp((CBUFFER_1.values[4].x * _176) + _140, 0.0, 1.0);
        float _181 = RVar[2u].z;
        float _188 = RVar[3u].z;
        float _191 = clamp((CBUFFER_1.values[4].z * _188) + _149, 0.0, 1.0);
        float _193 = RVar[2u].w;
        float _196 = (_144 * _193) + uintBitsToFloat(0u);
        RVar[123u].x = _172;
        RVar[123u].y = _179;
        RVar[123u].w = _191;
        RVar[122u].x = _196;
        float _205 = RVar[127u].w;
        float _207 = (CBUFFER_1.values[5].y * _205) + _172;
        float _211 = RVar[127u].x;
        float _213 = (CBUFFER_1.values[5].x * _211) + _179;
        float _215 = RVar[2u].w;
        float _223 = (CBUFFER_1.values[5].z * ((-_181) + uintBitsToFloat(1065353216u))) + _191;
        float _225 = RVar[127u].y;
        float _227 = RVar[4u].w;
        RVar[123u].x = _207;
        RVar[123u].y = _213;
        RVar[127u].z = clamp((_215 + _196) * 2.0, 0.0, 1.0);
        RVar[123u].w = _223;
        RVar[127u].w = (_225 * _227) + uintBitsToFloat(0u);
        float _247 = RVar[2u].y;
        float _251 = clamp(((CBUFFER_1.values[4].y * _247) + _207) * 2.0, 0.0, 1.0);
        float _255 = RVar[2u].x;
        float _259 = clamp(((CBUFFER_1.values[4].x * _255) + _213) * 2.0, 0.0, 1.0);
        float _263 = RVar[4u].x;
        float _266 = (CBUFFER_1.values[4].x * _263) + uintBitsToFloat(0u);
        float _270 = RVar[4u].y;
        float _273 = (CBUFFER_1.values[4].y * _270) + uintBitsToFloat(0u);
        RVar[127u].x = clamp(((CBUFFER_1.values[4].z * RVar[2u].z) + _223) * 2.0, 0.0, 1.0);
        RVar[123u].y = _251;
        RVar[123u].z = _259;
        RVar[123u].w = _266;
        RVar[122u].x = _273;
        float _280 = RVar[127u].z;
        float _282 = RVar[127u].w;
        float _291 = RVar[4u].z;
        float _294 = (CBUFFER_1.values[4].z * _291) + uintBitsToFloat(0u);
        RVar[123u].w = _294;
        RVar[4u].w = uintBitsToFloat(1065353216u);
        float _299 = RVar[127u].x;
        float _310 = clamp(clamp(_259 + _266, 0.0, 1.0) + uintBitsToFloat(0u), 0.0, 1.0);
        float _313 = clamp(clamp(_251 + _273, 0.0, 1.0) + uintBitsToFloat(0u), 0.0, 1.0);
        float _315 = RVar[1u].z;
        float _317 = RVar[1u].z;
        RVar[127u].z = _310;
        RVar[127u].w = _313;
        float _322 = RVar[1u].y;
        float _324 = RVar[1u].y;
        float _326 = (_322 * _324) + (_315 * _317);
        float _331 = (CBUFFER_1.values[4].w * clamp(((_280 + _282) + (-uintBitsToFloat(1056964608u))) * 2.0, 0.0, 1.0)) + uintBitsToFloat(0u);
        float _334 = clamp(clamp(_299 + _294, 0.0, 1.0) + uintBitsToFloat(0u), 0.0, 1.0);
        float _336 = RVar[0u].x;
        float _340 = RVar[0u].y;
        RVar[123u].x = _326;
        RVar[123u].y = _331;
        RVar[126u].z = _334;
        float _354 = RVar[1u].x;
        float _356 = RVar[1u].x;
        float _358 = (_354 * _356) + _326;
        float _360 = RVar[0u].z;
        float _367 = RVar[0u].w;
        float _369 = RVar[127u].w;
        RVar[2u].x = ((_336 + (-_310)) * RVar[0u].w) + RVar[127u].z;
        RVar[123u].y = _358;
        RVar[2u].w = clamp(_331 + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[2u].y = ((_340 + (-_313)) * _367) + _369;
        float _384 = inversesqrt(_358) * 0.5;
        RVar[2u].z = ((_360 + (-_334)) * RVar[0u].w) + RVar[126u].z;
        float _387 = RVar[1u].x;
        float _390 = (_387 * _384) + uintBitsToFloat(1056964608u);
        float _392 = RVar[1u].y;
        float _395 = (_392 * _384) + uintBitsToFloat(1056964608u);
        float _397 = RVar[1u].z;
        float _400 = (_397 * _384) + uintBitsToFloat(1056964608u);
        RVar[4u].x = _390;
        RVar[4u].y = _395;
        RVar[4u].z = _400;
        float _405 = RVar[4u].w;
        RVar[1u].x = _390;
        RVar[1u].y = _395;
        RVar[1u].z = _400;
        RVar[1u].w = _405;
        float _413 = RVar[2u].y;
        float _415 = RVar[2u].z;
        float _417 = RVar[2u].w;
        RVar[0u].x = RVar[2u].x;
        RVar[0u].y = _413;
        RVar[0u].z = _415;
        RVar[0u].w = _417;
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
    uint _493 = PS_PUSH.alphaFunc >> 8u;
    if (_493 == 1u)
    {
        _pixelTmp = vec4(1.0);
    }
    else
    {
        if (_493 == 2u)
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
    uint _521 = PS_PUSH.alphaFunc >> 8u;
    if (_521 == 1u)
    {
        _pixelTmp_1 = vec4(1.0);
    }
    else
    {
        if (_521 == 2u)
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