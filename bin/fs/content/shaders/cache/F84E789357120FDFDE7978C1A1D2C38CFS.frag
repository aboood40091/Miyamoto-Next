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
uniform sampler2D tex_map0;
uniform sampler2D tex_map1;

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
        vec4 _68 = texture(tex_map2, vec4(RVar[5u].xy, 0.0, RVar[5u].x).xy);
        RVar[5u] = vec4(_68.x, RVar[5u].y, RVar[5u].z, _68.w);
        vec4 _83 = texture(tex_map0, vec4(RVar[3u].xy, 0.0, RVar[3u].x).xy);
        RVar[3u] = vec4(_83.x, _83.y, _83.z, RVar[3u].w);
    }
    if (stateVar == 0)
    {
        float _93 = RVar[5u].w;
        float _97 = _93 + (-uintBitsToFloat(1056964608u));
        float _105 = RVar[0u].x;
        float _107 = RVar[3u].x;
        float _110 = (_105 * _107) + uintBitsToFloat(0u);
        float _112 = RVar[0u].y;
        float _114 = RVar[3u].y;
        float _117 = (_112 * _114) + uintBitsToFloat(0u);
        RVar[5u].y = RVar[5u].x + (-uintBitsToFloat(1056964608u));
        RVar[4u].z = uintBitsToFloat(0u);
        RVar[123u].w = _110;
        RVar[122u].x = _117;
        float _129 = RVar[0u].z;
        float _131 = RVar[3u].z;
        RVar[3u].x = clamp(_110 + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[3u].y = (_129 * _131) + uintBitsToFloat(0u);
        RVar[3u].z = _97 * CBUFFER_1.values[11].y;
        RVar[5u].w = _97 * CBUFFER_1.values[11].x;
        RVar[0u].w = clamp(_117 + uintBitsToFloat(0u), 0.0, 1.0);
    }
    if (stateVar == 0)
    {
        vec4 _176 = intBitsToFloat(ivec4(ivec3(textureSize(tex_map1, floatBitsToInt(vec4(RVar[4u].zz, 0.0, RVar[4u].z).x)), 1), textureQueryLevels(tex_map1)));
        RVar[6u] = vec4(_176.x, _176.y, RVar[6u].z, RVar[6u].w);
    }
    if (stateVar == 0)
    {
        float _186 = RVar[5u].y;
        float _190 = RVar[3u].z;
        float _192 = (_186 * CBUFFER_1.values[11].w) + _190;
        float _194 = RVar[5u].y;
        float _198 = RVar[5u].w;
        float _200 = (_194 * CBUFFER_1.values[11].z) + _198;
        float _202 = RVar[3u].y;
        float _208 = RVar[6u].x;
        RVar[123u].x = _192;
        RVar[123u].y = _200;
        RVar[3u].z = clamp(_202 + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[7u].w = uintBitsToFloat(0u);
        RVar[127u].w = float(floatBitsToInt(_208));
        float _219 = RVar[2u].z;
        float _221 = RVar[2u].z;
        float _224 = RVar[5u].y;
        float _229 = (_224 * CBUFFER_1.values[12].y) + _192;
        float _231 = RVar[5u].y;
        float _235 = (_231 * CBUFFER_1.values[12].x) + _200;
        float _237 = RVar[6u].y;
        RVar[123u].z = _229;
        RVar[123u].w = _235;
        RVar[127u].y = float(floatBitsToInt(_237));
        float _249 = RVar[2u].y;
        float _251 = RVar[2u].y;
        float _253 = (_249 * _251) + (_219 * _221);
        float _257 = RVar[127u].w;
        RVar[127u].x = _229 * uintBitsToFloat(1132396544u);
        RVar[123u].z = _253;
        RVar[6u].w = uintBitsToFloat(1065353216u);
        float _263 = RVar[2u].x;
        float _265 = RVar[2u].x;
        float _267 = (_263 * _265) + _253;
        float _270 = RVar[127u].y;
        RVar[123u].y = _267;
        float _277 = RVar[127u].x;
        float _281 = inversesqrt(_267) * 0.5;
        RVar[5u].x = RVar[4u].x + ((_235 * uintBitsToFloat(1132396544u)) * (1.0 / _257));
        float _289 = RVar[4u].y;
        float _292 = RVar[2u].z;
        float _297 = RVar[2u].y;
        RVar[6u].x = (RVar[2u].x * _281) + uintBitsToFloat(1056964608u);
        RVar[5u].y = _289 + (_277 * (1.0 / _270));
        RVar[6u].z = (_292 * _281) + uintBitsToFloat(1056964608u);
        RVar[6u].y = (_297 * _281) + uintBitsToFloat(1056964608u);
    }
    if (stateVar == 0)
    {
        vec4 _319 = texture(tex_map1, vec4(RVar[5u].xy, 0.0, RVar[5u].x).xy);
        RVar[5u] = vec4(_319.x, _319.y, _319.z, RVar[5u].w);
    }
    if (stateVar == 0)
    {
        float _328 = RVar[0u].z;
        float _330 = RVar[5u].z;
        float _333 = (_328 * _330) + uintBitsToFloat(0u);
        float _335 = RVar[0u].y;
        float _337 = RVar[5u].y;
        float _340 = (_335 * _337) + uintBitsToFloat(0u);
        float _342 = RVar[0u].x;
        float _344 = RVar[5u].x;
        float _347 = (_342 * _344) + uintBitsToFloat(0u);
        RVar[123u].x = _333;
        RVar[123u].y = _340;
        RVar[123u].z = _347;
        float _352 = RVar[3u].z;
        float _354 = clamp(_352 + _333, 0.0, 1.0);
        float _356 = RVar[0u].w;
        float _358 = clamp(_356 + _340, 0.0, 1.0);
        float _360 = RVar[3u].x;
        float _362 = clamp(_360 + _347, 0.0, 1.0);
        RVar[127u].y = _354;
        RVar[127u].z = _358;
        RVar[127u].w = _362;
        float _371 = RVar[1u].z;
        float _375 = RVar[1u].y;
        float _385 = RVar[1u].w;
        float _387 = RVar[127u].z;
        float _391 = RVar[1u].w;
        float _393 = RVar[127u].y;
        RVar[7u].x = ((RVar[1u].x + (-_362)) * RVar[1u].w) + RVar[127u].w;
        RVar[7u].y = ((_375 + (-_358)) * _385) + _387;
        RVar[7u].z = ((_371 + (-_354)) * _391) + _393;
        float _402 = RVar[6u].y;
        float _404 = RVar[6u].z;
        float _406 = RVar[6u].w;
        RVar[1u].x = RVar[6u].x;
        RVar[1u].y = _402;
        RVar[1u].z = _404;
        RVar[1u].w = _406;
        float _414 = RVar[7u].y;
        float _416 = RVar[7u].z;
        float _418 = RVar[7u].w;
        RVar[0u].x = RVar[7u].x;
        RVar[0u].y = _414;
        RVar[0u].z = _416;
        RVar[0u].w = _418;
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
    uint _494 = PS_PUSH.alphaFunc >> 8u;
    if (_494 == 1u)
    {
        _pixelTmp = vec4(1.0);
    }
    else
    {
        if (_494 == 2u)
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
    uint _522 = PS_PUSH.alphaFunc >> 8u;
    if (_522 == 1u)
    {
        _pixelTmp_1 = vec4(1.0);
    }
    else
    {
        if (_522 == 2u)
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