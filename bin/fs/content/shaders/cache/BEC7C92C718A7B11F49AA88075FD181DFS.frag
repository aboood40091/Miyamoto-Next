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
        float _306 = RVar[126u].x;
        float _308 = RVar[5u].y;
        float _314 = RVar[127u].y;
        float _316 = RVar[5u].x;
        float _324 = RVar[126u].y;
        float _326 = (CBUFFER_1.values[4].w * ((-_282) + uintBitsToFloat(1065353216u))) + _324;
        float _328 = RVar[2u].z;
        float _330 = RVar[2u].z;
        RVar[126u].x = clamp(((RVar[127u].w * RVar[5u].z) + _290) * 2.0, 0.0, 1.0);
        RVar[127u].y = clamp(((_306 * _308) + _273) * 2.0, 0.0, 1.0);
        RVar[127u].z = clamp(((_314 * _316) + _280) * 2.0, 0.0, 1.0);
        RVar[123u].w = _326;
        float _352 = RVar[126u].y;
        float _354 = RVar[5u].w;
        float _356 = (_352 * _354) + _326;
        RVar[126u].y = dot(vec4(RVar[2u].x, RVar[2u].y, _328 * _330, uintBitsToFloat(2147483648u)), vec4(RVar[2u].x, RVar[2u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[122u].x = _356;
        float _360 = RVar[1u].x;
        float _362 = RVar[127u].z;
        float _366 = RVar[1u].z;
        float _368 = RVar[126u].x;
        float _372 = RVar[1u].y;
        float _374 = RVar[127u].y;
        RVar[5u].w = clamp(_356 + (-uintBitsToFloat(1056964608u)), 0.0, 1.0);
        float _390 = RVar[1u].w;
        float _392 = RVar[127u].y;
        float _396 = RVar[1u].w;
        float _398 = RVar[126u].x;
        float _402 = RVar[126u].y;
        float _405 = inversesqrt(_402) * 0.5;
        RVar[5u].x = ((_360 + (-_362)) * RVar[1u].w) + RVar[127u].z;
        RVar[5u].y = ((_372 + (-_374)) * _390) + _392;
        RVar[5u].z = ((_366 + (-_368)) * _396) + _398;
        float _410 = RVar[2u].x;
        float _413 = (_410 * _405) + uintBitsToFloat(1056964608u);
        float _415 = RVar[2u].y;
        float _418 = (_415 * _405) + uintBitsToFloat(1056964608u);
        float _420 = RVar[2u].z;
        float _423 = (_420 * _405) + uintBitsToFloat(1056964608u);
        RVar[4u].x = _413;
        RVar[4u].y = _418;
        RVar[4u].z = _423;
        float _428 = RVar[4u].w;
        RVar[1u].x = _413;
        RVar[1u].y = _418;
        RVar[1u].z = _423;
        RVar[1u].w = _428;
        float _436 = RVar[5u].y;
        float _438 = RVar[5u].z;
        float _440 = RVar[5u].w;
        RVar[0u].x = RVar[5u].x;
        RVar[0u].y = _436;
        RVar[0u].z = _438;
        RVar[0u].w = _440;
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
    uint _516 = PS_PUSH.alphaFunc >> 8u;
    if (_516 == 1u)
    {
        _pixelTmp = vec4(1.0);
    }
    else
    {
        if (_516 == 2u)
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
    uint _544 = PS_PUSH.alphaFunc >> 8u;
    if (_544 == 1u)
    {
        _pixelTmp_1 = vec4(1.0);
    }
    else
    {
        if (_544 == 2u)
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