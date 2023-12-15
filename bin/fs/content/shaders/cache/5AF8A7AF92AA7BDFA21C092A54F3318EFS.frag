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
uniform sampler2D tex_map3;

layout(location = 2) in vec4 PARAM_2;
layout(location = 1) in vec4 PARAM_1;
layout(location = 0) in vec4 PARAM_0;
layout(location = 3) in vec4 PARAM_3;
layout(location = 4) in vec4 PARAM_4;
layout(location = 5) in vec4 PARAM_5;
layout(location = 6) in vec4 PARAM_6;
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
    RVar[6u] = PARAM_6;
    if (stateVar == 0)
    {
        vec4 _72 = texture(tex_map2, vec4(RVar[5u].xy, 0.0, RVar[5u].x).xy);
        RVar[5u] = vec4(_72.x, _72.y, _72.z, RVar[5u].w);
        RVar[3u] = texture(tex_map0, vec4(RVar[3u].xy, 0.0, RVar[3u].x).xy);
        vec4 _100 = texture(tex_map1, vec4(RVar[4u].xy, 0.0, RVar[4u].x).xy);
        RVar[4u] = vec4(_100.x, _100.y, _100.z, RVar[4u].w);
        vec4 _115 = texture(tex_map3, vec4(RVar[6u].xy, 0.0, RVar[6u].x).xy);
        RVar[6u] = vec4(_115.x, _115.y, _115.z, RVar[6u].w);
    }
    if (stateVar == 0)
    {
        float _125 = RVar[0u].w;
        float _131 = RVar[0u].z;
        float _133 = RVar[5u].z;
        float _136 = (_131 * _133) + uintBitsToFloat(0u);
        float _138 = RVar[0u].y;
        float _140 = RVar[5u].y;
        float _143 = (_138 * _140) + uintBitsToFloat(0u);
        float _145 = RVar[0u].x;
        float _147 = RVar[5u].x;
        float _150 = (_145 * _147) + uintBitsToFloat(0u);
        float _152 = RVar[6u].x;
        RVar[123u].y = _136;
        RVar[123u].z = _143;
        RVar[123u].w = _150;
        RVar[126u].y = (-_152) + uintBitsToFloat(1065353216u);
        float _167 = RVar[3u].w;
        float _170 = (clamp(_125 + uintBitsToFloat(0u), 0.0, 1.0) * _167) + uintBitsToFloat(0u);
        float _178 = RVar[6u].y;
        RVar[123u].y = _170;
        RVar[127u].x = (-_178) + uintBitsToFloat(1065353216u);
        float _186 = RVar[3u].x;
        float _189 = (clamp(_150 + uintBitsToFloat(0u), 0.0, 1.0) * _186) + uintBitsToFloat(0u);
        float _191 = RVar[6u].z;
        float _196 = RVar[3u].z;
        float _199 = (clamp(_136 + uintBitsToFloat(0u), 0.0, 1.0) * _196) + uintBitsToFloat(0u);
        float _201 = RVar[3u].y;
        float _204 = (clamp(_143 + uintBitsToFloat(0u), 0.0, 1.0) * _201) + uintBitsToFloat(0u);
        float _207 = clamp(_170 + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[123u].x = _189;
        RVar[125u].y = (-_191) + uintBitsToFloat(1065353216u);
        RVar[123u].z = _199;
        RVar[123u].w = _204;
        RVar[127u].y = _207;
        float _230 = (_207 * CBUFFER_1.values[10].w) + uintBitsToFloat(0u);
        RVar[123u].z = _230;
        RVar[3u].w = uintBitsToFloat(1065353216u);
        float _238 = RVar[4u].x;
        float _241 = (clamp(_189 + uintBitsToFloat(0u), 0.0, 1.0) * _238) + uintBitsToFloat(0u);
        float _243 = RVar[127u].y;
        float _247 = RVar[4u].z;
        float _250 = (clamp(_199 + uintBitsToFloat(0u), 0.0, 1.0) * _247) + uintBitsToFloat(0u);
        float _252 = RVar[4u].y;
        float _255 = (clamp(_204 + uintBitsToFloat(0u), 0.0, 1.0) * _252) + uintBitsToFloat(0u);
        float _257 = RVar[2u].z;
        float _259 = RVar[2u].z;
        RVar[123u].x = _241;
        RVar[127u].y = clamp(_243 + _230, 0.0, 1.0);
        RVar[123u].z = _250;
        RVar[123u].w = _255;
        float _275 = RVar[2u].y;
        float _277 = RVar[2u].y;
        float _279 = (_275 * _277) + (_257 * _259);
        RVar[122u].x = _279;
        float _283 = RVar[125u].y;
        float _288 = (clamp(_250 + uintBitsToFloat(0u), 0.0, 1.0) * _283) + CBUFFER_1.values[7].z;
        float _290 = RVar[127u].x;
        float _294 = (clamp(_255 + uintBitsToFloat(0u), 0.0, 1.0) * _290) + CBUFFER_1.values[7].y;
        float _296 = RVar[126u].y;
        float _300 = (clamp(_241 + uintBitsToFloat(0u), 0.0, 1.0) * _296) + CBUFFER_1.values[7].x;
        float _302 = RVar[2u].x;
        float _304 = RVar[2u].x;
        float _306 = (_302 * _304) + _279;
        float _308 = RVar[127u].y;
        RVar[123u].x = _288;
        RVar[123u].y = _294;
        RVar[123u].z = _300;
        RVar[123u].w = _306;
        RVar[4u].w = clamp(_308 + uintBitsToFloat(0u), 0.0, 1.0);
        float _318 = RVar[0u].z;
        float _320 = RVar[6u].z;
        float _323 = clamp((_318 * _320) + _288, 0.0, 1.0);
        float _325 = RVar[0u].y;
        float _327 = RVar[6u].y;
        float _330 = clamp((_325 * _327) + _294, 0.0, 1.0);
        float _332 = RVar[0u].x;
        float _334 = RVar[6u].x;
        float _337 = clamp((_332 * _334) + _300, 0.0, 1.0);
        float _340 = inversesqrt(_306) * 0.5;
        RVar[127u].y = _323;
        RVar[127u].z = _330;
        RVar[127u].w = _337;
        RVar[127u].x = _340;
        float _346 = RVar[1u].x;
        float _356 = RVar[1u].z;
        float _360 = RVar[1u].y;
        float _364 = RVar[2u].x;
        RVar[3u].y = (RVar[2u].y * _340) + uintBitsToFloat(1056964608u);
        RVar[3u].x = (_364 * _340) + uintBitsToFloat(1056964608u);
        float _377 = RVar[1u].w;
        float _379 = RVar[127u].z;
        float _383 = RVar[1u].w;
        float _385 = RVar[127u].y;
        float _389 = RVar[2u].z;
        float _391 = RVar[127u].x;
        float _394 = (_389 * _391) + uintBitsToFloat(1056964608u);
        RVar[4u].x = ((_346 + (-_337)) * RVar[1u].w) + RVar[127u].w;
        RVar[4u].y = ((_360 + (-_330)) * _377) + _379;
        RVar[4u].z = ((_356 + (-_323)) * _383) + _385;
        RVar[3u].z = _394;
        float _402 = RVar[3u].y;
        float _404 = RVar[3u].w;
        RVar[1u].x = RVar[3u].x;
        RVar[1u].y = _402;
        RVar[1u].z = _394;
        RVar[1u].w = _404;
        float _412 = RVar[4u].y;
        float _414 = RVar[4u].z;
        float _416 = RVar[4u].w;
        RVar[0u].x = RVar[4u].x;
        RVar[0u].y = _412;
        RVar[0u].z = _414;
        RVar[0u].w = _416;
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
    uint _492 = PS_PUSH.alphaFunc >> 8u;
    if (_492 == 1u)
    {
        _pixelTmp = vec4(1.0);
    }
    else
    {
        if (_492 == 2u)
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
    uint _520 = PS_PUSH.alphaFunc >> 8u;
    if (_520 == 1u)
    {
        _pixelTmp_1 = vec4(1.0);
    }
    else
    {
        if (_520 == 2u)
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