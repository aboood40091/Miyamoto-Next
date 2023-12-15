#version 430

struct PS_PUSH_DATA
{
    uint alphaFunc;
    float alphaRef;
    uint needsPremultiply; uint uItemID; int uIsSelected;
};

uniform PS_PUSH_DATA PS_PUSH;

uniform sampler2D cNormalMap0;
uniform sampler2D cTexMap0;
uniform sampler2D cLightMap0;
uniform sampler2D cLightMap1;

layout(location = 1) in vec4 PARAM_1;
layout(location = 0) in vec4 PARAM_0;
layout(location = 2) in vec4 PARAM_2;
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
    RVar[2u] = PARAM_2;
    RVar[3u] = PARAM_3;
    RVar[4u] = PARAM_4;
    RVar[5u] = PARAM_5;
    if (stateVar == 0)
    {
        vec4 _68 = texture(cNormalMap0, vec4(RVar[5u].xy, 0.0, RVar[5u].x).xy);
        RVar[5u] = vec4(_68.x, _68.y, RVar[5u].z, RVar[5u].w);
        RVar[4u] = texture(cTexMap0, vec4(RVar[4u].xy, 0.0, RVar[4u].x).xy);
    }
    if (stateVar == 0)
    {
        float _91 = RVar[0u].z;
        float _93 = RVar[0u].z;
        float _102 = RVar[4u].w;
        RVar[127u].y = RVar[3u].z * RVar[3u].z;
        RVar[8u].w = _102;
        RVar[7u].w = uintBitsToFloat(1065353216u);
        float _112 = RVar[5u].x;
        float _114 = RVar[5u].y;
        float _119 = RVar[5u].x;
        float _121 = RVar[5u].y;
        float _123 = RVar[5u].y;
        float _128 = RVar[0u].y;
        float _130 = RVar[0u].y;
        float _132 = (_128 * _130) + (_91 * _93);
        RVar[122u].x = _132;
        float _136 = RVar[0u].x;
        float _138 = RVar[0u].x;
        float _140 = (_136 * _138) + _132;
        float _145 = RVar[2u].z;
        float _147 = RVar[2u].z;
        float _150 = RVar[3u].y;
        float _152 = RVar[3u].y;
        float _154 = RVar[127u].y;
        float _156 = (_150 * _152) + _154;
        RVar[123u].x = _140;
        RVar[122u].x = _156;
        float _164 = RVar[2u].y;
        float _166 = RVar[2u].y;
        float _168 = (_164 * _166) + (_145 * _147);
        float _170 = RVar[3u].x;
        float _172 = RVar[3u].x;
        float _175 = inversesqrt(_140);
        RVar[123u].y = _168;
        RVar[127u].z = (_170 * _172) + _156;
        float _179 = RVar[0u].x;
        float _182 = RVar[0u].y;
        float _185 = RVar[0u].z;
        float _193 = sqrt((-min(dot(vec4(_112, _114, uintBitsToFloat(0u), uintBitsToFloat(2147483648u)), vec4(_119, _121, _123, uintBitsToFloat(0u))), uintBitsToFloat(1065353216u))) + uintBitsToFloat(1065353216u));
        RVar[127u].w = (RVar[2u].x * RVar[2u].x) + _168;
        RVar[5u].z = _193;
        float _197 = RVar[5u].x;
        float _199 = RVar[5u].y;
        float _204 = dot(vec4(_197, _199, _193, uintBitsToFloat(2147483648u)), vec4(_179 * _175, _182 * _175, _185 * _175, uintBitsToFloat(0u)));
        float _206 = RVar[127u].z;
        float _207 = inversesqrt(_206);
        RVar[6u].z = _204;
        float _211 = RVar[3u].x;
        float _214 = RVar[3u].y;
        float _217 = RVar[3u].z;
        RVar[127u].w = inversesqrt(RVar[127u].w);
        float _225 = RVar[5u].x;
        float _227 = RVar[5u].y;
        float _229 = RVar[5u].z;
        float _234 = dot(vec4(_225, _227, _229, uintBitsToFloat(2147483648u)), vec4(_211 * _207, _214 * _207, _217 * _207, uintBitsToFloat(0u)));
        RVar[3u].y = ((-_204) * uintBitsToFloat(1056964608u)) + uintBitsToFloat(1056964608u);
        float _246 = RVar[2u].x;
        float _248 = RVar[127u].w;
        float _251 = RVar[2u].y;
        float _253 = RVar[127u].w;
        float _256 = RVar[2u].z;
        float _258 = RVar[127u].w;
        RVar[3u].x = (_234 * uintBitsToFloat(1056964608u)) + uintBitsToFloat(1056964608u);
        RVar[0u].y = _246 * _248;
        RVar[0u].z = _251 * _253;
        RVar[0u].w = _256 * _258;
        RVar[7u].x = (_234 * uintBitsToFloat(1056964608u)) + uintBitsToFloat(1056964608u);
    }
    if (stateVar == 0)
    {
        vec4 _284 = texture(cLightMap0, vec4(RVar[3u].xy, 0.0, RVar[3u].x).xy);
        RVar[2u] = vec4(_284.x, _284.y, _284.z, RVar[2u].w);
        vec4 _299 = texture(cLightMap1, vec4(RVar[3u].xy, 0.0, RVar[3u].x).xy);
        RVar[3u] = vec4(_299.x, _299.y, _299.z, RVar[3u].w);
    }
    if (stateVar == 0)
    {
        float _316 = RVar[4u].x;
        float _318 = RVar[2u].x;
        float _320 = RVar[3u].x;
        float _322 = (_316 * _318) + _320;
        float _324 = RVar[4u].z;
        float _326 = RVar[2u].z;
        float _328 = RVar[3u].z;
        RVar[127u].x = (RVar[4u].y * RVar[2u].y) + RVar[3u].y;
        RVar[127u].y = _322;
        RVar[127u].w = (_324 * _326) + _328;
        float _352 = RVar[1u].x;
        float _356 = RVar[1u].z;
        float _358 = RVar[127u].w;
        float _362 = RVar[1u].y;
        float _364 = RVar[127u].x;
        float _372 = RVar[1u].w;
        float _374 = RVar[127u].y;
        RVar[7u].z = (dot(vec4(RVar[5u].x, RVar[5u].y, RVar[5u].z, uintBitsToFloat(2147483648u)), vec4(RVar[0u].y, RVar[0u].z, RVar[0u].w, uintBitsToFloat(0u))) * uintBitsToFloat(1056964608u)) + uintBitsToFloat(1056964608u);
        RVar[8u].x = ((_352 + (-_322)) * _372) + _374;
        float _386 = RVar[1u].w;
        float _388 = RVar[127u].w;
        float _392 = RVar[6u].z;
        float _396 = (_392 * uintBitsToFloat(1056964608u)) + uintBitsToFloat(1056964608u);
        RVar[8u].y = ((_362 + (-_364)) * RVar[1u].w) + RVar[127u].x;
        RVar[8u].z = ((_356 + (-_358)) * _386) + _388;
        RVar[7u].y = _396;
        float _403 = RVar[7u].z;
        float _405 = RVar[7u].w;
        RVar[1u].x = RVar[7u].x;
        RVar[1u].y = _396;
        RVar[1u].z = _403;
        RVar[1u].w = _405;
        float _413 = RVar[8u].y;
        float _415 = RVar[8u].z;
        float _417 = RVar[8u].w;
        RVar[0u].x = RVar[8u].x;
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
    uint _492 = PS_PUSH.alphaFunc >> 8u;
    if (_492 == 1u)
    {
        _pixelTmp = vec4(1.0);
    }
    else
    {
        if (_492 == 2u)
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
    uint _520 = PS_PUSH.alphaFunc >> 8u;
    if (_520 == 1u)
    {
        _pixelTmp_1 = vec4(1.0);
    }
    else
    {
        if (_520 == 2u)
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