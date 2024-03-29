#version 430

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
        vec4 _83 = texture(tex_map0, vec4(RVar[3u].xy, 0.0, RVar[3u].x).xy);
        RVar[3u] = vec4(_83.x, _83.y, _83.z, RVar[3u].w);
        vec4 _98 = texture(tex_map2, vec4(RVar[5u].xy, 0.0, RVar[5u].x).xy);
        RVar[5u] = vec4(_98.x, _98.y, _98.z, RVar[5u].w);
    }
    if (stateVar == 0)
    {
        float _108 = RVar[0u].y;
        float _110 = RVar[4u].y;
        float _113 = (_108 * _110) + uintBitsToFloat(0u);
        float _115 = RVar[0u].x;
        float _117 = RVar[4u].x;
        float _120 = (_115 * _117) + uintBitsToFloat(0u);
        float _122 = RVar[0u].x;
        float _124 = RVar[5u].x;
        float _129 = RVar[0u].z;
        float _131 = RVar[4u].z;
        float _134 = (_129 * _131) + uintBitsToFloat(0u);
        float _136 = RVar[0u].y;
        float _138 = RVar[5u].y;
        RVar[123u].x = _113;
        RVar[123u].y = _120;
        RVar[127u].z = (_122 * _124) + uintBitsToFloat(0u);
        RVar[123u].w = _134;
        RVar[127u].y = (_136 * _138) + uintBitsToFloat(0u);
        RVar[127u].w = (RVar[0u].z * RVar[5u].z) + uintBitsToFloat(0u);
        RVar[0u].w = uintBitsToFloat(0u);
        float _170 = RVar[2u].z;
        float _172 = RVar[2u].z;
        float _175 = RVar[3u].z;
        float _178 = (clamp(_134 + uintBitsToFloat(0u), 0.0, 1.0) * _175) + uintBitsToFloat(0u);
        float _180 = RVar[3u].y;
        float _183 = (clamp(_113 + uintBitsToFloat(0u), 0.0, 1.0) * _180) + uintBitsToFloat(0u);
        float _185 = RVar[3u].x;
        float _188 = (clamp(_120 + uintBitsToFloat(0u), 0.0, 1.0) * _185) + uintBitsToFloat(0u);
        RVar[123u].y = _178;
        RVar[123u].z = _183;
        RVar[123u].w = _188;
        RVar[3u].w = uintBitsToFloat(1065353216u);
        float _205 = RVar[2u].y;
        float _207 = RVar[2u].y;
        float _209 = (_205 * _207) + (_170 * _172);
        RVar[122u].x = _209;
        float _213 = RVar[2u].x;
        float _215 = RVar[2u].x;
        float _217 = (_213 * _215) + _209;
        float _219 = RVar[127u].w;
        float _221 = clamp(clamp(_178 + uintBitsToFloat(0u), 0.0, 1.0) + _219, 0.0, 1.0);
        float _223 = RVar[127u].y;
        float _225 = clamp(clamp(_183 + uintBitsToFloat(0u), 0.0, 1.0) + _223, 0.0, 1.0);
        float _227 = RVar[127u].z;
        float _229 = clamp(clamp(_188 + uintBitsToFloat(0u), 0.0, 1.0) + _227, 0.0, 1.0);
        RVar[123u].x = _217;
        RVar[127u].y = _221;
        RVar[127u].z = _225;
        RVar[127u].w = _229;
        float _235 = RVar[1u].x;
        float _239 = RVar[1u].z;
        float _243 = RVar[1u].y;
        float _248 = inversesqrt(_217) * 0.5;
        RVar[127u].x = _248;
        float _257 = RVar[1u].w;
        float _259 = RVar[127u].z;
        float _263 = RVar[1u].w;
        float _265 = RVar[127u].y;
        float _269 = RVar[2u].x;
        RVar[0u].x = ((_235 + (-_229)) * RVar[1u].w) + RVar[127u].w;
        RVar[0u].y = ((_243 + (-_225)) * _257) + _259;
        RVar[0u].z = ((_239 + (-_221)) * _263) + _265;
        RVar[3u].x = (_269 * _248) + uintBitsToFloat(1056964608u);
        float _279 = RVar[2u].y;
        float _281 = RVar[127u].x;
        float _284 = (_279 * _281) + uintBitsToFloat(1056964608u);
        float _286 = RVar[2u].z;
        float _288 = RVar[127u].x;
        float _291 = (_286 * _288) + uintBitsToFloat(1056964608u);
        RVar[3u].y = _284;
        RVar[3u].z = _291;
        float _297 = RVar[3u].w;
        RVar[2u].x = RVar[3u].x;
        RVar[2u].y = _284;
        RVar[2u].z = _291;
        RVar[2u].w = _297;
        float _305 = RVar[0u].y;
        float _307 = RVar[0u].z;
        float _309 = RVar[0u].w;
        RVar[1u].x = RVar[0u].x;
        RVar[1u].y = _305;
        RVar[1u].z = _307;
        RVar[1u].w = _309;
    }
    switch (PS_PUSH.alphaFunc & 255u)
    {
        case 0u:
        {
            discard;
        }
        case 1u:
        {
            if (!(RVar[1u].w < PS_PUSH.alphaRef))
            {
                discard;
            }
            break;
        }
        case 2u:
        {
            if (abs(RVar[1u].w - PS_PUSH.alphaRef) > 9.9999997473787516355514526367188e-05)
            {
                discard;
            }
            break;
        }
        case 3u:
        {
            if (!(RVar[1u].w <= PS_PUSH.alphaRef))
            {
                discard;
            }
            break;
        }
        case 4u:
        {
            if (!(RVar[1u].w > PS_PUSH.alphaRef))
            {
                discard;
            }
            break;
        }
        case 5u:
        {
            if (abs(RVar[1u].w - PS_PUSH.alphaRef) <= 9.9999997473787516355514526367188e-05)
            {
                discard;
            }
            break;
        }
        case 6u:
        {
            if (!(RVar[1u].w >= PS_PUSH.alphaRef))
            {
                discard;
            }
            break;
        }
    }
    _pixelTmp = RVar[1u];
    uint _385 = PS_PUSH.alphaFunc >> 8u;
    if (_385 == 1u)
    {
        _pixelTmp = vec4(1.0);
    }
    else
    {
        if (_385 == 2u)
        {
            _pixelTmp = vec4(0.0);
        }
    }
    if ((PS_PUSH.needsPremultiply & 1u) != 0u)
    {
        _pixelTmp *= vec4(_pixelTmp.www, 1.0);
    }
    if (PS_PUSH.uIsSelected != 0) PIXEL_0 = vec4(_pixelTmp.rgb * 0.5f + vec3(1.0f, 0.25f, 0.25f) * 0.5f, _pixelTmp.a); else PIXEL_0 = _pixelTmp; ItemID = PS_PUSH.uItemID;
    _pixelTmp_1 = RVar[2u];
    uint _413 = PS_PUSH.alphaFunc >> 8u;
    if (_413 == 1u)
    {
        _pixelTmp_1 = vec4(1.0);
    }
    else
    {
        if (_413 == 2u)
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