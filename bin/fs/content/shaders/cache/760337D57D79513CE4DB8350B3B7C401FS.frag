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

layout(location = 0) in vec4 PARAM_0;
layout(location = 1) in vec4 PARAM_1;
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
    RVar[0u] = PARAM_0;
    RVar[1u] = PARAM_1;
    RVar[2u] = PARAM_2;
    RVar[3u] = PARAM_3;
    RVar[4u] = PARAM_4;
    if (stateVar == 0)
    {
        vec4 _64 = texture(tex_map2, vec4(RVar[4u].xy, 0.0, RVar[4u].x).xy);
        RVar[4u] = vec4(_64.x, RVar[4u].y, RVar[4u].z, _64.w);
    }
    if (stateVar == 0)
    {
        float _74 = RVar[4u].w;
        float _78 = _74 + (-uintBitsToFloat(1056964608u));
        float _88 = RVar[1u].z;
        float _90 = RVar[1u].z;
        RVar[4u].y = RVar[4u].x + (-uintBitsToFloat(1056964608u));
        RVar[2u].z = uintBitsToFloat(0u);
        RVar[7u].w = uintBitsToFloat(1065353216u);
        RVar[4u].x = (RVar[1u].y * RVar[1u].y) + (_88 * _90);
        RVar[3u].z = _78 * CBUFFER_1.values[11].y;
        RVar[4u].w = _78 * CBUFFER_1.values[11].x;
    }
    if (stateVar == 0)
    {
        vec4 _138 = intBitsToFloat(ivec4(ivec3(textureSize(tex_map0, floatBitsToInt(vec4(RVar[2u].zz, 0.0, RVar[2u].z).x)), 1), textureQueryLevels(tex_map0)));
        RVar[5u] = vec4(_138.x, _138.y, RVar[5u].z, RVar[5u].w);
        vec4 _155 = intBitsToFloat(ivec4(ivec3(textureSize(tex_map1, floatBitsToInt(vec4(RVar[2u].zz, 0.0, RVar[2u].z).x)), 1), textureQueryLevels(tex_map1)));
        RVar[6u] = vec4(_155.x, _155.y, RVar[6u].z, RVar[6u].w);
    }
    if (stateVar == 0)
    {
        float _165 = RVar[4u].y;
        float _169 = RVar[3u].z;
        float _171 = (_165 * CBUFFER_1.values[11].w) + _169;
        float _173 = RVar[4u].y;
        float _177 = RVar[4u].w;
        float _179 = (_173 * CBUFFER_1.values[11].z) + _177;
        float _181 = RVar[1u].x;
        float _183 = RVar[1u].x;
        float _185 = RVar[4u].x;
        float _189 = RVar[5u].x;
        RVar[123u].x = _171;
        RVar[123u].y = _179;
        RVar[126u].z = (_181 * _183) + _185;
        RVar[127u].w = float(floatBitsToInt(_189));
        float _200 = RVar[4u].y;
        float _205 = (_200 * CBUFFER_1.values[12].y) + _171;
        float _207 = RVar[4u].y;
        float _211 = (_207 * CBUFFER_1.values[12].x) + _179;
        float _213 = RVar[5u].y;
        RVar[123u].z = _205;
        RVar[123u].w = _211;
        RVar[127u].z = float(floatBitsToInt(_213));
        float _223 = _211 * uintBitsToFloat(1132396544u);
        float _225 = RVar[127u].w;
        RVar[127u].x = _205 * uintBitsToFloat(1132396544u);
        RVar[127u].y = _223;
        float _231 = RVar[127u].z;
        float _237 = RVar[127u].x;
        float _240 = RVar[6u].x;
        RVar[4u].x = RVar[2u].x + (_223 * (1.0 / _225));
        RVar[127u].w = float(floatBitsToInt(_240));
        float _249 = RVar[6u].y;
        RVar[4u].y = RVar[2u].y + (_237 * (1.0 / _231));
        RVar[127u].z = float(floatBitsToInt(_249));
        float _261 = RVar[127u].z;
        float _267 = RVar[127u].x;
        float _270 = RVar[126u].z;
        float _274 = inversesqrt(_270) * 0.5;
        RVar[2u].x = RVar[3u].x + (RVar[127u].y * (1.0 / RVar[127u].w));
        float _282 = RVar[3u].y;
        float _285 = RVar[1u].z;
        float _290 = RVar[1u].y;
        RVar[7u].x = (RVar[1u].x * _274) + uintBitsToFloat(1056964608u);
        RVar[2u].y = _282 + (_267 * (1.0 / _261));
        RVar[7u].z = (_285 * _274) + uintBitsToFloat(1056964608u);
        RVar[7u].y = (_290 * _274) + uintBitsToFloat(1056964608u);
    }
    if (stateVar == 0)
    {
        RVar[4u] = texture(tex_map0, vec4(RVar[4u].xy, 0.0, RVar[4u].x).xy);
        RVar[2u] = texture(tex_map1, vec4(RVar[2u].xy, 0.0, RVar[2u].x).xy);
    }
    if (stateVar == 0)
    {
        float _334 = RVar[4u].z;
        float _337 = (CBUFFER_1.values[4].z * _334) + uintBitsToFloat(0u);
        float _341 = RVar[4u].y;
        float _344 = (CBUFFER_1.values[4].y * _341) + uintBitsToFloat(0u);
        float _348 = RVar[4u].x;
        float _351 = (CBUFFER_1.values[4].x * _348) + uintBitsToFloat(0u);
        RVar[123u].y = _337;
        RVar[123u].z = _344;
        RVar[123u].w = _351;
        float _362 = RVar[4u].w;
        float _365 = (CBUFFER_1.values[10].w * _362) + uintBitsToFloat(0u);
        float _376 = RVar[2u].x;
        float _379 = (CBUFFER_1.values[5].x * _376) + uintBitsToFloat(0u);
        RVar[123u].y = _365;
        RVar[126u].z = clamp(_337 + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[127u].w = clamp(_344 + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[122u].x = _379;
        float _386 = clamp(clamp(_351 + uintBitsToFloat(0u), 0.0, 1.0) + _379, 0.0, 1.0);
        float _390 = RVar[2u].z;
        float _393 = (CBUFFER_1.values[5].z * _390) + uintBitsToFloat(0u);
        float _397 = RVar[2u].y;
        float _400 = (CBUFFER_1.values[5].y * _397) + uintBitsToFloat(0u);
        RVar[127u].x = _386;
        RVar[123u].y = _393;
        RVar[123u].z = _400;
        float _409 = RVar[0u].x;
        float _413 = RVar[2u].w;
        float _416 = (clamp((_365 + uintBitsToFloat(0u)) * 0.5, 0.0, 1.0) * _413) + uintBitsToFloat(0u);
        float _418 = RVar[126u].z;
        float _420 = clamp(_418 + _393, 0.0, 1.0);
        float _422 = RVar[127u].w;
        float _424 = clamp(_422 + _400, 0.0, 1.0);
        RVar[123u].y = _416;
        RVar[126u].z = _420;
        RVar[127u].w = _424;
        float _435 = RVar[0u].z;
        float _439 = RVar[0u].y;
        RVar[2u].x = ((_409 + (-_386)) * RVar[0u].w) + RVar[127u].x;
        RVar[2u].w = clamp((_416 + uintBitsToFloat(0u)) * 0.5, 0.0, 1.0);
        float _455 = RVar[0u].w;
        float _457 = RVar[126u].z;
        RVar[2u].y = ((_439 + (-_424)) * RVar[0u].w) + RVar[127u].w;
        RVar[2u].z = ((_435 + (-_420)) * _455) + _457;
        float _465 = RVar[7u].y;
        float _467 = RVar[7u].z;
        float _469 = RVar[7u].w;
        RVar[1u].x = RVar[7u].x;
        RVar[1u].y = _465;
        RVar[1u].z = _467;
        RVar[1u].w = _469;
        float _477 = RVar[2u].y;
        float _479 = RVar[2u].z;
        float _481 = RVar[2u].w;
        RVar[0u].x = RVar[2u].x;
        RVar[0u].y = _477;
        RVar[0u].z = _479;
        RVar[0u].w = _481;
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
    uint _557 = PS_PUSH.alphaFunc >> 8u;
    if (_557 == 1u)
    {
        _pixelTmp = vec4(1.0);
    }
    else
    {
        if (_557 == 2u)
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
    uint _585 = PS_PUSH.alphaFunc >> 8u;
    if (_585 == 1u)
    {
        _pixelTmp_1 = vec4(1.0);
    }
    else
    {
        if (_585 == 2u)
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