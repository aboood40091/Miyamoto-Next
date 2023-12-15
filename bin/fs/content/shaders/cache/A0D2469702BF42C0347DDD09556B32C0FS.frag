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
        float _242 = RVar[7u].x;
        float _246 = RVar[4u].y;
        float _248 = (_242 * CBUFFER_1.values[11].w) + _246;
        float _250 = RVar[5u].x;
        RVar[123u].x = _228;
        RVar[126u].y = (_230 * _232) + uintBitsToFloat(0u);
        RVar[123u].w = _248;
        RVar[127u].w = float(floatBitsToInt(_250));
        float _260 = RVar[2u].w;
        float _262 = RVar[3u].x;
        float _265 = (_260 * _262) + uintBitsToFloat(0u);
        float _267 = RVar[7u].x;
        float _272 = (_267 * CBUFFER_1.values[12].y) + _248;
        float _274 = RVar[7u].x;
        float _278 = (_274 * CBUFFER_1.values[12].x) + _228;
        float _280 = RVar[3u].z;
        float _285 = RVar[5u].y;
        RVar[123u].x = _265;
        RVar[123u].y = _272;
        RVar[123u].z = _278;
        RVar[126u].w = (clamp(_237 + uintBitsToFloat(0u), 0.0, 1.0) * _280) + uintBitsToFloat(0u);
        RVar[127u].y = float(floatBitsToInt(_285));
        float _307 = RVar[127u].w;
        RVar[125u].y = clamp(RVar[0u].w + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[127u].z = clamp(_265 + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[127u].w = _272 * uintBitsToFloat(1132396544u);
        float _319 = RVar[126u].w;
        float _324 = RVar[8u].x;
        float _331 = RVar[127u].y;
        RVar[127u].x = clamp(RVar[126u].y + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[127u].y = clamp(_319 + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[126u].z = (-_324) + uintBitsToFloat(1065353216u);
        float _340 = RVar[8u].y;
        float _345 = RVar[8u].z;
        float _350 = RVar[127u].w;
        float _353 = RVar[125u].y;
        float _355 = RVar[3u].w;
        float _358 = (_353 * _355) + uintBitsToFloat(0u);
        RVar[3u].x = RVar[6u].x + ((_278 * uintBitsToFloat(1132396544u)) * (1.0 / _307));
        RVar[122u].x = _358;
        float _369 = RVar[6u].y;
        float _372 = RVar[127u].x;
        float _377 = RVar[127u].y;
        RVar[6u].x = (RVar[127u].z * RVar[126u].z) + uintBitsToFloat(0u);
        RVar[3u].y = _369 + (_350 * (1.0 / _331));
        RVar[3u].z = (_372 * ((-_340) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        RVar[3u].w = (_377 * ((-_345) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        RVar[6u].y = clamp(_358 + uintBitsToFloat(0u), 0.0, 1.0);
    }
    if (stateVar == 0)
    {
        vec4 _403 = texture(tex_map3, vec4(RVar[3u].xy, 0.0, RVar[3u].x).xy);
        RVar[5u] = vec4(_403.x, _403.y, _403.z, RVar[5u].w);
    }
    if (stateVar == 0)
    {
        float _421 = RVar[0u].y;
        float _423 = RVar[8u].y;
        float _425 = RVar[3u].z;
        float _428 = clamp((_421 * _423) + _425, 0.0, 1.0);
        float _430 = RVar[0u].x;
        float _432 = RVar[8u].x;
        float _434 = RVar[6u].x;
        float _441 = RVar[5u].y;
        float _444 = (CBUFFER_1.values[6].w * _441) + uintBitsToFloat(0u);
        RVar[127u].x = clamp((RVar[0u].z * RVar[8u].z) + RVar[3u].w, 0.0, 1.0);
        RVar[123u].y = _428;
        RVar[127u].z = clamp((_430 * _432) + _434, 0.0, 1.0);
        RVar[123u].w = _444;
        RVar[0u].w = uintBitsToFloat(1065353216u);
        float _454 = RVar[5u].z;
        float _457 = (CBUFFER_1.values[6].w * _454) + uintBitsToFloat(0u);
        float _459 = clamp(_428 + _444, 0.0, 1.0);
        float _463 = RVar[5u].x;
        float _466 = (CBUFFER_1.values[6].w * _463) + uintBitsToFloat(0u);
        float _468 = RVar[6u].y;
        float _474 = (_468 * CBUFFER_1.values[10].w) + uintBitsToFloat(0u);
        float _476 = RVar[2u].z;
        float _478 = RVar[2u].z;
        RVar[123u].x = _457;
        RVar[127u].y = _459;
        RVar[123u].z = _466;
        RVar[123u].w = _474;
        float _485 = RVar[2u].y;
        float _487 = RVar[2u].y;
        float _489 = (_485 * _487) + (_476 * _478);
        float _491 = RVar[127u].x;
        float _493 = clamp(_491 + _457, 0.0, 1.0);
        float _498 = RVar[127u].z;
        float _500 = clamp(_498 + _466, 0.0, 1.0);
        float _502 = RVar[1u].y;
        RVar[123u].x = _489;
        RVar[125u].y = _493;
        RVar[127u].w = _500;
        float _509 = RVar[1u].x;
        float _513 = RVar[2u].x;
        float _515 = RVar[2u].x;
        float _517 = (_513 * _515) + _489;
        float _519 = RVar[1u].z;
        float _526 = RVar[1u].w;
        float _528 = RVar[127u].y;
        RVar[123u].y = _517;
        RVar[5u].w = clamp(clamp(_474 + uintBitsToFloat(0u), 0.0, 1.0) + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[5u].y = ((_502 + (-_459)) * _526) + _528;
        float _541 = RVar[1u].w;
        float _543 = RVar[125u].y;
        float _548 = inversesqrt(_517) * 0.5;
        RVar[5u].x = ((_509 + (-_500)) * RVar[1u].w) + RVar[127u].w;
        RVar[5u].z = ((_519 + (-_493)) * _541) + _543;
        float _552 = RVar[2u].x;
        float _555 = (_552 * _548) + uintBitsToFloat(1056964608u);
        float _557 = RVar[2u].y;
        float _560 = (_557 * _548) + uintBitsToFloat(1056964608u);
        float _562 = RVar[2u].z;
        float _565 = (_562 * _548) + uintBitsToFloat(1056964608u);
        RVar[0u].x = _555;
        RVar[0u].y = _560;
        RVar[0u].z = _565;
        float _570 = RVar[0u].w;
        RVar[1u].x = _555;
        RVar[1u].y = _560;
        RVar[1u].z = _565;
        RVar[1u].w = _570;
        float _578 = RVar[5u].y;
        float _580 = RVar[5u].z;
        float _582 = RVar[5u].w;
        RVar[0u].x = RVar[5u].x;
        RVar[0u].y = _578;
        RVar[0u].z = _580;
        RVar[0u].w = _582;
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
    uint _657 = PS_PUSH.alphaFunc >> 8u;
    if (_657 == 1u)
    {
        _pixelTmp = vec4(1.0);
    }
    else
    {
        if (_657 == 2u)
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
    uint _685 = PS_PUSH.alphaFunc >> 8u;
    if (_685 == 1u)
    {
        _pixelTmp_1 = vec4(1.0);
    }
    else
    {
        if (_685 == 2u)
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