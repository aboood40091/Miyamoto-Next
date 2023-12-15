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
uniform sampler2D tex_map2;
uniform sampler2D tex_map3;
uniform sampler2D tex_map0;

layout(location = 0) in vec4 PARAM_0;
layout(location = 1) in vec4 PARAM_1;
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
    RVar[0u] = PARAM_0;
    RVar[1u] = PARAM_1;
    RVar[2u] = PARAM_3;
    RVar[3u] = PARAM_4;
    RVar[4u] = PARAM_5;
    RVar[5u] = PARAM_6;
    if (stateVar == 0)
    {
        vec4 _68 = texture(tex_map1, vec4(RVar[3u].xy, 0.0, RVar[3u].x).xy);
        RVar[3u] = vec4(_68.x, RVar[3u].y, RVar[3u].z, _68.w);
        vec4 _83 = texture(tex_map2, vec4(RVar[4u].xy, 0.0, RVar[4u].x).xy);
        RVar[4u] = vec4(_83.x, _83.y, _83.z, RVar[4u].w);
        vec4 _98 = texture(tex_map3, vec4(RVar[5u].xy, 0.0, RVar[5u].x).xy);
        RVar[6u] = vec4(_98.x, _98.y, _98.z, RVar[6u].w);
    }
    if (stateVar == 0)
    {
        float _116 = RVar[4u].x;
        float _122 = RVar[3u].w;
        float _125 = _122 + (-uintBitsToFloat(1056964608u));
        float _127 = RVar[4u].y;
        RVar[3u].x += (-uintBitsToFloat(1056964608u));
        RVar[5u].y = uintBitsToFloat(0u);
        RVar[4u].x = (-RVar[4u].z) + uintBitsToFloat(1065353216u);
        RVar[4u].y = _125 * CBUFFER_1.values[11].y;
        RVar[4u].z = _125 * CBUFFER_1.values[11].x;
        RVar[1u].w = (CBUFFER_1.values[4].x * ((-_116) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        RVar[2u].w = (CBUFFER_1.values[4].y * ((-_127) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
    }
    if (stateVar == 0)
    {
        vec4 _187 = intBitsToFloat(ivec4(ivec3(textureSize(tex_map0, floatBitsToInt(vec4(RVar[5u].yy, 0.0, RVar[5u].y).x)), 1), textureQueryLevels(tex_map0)));
        RVar[5u] = vec4(_187.x, _187.y, RVar[5u].z, RVar[5u].w);
    }
    if (stateVar == 0)
    {
        float _196 = RVar[3u].x;
        float _200 = RVar[4u].z;
        float _202 = (_196 * CBUFFER_1.values[11].z) + _200;
        float _204 = RVar[1u].z;
        float _206 = RVar[1u].z;
        float _211 = RVar[4u].x;
        float _216 = RVar[3u].x;
        float _220 = RVar[4u].y;
        float _222 = (_216 * CBUFFER_1.values[11].w) + _220;
        float _224 = RVar[5u].x;
        RVar[123u].x = _202;
        RVar[4u].z = (CBUFFER_1.values[4].z * _211) + uintBitsToFloat(0u);
        RVar[123u].w = _222;
        RVar[127u].z = float(floatBitsToInt(_224));
        float _234 = RVar[1u].y;
        float _236 = RVar[1u].y;
        float _238 = (_234 * _236) + (_204 * _206);
        float _240 = RVar[3u].x;
        float _245 = (_240 * CBUFFER_1.values[12].y) + _222;
        float _247 = RVar[3u].x;
        float _251 = (_247 * CBUFFER_1.values[12].x) + _202;
        float _254 = RVar[5u].y;
        RVar[123u].x = _238;
        RVar[123u].y = _245;
        RVar[123u].z = _251;
        RVar[5u].w = uintBitsToFloat(1065353216u);
        RVar[127u].y = float(floatBitsToInt(_254));
        float _274 = RVar[127u].z;
        RVar[126u].y = (RVar[1u].x * RVar[1u].x) + _238;
        RVar[127u].w = _245 * uintBitsToFloat(1132396544u);
        float _281 = RVar[127u].y;
        float _287 = RVar[127u].w;
        float _290 = RVar[126u].y;
        float _294 = inversesqrt(_290) * 0.5;
        RVar[3u].x = RVar[2u].x + ((_251 * uintBitsToFloat(1132396544u)) * (1.0 / _274));
        float _302 = RVar[2u].y;
        float _305 = RVar[1u].z;
        float _310 = RVar[1u].y;
        RVar[5u].x = (RVar[1u].x * _294) + uintBitsToFloat(1056964608u);
        RVar[3u].y = _302 + (_287 * (1.0 / _281));
        RVar[5u].z = (_305 * _294) + uintBitsToFloat(1056964608u);
        RVar[5u].y = (_310 * _294) + uintBitsToFloat(1056964608u);
    }
    if (stateVar == 0)
    {
        RVar[3u] = texture(tex_map0, vec4(RVar[3u].xy, 0.0, RVar[3u].x).xy);
    }
    if (stateVar == 0)
    {
        float _339 = RVar[3u].z;
        float _344 = RVar[3u].y;
        float _349 = RVar[3u].x;
        float _354 = RVar[3u].w;
        float _358 = (_354 * uintBitsToFloat(1065353216u)) + uintBitsToFloat(0u);
        RVar[123u].w = _358;
        float _368 = (CBUFFER_1.values[5].z * ((-_339) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        float _373 = (CBUFFER_1.values[5].y * ((-_344) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        float _378 = (CBUFFER_1.values[5].x * ((-_349) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        RVar[123u].y = _368;
        RVar[123u].z = _373;
        RVar[123u].w = _378;
        float _385 = RVar[3u].x;
        float _388 = clamp((CBUFFER_1.values[4].x * _385) + _378, 0.0, 1.0);
        float _395 = RVar[3u].z;
        float _398 = clamp((CBUFFER_1.values[4].z * _395) + _368, 0.0, 1.0);
        float _402 = RVar[3u].y;
        float _405 = clamp((CBUFFER_1.values[4].y * _402) + _373, 0.0, 1.0);
        RVar[123u].x = _388;
        RVar[123u].z = _398;
        RVar[123u].w = _405;
        float _410 = RVar[2u].w;
        float _414 = RVar[1u].w;
        float _418 = RVar[4u].z;
        RVar[1u].w = clamp(clamp(clamp(_358 + uintBitsToFloat(0u), 0.0, 1.0) + uintBitsToFloat(0u), 0.0, 1.0) + uintBitsToFloat(0u), 0.0, 1.0);
        float _426 = RVar[6u].z;
        float _429 = (clamp(_398 + _418, 0.0, 1.0) * _426) + uintBitsToFloat(0u);
        float _431 = RVar[6u].y;
        float _434 = (clamp(_405 + _410, 0.0, 1.0) * _431) + uintBitsToFloat(0u);
        float _436 = RVar[6u].x;
        float _439 = (clamp(_388 + _414, 0.0, 1.0) * _436) + uintBitsToFloat(0u);
        RVar[123u].x = _429;
        RVar[123u].y = _434;
        RVar[123u].z = _439;
        float _445 = clamp(_429 + uintBitsToFloat(0u), 0.0, 1.0);
        float _448 = clamp(_434 + uintBitsToFloat(0u), 0.0, 1.0);
        float _451 = clamp(_439 + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[126u].y = _445;
        RVar[127u].z = _448;
        RVar[127u].w = _451;
        float _460 = RVar[0u].z;
        float _464 = RVar[0u].y;
        float _474 = RVar[0u].w;
        float _476 = RVar[127u].z;
        float _480 = RVar[0u].w;
        float _482 = RVar[126u].y;
        RVar[1u].x = ((RVar[0u].x + (-_451)) * RVar[0u].w) + RVar[127u].w;
        RVar[1u].y = ((_464 + (-_448)) * _474) + _476;
        RVar[1u].z = ((_460 + (-_445)) * _480) + _482;
        float _491 = RVar[5u].y;
        float _493 = RVar[5u].z;
        float _495 = RVar[5u].w;
        RVar[3u].x = RVar[5u].x;
        RVar[3u].y = _491;
        RVar[3u].z = _493;
        RVar[3u].w = _495;
        float _503 = RVar[1u].y;
        float _505 = RVar[1u].z;
        float _507 = RVar[1u].w;
        RVar[2u].x = RVar[1u].x;
        RVar[2u].y = _503;
        RVar[2u].z = _505;
        RVar[2u].w = _507;
    }
    switch (PS_PUSH.alphaFunc & 255u)
    {
        case 0u:
        {
            discard;
        }
        case 1u:
        {
            if (!(RVar[2u].w < PS_PUSH.alphaRef))
            {
                discard;
            }
            break;
        }
        case 2u:
        {
            if (abs(RVar[2u].w - PS_PUSH.alphaRef) > 9.9999997473787516355514526367188e-05)
            {
                discard;
            }
            break;
        }
        case 3u:
        {
            if (!(RVar[2u].w <= PS_PUSH.alphaRef))
            {
                discard;
            }
            break;
        }
        case 4u:
        {
            if (!(RVar[2u].w > PS_PUSH.alphaRef))
            {
                discard;
            }
            break;
        }
        case 5u:
        {
            if (abs(RVar[2u].w - PS_PUSH.alphaRef) <= 9.9999997473787516355514526367188e-05)
            {
                discard;
            }
            break;
        }
        case 6u:
        {
            if (!(RVar[2u].w >= PS_PUSH.alphaRef))
            {
                discard;
            }
            break;
        }
    }
    _pixelTmp = RVar[2u];
    uint _583 = PS_PUSH.alphaFunc >> 8u;
    if (_583 == 1u)
    {
        _pixelTmp = vec4(1.0);
    }
    else
    {
        if (_583 == 2u)
        {
            _pixelTmp = vec4(0.0);
        }
    }
    if ((PS_PUSH.needsPremultiply & 1u) != 0u)
    {
        _pixelTmp *= vec4(_pixelTmp.www, 1.0);
    }
    if (PS_PUSH.uIsSelected != 0) PIXEL_0 = vec4(_pixelTmp.rgb * 0.5f + vec3(1.0f, 0.25f, 0.25f) * 0.5f, _pixelTmp.a); else PIXEL_0 = _pixelTmp; ItemID = PS_PUSH.uItemID;
    _pixelTmp_1 = RVar[3u];
    uint _611 = PS_PUSH.alphaFunc >> 8u;
    if (_611 == 1u)
    {
        _pixelTmp_1 = vec4(1.0);
    }
    else
    {
        if (_611 == 2u)
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