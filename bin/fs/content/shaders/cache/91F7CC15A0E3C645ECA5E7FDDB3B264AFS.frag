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

layout(location = 2) in vec4 PARAM_2;
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
    RVar[0u] = PARAM_2;
    RVar[1u] = PARAM_1;
    RVar[2u] = PARAM_0;
    RVar[3u] = PARAM_3;
    RVar[4u] = PARAM_4;
    RVar[5u] = PARAM_5;
    if (stateVar == 0)
    {
        vec4 _68 = texture(tex_map1, vec4(RVar[4u].xy, 0.0, RVar[4u].x).xy);
        RVar[4u] = vec4(_68.x, _68.y, _68.z, RVar[4u].w);
        RVar[3u] = texture(tex_map0, vec4(RVar[3u].xy, 0.0, RVar[3u].x).xy);
        vec4 _96 = texture(tex_map2, vec4(RVar[5u].xy, 0.0, RVar[5u].x).xy);
        RVar[5u] = vec4(_96.x, _96.y, _96.z, RVar[5u].w);
    }
    if (stateVar == 0)
    {
        float _112 = RVar[0u].z;
        float _118 = RVar[0u].y;
        float _123 = RVar[0u].x;
        float _128 = RVar[0u].x;
        float _130 = RVar[5u].x;
        RVar[127u].x = clamp(RVar[0u].w + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[127u].z = (_128 * _130) + uintBitsToFloat(0u);
        float _147 = (CBUFFER_1.values[10].w * ((-_123) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        float _149 = RVar[0u].y;
        float _151 = RVar[5u].y;
        float _159 = (CBUFFER_1.values[10].w * ((-_112) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        float _164 = (CBUFFER_1.values[10].w * ((-_118) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        float _166 = RVar[0u].z;
        float _168 = RVar[5u].z;
        RVar[123u].x = _147;
        RVar[127u].y = (_149 * _151) + uintBitsToFloat(0u);
        RVar[123u].z = _159;
        RVar[123u].w = _164;
        RVar[126u].x = (_166 * _168) + uintBitsToFloat(0u);
        float _180 = RVar[4u].y;
        float _185 = RVar[4u].x;
        float _190 = RVar[127u].x;
        float _192 = RVar[3u].w;
        float _195 = (_190 * _192) + uintBitsToFloat(0u);
        float _197 = RVar[4u].z;
        RVar[123u].z = _195;
        RVar[4u].w = uintBitsToFloat(1065353216u);
        float _205 = RVar[3u].y;
        float _208 = (clamp(_180 + (-_164), 0.0, 1.0) * _205) + uintBitsToFloat(0u);
        float _210 = RVar[3u].x;
        float _213 = (clamp(_185 + (-_147), 0.0, 1.0) * _210) + uintBitsToFloat(0u);
        float _218 = RVar[3u].z;
        float _221 = (clamp(_197 + (-_159), 0.0, 1.0) * _218) + uintBitsToFloat(0u);
        float _223 = RVar[2u].z;
        float _225 = RVar[2u].z;
        RVar[123u].x = _208;
        RVar[123u].y = _213;
        RVar[123u].w = _221;
        float _243 = RVar[2u].y;
        float _245 = RVar[2u].y;
        float _247 = (_243 * _245) + (_223 * _225);
        RVar[3u].w = clamp(clamp(_195 + uintBitsToFloat(0u), 0.0, 1.0) + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[122u].x = _247;
        float _252 = RVar[2u].x;
        float _254 = RVar[2u].x;
        float _256 = (_252 * _254) + _247;
        float _258 = RVar[126u].x;
        float _260 = clamp(clamp(_221 + uintBitsToFloat(0u), 0.0, 1.0) + _258, 0.0, 1.0);
        float _262 = RVar[127u].y;
        float _264 = clamp(clamp(_208 + uintBitsToFloat(0u), 0.0, 1.0) + _262, 0.0, 1.0);
        float _266 = RVar[127u].z;
        float _268 = clamp(clamp(_213 + uintBitsToFloat(0u), 0.0, 1.0) + _266, 0.0, 1.0);
        RVar[123u].x = _256;
        RVar[127u].y = _260;
        RVar[127u].z = _264;
        RVar[127u].w = _268;
        float _274 = RVar[1u].x;
        float _278 = RVar[1u].z;
        float _282 = RVar[1u].y;
        float _287 = inversesqrt(_256) * 0.5;
        RVar[126u].x = _287;
        float _296 = RVar[1u].w;
        float _298 = RVar[127u].z;
        float _302 = RVar[1u].w;
        float _304 = RVar[127u].y;
        float _308 = RVar[2u].x;
        RVar[3u].x = ((_274 + (-_268)) * RVar[1u].w) + RVar[127u].w;
        RVar[3u].y = ((_282 + (-_264)) * _296) + _298;
        RVar[3u].z = ((_278 + (-_260)) * _302) + _304;
        RVar[4u].x = (_308 * _287) + uintBitsToFloat(1056964608u);
        float _318 = RVar[2u].y;
        float _320 = RVar[126u].x;
        float _323 = (_318 * _320) + uintBitsToFloat(1056964608u);
        float _325 = RVar[2u].z;
        float _327 = RVar[126u].x;
        float _330 = (_325 * _327) + uintBitsToFloat(1056964608u);
        RVar[4u].y = _323;
        RVar[4u].z = _330;
        float _336 = RVar[4u].w;
        RVar[1u].x = RVar[4u].x;
        RVar[1u].y = _323;
        RVar[1u].z = _330;
        RVar[1u].w = _336;
        float _344 = RVar[3u].y;
        float _346 = RVar[3u].z;
        float _348 = RVar[3u].w;
        RVar[0u].x = RVar[3u].x;
        RVar[0u].y = _344;
        RVar[0u].z = _346;
        RVar[0u].w = _348;
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
    uint _424 = PS_PUSH.alphaFunc >> 8u;
    if (_424 == 1u)
    {
        _pixelTmp = vec4(1.0);
    }
    else
    {
        if (_424 == 2u)
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
    uint _452 = PS_PUSH.alphaFunc >> 8u;
    if (_452 == 1u)
    {
        _pixelTmp_1 = vec4(1.0);
    }
    else
    {
        if (_452 == 2u)
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