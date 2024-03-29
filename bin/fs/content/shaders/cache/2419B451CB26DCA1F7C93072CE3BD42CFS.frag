#version 430

struct PS_PUSH_DATA
{
    uint alphaFunc;
    float alphaRef;
    uint needsPremultiply; uint uItemID; int uIsSelected;
};

uniform PS_PUSH_DATA PS_PUSH;

uniform sampler2D tex_map1;
uniform sampler2D tex_map2;
uniform sampler2D tex_map0;

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
        vec4 _83 = texture(tex_map2, vec4(RVar[5u].xy, 0.0, RVar[5u].x).xy);
        RVar[5u] = vec4(_83.x, _83.y, _83.z, RVar[5u].w);
        vec4 _98 = texture(tex_map0, vec4(RVar[3u].xy, 0.0, RVar[3u].x).xy);
        RVar[3u] = vec4(_98.x, _98.y, _98.z, RVar[3u].w);
    }
    if (stateVar == 0)
    {
        float _108 = RVar[0u].z;
        float _110 = RVar[4u].z;
        float _113 = (_108 * _110) + uintBitsToFloat(0u);
        float _115 = RVar[0u].y;
        float _117 = RVar[4u].y;
        float _120 = (_115 * _117) + uintBitsToFloat(0u);
        float _122 = RVar[0u].x;
        float _124 = RVar[4u].x;
        float _127 = (_122 * _124) + uintBitsToFloat(0u);
        float _129 = RVar[0u].x;
        float _131 = RVar[5u].x;
        float _134 = (_129 * _131) + uintBitsToFloat(0u);
        float _136 = RVar[0u].y;
        float _138 = RVar[5u].y;
        RVar[123u].x = _113;
        RVar[123u].y = _120;
        RVar[123u].z = _127;
        RVar[123u].w = _134;
        RVar[127u].x = (_136 * _138) + uintBitsToFloat(0u);
        float _150 = RVar[0u].z;
        float _152 = RVar[5u].z;
        float _155 = (_150 * _152) + uintBitsToFloat(0u);
        RVar[123u].x = _155;
        RVar[127u].z = clamp((_134 + uintBitsToFloat(0u)) * 2.0, 0.0, 1.0);
        float _180 = RVar[3u].z;
        float _183 = (clamp(_113 + uintBitsToFloat(0u), 0.0, 1.0) * _180) + uintBitsToFloat(0u);
        float _185 = RVar[3u].y;
        float _188 = (clamp(_120 + uintBitsToFloat(0u), 0.0, 1.0) * _185) + uintBitsToFloat(0u);
        float _190 = RVar[3u].x;
        float _193 = (clamp(_127 + uintBitsToFloat(0u), 0.0, 1.0) * _190) + uintBitsToFloat(0u);
        RVar[127u].x = clamp((RVar[127u].x + uintBitsToFloat(0u)) * 2.0, 0.0, 1.0);
        RVar[123u].y = _183;
        RVar[123u].z = _188;
        RVar[123u].w = _193;
        RVar[126u].x = clamp((_155 + uintBitsToFloat(0u)) * 2.0, 0.0, 1.0);
        float _205 = RVar[0u].w;
        float _219 = RVar[127u].z;
        RVar[127u].z = clamp(_183 + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[127u].w = clamp(_188 + uintBitsToFloat(0u), 0.0, 1.0);
        float _225 = RVar[126u].x;
        float _229 = RVar[127u].x;
        float _236 = clamp(clamp(_193 + uintBitsToFloat(0u), 0.0, 1.0) + (_219 + uintBitsToFloat(0u)), 0.0, 1.0);
        RVar[126u].w = _236;
        RVar[0u].w = uintBitsToFloat(1065353216u);
        float _246 = RVar[127u].z;
        float _250 = RVar[127u].w;
        float _252 = clamp(_250 + (_229 + uintBitsToFloat(0u)), 0.0, 1.0);
        float _257 = RVar[2u].z;
        float _259 = RVar[2u].z;
        RVar[127u].x = RVar[1u].x + (-_236);
        RVar[127u].y = clamp(_246 + (_225 + uintBitsToFloat(0u)), 0.0, 1.0);
        RVar[127u].z = _252;
        RVar[127u].w = clamp(clamp(clamp(_205 + uintBitsToFloat(0u), 0.0, 1.0) + uintBitsToFloat(0u), 0.0, 1.0) + uintBitsToFloat(0u), 0.0, 1.0);
        float _266 = RVar[2u].x;
        float _268 = RVar[2u].y;
        float _273 = RVar[2u].x;
        float _275 = RVar[2u].y;
        float _281 = RVar[1u].y;
        float _293 = RVar[1u].w;
        float _295 = RVar[127u].z;
        float _299 = RVar[1u].z;
        float _301 = RVar[127u].y;
        float _305 = RVar[127u].w;
        float _311 = inversesqrt(dot(vec4(_266, _268, _257 * _259, uintBitsToFloat(2147483648u)), vec4(_273, _275, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)))) * 0.5;
        RVar[3u].x = (RVar[127u].x * RVar[1u].w) + RVar[126u].w;
        RVar[3u].y = ((_281 + (-_252)) * _293) + _295;
        RVar[3u].w = clamp(_305 + uintBitsToFloat(0u), 0.0, 1.0);
        float _316 = RVar[2u].x;
        float _320 = (_316 * _311) + uintBitsToFloat(1056964608u);
        float _322 = RVar[2u].y;
        float _325 = (_322 * _311) + uintBitsToFloat(1056964608u);
        float _327 = RVar[1u].w;
        float _329 = RVar[127u].y;
        float _333 = RVar[2u].z;
        float _336 = (_333 * _311) + uintBitsToFloat(1056964608u);
        RVar[0u].x = _320;
        RVar[0u].y = _325;
        RVar[3u].z = ((_299 + (-_301)) * _327) + _329;
        RVar[0u].z = _336;
        float _342 = RVar[0u].w;
        RVar[1u].x = _320;
        RVar[1u].y = _325;
        RVar[1u].z = _336;
        RVar[1u].w = _342;
        float _350 = RVar[3u].y;
        float _352 = RVar[3u].z;
        float _354 = RVar[3u].w;
        RVar[0u].x = RVar[3u].x;
        RVar[0u].y = _350;
        RVar[0u].z = _352;
        RVar[0u].w = _354;
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
    uint _430 = PS_PUSH.alphaFunc >> 8u;
    if (_430 == 1u)
    {
        _pixelTmp = vec4(1.0);
    }
    else
    {
        if (_430 == 2u)
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
    uint _458 = PS_PUSH.alphaFunc >> 8u;
    if (_458 == 1u)
    {
        _pixelTmp_1 = vec4(1.0);
    }
    else
    {
        if (_458 == 2u)
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