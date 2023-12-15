#version 410

layout(std140) uniform Shp
{
    vec4 values[4];
} CBUFFER_1;

layout(std140) uniform MdlMtx
{
    vec4 values[192];
} CBUFFER_2;

layout(std140) uniform MdlEnvView
{
    vec4 values[49];
} CBUFFER_3;

layout(std140) uniform Mat
{
    vec4 values[10];
} CBUFFER_4;

struct VS_PUSH_CONSTANTS
{
    vec4 posMulAdd;
    vec4 zSpaceMul;
    float pointSize;
};

uniform VS_PUSH_CONSTANTS VS_PUSH;

layout(location = 0) out vec4 PARAM_0;
layout(location = 1) out vec4 PARAM_1;
layout(location = 2) out vec4 PARAM_2;
layout(location = 0) in uvec4 aBlendIndex_0_0;
layout(location = 1) in uvec4 aBlendWeight_0_0;
layout(location = 2) in uvec3 aNormal_0_0;
layout(location = 3) in uvec3 aPosition_0_0;
layout(location = 4) in uvec2 aTexCoord0_0_0;
int stackIdxVar;
int stateVar;
vec4 RVar[128];
int stackVar[16];
bool predVar;

void fs_main()
{
    if (stateVar == 0)
    {
        RVar[1u] = intBitsToFloat(ivec4(int(aBlendIndex_0_0.x), int(aBlendIndex_0_0.y), int(aBlendIndex_0_0.z), int(aBlendIndex_0_0.w)));
        RVar[2u] = vec4(uintBitsToFloat(aBlendWeight_0_0.x), uintBitsToFloat(aBlendWeight_0_0.y), uintBitsToFloat(aBlendWeight_0_0.z), uintBitsToFloat(aBlendWeight_0_0.w));
        RVar[3u] = vec4(vec4(uintBitsToFloat(aNormal_0_0.x), uintBitsToFloat(aNormal_0_0.y), uintBitsToFloat(aNormal_0_0.z), 1.0).xyz, 1.0);
        RVar[4u] = vec4(vec4(uintBitsToFloat(aPosition_0_0.x), uintBitsToFloat(aPosition_0_0.y), uintBitsToFloat(aPosition_0_0.z), 1.0).xyz, 1.0);
        RVar[5u] = vec4(vec4(uintBitsToFloat(aTexCoord0_0_0.x), uintBitsToFloat(aTexCoord0_0_0.y), 0.0, 1.0).xy, 0.0, 1.0);
    }
    if (stateVar == 0)
    {
        return;
    }
}

