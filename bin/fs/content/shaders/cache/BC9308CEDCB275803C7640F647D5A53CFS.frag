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
uniform sampler2D cSpecMaskMap0;
uniform sampler2D cLightMap0;
uniform sampler2D cLightMap1;

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
        vec4 _76 = texture(cNormalMap0, vec4(RVar[6u].xy, 0.0, RVar[6u].x).xy);
        RVar[6u] = vec4(_76.x, _76.y, RVar[6u].z, RVar[6u].w);
        RVar[5u] = texture(cTexMap0, vec4(RVar[5u].xy, 0.0, RVar[5u].x).xy);
        RVar[7u] = vec4(texture(cSpecMaskMap0, vec4(RVar[7u].xy, 0.0, RVar[7u].x).xy).x, RVar[7u].y, RVar[7u].z, RVar[7u].w);
    }
    if (stateVar == 0)
    {
        float _119 = RVar[1u].x;
        float _121 = RVar[5u].x;
        float _125 = RVar[1u].y;
        float _127 = RVar[5u].y;
        float _130 = RVar[1u].w;
        float _132 = RVar[5u].w;
        RVar[1u].x = RVar[1u].z * RVar[5u].z;
        RVar[1u].y = _119 * _121;
        RVar[1u].w = _125 * _127;
        float _138 = RVar[6u].x;
        float _140 = RVar[6u].y;
        float _145 = RVar[6u].x;
        float _147 = RVar[6u].y;
        float _149 = RVar[6u].y;
        RVar[9u].w = _130 * _132;
        float _156 = RVar[0u].z;
        float _158 = RVar[0u].z;
        float _170 = RVar[7u].x;
        float _172 = RVar[4u].z;
        float _174 = RVar[4u].z;
        RVar[126u].y = RVar[3u].z * RVar[3u].z;
        RVar[8u].w = _170;
        RVar[127u].x = _172 * _174;
        float _183 = RVar[0u].x;
        float _185 = RVar[0u].y;
        float _189 = RVar[0u].x;
        float _191 = RVar[0u].y;
        RVar[127u].y = (-min(dot(vec4(_138, _140, uintBitsToFloat(0u), uintBitsToFloat(2147483648u)), vec4(_145, _147, _149, uintBitsToFloat(0u))), uintBitsToFloat(1065353216u))) + uintBitsToFloat(1065353216u);
        float _216 = inversesqrt(dot(vec4(_183, _185, _156 * _158, uintBitsToFloat(2147483648u)), vec4(_189, _191, uintBitsToFloat(1065353216u), uintBitsToFloat(0u))));
        RVar[127u].x = dot(vec4(RVar[4u].x, RVar[4u].y, RVar[127u].x, uintBitsToFloat(2147483648u)), vec4(RVar[4u].x, RVar[4u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        float _219 = RVar[0u].x;
        float _222 = RVar[0u].y;
        float _225 = RVar[0u].z;
        float _228 = RVar[127u].y;
        float _229 = sqrt(_228);
        RVar[1u].z = _229;
        float _232 = RVar[6u].x;
        float _234 = RVar[6u].y;
        float _239 = dot(vec4(_232, _234, _229, uintBitsToFloat(2147483648u)), vec4(_219 * _216, _222 * _216, _225 * _216, uintBitsToFloat(0u)));
        float _241 = RVar[127u].x;
        float _242 = inversesqrt(_241);
        RVar[126u].x = _239;
        float _245 = RVar[4u].x;
        float _248 = RVar[4u].y;
        float _251 = RVar[4u].z;
        RVar[127u].x = (RVar[3u].y * RVar[3u].y) + RVar[126u].y;
        float _264 = RVar[6u].x;
        float _266 = RVar[6u].y;
        float _268 = RVar[1u].z;
        float _273 = dot(vec4(_264, _266, _268, uintBitsToFloat(2147483648u)), vec4(_245 * _242, _248 * _242, _251 * _242, uintBitsToFloat(0u)));
        RVar[4u].y = ((-_239) * uintBitsToFloat(1056964608u)) + uintBitsToFloat(1056964608u);
        float _285 = RVar[126u].x;
        float _291 = RVar[3u].x;
        float _293 = RVar[3u].x;
        float _295 = RVar[127u].x;
        RVar[4u].x = (_273 * uintBitsToFloat(1056964608u)) + uintBitsToFloat(1056964608u);
        RVar[8u].y = (_285 * uintBitsToFloat(1056964608u)) + uintBitsToFloat(1056964608u);
        RVar[5u].w = (_291 * _293) + _295;
        RVar[8u].x = (_273 * uintBitsToFloat(1056964608u)) + uintBitsToFloat(1056964608u);
    }
    if (stateVar == 0)
    {
        vec4 _321 = texture(cLightMap0, vec4(RVar[4u].xy, 0.0, RVar[4u].x).xy);
        RVar[0u] = vec4(_321.x, _321.y, _321.z, RVar[0u].w);
        vec4 _336 = texture(cLightMap1, vec4(RVar[4u].xy, 0.0, RVar[4u].x).xy);
        RVar[4u] = vec4(_336.x, _336.y, _336.z, RVar[4u].w);
    }
    if (stateVar == 0)
    {
        float _345 = RVar[0u].x;
        float _347 = RVar[1u].y;
        float _350 = RVar[0u].z;
        float _352 = RVar[1u].x;
        float _355 = RVar[0u].y;
        float _357 = RVar[1u].w;
        float _360 = RVar[5u].w;
        float _361 = inversesqrt(_360);
        RVar[127u].w = _361;
        float _364 = RVar[4u].y;
        float _366 = RVar[7u].x;
        float _368 = (_364 * _366) + (_355 * _357);
        float _370 = RVar[4u].x;
        float _372 = RVar[7u].x;
        float _374 = (_370 * _372) + (_345 * _347);
        float _376 = RVar[3u].x;
        float _379 = RVar[4u].z;
        float _381 = RVar[7u].x;
        float _383 = (_379 * _381) + (_350 * _352);
        float _385 = RVar[3u].y;
        RVar[127u].x = _368;
        RVar[127u].y = _374;
        RVar[127u].z = _376 * _361;
        RVar[126u].w = _383;
        RVar[126u].y = _385 * _361;
        float _393 = RVar[2u].x;
        float _401 = RVar[3u].z;
        float _403 = RVar[127u].w;
        float _406 = RVar[2u].z;
        RVar[125u].y = RVar[2u].y + (-_368);
        RVar[127u].w = _406 + (-_383);
        float _413 = RVar[6u].x;
        float _415 = RVar[6u].y;
        float _417 = RVar[1u].z;
        float _421 = RVar[127u].z;
        float _423 = RVar[126u].y;
        RVar[9u].x = ((_393 + (-_374)) * RVar[2u].w) + RVar[127u].y;
        float _443 = RVar[127u].w;
        float _445 = RVar[2u].w;
        float _447 = RVar[126u].w;
        float _453 = (dot(vec4(_413, _415, _417, uintBitsToFloat(2147483648u)), vec4(_421, _423, _401 * _403, uintBitsToFloat(0u))) * uintBitsToFloat(1056964608u)) + uintBitsToFloat(1056964608u);
        RVar[9u].y = (RVar[125u].y * RVar[2u].w) + RVar[127u].x;
        RVar[9u].z = (_443 * _445) + _447;
        RVar[8u].z = _453;
        float _460 = RVar[8u].y;
        float _462 = RVar[8u].w;
        RVar[1u].x = RVar[8u].x;
        RVar[1u].y = _460;
        RVar[1u].z = _453;
        RVar[1u].w = _462;
        float _470 = RVar[9u].y;
        float _472 = RVar[9u].z;
        float _474 = RVar[9u].w;
        RVar[0u].x = RVar[9u].x;
        RVar[0u].y = _470;
        RVar[0u].z = _472;
        RVar[0u].w = _474;
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
    uint _549 = PS_PUSH.alphaFunc >> 8u;
    if (_549 == 1u)
    {
        _pixelTmp = vec4(1.0);
    }
    else
    {
        if (_549 == 2u)
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
    uint _577 = PS_PUSH.alphaFunc >> 8u;
    if (_577 == 1u)
    {
        _pixelTmp_1 = vec4(1.0);
    }
    else
    {
        if (_577 == 2u)
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