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

uniform sampler2D tex_map4;
uniform sampler2D tex_map1;
uniform sampler2D tex_map0;
uniform sampler2D tex_map2;
uniform sampler2D tex_map3;

layout(location = 2) in vec4 PARAM_2;
layout(location = 0) in vec4 PARAM_0;
layout(location = 1) in vec4 PARAM_1;
layout(location = 3) in vec4 PARAM_3;
layout(location = 4) in vec4 PARAM_4;
layout(location = 5) in vec4 PARAM_5;
layout(location = 6) in vec4 PARAM_6;
layout(location = 7) in vec4 PARAM_7;
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
    RVar[6u] = PARAM_6;
    RVar[7u] = PARAM_7;
    if (stateVar == 0)
    {
        vec4 _76 = texture(tex_map4, vec4(RVar[7u].xy, 0.0, RVar[7u].x).xy);
        RVar[7u] = vec4(_76.x, RVar[7u].y, RVar[7u].z, _76.w);
        vec4 _91 = texture(tex_map1, vec4(RVar[4u].xy, 0.0, RVar[4u].x).xy);
        RVar[4u] = vec4(_91.x, _91.y, _91.z, RVar[4u].w);
        RVar[3u] = texture(tex_map0, vec4(RVar[3u].xy, 0.0, RVar[3u].x).xy);
        vec4 _119 = texture(tex_map2, vec4(RVar[5u].xy, 0.0, RVar[5u].x).xy);
        RVar[8u] = vec4(_119.x, _119.y, _119.z, RVar[8u].w);
    }
    if (stateVar == 0)
    {
        float _137 = RVar[0u].x;
        float _139 = RVar[4u].x;
        float _142 = (_137 * _139) + uintBitsToFloat(0u);
        float _144 = RVar[7u].w;
        float _147 = _144 + (-uintBitsToFloat(1056964608u));
        float _149 = RVar[0u].y;
        float _151 = RVar[4u].y;
        float _154 = (_149 * _151) + uintBitsToFloat(0u);
        RVar[7u].x += (-uintBitsToFloat(1056964608u));
        RVar[5u].y = uintBitsToFloat(0u);
        RVar[123u].z = _142;
        RVar[122u].x = _154;
        RVar[4u].x = (RVar[0u].z * RVar[4u].z) + uintBitsToFloat(0u);
        RVar[4u].y = _147 * CBUFFER_1.values[11].y;
        RVar[4u].z = _147 * CBUFFER_1.values[11].x;
        RVar[2u].w = clamp(_142 + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[7u].w = clamp(_154 + uintBitsToFloat(0u), 0.0, 1.0);
    }
    if (stateVar == 0)
    {
        vec4 _213 = intBitsToFloat(ivec4(ivec3(textureSize(tex_map3, floatBitsToInt(vec4(RVar[5u].yy, 0.0, RVar[5u].y).x)), 1), textureQueryLevels(tex_map3)));
        RVar[5u] = vec4(_213.x, _213.y, RVar[5u].z, RVar[5u].w);
    }
    if (stateVar == 0)
    {
        float _222 = RVar[7u].x;
        float _226 = RVar[4u].z;
        float _228 = (_222 * CBUFFER_1.values[11].z) + _226;
        float _230 = RVar[7u].w;
        float _232 = RVar[3u].y;
        float _237 = RVar[4u].x;
        float _240 = clamp(_237 + uintBitsToFloat(0u), 0.0, 1.0);
        float _242 = RVar[7u].x;
        float _246 = RVar[4u].y;
        float _248 = (_242 * CBUFFER_1.values[11].w) + _246;
        float _250 = RVar[5u].x;
        RVar[123u].x = _228;
        RVar[126u].y = (_230 * _232) + uintBitsToFloat(0u);
        RVar[4u].z = _240;
        RVar[123u].w = _248;
        RVar[127u].w = float(floatBitsToInt(_250));
        float _261 = RVar[2u].w;
        float _263 = RVar[3u].x;
        float _266 = (_261 * _263) + uintBitsToFloat(0u);
        float _268 = RVar[7u].x;
        float _273 = (_268 * CBUFFER_1.values[12].y) + _248;
        float _275 = RVar[7u].x;
        float _279 = (_275 * CBUFFER_1.values[12].x) + _228;
        float _281 = RVar[3u].z;
        float _286 = RVar[5u].y;
        RVar[123u].x = _266;
        RVar[123u].y = _273;
        RVar[123u].z = _279;
        RVar[126u].w = (_240 * _281) + uintBitsToFloat(0u);
        RVar[127u].y = float(floatBitsToInt(_286));
        float _308 = RVar[127u].w;
        RVar[125u].y = clamp(RVar[0u].w + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[127u].z = clamp(_266 + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[127u].w = _273 * uintBitsToFloat(1132396544u);
        float _320 = RVar[126u].w;
        float _325 = RVar[8u].x;
        float _332 = RVar[127u].y;
        RVar[127u].x = clamp(RVar[126u].y + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[127u].y = clamp(_320 + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[126u].z = (-_325) + uintBitsToFloat(1065353216u);
        float _341 = RVar[8u].y;
        float _346 = RVar[8u].z;
        float _351 = RVar[127u].w;
        float _354 = RVar[125u].y;
        float _356 = RVar[3u].w;
        float _359 = (_354 * _356) + uintBitsToFloat(0u);
        RVar[3u].x = RVar[6u].x + ((_279 * uintBitsToFloat(1132396544u)) * (1.0 / _308));
        RVar[122u].x = _359;
        float _370 = RVar[6u].y;
        float _373 = RVar[127u].x;
        float _378 = RVar[127u].y;
        RVar[6u].x = (RVar[127u].z * RVar[126u].z) + uintBitsToFloat(0u);
        RVar[3u].y = _370 + (_351 * (1.0 / _332));
        RVar[3u].z = (_373 * ((-_341) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        RVar[3u].w = (_378 * ((-_346) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        RVar[6u].y = clamp(_359 + uintBitsToFloat(0u), 0.0, 1.0);
    }
    if (stateVar == 0)
    {
        vec4 _404 = texture(tex_map3, vec4(RVar[3u].xy, 0.0, RVar[3u].x).xy);
        RVar[5u] = vec4(_404.x, _404.y, _404.z, RVar[5u].w);
    }
    if (stateVar == 0)
    {
        float _422 = RVar[0u].y;
        float _424 = RVar[8u].y;
        float _426 = RVar[3u].z;
        float _429 = clamp((_422 * _424) + _426, 0.0, 1.0);
        float _431 = RVar[0u].x;
        float _433 = RVar[8u].x;
        float _435 = RVar[6u].x;
        float _440 = RVar[7u].w;
        float _442 = RVar[5u].y;
        float _445 = (_440 * _442) + uintBitsToFloat(0u);
        RVar[127u].x = clamp((RVar[0u].z * RVar[8u].z) + RVar[3u].w, 0.0, 1.0);
        RVar[123u].y = _429;
        RVar[127u].z = clamp((_431 * _433) + _435, 0.0, 1.0);
        RVar[123u].w = _445;
        RVar[0u].w = uintBitsToFloat(1065353216u);
        float _453 = RVar[4u].z;
        float _455 = RVar[5u].z;
        float _458 = (_453 * _455) + uintBitsToFloat(0u);
        float _460 = clamp(_429 + _445, 0.0, 1.0);
        float _462 = RVar[2u].w;
        float _464 = RVar[5u].x;
        float _467 = (_462 * _464) + uintBitsToFloat(0u);
        float _469 = RVar[6u].y;
        float _475 = (_469 * CBUFFER_1.values[10].w) + uintBitsToFloat(0u);
        float _477 = RVar[2u].z;
        float _479 = RVar[2u].z;
        RVar[123u].x = _458;
        RVar[127u].y = _460;
        RVar[123u].z = _467;
        RVar[123u].w = _475;
        float _486 = RVar[2u].y;
        float _488 = RVar[2u].y;
        float _490 = (_486 * _488) + (_477 * _479);
        float _492 = RVar[127u].x;
        float _494 = clamp(_492 + _458, 0.0, 1.0);
        float _499 = RVar[127u].z;
        float _501 = clamp(_499 + _467, 0.0, 1.0);
        float _503 = RVar[1u].y;
        RVar[123u].x = _490;
        RVar[125u].y = _494;
        RVar[127u].w = _501;
        float _510 = RVar[1u].x;
        float _514 = RVar[2u].x;
        float _516 = RVar[2u].x;
        float _518 = (_514 * _516) + _490;
        float _520 = RVar[1u].z;
        float _527 = RVar[1u].w;
        float _529 = RVar[127u].y;
        RVar[123u].y = _518;
        RVar[4u].w = clamp(clamp(_475 + uintBitsToFloat(0u), 0.0, 1.0) + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[4u].y = ((_503 + (-_460)) * _527) + _529;
        float _542 = RVar[1u].w;
        float _544 = RVar[125u].y;
        float _549 = inversesqrt(_518) * 0.5;
        RVar[4u].x = ((_510 + (-_501)) * RVar[1u].w) + RVar[127u].w;
        RVar[4u].z = ((_520 + (-_494)) * _542) + _544;
        float _553 = RVar[2u].x;
        float _556 = (_553 * _549) + uintBitsToFloat(1056964608u);
        float _558 = RVar[2u].y;
        float _561 = (_558 * _549) + uintBitsToFloat(1056964608u);
        float _563 = RVar[2u].z;
        float _566 = (_563 * _549) + uintBitsToFloat(1056964608u);
        RVar[0u].x = _556;
        RVar[0u].y = _561;
        RVar[0u].z = _566;
        float _571 = RVar[0u].w;
        RVar[1u].x = _556;
        RVar[1u].y = _561;
        RVar[1u].z = _566;
        RVar[1u].w = _571;
        float _579 = RVar[4u].y;
        float _581 = RVar[4u].z;
        float _583 = RVar[4u].w;
        RVar[0u].x = RVar[4u].x;
        RVar[0u].y = _579;
        RVar[0u].z = _581;
        RVar[0u].w = _583;
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
    uint _658 = PS_PUSH.alphaFunc >> 8u;
    if (_658 == 1u)
    {
        _pixelTmp = vec4(1.0);
    }
    else
    {
        if (_658 == 2u)
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
    uint _686 = PS_PUSH.alphaFunc >> 8u;
    if (_686 == 1u)
    {
        _pixelTmp_1 = vec4(1.0);
    }
    else
    {
        if (_686 == 2u)
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