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

layout(location = 2) in vec4 PARAM_2;
layout(location = 1) in vec4 PARAM_1;
layout(location = 0) in vec4 PARAM_0;
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
    RVar[0u] = PARAM_2;
    RVar[1u] = PARAM_1;
    RVar[2u] = PARAM_0;
    RVar[3u] = PARAM_3;
    RVar[4u] = PARAM_4;
    if (stateVar == 0)
    {
        vec4 _64 = texture(tex_map1, vec4(RVar[4u].xy, 0.0, RVar[4u].x).xy);
        RVar[4u] = vec4(_64.x, _64.y, _64.z, RVar[4u].w);
        RVar[3u] = texture(tex_map0, vec4(RVar[3u].xy, 0.0, RVar[3u].x).xy);
    }
    if (stateVar == 0)
    {
        float _87 = RVar[0u].x;
        float _93 = RVar[0u].w;
        float _99 = RVar[0u].z;
        float _104 = RVar[0u].y;
        RVar[0u].w = uintBitsToFloat(1065353216u);
        float _120 = (CBUFFER_1.values[10].w * ((-_104) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        float _125 = (CBUFFER_1.values[10].w * ((-_87) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        float _127 = RVar[3u].w;
        float _130 = (clamp(_93 + uintBitsToFloat(0u), 0.0, 1.0) * _127) + uintBitsToFloat(0u);
        float _135 = (CBUFFER_1.values[10].w * ((-_99) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        float _137 = RVar[2u].z;
        float _139 = RVar[2u].z;
        RVar[123u].x = _120;
        RVar[123u].y = _125;
        RVar[123u].z = _130;
        RVar[123u].w = _135;
        float _147 = RVar[4u].z;
        float _152 = RVar[4u].y;
        float _157 = RVar[4u].x;
        float _165 = RVar[2u].y;
        float _167 = RVar[2u].y;
        float _169 = (_165 * _167) + (_137 * _139);
        RVar[4u].w = clamp(_130 + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[122u].x = _169;
        float _174 = RVar[3u].z;
        float _177 = (clamp(_147 + (-_135), 0.0, 1.0) * _174) + uintBitsToFloat(0u);
        float _179 = RVar[3u].y;
        float _182 = (clamp(_152 + (-_120), 0.0, 1.0) * _179) + uintBitsToFloat(0u);
        float _184 = RVar[3u].x;
        float _187 = (clamp(_157 + (-_125), 0.0, 1.0) * _184) + uintBitsToFloat(0u);
        float _189 = RVar[2u].x;
        float _191 = RVar[2u].x;
        float _193 = (_189 * _191) + _169;
        RVar[123u].x = _177;
        RVar[123u].y = _182;
        RVar[123u].z = _187;
        RVar[123u].w = _193;
        float _206 = inversesqrt(_193) * 0.5;
        RVar[127u].x = _206;
        float _215 = clamp(((_187 + uintBitsToFloat(0u)) + (-uintBitsToFloat(1056964608u))) * 4.0, 0.0, 1.0);
        float _217 = RVar[2u].y;
        float _225 = clamp(((_177 + uintBitsToFloat(0u)) + (-uintBitsToFloat(1056964608u))) * 4.0, 0.0, 1.0);
        float _230 = clamp(((_182 + uintBitsToFloat(0u)) + (-uintBitsToFloat(1056964608u))) * 4.0, 0.0, 1.0);
        float _232 = RVar[2u].x;
        RVar[126u].x = _215;
        RVar[0u].y = (_217 * _206) + uintBitsToFloat(1056964608u);
        RVar[127u].z = _225;
        RVar[127u].w = _230;
        RVar[0u].x = (_232 * _206) + uintBitsToFloat(1056964608u);
        float _243 = RVar[1u].x;
        float _247 = RVar[1u].z;
        float _251 = RVar[1u].y;
        RVar[0u].z = (RVar[2u].z * RVar[127u].x) + uintBitsToFloat(1056964608u);
        float _269 = RVar[1u].w;
        float _271 = RVar[127u].w;
        float _275 = RVar[1u].w;
        float _277 = RVar[127u].z;
        RVar[4u].x = ((_243 + (-_215)) * RVar[1u].w) + RVar[126u].x;
        RVar[4u].y = ((_251 + (-_230)) * _269) + _271;
        RVar[4u].z = ((_247 + (-_225)) * _275) + _277;
        float _286 = RVar[0u].y;
        float _288 = RVar[0u].z;
        float _290 = RVar[0u].w;
        RVar[1u].x = RVar[0u].x;
        RVar[1u].y = _286;
        RVar[1u].z = _288;
        RVar[1u].w = _290;
        float _298 = RVar[4u].y;
        float _300 = RVar[4u].z;
        float _302 = RVar[4u].w;
        RVar[0u].x = RVar[4u].x;
        RVar[0u].y = _298;
        RVar[0u].z = _300;
        RVar[0u].w = _302;
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
    uint _378 = PS_PUSH.alphaFunc >> 8u;
    if (_378 == 1u)
    {
        _pixelTmp = vec4(1.0);
    }
    else
    {
        if (_378 == 2u)
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
    uint _406 = PS_PUSH.alphaFunc >> 8u;
    if (_406 == 1u)
    {
        _pixelTmp_1 = vec4(1.0);
    }
    else
    {
        if (_406 == 2u)
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