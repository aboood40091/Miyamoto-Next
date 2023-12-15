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

uniform sampler2D tex_map2;
uniform sampler2D tex_map1;
uniform sampler2D tex_map0;

layout(location = 1) in vec4 PARAM_1;
layout(location = 0) in vec4 PARAM_0;
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
    RVar[0u] = PARAM_1;
    RVar[1u] = PARAM_0;
    RVar[2u] = PARAM_2;
    RVar[3u] = PARAM_3;
    RVar[4u] = PARAM_4;
    if (stateVar == 0)
    {
        vec4 _64 = texture(tex_map2, vec4(RVar[4u].xy, 0.0, RVar[4u].x).xy);
        RVar[4u] = vec4(_64.x, RVar[4u].y, RVar[4u].z, _64.w);
        vec4 _79 = texture(tex_map1, vec4(RVar[3u].xy, 0.0, RVar[3u].x).xy);
        RVar[8u] = vec4(_79.x, _79.y, _79.z, RVar[8u].w);
    }
    if (stateVar == 0)
    {
        float _90 = RVar[4u].w;
        float _94 = _90 + (-uintBitsToFloat(1056964608u));
        float _97 = RVar[4u].x;
        RVar[4u].y = uintBitsToFloat(0u);
        RVar[3u].z = _97 + (-uintBitsToFloat(1056964608u));
        RVar[1u].w = (-CBUFFER_1.values[7].x) + uintBitsToFloat(1065353216u);
        RVar[7u].x = (-CBUFFER_1.values[7].y) + uintBitsToFloat(1065353216u);
        float _133 = RVar[1u].z;
        float _135 = RVar[1u].z;
        RVar[4u].x = _94 * CBUFFER_1.values[11].x;
        RVar[7u].y = (-CBUFFER_1.values[7].z) + uintBitsToFloat(1065353216u);
        RVar[2u].z = _133 * _135;
        RVar[4u].w = _94 * CBUFFER_1.values[11].y;
        RVar[9u].w = uintBitsToFloat(1065353216u);
    }
    if (stateVar == 0)
    {
        vec4 _167 = intBitsToFloat(ivec4(ivec3(textureSize(tex_map1, floatBitsToInt(vec4(RVar[4u].yy, 0.0, RVar[4u].y).x)), 1), textureQueryLevels(tex_map1)));
        RVar[5u] = vec4(_167.x, _167.y, RVar[5u].z, RVar[5u].w);
        vec4 _184 = intBitsToFloat(ivec4(ivec3(textureSize(tex_map0, floatBitsToInt(vec4(RVar[4u].yy, 0.0, RVar[4u].y).x)), 1), textureQueryLevels(tex_map0)));
        RVar[6u] = vec4(_184.x, _184.y, RVar[6u].z, RVar[6u].w);
    }
    if (stateVar == 0)
    {
        float _194 = RVar[1u].y;
        float _196 = RVar[1u].y;
        float _198 = RVar[2u].z;
        float _200 = (_194 * _196) + _198;
        float _202 = RVar[3u].z;
        float _206 = RVar[4u].w;
        float _208 = (_202 * CBUFFER_1.values[11].w) + _206;
        float _210 = RVar[3u].z;
        float _214 = RVar[4u].x;
        float _216 = (_210 * CBUFFER_1.values[11].z) + _214;
        float _218 = RVar[5u].x;
        RVar[123u].x = _200;
        RVar[123u].y = _208;
        RVar[123u].z = _216;
        RVar[127u].y = float(floatBitsToInt(_218));
        float _228 = RVar[3u].z;
        float _233 = (_228 * CBUFFER_1.values[12].x) + _216;
        float _235 = RVar[1u].x;
        float _237 = RVar[1u].x;
        float _241 = RVar[3u].z;
        float _245 = (_241 * CBUFFER_1.values[12].y) + _208;
        float _247 = RVar[5u].y;
        RVar[123u].x = _233;
        RVar[125u].y = (_235 * _237) + _200;
        RVar[123u].w = _245;
        RVar[127u].x = float(floatBitsToInt(_247));
        float _261 = RVar[6u].x;
        RVar[127u].z = _233 * uintBitsToFloat(1132396544u);
        RVar[127u].w = _245 * uintBitsToFloat(1132396544u);
        RVar[126u].y = float(floatBitsToInt(_261));
        RVar[126u].x = float(floatBitsToInt(RVar[6u].y));
        float _280 = RVar[127u].x;
        float _286 = RVar[127u].w;
        float _289 = RVar[126u].y;
        RVar[6u].x = RVar[3u].x + (RVar[127u].z * (1.0 / RVar[127u].y));
        float _293 = RVar[127u].z;
        float _299 = RVar[126u].x;
        RVar[6u].z = RVar[3u].y + (_286 * (1.0 / _280));
        float _306 = RVar[127u].w;
        float _309 = RVar[125u].y;
        float _313 = inversesqrt(_309) * 0.5;
        RVar[3u].x = RVar[2u].x + (_293 * (1.0 / _289));
        float _321 = RVar[2u].y;
        float _324 = RVar[1u].z;
        float _329 = RVar[1u].y;
        RVar[9u].x = (RVar[1u].x * _313) + uintBitsToFloat(1056964608u);
        RVar[3u].y = _321 + (_306 * (1.0 / _299));
        RVar[9u].z = (_324 * _313) + uintBitsToFloat(1056964608u);
        RVar[9u].y = (_329 * _313) + uintBitsToFloat(1056964608u);
    }
    if (stateVar == 0)
    {
        RVar[6u] = texture(tex_map1, vec4(RVar[6u].xz, 0.0, RVar[6u].x).xy);
        RVar[3u] = texture(tex_map0, vec4(RVar[3u].xy, 0.0, RVar[3u].x).xy);
    }
    if (stateVar == 0)
    {
        float _369 = RVar[6u].x;
        float _376 = RVar[3u].x;
        float _379 = (CBUFFER_1.values[6].x * _376) + uintBitsToFloat(0u);
        float _381 = RVar[6u].z;
        float _386 = RVar[6u].y;
        float _393 = RVar[3u].y;
        RVar[123u].y = _379;
        RVar[127u].z = (-_381) + uintBitsToFloat(1065353216u);
        RVar[127u].w = (CBUFFER_1.values[6].y * _393) + uintBitsToFloat(0u);
        float _411 = (CBUFFER_1.values[5].x * ((-_369) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        float _415 = RVar[3u].z;
        float _418 = (CBUFFER_1.values[6].z * _415) + uintBitsToFloat(0u);
        float _423 = (CBUFFER_1.values[5].y * ((-_386) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        RVar[126u].x = (RVar[3u].w * uintBitsToFloat(1065353216u)) + uintBitsToFloat(0u);
        RVar[123u].y = _411;
        RVar[123u].z = _418;
        RVar[123u].w = _423;
        RVar[125u].y = clamp(_379 + uintBitsToFloat(0u), 0.0, 1.0);
        float _433 = RVar[127u].w;
        float _441 = RVar[6u].y;
        float _444 = clamp((CBUFFER_1.values[4].y * _441) + _423, 0.0, 1.0);
        float _448 = RVar[6u].x;
        float _451 = clamp((CBUFFER_1.values[4].x * _448) + _411, 0.0, 1.0);
        float _455 = RVar[127u].z;
        float _458 = (CBUFFER_1.values[5].z * _455) + uintBitsToFloat(0u);
        RVar[123u].y = _444;
        RVar[123u].z = _451;
        RVar[123u].w = _458;
        RVar[127u].w = clamp(_418 + uintBitsToFloat(0u), 0.0, 1.0);
        float _469 = RVar[6u].z;
        float _472 = clamp((CBUFFER_1.values[4].z * _469) + _458, 0.0, 1.0);
        float _474 = RVar[7u].x;
        float _476 = (clamp(_433 + uintBitsToFloat(0u), 0.0, 1.0) * _474) + _444;
        float _478 = RVar[125u].y;
        float _480 = RVar[1u].w;
        float _482 = (_478 * _480) + _451;
        float _484 = RVar[126u].x;
        RVar[123u].x = _472;
        RVar[123u].y = _476;
        RVar[123u].z = _482;
        float _492 = RVar[127u].w;
        float _494 = RVar[7u].y;
        float _496 = (_492 * _494) + _472;
        float _498 = RVar[8u].x;
        float _503 = clamp((_498 * CBUFFER_1.values[7].x) + _482, 0.0, 1.0);
        float _505 = RVar[8u].y;
        float _510 = clamp((_505 * CBUFFER_1.values[7].y) + _476, 0.0, 1.0);
        float _512 = RVar[6u].w;
        float _515 = (clamp(_484 + uintBitsToFloat(0u), 0.0, 1.0) * _512) + uintBitsToFloat(0u);
        RVar[123u].x = _496;
        RVar[125u].y = _503;
        RVar[127u].z = _510;
        RVar[123u].w = _515;
        float _521 = RVar[0u].x;
        float _525 = RVar[8u].z;
        float _530 = clamp((_525 * CBUFFER_1.values[7].z) + _496, 0.0, 1.0);
        float _532 = RVar[6u].w;
        float _535 = RVar[0u].y;
        RVar[126u].y = _530;
        float _546 = RVar[0u].w;
        float _548 = RVar[127u].z;
        float _552 = RVar[0u].z;
        RVar[6u].x = ((_521 + (-_503)) * RVar[0u].w) + RVar[125u].y;
        RVar[6u].y = ((_535 + (-_510)) * _546) + _548;
        RVar[6u].z = ((_552 + (-_530)) * RVar[0u].w) + RVar[126u].y;
        RVar[6u].w = clamp(clamp(((_532 + _515) + (-uintBitsToFloat(1056964608u))) * 2.0, 0.0, 1.0) + uintBitsToFloat(0u), 0.0, 1.0);
        float _577 = RVar[9u].y;
        float _579 = RVar[9u].z;
        float _581 = RVar[9u].w;
        RVar[1u].x = RVar[9u].x;
        RVar[1u].y = _577;
        RVar[1u].z = _579;
        RVar[1u].w = _581;
        float _589 = RVar[6u].y;
        float _591 = RVar[6u].z;
        float _593 = RVar[6u].w;
        RVar[0u].x = RVar[6u].x;
        RVar[0u].y = _589;
        RVar[0u].z = _591;
        RVar[0u].w = _593;
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
    uint _668 = PS_PUSH.alphaFunc >> 8u;
    if (_668 == 1u)
    {
        _pixelTmp = vec4(1.0);
    }
    else
    {
        if (_668 == 2u)
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
    uint _696 = PS_PUSH.alphaFunc >> 8u;
    if (_696 == 1u)
    {
        _pixelTmp_1 = vec4(1.0);
    }
    else
    {
        if (_696 == 2u)
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