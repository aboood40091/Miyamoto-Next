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
        RVar[3u] = texture(tex_map0, vec4(RVar[3u].xy, 0.0, RVar[3u].x).xy);
        vec4 _96 = texture(tex_map2, vec4(RVar[5u].xy, 0.0, RVar[5u].x).xy);
        RVar[5u] = vec4(_96.x, _96.y, _96.z, RVar[5u].w);
    }
    if (stateVar == 0)
    {
        float _106 = RVar[0u].x;
        float _108 = RVar[4u].x;
        float _111 = (_106 * _108) + uintBitsToFloat(0u);
        float _113 = RVar[0u].w;
        float _119 = RVar[0u].z;
        float _121 = RVar[4u].z;
        float _124 = (_119 * _121) + uintBitsToFloat(0u);
        float _126 = RVar[0u].y;
        float _128 = RVar[4u].y;
        float _131 = (_126 * _128) + uintBitsToFloat(0u);
        float _133 = RVar[0u].x;
        float _135 = RVar[5u].x;
        RVar[123u].x = _111;
        RVar[127u].y = clamp(_113 + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[123u].z = _124;
        RVar[123u].w = _131;
        RVar[127u].z = (_133 * _135) + uintBitsToFloat(0u);
        float _163 = RVar[0u].z;
        float _165 = RVar[5u].z;
        RVar[126u].z = (RVar[0u].y * RVar[5u].y) + uintBitsToFloat(0u);
        RVar[127u].x = (_163 * _165) + uintBitsToFloat(0u);
        float _173 = RVar[3u].y;
        float _176 = (clamp(_131 + uintBitsToFloat(0u), 0.0, 1.0) * _173) + uintBitsToFloat(0u);
        float _178 = RVar[3u].x;
        float _181 = (clamp(_111 + uintBitsToFloat(0u), 0.0, 1.0) * _178) + uintBitsToFloat(0u);
        float _183 = RVar[127u].y;
        float _185 = RVar[3u].w;
        float _188 = (_183 * _185) + uintBitsToFloat(0u);
        float _190 = RVar[3u].z;
        float _193 = (clamp(_124 + uintBitsToFloat(0u), 0.0, 1.0) * _190) + uintBitsToFloat(0u);
        RVar[123u].x = _176;
        RVar[123u].y = _181;
        RVar[123u].z = _188;
        RVar[123u].w = _193;
        RVar[3u].w = uintBitsToFloat(1065353216u);
        float _214 = RVar[2u].z;
        float _216 = RVar[2u].z;
        float _219 = RVar[2u].y;
        float _221 = RVar[2u].y;
        float _223 = (_219 * _221) + (_214 * _216);
        float _225 = RVar[127u].x;
        float _227 = clamp(clamp(_193 + uintBitsToFloat(0u), 0.0, 1.0) + _225, 0.0, 1.0);
        float _229 = RVar[126u].z;
        float _231 = clamp(clamp(_176 + uintBitsToFloat(0u), 0.0, 1.0) + _229, 0.0, 1.0);
        float _233 = RVar[127u].z;
        float _235 = clamp(clamp(_181 + uintBitsToFloat(0u), 0.0, 1.0) + _233, 0.0, 1.0);
        RVar[123u].x = _223;
        RVar[127u].y = _227;
        RVar[127u].z = _231;
        RVar[127u].w = _235;
        RVar[0u].w = clamp(clamp(_188 + uintBitsToFloat(0u), 0.0, 1.0) + uintBitsToFloat(0u), 0.0, 1.0);
        float _245 = RVar[1u].x;
        float _249 = RVar[2u].x;
        float _251 = RVar[2u].x;
        float _253 = (_249 * _251) + _223;
        float _255 = RVar[1u].z;
        float _259 = RVar[1u].y;
        RVar[123u].y = _253;
        float _270 = RVar[1u].w;
        float _272 = RVar[127u].z;
        float _276 = RVar[1u].w;
        float _278 = RVar[127u].y;
        float _283 = inversesqrt(_253) * 0.5;
        RVar[0u].x = ((_245 + (-_235)) * RVar[1u].w) + RVar[127u].w;
        RVar[0u].y = ((_259 + (-_231)) * _270) + _272;
        RVar[0u].z = ((_255 + (-_227)) * _276) + _278;
        float _288 = RVar[2u].x;
        float _292 = (_288 * _283) + uintBitsToFloat(1056964608u);
        float _294 = RVar[2u].y;
        float _297 = (_294 * _283) + uintBitsToFloat(1056964608u);
        float _299 = RVar[2u].z;
        float _302 = (_299 * _283) + uintBitsToFloat(1056964608u);
        RVar[3u].x = _292;
        RVar[3u].y = _297;
        RVar[3u].z = _302;
        float _307 = RVar[3u].w;
        RVar[2u].x = _292;
        RVar[2u].y = _297;
        RVar[2u].z = _302;
        RVar[2u].w = _307;
        float _315 = RVar[0u].y;
        float _317 = RVar[0u].z;
        float _319 = RVar[0u].w;
        RVar[1u].x = RVar[0u].x;
        RVar[1u].y = _315;
        RVar[1u].z = _317;
        RVar[1u].w = _319;
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
    uint _395 = PS_PUSH.alphaFunc >> 8u;
    if (_395 == 1u)
    {
        _pixelTmp = vec4(1.0);
    }
    else
    {
        if (_395 == 2u)
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
    uint _423 = PS_PUSH.alphaFunc >> 8u;
    if (_423 == 1u)
    {
        _pixelTmp_1 = vec4(1.0);
    }
    else
    {
        if (_423 == 2u)
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