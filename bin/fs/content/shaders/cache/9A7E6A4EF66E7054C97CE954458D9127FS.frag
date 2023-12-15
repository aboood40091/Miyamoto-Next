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
        vec4 _68 = texture(tex_map2, vec4(RVar[5u].xy, 0.0, RVar[5u].x).xy);
        RVar[5u] = vec4(_68.x, _68.y, _68.z, RVar[5u].w);
        RVar[3u] = texture(tex_map0, vec4(RVar[3u].xy, 0.0, RVar[3u].x).xy);
        vec4 _96 = texture(tex_map1, vec4(RVar[4u].xy, 0.0, RVar[4u].x).xy);
        RVar[4u] = vec4(_96.x, _96.y, _96.z, RVar[4u].w);
    }
    if (stateVar == 0)
    {
        float _106 = RVar[0u].y;
        float _108 = RVar[5u].y;
        float _111 = (_106 * _108) + uintBitsToFloat(0u);
        float _113 = RVar[0u].x;
        float _115 = RVar[5u].x;
        float _118 = (_113 * _115) + uintBitsToFloat(0u);
        float _120 = RVar[0u].w;
        float _126 = RVar[0u].z;
        float _128 = RVar[5u].z;
        float _131 = (_126 * _128) + uintBitsToFloat(0u);
        RVar[123u].x = _111;
        RVar[123u].y = _118;
        RVar[123u].w = _131;
        RVar[0u].w = uintBitsToFloat(1065353216u);
        float _149 = RVar[3u].w;
        float _152 = (clamp(_120 + uintBitsToFloat(0u), 0.0, 1.0) * _149) + uintBitsToFloat(0u);
        float _154 = RVar[2u].z;
        float _156 = RVar[2u].z;
        RVar[123u].w = _152;
        float _160 = RVar[3u].z;
        float _163 = (clamp(_131 + uintBitsToFloat(0u), 0.0, 1.0) * _160) + uintBitsToFloat(0u);
        float _165 = RVar[3u].y;
        float _168 = (clamp(_111 + uintBitsToFloat(0u), 0.0, 1.0) * _165) + uintBitsToFloat(0u);
        float _170 = RVar[3u].x;
        float _173 = (clamp(_118 + uintBitsToFloat(0u), 0.0, 1.0) * _170) + uintBitsToFloat(0u);
        float _176 = clamp(_152 + uintBitsToFloat(0u), 0.0, 1.0);
        float _178 = RVar[2u].y;
        float _180 = RVar[2u].y;
        float _182 = (_178 * _180) + (_154 * _156);
        RVar[123u].x = _163;
        RVar[123u].y = _168;
        RVar[123u].z = _173;
        RVar[127u].w = _176;
        RVar[122u].x = _182;
        float _191 = RVar[2u].x;
        float _193 = RVar[2u].x;
        float _195 = (_191 * _193) + _182;
        RVar[123u].x = _195;
        RVar[127u].y = (_176 * CBUFFER_1.values[10].w) + uintBitsToFloat(0u);
        float _219 = RVar[4u].z;
        float _222 = (clamp(_163 + uintBitsToFloat(0u), 0.0, 1.0) * _219) + uintBitsToFloat(0u);
        float _224 = RVar[4u].y;
        float _227 = (clamp(_168 + uintBitsToFloat(0u), 0.0, 1.0) * _224) + uintBitsToFloat(0u);
        float _229 = RVar[4u].x;
        float _232 = (clamp(_173 + uintBitsToFloat(0u), 0.0, 1.0) * _229) + uintBitsToFloat(0u);
        float _235 = inversesqrt(_195) * 0.5;
        RVar[123u].y = _222;
        RVar[123u].z = _227;
        RVar[123u].w = _232;
        RVar[126u].x = _235;
        float _245 = clamp(CBUFFER_1.values[7].x + _232, 0.0, 1.0);
        float _247 = RVar[2u].y;
        float _255 = clamp(CBUFFER_1.values[7].z + _222, 0.0, 1.0);
        float _259 = clamp(CBUFFER_1.values[7].y + _227, 0.0, 1.0);
        float _261 = RVar[127u].w;
        float _263 = RVar[127u].y;
        RVar[127u].x = _245;
        RVar[0u].y = (_247 * _235) + uintBitsToFloat(1056964608u);
        RVar[127u].z = _255;
        RVar[127u].w = _259;
        RVar[4u].w = clamp(_261 + _263, 0.0, 1.0);
        float _272 = RVar[1u].x;
        float _276 = RVar[1u].z;
        float _280 = RVar[1u].y;
        RVar[0u].x = (RVar[2u].x * RVar[126u].x) + uintBitsToFloat(1056964608u);
        float _298 = RVar[1u].w;
        float _300 = RVar[127u].w;
        float _304 = RVar[1u].w;
        float _306 = RVar[127u].z;
        float _310 = RVar[2u].z;
        float _312 = RVar[126u].x;
        float _315 = (_310 * _312) + uintBitsToFloat(1056964608u);
        RVar[4u].x = ((_272 + (-_245)) * RVar[1u].w) + RVar[127u].x;
        RVar[4u].y = ((_280 + (-_259)) * _298) + _300;
        RVar[4u].z = ((_276 + (-_255)) * _304) + _306;
        RVar[0u].z = _315;
        float _323 = RVar[0u].y;
        float _325 = RVar[0u].w;
        RVar[1u].x = RVar[0u].x;
        RVar[1u].y = _323;
        RVar[1u].z = _315;
        RVar[1u].w = _325;
        float _333 = RVar[4u].y;
        float _335 = RVar[4u].z;
        float _337 = RVar[4u].w;
        RVar[0u].x = RVar[4u].x;
        RVar[0u].y = _333;
        RVar[0u].z = _335;
        RVar[0u].w = _337;
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
    uint _413 = PS_PUSH.alphaFunc >> 8u;
    if (_413 == 1u)
    {
        _pixelTmp = vec4(1.0);
    }
    else
    {
        if (_413 == 2u)
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
    uint _441 = PS_PUSH.alphaFunc >> 8u;
    if (_441 == 1u)
    {
        _pixelTmp_1 = vec4(1.0);
    }
    else
    {
        if (_441 == 2u)
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