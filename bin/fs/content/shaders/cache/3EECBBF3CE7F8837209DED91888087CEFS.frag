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
        float _228 = (clamp(_188 + uintBitsToFloat(0u), 0.0, 1.0) * CBUFFER_1.values[10].w) + uintBitsToFloat(0u);
        float _230 = RVar[127u].x;
        float _234 = RVar[126u].z;
        float _238 = RVar[127u].z;
        float _242 = RVar[2u].y;
        float _244 = RVar[2u].y;
        float _246 = (_242 * _244) + (_214 * _216);
        RVar[123u].x = _228;
        RVar[122u].x = _246;
        float _255 = (CBUFFER_1.values[4].z * clamp(clamp(_193 + uintBitsToFloat(0u), 0.0, 1.0) + _230, 0.0, 1.0)) + uintBitsToFloat(0u);
        float _260 = (CBUFFER_1.values[4].y * clamp(clamp(_176 + uintBitsToFloat(0u), 0.0, 1.0) + _234, 0.0, 1.0)) + uintBitsToFloat(0u);
        float _265 = (CBUFFER_1.values[4].x * clamp(clamp(_181 + uintBitsToFloat(0u), 0.0, 1.0) + _238, 0.0, 1.0)) + uintBitsToFloat(0u);
        float _267 = RVar[2u].x;
        float _269 = RVar[2u].x;
        float _271 = (_267 * _269) + _246;
        RVar[123u].x = _255;
        RVar[123u].y = _260;
        RVar[123u].z = _265;
        RVar[123u].w = _271;
        RVar[127u].w = clamp(_228 + uintBitsToFloat(0u), 0.0, 1.0);
        float _282 = clamp(_255 + uintBitsToFloat(0u), 0.0, 1.0);
        float _285 = clamp(_260 + uintBitsToFloat(0u), 0.0, 1.0);
        float _288 = clamp(_265 + uintBitsToFloat(0u), 0.0, 1.0);
        float _291 = inversesqrt(_271) * 0.5;
        RVar[127u].y = _282;
        RVar[127u].z = _285;
        RVar[126u].w = _288;
        RVar[127u].x = _291;
        float _297 = RVar[1u].x;
        float _307 = RVar[1u].z;
        float _311 = RVar[1u].y;
        float _315 = RVar[127u].w;
        RVar[3u].y = (RVar[2u].y * _291) + uintBitsToFloat(1056964608u);
        RVar[0u].w = clamp(_315 + uintBitsToFloat(0u), 0.0, 1.0);
        float _328 = RVar[1u].w;
        float _330 = RVar[127u].z;
        float _334 = RVar[1u].w;
        float _336 = RVar[127u].y;
        float _340 = RVar[2u].x;
        float _342 = RVar[127u].x;
        RVar[0u].x = ((_297 + (-_288)) * RVar[1u].w) + RVar[126u].w;
        RVar[0u].y = ((_311 + (-_285)) * _328) + _330;
        RVar[0u].z = ((_307 + (-_282)) * _334) + _336;
        RVar[3u].x = (_340 * _342) + uintBitsToFloat(1056964608u);
        float _351 = RVar[2u].z;
        float _353 = RVar[127u].x;
        float _356 = (_351 * _353) + uintBitsToFloat(1056964608u);
        RVar[3u].z = _356;
        float _361 = RVar[3u].y;
        float _363 = RVar[3u].w;
        RVar[2u].x = RVar[3u].x;
        RVar[2u].y = _361;
        RVar[2u].z = _356;
        RVar[2u].w = _363;
        float _371 = RVar[0u].y;
        float _373 = RVar[0u].z;
        float _375 = RVar[0u].w;
        RVar[1u].x = RVar[0u].x;
        RVar[1u].y = _371;
        RVar[1u].z = _373;
        RVar[1u].w = _375;
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
    _pixelTmp_1 = RVar[2u];
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