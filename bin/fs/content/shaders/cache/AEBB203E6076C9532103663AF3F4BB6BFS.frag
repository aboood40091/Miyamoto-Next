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
        RVar[126u].z = (_136 * _138) + uintBitsToFloat(0u);
        float _161 = RVar[0u].z;
        float _163 = RVar[5u].z;
        float _166 = (_161 * _163) + uintBitsToFloat(0u);
        RVar[123u].w = _166;
        RVar[5u].w = uintBitsToFloat(0u);
        float _171 = RVar[127u].z;
        float _177 = RVar[2u].z;
        float _179 = RVar[2u].z;
        float _182 = RVar[126u].z;
        RVar[0u].w = uintBitsToFloat(1065353216u);
        float _189 = RVar[3u].z;
        float _192 = (clamp(clamp(_134 + uintBitsToFloat(0u), 0.0, 1.0) + _166, 0.0, 1.0) * _189) + uintBitsToFloat(0u);
        float _194 = RVar[3u].y;
        float _197 = (clamp(clamp(_113 + uintBitsToFloat(0u), 0.0, 1.0) + _182, 0.0, 1.0) * _194) + uintBitsToFloat(0u);
        float _199 = RVar[3u].x;
        float _202 = (clamp(clamp(_120 + uintBitsToFloat(0u), 0.0, 1.0) + _171, 0.0, 1.0) * _199) + uintBitsToFloat(0u);
        float _204 = RVar[2u].y;
        float _206 = RVar[2u].y;
        float _208 = (_204 * _206) + (_177 * _179);
        RVar[123u].x = _192;
        RVar[123u].y = _197;
        RVar[123u].z = _202;
        RVar[122u].x = _208;
        float _215 = RVar[2u].x;
        float _217 = RVar[2u].x;
        float _219 = (_215 * _217) + _208;
        float _222 = clamp(_192 + uintBitsToFloat(0u), 0.0, 1.0);
        float _225 = clamp(_197 + uintBitsToFloat(0u), 0.0, 1.0);
        float _228 = clamp(_202 + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[123u].x = _219;
        RVar[127u].y = _222;
        RVar[127u].z = _225;
        RVar[127u].w = _228;
        float _234 = RVar[1u].x;
        float _238 = RVar[1u].z;
        float _242 = RVar[1u].y;
        float _247 = inversesqrt(_219) * 0.5;
        RVar[127u].x = _247;
        float _256 = RVar[1u].w;
        float _258 = RVar[127u].z;
        float _262 = RVar[1u].w;
        float _264 = RVar[127u].y;
        float _268 = RVar[2u].x;
        RVar[5u].x = ((_234 + (-_228)) * RVar[1u].w) + RVar[127u].w;
        RVar[5u].y = ((_242 + (-_225)) * _256) + _258;
        RVar[5u].z = ((_238 + (-_222)) * _262) + _264;
        RVar[0u].x = (_268 * _247) + uintBitsToFloat(1056964608u);
        float _278 = RVar[2u].y;
        float _280 = RVar[127u].x;
        float _283 = (_278 * _280) + uintBitsToFloat(1056964608u);
        float _285 = RVar[2u].z;
        float _287 = RVar[127u].x;
        float _290 = (_285 * _287) + uintBitsToFloat(1056964608u);
        RVar[0u].y = _283;
        RVar[0u].z = _290;
        float _296 = RVar[0u].w;
        RVar[1u].x = RVar[0u].x;
        RVar[1u].y = _283;
        RVar[1u].z = _290;
        RVar[1u].w = _296;
        float _304 = RVar[5u].y;
        float _306 = RVar[5u].z;
        float _308 = RVar[5u].w;
        RVar[0u].x = RVar[5u].x;
        RVar[0u].y = _304;
        RVar[0u].z = _306;
        RVar[0u].w = _308;
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
    uint _384 = PS_PUSH.alphaFunc >> 8u;
    if (_384 == 1u)
    {
        _pixelTmp = vec4(1.0);
    }
    else
    {
        if (_384 == 2u)
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
    uint _412 = PS_PUSH.alphaFunc >> 8u;
    if (_412 == 1u)
    {
        _pixelTmp_1 = vec4(1.0);
    }
    else
    {
        if (_412 == 2u)
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