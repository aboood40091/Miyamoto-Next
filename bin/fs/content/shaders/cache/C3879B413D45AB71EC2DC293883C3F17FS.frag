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
layout(location = 0) in vec4 PARAM_0;
layout(location = 1) in vec4 PARAM_1;
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
    RVar[1u] = PARAM_0;
    RVar[2u] = PARAM_1;
    RVar[3u] = PARAM_3;
    RVar[4u] = PARAM_4;
    if (stateVar == 0)
    {
        vec4 _64 = texture(tex_map1, vec4(RVar[4u].xy, 0.0, RVar[4u].x).xy);
        RVar[4u] = vec4(_64.x, RVar[4u].y, RVar[4u].z, _64.w);
    }
    if (stateVar == 0)
    {
        float _74 = RVar[2u].z;
        float _76 = RVar[2u].z;
        float _79 = RVar[4u].w;
        float _83 = _79 + (-uintBitsToFloat(1056964608u));
        RVar[0u].z = RVar[4u].x + (-uintBitsToFloat(1056964608u));
        RVar[4u].w = uintBitsToFloat(0u);
        RVar[6u].w = uintBitsToFloat(1065353216u);
        float _109 = RVar[2u].y;
        float _111 = RVar[2u].y;
        RVar[4u].x = _83 * CBUFFER_1.values[11].x;
        RVar[2u].w = _83 * CBUFFER_1.values[11].y;
        RVar[5u].x = (_109 * _111) + (_74 * _76);
    }
    if (stateVar == 0)
    {
        vec4 _139 = intBitsToFloat(ivec4(ivec3(textureSize(tex_map0, floatBitsToInt(vec4(RVar[4u].ww, 0.0, RVar[4u].w).x)), 1), textureQueryLevels(tex_map0)));
        RVar[0u] = vec4(_139.x, _139.y, RVar[0u].z, RVar[0u].w);
    }
    if (stateVar == 0)
    {
        float _148 = RVar[0u].z;
        float _152 = RVar[2u].w;
        float _154 = (_148 * CBUFFER_1.values[11].w) + _152;
        float _156 = RVar[0u].z;
        float _160 = RVar[4u].x;
        float _162 = (_156 * CBUFFER_1.values[11].z) + _160;
        float _164 = RVar[0u].x;
        RVar[123u].y = _154;
        RVar[123u].z = _162;
        RVar[127u].x = float(floatBitsToInt(_164));
        float _173 = RVar[0u].z;
        float _178 = (_173 * CBUFFER_1.values[12].x) + _162;
        float _180 = RVar[2u].x;
        float _182 = RVar[2u].x;
        float _184 = RVar[5u].x;
        float _188 = RVar[0u].z;
        float _192 = (_188 * CBUFFER_1.values[12].y) + _154;
        float _194 = RVar[0u].y;
        RVar[123u].x = _178;
        RVar[126u].y = (_180 * _182) + _184;
        RVar[123u].w = _192;
        RVar[127u].w = float(floatBitsToInt(_194));
        float _208 = RVar[127u].x;
        RVar[127u].y = _192 * uintBitsToFloat(1132396544u);
        float _213 = RVar[127u].w;
        float _219 = RVar[127u].y;
        float _222 = RVar[126u].y;
        float _226 = inversesqrt(_222) * 0.5;
        RVar[0u].x = RVar[3u].x + ((_178 * uintBitsToFloat(1132396544u)) * (1.0 / _208));
        float _234 = RVar[3u].y;
        float _237 = RVar[2u].z;
        float _242 = RVar[2u].y;
        RVar[6u].x = (RVar[2u].x * _226) + uintBitsToFloat(1056964608u);
        RVar[0u].y = _234 + (_219 * (1.0 / _213));
        RVar[6u].z = (_237 * _226) + uintBitsToFloat(1056964608u);
        RVar[6u].y = (_242 * _226) + uintBitsToFloat(1056964608u);
    }
    if (stateVar == 0)
    {
        RVar[2u] = texture(tex_map0, vec4(RVar[0u].xy, 0.0, RVar[0u].x).xy);
    }
    if (stateVar == 0)
    {
        float _271 = RVar[2u].x;
        float _274 = clamp(_271 + uintBitsToFloat(0u), 0.0, 1.0);
        float _276 = RVar[0u].w;
        float _278 = RVar[2u].w;
        float _281 = (_276 * _278) + uintBitsToFloat(0u);
        float _283 = RVar[2u].z;
        float _286 = clamp(_283 + uintBitsToFloat(0u), 0.0, 1.0);
        float _288 = RVar[2u].y;
        float _291 = clamp(_288 + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[127u].x = _274;
        RVar[123u].y = _281;
        RVar[127u].z = _286;
        RVar[127u].w = _291;
        float _297 = RVar[1u].x;
        float _301 = RVar[1u].z;
        float _305 = RVar[1u].y;
        RVar[0u].w = clamp(_281 + uintBitsToFloat(0u), 0.0, 1.0);
        float _319 = RVar[1u].w;
        float _321 = RVar[127u].w;
        float _325 = RVar[1u].w;
        float _327 = RVar[127u].z;
        RVar[0u].x = ((_297 + (-_274)) * RVar[1u].w) + RVar[127u].x;
        RVar[0u].y = ((_305 + (-_291)) * _319) + _321;
        RVar[0u].z = ((_301 + (-_286)) * _325) + _327;
        float _336 = RVar[6u].y;
        float _338 = RVar[6u].z;
        float _340 = RVar[6u].w;
        RVar[2u].x = RVar[6u].x;
        RVar[2u].y = _336;
        RVar[2u].z = _338;
        RVar[2u].w = _340;
        float _348 = RVar[0u].y;
        float _350 = RVar[0u].z;
        float _352 = RVar[0u].w;
        RVar[1u].x = RVar[0u].x;
        RVar[1u].y = _348;
        RVar[1u].z = _350;
        RVar[1u].w = _352;
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
    uint _428 = PS_PUSH.alphaFunc >> 8u;
    if (_428 == 1u)
    {
        _pixelTmp = vec4(1.0);
    }
    else
    {
        if (_428 == 2u)
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
    uint _456 = PS_PUSH.alphaFunc >> 8u;
    if (_456 == 1u)
    {
        _pixelTmp_1 = vec4(1.0);
    }
    else
    {
        if (_456 == 2u)
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