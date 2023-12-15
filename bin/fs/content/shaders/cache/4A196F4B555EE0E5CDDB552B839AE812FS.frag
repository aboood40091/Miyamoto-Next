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

uniform sampler2D tex_map0;
uniform sampler2D tex_map1;

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
        RVar[3u] = texture(tex_map0, vec4(RVar[3u].xy, 0.0, RVar[3u].x).xy);
        RVar[4u] = texture(tex_map1, vec4(RVar[4u].xy, 0.0, RVar[4u].x).xy);
    }
    if (stateVar == 0)
    {
        float _85 = RVar[3u].z;
        float _90 = (_85 * uintBitsToFloat(1065353216u)) + uintBitsToFloat(0u);
        float _92 = RVar[3u].y;
        float _96 = (_92 * uintBitsToFloat(1065353216u)) + uintBitsToFloat(0u);
        float _98 = RVar[3u].x;
        float _102 = (_98 * uintBitsToFloat(1065353216u)) + uintBitsToFloat(0u);
        float _115 = RVar[3u].w;
        float _120 = (_115 * CBUFFER_1.values[10].w) + uintBitsToFloat(0u);
        RVar[123u].x = _90;
        RVar[123u].y = _96;
        RVar[123u].z = _102;
        RVar[122u].x = _120;
        float _128 = RVar[4u].w;
        float _131 = (((-CBUFFER_1.values[10].w) + uintBitsToFloat(1065353216u)) * _128) + uintBitsToFloat(0u);
        RVar[123u].x = _131;
        float _147 = RVar[4u].y;
        float _150 = (clamp(_96 + uintBitsToFloat(0u), 0.0, 1.0) * _147) + uintBitsToFloat(0u);
        float _152 = RVar[4u].x;
        float _155 = (clamp(_102 + uintBitsToFloat(0u), 0.0, 1.0) * _152) + uintBitsToFloat(0u);
        float _159 = RVar[4u].z;
        float _162 = (clamp(_90 + uintBitsToFloat(0u), 0.0, 1.0) * _159) + uintBitsToFloat(0u);
        RVar[123u].x = _150;
        RVar[123u].y = _155;
        RVar[123u].w = _162;
        RVar[4u].w = uintBitsToFloat(1065353216u);
        float _170 = clamp(_162 + uintBitsToFloat(0u), 0.0, 1.0);
        float _173 = clamp(_150 + uintBitsToFloat(0u), 0.0, 1.0);
        float _176 = clamp(_155 + uintBitsToFloat(0u), 0.0, 1.0);
        float _178 = RVar[0u].w;
        float _181 = (_178 * clamp(clamp(_120 + uintBitsToFloat(0u), 0.0, 1.0) + _131, 0.0, 1.0)) + uintBitsToFloat(0u);
        float _183 = RVar[2u].z;
        float _185 = RVar[2u].z;
        RVar[127u].x = _170;
        RVar[127u].y = _173;
        RVar[127u].z = _176;
        RVar[123u].w = _181;
        float _205 = RVar[2u].y;
        float _207 = RVar[2u].y;
        float _209 = (_205 * _207) + (_183 * _185);
        RVar[122u].x = _209;
        float _216 = (CBUFFER_1.values[5].z * ((-_170) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        float _221 = (CBUFFER_1.values[5].y * ((-_173) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        float _226 = (CBUFFER_1.values[5].x * ((-_176) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        float _228 = RVar[2u].x;
        float _230 = RVar[2u].x;
        float _232 = (_228 * _230) + _209;
        RVar[123u].x = _216;
        RVar[123u].y = _221;
        RVar[123u].z = _226;
        RVar[123u].w = _232;
        RVar[3u].w = clamp(clamp(_181 + uintBitsToFloat(0u), 0.0, 1.0) + uintBitsToFloat(0u), 0.0, 1.0);
        float _245 = RVar[127u].x;
        float _248 = clamp((CBUFFER_1.values[4].z * _245) + _216, 0.0, 1.0);
        float _252 = RVar[127u].y;
        float _255 = clamp((CBUFFER_1.values[4].y * _252) + _221, 0.0, 1.0);
        float _259 = RVar[127u].z;
        float _262 = clamp((CBUFFER_1.values[4].x * _259) + _226, 0.0, 1.0);
        float _265 = inversesqrt(_232) * 0.5;
        RVar[123u].y = _248;
        RVar[123u].z = _255;
        RVar[123u].w = _262;
        RVar[127u].x = _265;
        float _271 = RVar[0u].z;
        float _274 = (_271 * _248) + uintBitsToFloat(0u);
        float _276 = RVar[0u].y;
        float _279 = (_276 * _255) + uintBitsToFloat(0u);
        float _281 = RVar[0u].x;
        float _284 = (_281 * _262) + uintBitsToFloat(0u);
        float _286 = RVar[2u].x;
        RVar[123u].x = _274;
        RVar[123u].y = _279;
        RVar[123u].z = _284;
        RVar[4u].x = (_286 * _265) + uintBitsToFloat(1056964608u);
        float _297 = clamp(_274 + uintBitsToFloat(0u), 0.0, 1.0);
        float _300 = clamp(_279 + uintBitsToFloat(0u), 0.0, 1.0);
        float _303 = clamp(_284 + uintBitsToFloat(0u), 0.0, 1.0);
        float _305 = RVar[2u].y;
        float _307 = RVar[127u].x;
        RVar[127u].y = _297;
        RVar[127u].z = _300;
        RVar[127u].w = _303;
        RVar[4u].y = (_305 * _307) + uintBitsToFloat(1056964608u);
        float _316 = RVar[1u].x;
        float _320 = RVar[1u].z;
        float _324 = RVar[1u].y;
        RVar[4u].z = (RVar[2u].z * RVar[127u].x) + uintBitsToFloat(1056964608u);
        float _342 = RVar[1u].w;
        float _344 = RVar[127u].z;
        float _348 = RVar[1u].w;
        float _350 = RVar[127u].y;
        RVar[3u].x = ((_316 + (-_303)) * RVar[1u].w) + RVar[127u].w;
        RVar[3u].y = ((_324 + (-_300)) * _342) + _344;
        RVar[3u].z = ((_320 + (-_297)) * _348) + _350;
        float _359 = RVar[4u].y;
        float _361 = RVar[4u].z;
        float _363 = RVar[4u].w;
        RVar[1u].x = RVar[4u].x;
        RVar[1u].y = _359;
        RVar[1u].z = _361;
        RVar[1u].w = _363;
        float _371 = RVar[3u].y;
        float _373 = RVar[3u].z;
        float _375 = RVar[3u].w;
        RVar[0u].x = RVar[3u].x;
        RVar[0u].y = _371;
        RVar[0u].z = _373;
        RVar[0u].w = _375;
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
    uint _451 = PS_PUSH.alphaFunc >> 8u;
    if (_451 == 1u)
    {
        _pixelTmp = vec4(1.0);
    }
    else
    {
        if (_451 == 2u)
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
    uint _479 = PS_PUSH.alphaFunc >> 8u;
    if (_479 == 1u)
    {
        _pixelTmp_1 = vec4(1.0);
    }
    else
    {
        if (_479 == 2u)
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