void main()
{
    stackIdxVar = 0;
    stateVar = 0;
    RVar[0u] = vec4(intBitsToFloat(gl_VertexID - floatBitsToInt(VS_PUSH.zSpaceMul.z)), intBitsToFloat(gl_InstanceID - floatBitsToInt(VS_PUSH.zSpaceMul.w)), 0.0, 0.0);
    fs_main();
    stackVar[stackIdxVar] = stateVar;
    stackIdxVar++;
    if (stateVar == 0)
    {
        RVar[6u].x = uintBitsToFloat(0u);
        RVar[6u].y = uintBitsToFloat(0u);
        RVar[6u].z = uintBitsToFloat(0u);
        RVar[0u].w = intBitsToFloat((floatBitsToInt(CBUFFER_1.values[3].x) != (0)) ? (-1) : 0);
        bool _90 = floatBitsToInt(RVar[0u].w) == (0);
        predVar = _90;
        stateVar = _90 ? 0 : 1;
    }
    if (stateVar == 0)
    {
        float _123 = RVar[3u].z;
        RVar[127u].y = dot(vec4(RVar[4u].x, RVar[4u].y, RVar[4u].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_2.values[0].x, CBUFFER_2.values[0].y, CBUFFER_2.values[0].z, uintBitsToFloat(0u)));
        RVar[126u].x = _123 * CBUFFER_2.values[0].z;
        RVar[127u].x = dot(vec4(RVar[4u].x, RVar[4u].y, RVar[4u].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_2.values[1].x, CBUFFER_2.values[1].y, CBUFFER_2.values[1].z, uintBitsToFloat(0u)));
        RVar[127u].w = dot(vec4(RVar[4u].x, RVar[4u].y, RVar[4u].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_2.values[2].x, CBUFFER_2.values[2].y, CBUFFER_2.values[2].z, uintBitsToFloat(0u)));
        float _175 = RVar[127u].x;
        RVar[19u].x = CBUFFER_2.values[0].w + RVar[127u].y;
        RVar[19u].y = CBUFFER_2.values[1].w + _175;
        float _181 = RVar[3u].y;
        float _185 = RVar[126u].x;
        float _187 = (_181 * CBUFFER_2.values[0].y) + _185;
        float _191 = RVar[127u].w;
        RVar[123u].x = _187;
        RVar[19u].z = CBUFFER_2.values[2].w + _191;
        float _203 = RVar[3u].z;
        RVar[6u].x = (RVar[3u].x * CBUFFER_2.values[0].x) + _187;
        float _224 = RVar[3u].z;
        RVar[6u].y = dot(vec4(RVar[3u].x, RVar[3u].y, _203 * CBUFFER_2.values[1].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_2.values[1].x, CBUFFER_2.values[1].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[6u].z = dot(vec4(RVar[3u].x, RVar[3u].y, _224 * CBUFFER_2.values[2].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_2.values[2].x, CBUFFER_2.values[2].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
    }
    if (stackVar[stackIdxVar - 1] == 0)
    {
        stateVar = int(stateVar == 0);
    }
    stackVar[stackIdxVar] = stateVar;
    stackIdxVar++;
    if (stateVar == 0)
    {
        RVar[0u].w = intBitsToFloat((floatBitsToInt(CBUFFER_1.values[3].x) != (1)) ? (-1) : 0);
        bool _274 = floatBitsToInt(RVar[0u].w) == (0);
        predVar = _274;
        stateVar = _274 ? 0 : 1;
    }
    if (stateVar == 0)
    {
        float _283 = RVar[1u].x;
        float _287 = intBitsToFloat(floatBitsToInt(_283) * (3));
        RVar[1u].x = _287;
        RVar[0u].x = intBitsToFloat(floatBitsToInt(_287) + (2));
        RVar[1u].z = intBitsToFloat(floatBitsToInt(_287) + (1));
    }
    if (stateVar == 0)
    {
        RVar[2u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].x)];
        RVar[1u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].z)];
        RVar[0u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].x)];
    }
    if (stateVar == 0)
    {
        float _327 = RVar[4u].x;
        float _329 = RVar[4u].y;
        float _331 = RVar[4u].z;
        float _335 = RVar[2u].x;
        float _337 = RVar[2u].y;
        float _339 = RVar[2u].z;
        RVar[127u].x = RVar[3u].z * RVar[2u].z;
        float _350 = RVar[4u].x;
        float _352 = RVar[4u].y;
        float _354 = RVar[4u].z;
        float _358 = RVar[1u].x;
        float _360 = RVar[1u].y;
        float _362 = RVar[1u].z;
        RVar[19u].x = RVar[2u].w + dot(vec4(_327, _329, _331, uintBitsToFloat(2147483648u)), vec4(_335, _337, _339, uintBitsToFloat(0u)));
        float _371 = RVar[4u].x;
        float _373 = RVar[4u].y;
        float _375 = RVar[4u].z;
        float _379 = RVar[0u].x;
        float _381 = RVar[0u].y;
        float _383 = RVar[0u].z;
        RVar[19u].y = RVar[1u].w + dot(vec4(_350, _352, _354, uintBitsToFloat(2147483648u)), vec4(_358, _360, _362, uintBitsToFloat(0u)));
        float _392 = RVar[3u].y;
        float _394 = RVar[2u].y;
        float _396 = RVar[127u].x;
        float _398 = (_392 * _394) + _396;
        float _400 = RVar[0u].w;
        RVar[123u].x = _398;
        RVar[19u].z = _400 + dot(vec4(_371, _373, _375, uintBitsToFloat(2147483648u)), vec4(_379, _381, _383, uintBitsToFloat(0u)));
        float _411 = RVar[3u].z;
        float _413 = RVar[1u].z;
        RVar[6u].x = (RVar[3u].x * RVar[2u].x) + _398;
        float _431 = RVar[3u].z;
        float _433 = RVar[0u].z;
        RVar[6u].y = dot(vec4(RVar[3u].x, RVar[3u].y, _411 * _413, uintBitsToFloat(2147483648u)), vec4(RVar[1u].x, RVar[1u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[6u].z = dot(vec4(RVar[3u].x, RVar[3u].y, _431 * _433, uintBitsToFloat(2147483648u)), vec4(RVar[0u].x, RVar[0u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
    }
    if (stackVar[stackIdxVar - 1] == 0)
    {
        stateVar = int(stateVar == 0);
    }
    stackVar[stackIdxVar] = stateVar;
    stackIdxVar++;
    if (stateVar == 0)
    {
        RVar[0u].w = intBitsToFloat((floatBitsToInt(CBUFFER_1.values[3].x) != (4)) ? (-1) : 0);
        bool _482 = floatBitsToInt(RVar[0u].w) == (0);
        predVar = _482;
        stateVar = _482 ? 0 : 1;
    }
    if (stateVar == 0)
    {
        float _491 = RVar[1u].x;
        float _495 = intBitsToFloat(floatBitsToInt(_491) * (3));
        RVar[0u].x = _495;
        float _506 = RVar[1u].y;
        float _510 = intBitsToFloat(floatBitsToInt(_506) * (3));
        RVar[0u].z = intBitsToFloat(floatBitsToInt(_495) + (2));
        RVar[0u].w = intBitsToFloat(floatBitsToInt(_495) + (1));
        RVar[3u].w = _510;
        float _523 = RVar[1u].z;
        float _527 = intBitsToFloat(floatBitsToInt(_523) * (3));
        RVar[0u].y = intBitsToFloat(floatBitsToInt(_510) + (2));
        RVar[6u].z = intBitsToFloat(floatBitsToInt(_510) + (1));
        RVar[7u].z = _527;
        float _541 = RVar[1u].w;
        RVar[1u].x = intBitsToFloat(floatBitsToInt(_527) + (2));
        RVar[1u].y = intBitsToFloat(floatBitsToInt(_527) + (1));
        RVar[6u].y = intBitsToFloat(floatBitsToInt(_541) * (3));
    }
    if (stateVar == 0)
    {
        RVar[8u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].x)];
        RVar[10u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].w)];
        RVar[9u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].z)];
        RVar[11u] = CBUFFER_2.values[floatBitsToUint(RVar[3u].w)];
        RVar[13u] = CBUFFER_2.values[floatBitsToUint(RVar[6u].z)];
        RVar[12u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].y)];
        RVar[15u] = CBUFFER_2.values[floatBitsToUint(RVar[7u].z)];
        RVar[14u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].y)];
    }
    if (stateVar == 0)
    {
        float _620 = RVar[6u].y;
        float _626 = RVar[3u].z;
        float _628 = RVar[10u].z;
        float _631 = RVar[3u].y;
        float _633 = RVar[9u].y;
        float _636 = RVar[3u].z;
        float _638 = RVar[8u].z;
        RVar[0u].x = intBitsToFloat(floatBitsToInt(RVar[6u].y) + (2));
        RVar[1u].y = intBitsToFloat(floatBitsToInt(_620) + (1));
        RVar[7u].z = _626 * _628;
        RVar[0u].w = _631 * _633;
        float _662 = RVar[3u].y;
        float _664 = RVar[8u].y;
        RVar[3u].w = dot(vec4(RVar[4u].x, RVar[4u].y, RVar[4u].z, uintBitsToFloat(2147483648u)), vec4(RVar[8u].x, RVar[8u].y, RVar[8u].z, uintBitsToFloat(0u)));
        RVar[6u].x = (_662 * _664) + (_636 * _638);
    }
    if (stateVar == 0)
    {
        RVar[16u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].x)];
        RVar[17u] = CBUFFER_2.values[floatBitsToUint(RVar[6u].y)];
        RVar[18u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].y)];
        RVar[1u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].x)];
    }
    if (stateVar == 0)
    {
        float _704 = RVar[4u].x;
        float _706 = RVar[4u].y;
        float _708 = RVar[4u].z;
        float _712 = RVar[10u].x;
        float _714 = RVar[10u].y;
        float _716 = RVar[10u].z;
        RVar[127u].z = RVar[8u].w + RVar[3u].w;
        float _727 = RVar[4u].x;
        float _729 = RVar[4u].y;
        float _731 = RVar[4u].z;
        float _735 = RVar[9u].x;
        float _737 = RVar[9u].y;
        float _739 = RVar[9u].z;
        float _744 = RVar[10u].w;
        float _747 = RVar[9u].w;
        float _755 = RVar[2u].x;
        float _758 = RVar[3u].x;
        float _760 = RVar[9u].x;
        float _762 = RVar[0u].w;
        float _766 = RVar[3u].y;
        float _768 = RVar[10u].y;
        float _770 = RVar[7u].z;
        RVar[127u].y = RVar[2u].x * RVar[127u].z;
        RVar[127u].z = _755 * (_744 + dot(vec4(_704, _706, _708, uintBitsToFloat(2147483648u)), vec4(_712, _714, _716, uintBitsToFloat(0u))));
        RVar[125u].w = (_758 * _760) + _762;
        RVar[124u].x = (_766 * _768) + _770;
        float _780 = RVar[4u].x;
        float _782 = RVar[4u].y;
        float _784 = RVar[4u].z;
        float _788 = RVar[11u].x;
        float _790 = RVar[11u].y;
        float _792 = RVar[11u].z;
        RVar[127u].w = RVar[2u].x * (_747 + dot(vec4(_727, _729, _731, uintBitsToFloat(2147483648u)), vec4(_735, _737, _739, uintBitsToFloat(0u))));
        float _801 = RVar[4u].x;
        float _803 = RVar[4u].y;
        float _805 = RVar[4u].z;
        float _809 = RVar[13u].x;
        float _811 = RVar[13u].y;
        float _813 = RVar[13u].z;
        RVar[126u].y = RVar[11u].w + dot(vec4(_780, _782, _784, uintBitsToFloat(2147483648u)), vec4(_788, _790, _792, uintBitsToFloat(0u)));
        float _822 = RVar[4u].x;
        float _824 = RVar[4u].y;
        float _826 = RVar[4u].z;
        float _830 = RVar[12u].x;
        float _832 = RVar[12u].y;
        float _834 = RVar[12u].z;
        RVar[127u].x = RVar[13u].w + dot(vec4(_801, _803, _805, uintBitsToFloat(2147483648u)), vec4(_809, _811, _813, uintBitsToFloat(0u)));
        float _847 = RVar[127u].z;
        float _851 = RVar[127u].w;
        float _855 = RVar[12u].w;
        float _858 = RVar[2u].y;
        float _860 = RVar[126u].y;
        RVar[126u].x = RVar[127u].y + uintBitsToFloat(0u);
        RVar[127u].y = _847 + uintBitsToFloat(0u);
        RVar[127u].z = _851 + uintBitsToFloat(0u);
        RVar[127u].w = _855 + dot(vec4(_822, _824, _826, uintBitsToFloat(2147483648u)), vec4(_830, _832, _834, uintBitsToFloat(0u)));
        RVar[125u].x = _858 * _860;
        float _868 = RVar[4u].x;
        float _870 = RVar[4u].y;
        float _872 = RVar[4u].z;
        float _876 = RVar[15u].x;
        float _878 = RVar[15u].y;
        float _880 = RVar[15u].z;
        RVar[126u].w = RVar[2u].y * RVar[127u].x;
        float _891 = RVar[4u].x;
        float _893 = RVar[4u].y;
        float _895 = RVar[4u].z;
        float _899 = RVar[14u].x;
        float _901 = RVar[14u].y;
        float _903 = RVar[14u].z;
        RVar[127u].x = RVar[15u].w + dot(vec4(_868, _870, _872, uintBitsToFloat(2147483648u)), vec4(_876, _878, _880, uintBitsToFloat(0u)));
        float _912 = RVar[4u].x;
        float _914 = RVar[4u].y;
        float _916 = RVar[4u].z;
        float _920 = RVar[16u].x;
        float _922 = RVar[16u].y;
        float _924 = RVar[16u].z;
        float _929 = RVar[14u].w;
        float _937 = RVar[2u].z;
        float _939 = RVar[127u].x;
        float _942 = RVar[16u].w;
        float _945 = RVar[126u].x;
        float _947 = RVar[125u].x;
        float _950 = RVar[2u].z;
        RVar[127u].x = RVar[2u].y * RVar[127u].w;
        RVar[126u].y = _937 * _939;
        RVar[126u].z = _942 + dot(vec4(_912, _914, _916, uintBitsToFloat(2147483648u)), vec4(_920, _922, _924, uintBitsToFloat(0u)));
        RVar[127u].w = _945 + _947;
        RVar[124u].z = _950 * (_929 + dot(vec4(_891, _893, _895, uintBitsToFloat(2147483648u)), vec4(_899, _901, _903, uintBitsToFloat(0u))));
        float _975 = RVar[127u].y;
        float _977 = RVar[126u].w;
        RVar[126u].x = dot(vec4(RVar[4u].x, RVar[4u].y, RVar[4u].z, uintBitsToFloat(2147483648u)), vec4(RVar[17u].x, RVar[17u].y, RVar[17u].z, uintBitsToFloat(0u)));
        RVar[125u].z = _975 + _977;
        float _999 = RVar[127u].z;
        float _1001 = RVar[127u].x;
        RVar[127u].x = dot(vec4(RVar[4u].x, RVar[4u].y, RVar[4u].z, uintBitsToFloat(2147483648u)), vec4(RVar[18u].x, RVar[18u].y, RVar[18u].z, uintBitsToFloat(0u)));
        RVar[127u].y = _999 + _1001;
        float _1006 = RVar[4u].x;
        float _1008 = RVar[4u].y;
        float _1010 = RVar[4u].z;
        float _1014 = RVar[1u].x;
        float _1016 = RVar[1u].y;
        float _1018 = RVar[1u].z;
        RVar[126u].w = RVar[17u].w + RVar[126u].x;
        float _1029 = RVar[1u].w;
        float _1032 = RVar[2u].z;
        float _1034 = RVar[126u].z;
        float _1042 = RVar[18u].w;
        float _1044 = RVar[127u].x;
        float _1047 = RVar[3u].y;
        float _1049 = RVar[11u].y;
        RVar[126u].z = RVar[127u].w + RVar[126u].y;
        RVar[127u].x = _1047 * _1049;
        float _1054 = RVar[127u].y;
        float _1057 = RVar[125u].z;
        float _1059 = RVar[124u].z;
        float _1067 = RVar[2u].w;
        float _1070 = RVar[2u].w;
        float _1078 = RVar[3u].x;
        float _1080 = RVar[8u].x;
        float _1082 = RVar[6u].x;
        float _1086 = RVar[3u].z;
        float _1088 = RVar[9u].z;
        float _1090 = RVar[125u].w;
        RVar[19u].x = RVar[126u].z + (RVar[2u].w * RVar[126u].w);
        RVar[19u].y = (_1057 + _1059) + (_1067 * (_1042 + _1044));
        RVar[19u].z = (_1054 + (_1032 * _1034)) + (_1070 * (_1029 + dot(vec4(_1006, _1008, _1010, uintBitsToFloat(2147483648u)), vec4(_1014, _1016, _1018, uintBitsToFloat(0u)))));
        RVar[125u].w = (_1078 * _1080) + _1082;
        RVar[126u].y = (_1086 * _1088) + _1090;
        float _1099 = RVar[3u].z;
        float _1101 = RVar[13u].z;
        float _1109 = RVar[3u].y;
        float _1111 = RVar[14u].y;
        float _1114 = RVar[3u].x;
        float _1116 = RVar[10u].x;
        float _1118 = RVar[124u].x;
        float _1122 = RVar[3u].z;
        float _1124 = RVar[12u].z;
        RVar[127u].y = RVar[3u].y * RVar[15u].y;
        RVar[126u].z = _1109 * _1111;
        RVar[126u].w = (_1114 * _1116) + _1118;
        RVar[124u].x = _1122 * _1124;
        float _1147 = RVar[3u].y;
        float _1149 = RVar[13u].y;
        RVar[11u].x = dot(vec4(RVar[3u].x, RVar[3u].z, RVar[127u].x, uintBitsToFloat(2147483648u)), vec4(RVar[11u].x, RVar[11u].z, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[127u].x = (_1147 * _1149) + (_1099 * _1101);
        float _1171 = RVar[3u].z;
        float _1173 = RVar[15u].z;
        float _1175 = RVar[127u].y;
        RVar[12u].x = dot(vec4(RVar[3u].x, RVar[3u].y, RVar[124u].x, uintBitsToFloat(2147483648u)), vec4(RVar[12u].x, RVar[12u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[10u].x = (_1171 * _1173) + _1175;
        float _1181 = RVar[3u].z;
        float _1183 = RVar[14u].z;
        float _1185 = RVar[126u].z;
        float _1187 = (_1181 * _1183) + _1185;
        float _1189 = RVar[3u].y;
        float _1191 = RVar[17u].y;
        float _1194 = RVar[3u].x;
        float _1196 = RVar[13u].x;
        float _1198 = RVar[127u].x;
        float _1202 = RVar[3u].y;
        float _1204 = RVar[16u].y;
        RVar[123u].x = _1187;
        RVar[13u].y = _1189 * _1191;
        RVar[13u].z = (_1194 * _1196) + _1198;
        float _1217 = RVar[2u].x;
        float _1219 = RVar[126u].y;
        float _1224 = RVar[2u].x;
        float _1226 = RVar[126u].w;
        float _1231 = RVar[3u].x;
        float _1233 = RVar[14u].x;
        float _1237 = RVar[3u].z;
        float _1239 = RVar[16u].z;
        RVar[14u].x = (RVar[2u].x * RVar[125u].w) + uintBitsToFloat(0u);
        RVar[14u].y = (_1217 * _1219) + uintBitsToFloat(0u);
        RVar[14u].z = (_1224 * _1226) + uintBitsToFloat(0u);
        RVar[14u].w = (_1231 * _1233) + _1187;
        RVar[13u].x = (_1237 * _1239) + (_1202 * _1204);
    }
    if (stateVar == 0)
    {
        float _1260 = RVar[2u].y;
        float _1262 = RVar[13u].z;
        float _1264 = RVar[14u].z;
        float _1266 = (_1260 * _1262) + _1264;
        float _1268 = RVar[2u].y;
        float _1270 = RVar[11u].x;
        float _1272 = RVar[14u].x;
        RVar[127u].x = (RVar[2u].y * RVar[12u].x) + RVar[14u].y;
        RVar[123u].y = _1266;
        RVar[126u].w = (_1268 * _1270) + _1272;
        float _1287 = RVar[2u].z;
        float _1289 = RVar[14u].w;
        float _1293 = RVar[3u].x;
        float _1295 = RVar[15u].x;
        float _1297 = RVar[10u].x;
        float _1299 = (_1293 * _1295) + _1297;
        float _1301 = RVar[3u].y;
        float _1303 = RVar[18u].y;
        RVar[124u].x = (RVar[3u].z * RVar[17u].z) + RVar[13u].y;
        RVar[126u].y = (_1287 * _1289) + _1266;
        RVar[123u].w = _1299;
        float _1315 = RVar[2u].z;
        float _1317 = RVar[126u].w;
        float _1321 = RVar[3u].x;
        float _1323 = RVar[16u].x;
        float _1325 = RVar[13u].x;
        float _1327 = (_1321 * _1323) + _1325;
        float _1329 = RVar[3u].y;
        float _1331 = RVar[1u].y;
        RVar[126u].x = (RVar[3u].z * RVar[18u].z) + (_1301 * _1303);
        RVar[126u].z = (_1315 * _1299) + _1317;
        RVar[123u].w = _1327;
        float _1351 = RVar[2u].z;
        float _1353 = RVar[127u].x;
        RVar[127u].x = dot(vec4(RVar[3u].x, RVar[3u].z, _1329 * _1331, uintBitsToFloat(2147483648u)), vec4(RVar[1u].x, RVar[1u].z, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[125u].z = (_1351 * _1327) + _1353;
        float _1359 = RVar[3u].x;
        float _1361 = RVar[17u].x;
        float _1363 = RVar[124u].x;
        float _1365 = (_1359 * _1361) + _1363;
        RVar[123u].y = _1365;
        float _1374 = RVar[3u].x;
        float _1376 = RVar[18u].x;
        float _1378 = RVar[126u].x;
        float _1380 = (_1374 * _1376) + _1378;
        RVar[6u].x = (RVar[2u].w * _1365) + RVar[126u].z;
        RVar[123u].w = _1380;
        float _1390 = RVar[2u].w;
        float _1392 = RVar[127u].x;
        float _1394 = RVar[125u].z;
        RVar[6u].y = (RVar[2u].w * _1380) + RVar[126u].y;
        RVar[6u].z = (_1390 * _1392) + _1394;
    }
    if (stackVar[stackIdxVar - 1] == 0)
    {
        stateVar = int(stateVar == 0);
    }
    stackVar[stackIdxVar] = stateVar;
    stackIdxVar++;
    if (stateVar == 0)
    {
        RVar[0u].w = intBitsToFloat((floatBitsToInt(CBUFFER_1.values[3].x) != (3)) ? (-1) : 0);
        bool _1429 = floatBitsToInt(RVar[0u].w) == (0);
        predVar = _1429;
        stateVar = _1429 ? 0 : 1;
    }
    if (stateVar == 0)
    {
        float _1438 = RVar[1u].x;
        float _1442 = intBitsToFloat(floatBitsToInt(_1438) * (3));
        RVar[0u].w = _1442;
        float _1453 = RVar[1u].y;
        float _1457 = intBitsToFloat(floatBitsToInt(_1453) * (3));
        RVar[0u].y = intBitsToFloat(floatBitsToInt(_1442) + (2));
        RVar[0u].z = intBitsToFloat(floatBitsToInt(_1442) + (1));
        RVar[6u].z = _1457;
        float _1470 = RVar[1u].z;
        float _1474 = intBitsToFloat(floatBitsToInt(_1470) * (3));
        RVar[1u].x = intBitsToFloat(floatBitsToInt(_1457) + (2));
        RVar[1u].y = intBitsToFloat(floatBitsToInt(_1457) + (1));
        RVar[6u].y = _1474;
        RVar[0u].x = intBitsToFloat(floatBitsToInt(_1474) + (2));
        RVar[7u].y = intBitsToFloat(floatBitsToInt(_1474) + (1));
    }
    if (stateVar == 0)
    {
        RVar[8u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].w)];
        RVar[9u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].z)];
        RVar[10u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].y)];
        RVar[11u] = CBUFFER_2.values[floatBitsToUint(RVar[6u].z)];
        RVar[13u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].y)];
        RVar[12u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].x)];
        RVar[15u] = CBUFFER_2.values[floatBitsToUint(RVar[6u].y)];
        RVar[14u] = CBUFFER_2.values[floatBitsToUint(RVar[7u].y)];
    }
    if (stateVar == 0)
    {
        float _1545 = RVar[4u].x;
        float _1547 = RVar[4u].y;
        float _1549 = RVar[4u].z;
        float _1553 = RVar[8u].x;
        float _1555 = RVar[8u].y;
        float _1557 = RVar[8u].z;
        RVar[1u].x = RVar[3u].z * RVar[8u].z;
        float _1585 = RVar[8u].w;
        RVar[7u].y = dot(vec4(RVar[4u].x, RVar[4u].y, RVar[4u].z, uintBitsToFloat(2147483648u)), vec4(RVar[9u].x, RVar[9u].y, RVar[9u].z, uintBitsToFloat(0u)));
        RVar[6u].y = _1585 + dot(vec4(_1545, _1547, _1549, uintBitsToFloat(2147483648u)), vec4(_1553, _1555, _1557, uintBitsToFloat(0u)));
    }
    if (stateVar == 0)
    {
        RVar[0u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].x)];
    }
    if (stateVar == 0)
    {
        float _1604 = RVar[4u].x;
        float _1606 = RVar[4u].y;
        float _1608 = RVar[4u].z;
        float _1612 = RVar[10u].x;
        float _1614 = RVar[10u].y;
        float _1616 = RVar[10u].z;
        float _1621 = RVar[9u].w;
        float _1623 = RVar[7u].y;
        float _1631 = RVar[2u].x;
        float _1634 = RVar[3u].z;
        float _1636 = RVar[9u].z;
        float _1639 = RVar[10u].w;
        float _1642 = RVar[3u].y;
        float _1644 = RVar[8u].y;
        float _1646 = RVar[1u].x;
        RVar[127u].x = RVar[2u].x * RVar[6u].y;
        RVar[127u].y = _1631 * (_1621 + _1623);
        RVar[125u].z = _1634 * _1636;
        RVar[125u].x = (_1642 * _1644) + _1646;
        float _1654 = RVar[4u].x;
        float _1656 = RVar[4u].y;
        float _1658 = RVar[4u].z;
        float _1662 = RVar[11u].x;
        float _1664 = RVar[11u].y;
        float _1666 = RVar[11u].z;
        RVar[127u].z = RVar[2u].x * (_1639 + dot(vec4(_1604, _1606, _1608, uintBitsToFloat(2147483648u)), vec4(_1612, _1614, _1616, uintBitsToFloat(0u))));
        float _1675 = RVar[4u].x;
        float _1677 = RVar[4u].y;
        float _1679 = RVar[4u].z;
        float _1683 = RVar[13u].x;
        float _1685 = RVar[13u].y;
        float _1687 = RVar[13u].z;
        RVar[126u].x = RVar[11u].w + dot(vec4(_1654, _1656, _1658, uintBitsToFloat(2147483648u)), vec4(_1662, _1664, _1666, uintBitsToFloat(0u)));
        float _1696 = RVar[4u].x;
        float _1698 = RVar[4u].y;
        float _1700 = RVar[4u].z;
        float _1704 = RVar[12u].x;
        float _1706 = RVar[12u].y;
        float _1708 = RVar[12u].z;
        RVar[127u].w = RVar[13u].w + dot(vec4(_1675, _1677, _1679, uintBitsToFloat(2147483648u)), vec4(_1683, _1685, _1687, uintBitsToFloat(0u)));
        float _1721 = RVar[127u].z;
        float _1725 = RVar[12u].w;
        float _1728 = RVar[127u].x;
        float _1732 = RVar[2u].y;
        float _1734 = RVar[126u].x;
        RVar[127u].x = RVar[127u].y + uintBitsToFloat(0u);
        RVar[127u].y = _1721 + uintBitsToFloat(0u);
        RVar[127u].z = _1725 + dot(vec4(_1696, _1698, _1700, uintBitsToFloat(2147483648u)), vec4(_1704, _1706, _1708, uintBitsToFloat(0u)));
        RVar[126u].w = _1728 + uintBitsToFloat(0u);
        RVar[125u].w = _1732 * _1734;
        float _1742 = RVar[4u].x;
        float _1744 = RVar[4u].y;
        float _1746 = RVar[4u].z;
        float _1750 = RVar[15u].x;
        float _1752 = RVar[15u].y;
        float _1754 = RVar[15u].z;
        RVar[126u].z = RVar[2u].y * RVar[127u].w;
        float _1765 = RVar[4u].x;
        float _1767 = RVar[4u].y;
        float _1769 = RVar[4u].z;
        float _1773 = RVar[14u].x;
        float _1775 = RVar[14u].y;
        float _1777 = RVar[14u].z;
        RVar[127u].w = RVar[15u].w + dot(vec4(_1742, _1744, _1746, uintBitsToFloat(2147483648u)), vec4(_1750, _1752, _1754, uintBitsToFloat(0u)));
        float _1786 = RVar[4u].x;
        float _1788 = RVar[4u].y;
        float _1790 = RVar[4u].z;
        float _1794 = RVar[0u].x;
        float _1796 = RVar[0u].y;
        float _1798 = RVar[0u].z;
        float _1803 = RVar[14u].w;
        float _1811 = RVar[2u].y;
        float _1813 = RVar[127u].z;
        float _1816 = RVar[126u].w;
        float _1818 = RVar[125u].w;
        float _1821 = RVar[0u].w;
        float _1824 = RVar[2u].z;
        RVar[127u].x += RVar[126u].z;
        RVar[127u].z = _1816 + _1818;
        RVar[126u].z = _1824 * (_1803 + dot(vec4(_1765, _1767, _1769, uintBitsToFloat(2147483648u)), vec4(_1773, _1775, _1777, uintBitsToFloat(0u))));
        float _1830 = RVar[127u].y;
        float _1833 = RVar[2u].z;
        float _1836 = RVar[2u].z;
        float _1838 = RVar[127u].w;
        float _1849 = RVar[3u].y;
        float _1851 = RVar[9u].y;
        float _1853 = RVar[125u].z;
        float _1855 = (_1849 * _1851) + _1853;
        RVar[127u].w = (RVar[3u].x * RVar[8u].x) + RVar[125u].x;
        RVar[122u].x = _1855;
        float _1863 = RVar[127u].x;
        float _1865 = RVar[126u].z;
        float _1869 = RVar[3u].x;
        float _1871 = RVar[9u].x;
        float _1875 = RVar[3u].y;
        float _1877 = RVar[10u].y;
        RVar[19u].x = RVar[127u].z + (_1836 * _1838);
        RVar[19u].y = _1863 + _1865;
        RVar[19u].z = (_1830 + (_1811 * _1813)) + (_1833 * (_1821 + dot(vec4(_1786, _1788, _1790, uintBitsToFloat(2147483648u)), vec4(_1794, _1796, _1798, uintBitsToFloat(0u)))));
        RVar[126u].w = (_1869 * _1871) + _1855;
        float _1884 = RVar[3u].x;
        float _1886 = RVar[3u].z;
        float _1890 = RVar[10u].x;
        float _1892 = RVar[10u].z;
        RVar[127u].w = (RVar[2u].x * RVar[127u].w) + uintBitsToFloat(0u);
        float _1906 = RVar[3u].z;
        float _1908 = RVar[11u].z;
        float _1918 = RVar[3u].y;
        float _1920 = RVar[12u].y;
        float _1923 = RVar[2u].x;
        float _1928 = RVar[3u].z;
        float _1930 = RVar[13u].z;
        RVar[127u].y = (RVar[2u].x * RVar[126u].w) + uintBitsToFloat(0u);
        RVar[127u].z = _1918 * _1920;
        RVar[124u].w = (_1923 * dot(vec4(_1884, _1886, _1875 * _1877, uintBitsToFloat(2147483648u)), vec4(_1890, _1892, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)))) + uintBitsToFloat(0u);
        float _1950 = RVar[3u].y;
        float _1952 = RVar[13u].y;
        float _1954 = (_1950 * _1952) + (_1928 * _1930);
        RVar[126u].w = dot(vec4(RVar[3u].x, RVar[3u].y, _1906 * _1908, uintBitsToFloat(2147483648u)), vec4(RVar[11u].x, RVar[11u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[122u].x = _1954;
        float _1974 = RVar[3u].x;
        float _1976 = RVar[13u].x;
        float _1978 = (_1974 * _1976) + _1954;
        RVar[125u].w = dot(vec4(RVar[3u].x, RVar[3u].z, RVar[127u].z, uintBitsToFloat(2147483648u)), vec4(RVar[12u].x, RVar[12u].z, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[122u].x = _1978;
        float _1988 = RVar[3u].z;
        float _1990 = RVar[14u].z;
        float _1993 = RVar[2u].y;
        float _1995 = RVar[126u].w;
        float _1997 = RVar[127u].w;
        float _2001 = RVar[3u].x;
        float _2003 = RVar[0u].x;
        float _2006 = RVar[3u].z;
        float _2008 = RVar[15u].z;
        RVar[127u].x = (RVar[2u].y * _1978) + RVar[127u].y;
        RVar[127u].y = _1988 * _1990;
        RVar[127u].z = (_1993 * _1995) + _1997;
        float _2028 = RVar[3u].y;
        float _2030 = RVar[15u].y;
        float _2032 = (_2028 * _2030) + (_2006 * _2008);
        RVar[125u].x = dot(vec4(RVar[3u].z, RVar[3u].y, _2001 * _2003, uintBitsToFloat(2147483648u)), vec4(RVar[0u].z, RVar[0u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[122u].x = _2032;
        float _2036 = RVar[3u].x;
        float _2038 = RVar[3u].y;
        float _2040 = RVar[127u].y;
        float _2044 = RVar[14u].x;
        float _2046 = RVar[14u].y;
        float _2052 = RVar[3u].x;
        float _2054 = RVar[15u].x;
        float _2056 = (_2052 * _2054) + _2032;
        RVar[122u].x = _2056;
        float _2065 = RVar[2u].z;
        float _2067 = RVar[127u].x;
        float _2071 = RVar[2u].y;
        float _2073 = RVar[125u].w;
        float _2075 = RVar[124u].w;
        float _2077 = (_2071 * _2073) + _2075;
        RVar[6u].x = (RVar[2u].z * _2056) + RVar[127u].z;
        RVar[6u].y = (_2065 * dot(vec4(_2036, _2038, _2040, uintBitsToFloat(2147483648u)), vec4(_2044, _2046, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)))) + _2067;
        RVar[123u].z = _2077;
        RVar[6u].z = (RVar[2u].z * RVar[125u].x) + _2077;
    }
    if (stackVar[stackIdxVar - 1] == 0)
    {
        stateVar = int(stateVar == 0);
    }
    stackVar[stackIdxVar] = stateVar;
    stackIdxVar++;
    if (stateVar == 0)
    {
        RVar[0u].w = intBitsToFloat((floatBitsToInt(CBUFFER_1.values[3].x) != (2)) ? (-1) : 0);
        bool _2118 = floatBitsToInt(RVar[0u].w) == (0);
        predVar = _2118;
        stateVar = _2118 ? 0 : 1;
    }
    if (stateVar == 0)
    {
        float _2127 = RVar[1u].x;
        float _2131 = intBitsToFloat(floatBitsToInt(_2127) * (3));
        RVar[0u].z = _2131;
        float _2142 = RVar[1u].y;
        float _2146 = intBitsToFloat(floatBitsToInt(_2142) * (3));
        RVar[1u].x = intBitsToFloat(floatBitsToInt(_2131) + (2));
        RVar[1u].y = intBitsToFloat(floatBitsToInt(_2131) + (1));
        RVar[0u].y = _2146;
        RVar[0u].x = intBitsToFloat(floatBitsToInt(_2146) + (2));
        RVar[6u].y = intBitsToFloat(floatBitsToInt(_2146) + (1));
    }
    if (stateVar == 0)
    {
        RVar[7u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].z)];
        RVar[8u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].y)];
        RVar[1u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].x)];
        RVar[9u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].y)];
        RVar[6u] = CBUFFER_2.values[floatBitsToUint(RVar[6u].y)];
        RVar[0u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].x)];
    }
    if (stateVar == 0)
    {
        float _2205 = RVar[4u].x;
        float _2207 = RVar[4u].y;
        float _2209 = RVar[4u].z;
        float _2213 = RVar[7u].x;
        float _2215 = RVar[7u].y;
        float _2217 = RVar[7u].z;
        RVar[126u].x = RVar[3u].z * RVar[7u].z;
        float _2228 = RVar[4u].x;
        float _2230 = RVar[4u].y;
        float _2232 = RVar[4u].z;
        float _2236 = RVar[8u].x;
        float _2238 = RVar[8u].y;
        float _2240 = RVar[8u].z;
        RVar[127u].x = RVar[7u].w + dot(vec4(_2205, _2207, _2209, uintBitsToFloat(2147483648u)), vec4(_2213, _2215, _2217, uintBitsToFloat(0u)));
        float _2249 = RVar[4u].x;
        float _2251 = RVar[4u].y;
        float _2253 = RVar[4u].z;
        float _2257 = RVar[1u].x;
        float _2259 = RVar[1u].y;
        float _2261 = RVar[1u].z;
        float _2272 = RVar[3u].z;
        float _2274 = RVar[8u].z;
        float _2277 = RVar[1u].w;
        float _2280 = RVar[2u].x;
        float _2282 = RVar[127u].x;
        float _2285 = RVar[3u].y;
        float _2287 = RVar[7u].y;
        float _2289 = RVar[126u].x;
        RVar[127u].x = RVar[2u].x * (RVar[8u].w + dot(vec4(_2228, _2230, _2232, uintBitsToFloat(2147483648u)), vec4(_2236, _2238, _2240, uintBitsToFloat(0u))));
        RVar[126u].y = _2272 * _2274;
        RVar[127u].w = _2280 * _2282;
        RVar[126u].x = (_2285 * _2287) + _2289;
        float _2297 = RVar[4u].x;
        float _2299 = RVar[4u].y;
        float _2301 = RVar[4u].z;
        float _2305 = RVar[9u].x;
        float _2307 = RVar[9u].y;
        float _2309 = RVar[9u].z;
        RVar[127u].y = RVar[2u].x * (_2277 + dot(vec4(_2249, _2251, _2253, uintBitsToFloat(2147483648u)), vec4(_2257, _2259, _2261, uintBitsToFloat(0u))));
        float _2318 = RVar[4u].x;
        float _2320 = RVar[4u].y;
        float _2322 = RVar[4u].z;
        float _2326 = RVar[6u].x;
        float _2328 = RVar[6u].y;
        float _2330 = RVar[6u].z;
        RVar[126u].w = RVar[9u].w + dot(vec4(_2297, _2299, _2301, uintBitsToFloat(2147483648u)), vec4(_2305, _2307, _2309, uintBitsToFloat(0u)));
        float _2339 = RVar[4u].x;
        float _2341 = RVar[4u].y;
        float _2343 = RVar[4u].z;
        float _2347 = RVar[0u].x;
        float _2349 = RVar[0u].y;
        float _2351 = RVar[0u].z;
        RVar[125u].w = RVar[6u].w + dot(vec4(_2318, _2320, _2322, uintBitsToFloat(2147483648u)), vec4(_2326, _2328, _2330, uintBitsToFloat(0u)));
        float _2364 = RVar[127u].x;
        float _2368 = RVar[127u].w;
        float _2372 = RVar[0u].w;
        float _2375 = RVar[2u].y;
        float _2377 = RVar[126u].w;
        RVar[127u].x = RVar[127u].y + uintBitsToFloat(0u);
        RVar[127u].y = _2364 + uintBitsToFloat(0u);
        float _2382 = RVar[2u].y;
        float _2393 = RVar[2u].y;
        float _2395 = RVar[125u].w;
        float _2398 = RVar[3u].z;
        float _2400 = RVar[1u].z;
        RVar[126u].y = (RVar[3u].x * RVar[8u].x) + RVar[126u].y;
        RVar[19u].x = (_2368 + uintBitsToFloat(0u)) + (_2375 * _2377);
        float _2412 = RVar[127u].y;
        float _2415 = RVar[127u].x;
        float _2418 = RVar[3u].z;
        float _2420 = RVar[6u].z;
        float _2423 = RVar[3u].z;
        float _2425 = RVar[9u].z;
        RVar[127u].x = (RVar[3u].y * RVar[1u].y) + (_2398 * _2400);
        RVar[19u].y = _2412 + (_2393 * _2395);
        RVar[19u].z = _2415 + (_2382 * (_2372 + dot(vec4(_2339, _2341, _2343, uintBitsToFloat(2147483648u)), vec4(_2347, _2349, _2351, uintBitsToFloat(0u)))));
        RVar[125u].w = _2418 * _2420;
        RVar[125u].x = _2423 * _2425;
        float _2433 = RVar[3u].z;
        float _2435 = RVar[0u].z;
        float _2446 = RVar[3u].x;
        float _2448 = RVar[7u].x;
        float _2450 = RVar[126u].x;
        RVar[126u].y = (RVar[3u].y * RVar[8u].y) + RVar[126u].y;
        RVar[127u].w = (_2446 * _2448) + _2450;
        float _2464 = RVar[3u].x;
        float _2466 = RVar[1u].x;
        float _2468 = RVar[127u].x;
        float _2472 = RVar[3u].y;
        float _2474 = RVar[0u].y;
        RVar[127u].x = (RVar[3u].y * RVar[6u].y) + RVar[125u].w;
        RVar[125u].w = (_2464 * _2466) + _2468;
        RVar[126u].x = (_2472 * _2474) + (_2433 * _2435);
        RVar[127u].y = dot(vec4(RVar[3u].x, RVar[3u].y, RVar[125u].x, uintBitsToFloat(2147483648u)), vec4(RVar[9u].x, RVar[9u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[126u].w = (RVar[3u].x * RVar[6u].x) + RVar[127u].x;
        RVar[126u].x = (RVar[3u].x * RVar[0u].x) + RVar[126u].x;
        float _2516 = RVar[2u].x;
        float _2518 = RVar[126u].y;
        float _2521 = (_2516 * _2518) + uintBitsToFloat(0u);
        float _2523 = RVar[2u].x;
        float _2525 = RVar[125u].w;
        float _2528 = (_2523 * _2525) + uintBitsToFloat(0u);
        float _2530 = RVar[2u].x;
        float _2532 = RVar[127u].w;
        float _2535 = (_2530 * _2532) + uintBitsToFloat(0u);
        RVar[123u].x = _2521;
        RVar[123u].y = _2528;
        RVar[123u].z = _2535;
        float _2546 = RVar[2u].y;
        float _2548 = RVar[126u].w;
        float _2552 = RVar[2u].y;
        float _2554 = RVar[126u].x;
        RVar[6u].x = (RVar[2u].y * RVar[127u].y) + _2535;
        RVar[6u].y = (_2546 * _2548) + _2521;
        RVar[6u].z = (_2552 * _2554) + _2528;
    }
    if (stackVar[stackIdxVar - 1] == 0)
    {
        stateVar = int(stateVar == 0);
    }
    if (stateVar == 0)
    {
        float _2577 = RVar[6u].y;
        float _2579 = RVar[6u].z;
        RVar[19u].x = RVar[6u].x;
        RVar[19u].y = _2577;
        RVar[19u].z = _2579;
    }
    int stackIdx = stackIdxVar;
    int newStackIdx = stackIdx - 1;
    stackIdxVar = newStackIdx;
    stateVar = stackVar[newStackIdx];
    int stackIdx_1 = stackIdxVar;
    int newStackIdx_1 = stackIdx_1 - 2;
    stackIdxVar = newStackIdx_1;
    stateVar = stackVar[newStackIdx_1];
    int stackIdx_2 = stackIdxVar;
    int newStackIdx_2 = stackIdx_2 - 2;
    stackIdxVar = newStackIdx_2;
    stateVar = stackVar[newStackIdx_2];
    if (stateVar == 0)
    {
        RVar[127u].w = dot(vec4(RVar[19u].x, RVar[19u].y, RVar[19u].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[3].x, CBUFFER_3.values[3].y, CBUFFER_3.values[3].z, uintBitsToFloat(0u)));
        RVar[2u].z = uintBitsToFloat(1065353216u);
        float _2640 = RVar[6u].z;
        float _2642 = RVar[6u].z;
        RVar[127u].z = dot(vec4(RVar[19u].x, RVar[19u].y, RVar[19u].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[4].x, CBUFFER_3.values[4].y, CBUFFER_3.values[4].z, uintBitsToFloat(0u)));
        float _2664 = RVar[6u].y;
        float _2666 = RVar[6u].y;
        float _2668 = (_2664 * _2666) + (_2640 * _2642);
        RVar[127u].y = dot(vec4(RVar[19u].x, RVar[19u].y, RVar[19u].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[5].x, CBUFFER_3.values[5].y, CBUFFER_3.values[5].z, uintBitsToFloat(0u)));
        RVar[122u].x = _2668;
        float _2690 = RVar[6u].x;
        float _2692 = RVar[6u].x;
        float _2694 = (_2690 * _2692) + _2668;
        RVar[126u].w = dot(vec4(RVar[19u].x, RVar[19u].y, RVar[19u].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[6].x, CBUFFER_3.values[6].y, CBUFFER_3.values[6].z, uintBitsToFloat(0u)));
        RVar[122u].x = _2694;
        float _2705 = RVar[127u].z;
        float _2708 = inversesqrt(_2694);
        RVar[1u].x = CBUFFER_3.values[3].w + RVar[127u].w;
        RVar[1u].y = CBUFFER_3.values[4].w + _2705;
        float _2715 = RVar[6u].y;
        float _2720 = RVar[127u].y;
        float _2725 = RVar[126u].w;
        float _2728 = RVar[6u].z;
        RVar[6u].x *= _2708;
        RVar[2u].y = _2715 * _2708;
        RVar[1u].z = CBUFFER_3.values[5].w + _2720;
        RVar[1u].w = CBUFFER_3.values[6].w + _2725;
        RVar[0u].z = _2728 * _2708;
        float _2760 = RVar[19u].z;
        RVar[0u].x = intBitsToFloat(floatBitsToInt(CBUFFER_4.values[0].x) + (25));
        RVar[0u].y = intBitsToFloat(floatBitsToInt(CBUFFER_4.values[0].x) + (41));
        RVar[0u].w = intBitsToFloat(floatBitsToInt(CBUFFER_4.values[0].x) + (33));
        RVar[2u].x = _2760 * CBUFFER_3.values[2].z;
    }
    if (stateVar == 0)
    {
        RVar[3u] = vec4(CBUFFER_3.values[floatBitsToUint(RVar[0u].w)].x, RVar[3u].y, RVar[3u].z, RVar[3u].w);
        RVar[4u] = vec4(CBUFFER_3.values[floatBitsToUint(RVar[0u].y)].x, RVar[4u].y, RVar[4u].z, RVar[4u].w);
        uint _2790 = floatBitsToUint(RVar[0u].x);
        RVar[7u] = vec4(CBUFFER_3.values[_2790].x, CBUFFER_3.values[_2790].y, CBUFFER_3.values[_2790].z, RVar[7u].w);
    }
    vec4 _2812 = (RVar[1u] * vec4(VS_PUSH.posMulAdd.xy, 1.0, 1.0)) + vec4(VS_PUSH.posMulAdd.zw, 0.0, 0.0);
    vec4 _2815 = _2812;
    _2815.y = -_2812.y;
    vec4 _2823 = _2815;
    _2823.z = (_2815.z + (_2815.w * VS_PUSH.zSpaceMul.x)) * VS_PUSH.zSpaceMul.y;
    gl_Position = _2823;
    if (stateVar == 0)
    {
        float _2829 = RVar[19u].x;
        float _2831 = RVar[19u].y;
        float _2833 = RVar[2u].x;
        float _2845 = RVar[0u].z;
        float _2853 = RVar[2u].y;
        float _2857 = (_2853 * CBUFFER_3.values[0].y) + (_2845 * CBUFFER_3.values[0].z);
        RVar[122u].x = _2857;
        float _2867 = RVar[3u].x;
        float _2871 = RVar[0u].z;
        RVar[0u].x = (RVar[6u].x * CBUFFER_3.values[0].x) + _2857;
        float _2883 = RVar[4u].x;
        float _2887 = RVar[2u].z;
        RVar[127u].x = (RVar[2u].y * CBUFFER_3.values[1].y) + (_2871 * CBUFFER_3.values[1].z);
        RVar[7u].w = clamp(((-(CBUFFER_3.values[2].w + dot(vec4(_2829, _2831, _2833, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[2].x, CBUFFER_3.values[2].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u))))) + (-_2867)) * _2883, 0.0, 1.0);
        RVar[1u].x = dot(vec4(RVar[5u].x, RVar[5u].y, RVar[2u].z, _2887 * CBUFFER_4.values[1].w), vec4(CBUFFER_4.values[1].x, CBUFFER_4.values[1].y, CBUFFER_4.values[1].z, uintBitsToFloat(1065353216u)));
        RVar[1u].y = dot(vec4(RVar[5u].x, RVar[5u].y, RVar[2u].z, RVar[2u].z), CBUFFER_4.values[2]);
        float _2925 = RVar[0u].z;
        RVar[0u].y = (RVar[6u].x * CBUFFER_3.values[1].x) + RVar[127u].x;
        RVar[0u].z = dot(vec4(RVar[6u].x, RVar[2u].y, _2925 * CBUFFER_3.values[2].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[2].x, CBUFFER_3.values[2].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
    }
    PARAM_0 = RVar[7u];
    PARAM_1 = RVar[0u];
    PARAM_2 = vec4(RVar[1u].x, RVar[1u].y, RVar[1u].z, RVar[1u].z);
    if (stateVar == 0)
    {
    }
}

 