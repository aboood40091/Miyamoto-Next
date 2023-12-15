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
layout(location = 3) out vec4 PARAM_3;
layout(location = 4) out vec4 PARAM_4;
layout(location = 5) out vec4 PARAM_5;
layout(location = 0) in uvec4 aBlendIndex_0_0;
layout(location = 1) in uvec4 aBlendWeight_0_0;
layout(location = 2) in uvec3 aNormal_0_0;
layout(location = 3) in uvec3 aPosition_0_0;
layout(location = 4) in uvec4 aTangent_0_0;
layout(location = 5) in uvec2 aTexCoord0_0_0;
layout(location = 6) in uvec2 aTexCoordNormal_0_0;
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
        RVar[5u] = vec4(uintBitsToFloat(aTangent_0_0.x), uintBitsToFloat(aTangent_0_0.y), uintBitsToFloat(aTangent_0_0.z), uintBitsToFloat(aTangent_0_0.w));
        RVar[6u] = vec4(vec4(uintBitsToFloat(aTexCoord0_0_0.x), uintBitsToFloat(aTexCoord0_0_0.y), 0.0, 1.0).xy, 0.0, 1.0);
        RVar[7u] = vec4(vec4(uintBitsToFloat(aTexCoordNormal_0_0.x), uintBitsToFloat(aTexCoordNormal_0_0.y), 0.0, 1.0).xy, 0.0, 1.0);
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
        RVar[9u].x = uintBitsToFloat(0u);
        RVar[9u].y = uintBitsToFloat(0u);
        RVar[9u].z = uintBitsToFloat(0u);
        RVar[0u].w = intBitsToFloat((floatBitsToInt(CBUFFER_1.values[3].x) != (0)) ? (-1) : 0);
        bool _90 = floatBitsToInt(RVar[0u].w) == (0);
        predVar = _90;
        stateVar = _90 ? 0 : 1;
    }
    if (stateVar == 0)
    {
        float _123 = RVar[3u].z;
        RVar[127u].w = dot(vec4(RVar[4u].x, RVar[4u].y, RVar[4u].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_2.values[0].x, CBUFFER_2.values[0].y, CBUFFER_2.values[0].z, uintBitsToFloat(0u)));
        RVar[126u].x = _123 * CBUFFER_2.values[0].z;
        RVar[127u].x = dot(vec4(RVar[4u].x, RVar[4u].y, RVar[4u].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_2.values[1].x, CBUFFER_2.values[1].y, CBUFFER_2.values[1].z, uintBitsToFloat(0u)));
        RVar[126u].w = dot(vec4(RVar[4u].x, RVar[4u].y, RVar[4u].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_2.values[2].x, CBUFFER_2.values[2].y, CBUFFER_2.values[2].z, uintBitsToFloat(0u)));
        float _175 = RVar[127u].x;
        float _179 = RVar[5u].z;
        RVar[20u].x = CBUFFER_2.values[0].w + RVar[127u].w;
        RVar[20u].y = CBUFFER_2.values[1].w + _175;
        float _187 = RVar[3u].y;
        float _191 = RVar[126u].x;
        float _193 = (_187 * CBUFFER_2.values[0].y) + _191;
        float _197 = RVar[126u].w;
        float _200 = RVar[5u].y;
        float _204 = (_200 * CBUFFER_2.values[0].y) + (_179 * CBUFFER_2.values[0].z);
        RVar[123u].x = _193;
        RVar[20u].z = CBUFFER_2.values[2].w + _197;
        RVar[122u].x = _204;
        float _217 = RVar[3u].z;
        float _222 = RVar[5u].z;
        float _227 = RVar[5u].x;
        RVar[4u].x = (RVar[3u].x * CBUFFER_2.values[0].x) + _193;
        RVar[9u].x = (_227 * CBUFFER_2.values[0].x) + _204;
        float _250 = RVar[5u].y;
        RVar[4u].y = dot(vec4(RVar[3u].x, RVar[3u].y, _217 * CBUFFER_2.values[1].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_2.values[1].x, CBUFFER_2.values[1].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[126u].x = (_250 * CBUFFER_2.values[1].y) + (_222 * CBUFFER_2.values[1].z);
        RVar[4u].z = dot(vec4(RVar[3u].x, RVar[3u].y, RVar[3u].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_2.values[2].x, CBUFFER_2.values[2].y, CBUFFER_2.values[2].z, uintBitsToFloat(0u)));
        float _276 = RVar[5u].z;
        RVar[9u].y = (RVar[5u].x * CBUFFER_2.values[1].x) + RVar[126u].x;
        RVar[9u].z = dot(vec4(RVar[5u].x, RVar[5u].y, _276 * CBUFFER_2.values[2].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_2.values[2].x, CBUFFER_2.values[2].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
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
        bool _334 = floatBitsToInt(RVar[0u].w) == (0);
        predVar = _334;
        stateVar = _334 ? 0 : 1;
    }
    if (stateVar == 0)
    {
        float _343 = RVar[1u].x;
        float _347 = intBitsToFloat(floatBitsToInt(_343) * (3));
        RVar[1u].w = _347;
        RVar[1u].x = intBitsToFloat(floatBitsToInt(_347) + (2));
        RVar[1u].y = intBitsToFloat(floatBitsToInt(_347) + (1));
    }
    if (stateVar == 0)
    {
        RVar[0u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].w)];
        RVar[2u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].y)];
        RVar[1u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].x)];
    }
    if (stateVar == 0)
    {
        float _387 = RVar[4u].x;
        float _389 = RVar[4u].y;
        float _391 = RVar[4u].z;
        float _395 = RVar[0u].x;
        float _397 = RVar[0u].y;
        float _399 = RVar[0u].z;
        RVar[127u].x = RVar[3u].z * RVar[0u].z;
        float _410 = RVar[4u].x;
        float _412 = RVar[4u].y;
        float _414 = RVar[4u].z;
        float _418 = RVar[2u].x;
        float _420 = RVar[2u].y;
        float _422 = RVar[2u].z;
        RVar[20u].x = RVar[0u].w + dot(vec4(_387, _389, _391, uintBitsToFloat(2147483648u)), vec4(_395, _397, _399, uintBitsToFloat(0u)));
        float _431 = RVar[4u].x;
        float _433 = RVar[4u].y;
        float _435 = RVar[4u].z;
        float _439 = RVar[1u].x;
        float _441 = RVar[1u].y;
        float _443 = RVar[1u].z;
        RVar[20u].y = RVar[2u].w + dot(vec4(_410, _412, _414, uintBitsToFloat(2147483648u)), vec4(_418, _420, _422, uintBitsToFloat(0u)));
        float _452 = RVar[3u].y;
        float _454 = RVar[0u].y;
        float _456 = RVar[127u].x;
        float _458 = (_452 * _454) + _456;
        float _460 = RVar[1u].w;
        float _463 = RVar[5u].z;
        float _465 = RVar[0u].z;
        RVar[123u].x = _458;
        RVar[20u].z = _460 + dot(vec4(_431, _433, _435, uintBitsToFloat(2147483648u)), vec4(_439, _441, _443, uintBitsToFloat(0u)));
        float _484 = RVar[3u].x;
        float _486 = RVar[0u].x;
        RVar[9u].x = dot(vec4(RVar[5u].x, RVar[5u].y, _463 * _465, uintBitsToFloat(2147483648u)), vec4(RVar[0u].x, RVar[0u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[4u].x = (_484 * _486) + _458;
        float _509 = RVar[3u].z;
        float _511 = RVar[1u].z;
        RVar[4u].y = dot(vec4(RVar[3u].x, RVar[3u].y, RVar[3u].z, uintBitsToFloat(2147483648u)), vec4(RVar[2u].x, RVar[2u].y, RVar[2u].z, uintBitsToFloat(0u)));
        float _529 = RVar[5u].z;
        float _531 = RVar[2u].z;
        RVar[4u].z = dot(vec4(RVar[3u].x, RVar[3u].y, _509 * _511, uintBitsToFloat(2147483648u)), vec4(RVar[1u].x, RVar[1u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        float _549 = RVar[5u].z;
        float _551 = RVar[1u].z;
        RVar[9u].y = dot(vec4(RVar[5u].x, RVar[5u].y, _529 * _531, uintBitsToFloat(2147483648u)), vec4(RVar[2u].x, RVar[2u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[9u].z = dot(vec4(RVar[5u].x, RVar[5u].y, _549 * _551, uintBitsToFloat(2147483648u)), vec4(RVar[1u].x, RVar[1u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
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
        bool _600 = floatBitsToInt(RVar[0u].w) == (0);
        predVar = _600;
        stateVar = _600 ? 0 : 1;
    }
    if (stateVar == 0)
    {
        float _609 = RVar[1u].x;
        float _613 = intBitsToFloat(floatBitsToInt(_609) * (3));
        RVar[0u].x = _613;
        float _624 = RVar[1u].y;
        float _628 = intBitsToFloat(floatBitsToInt(_624) * (3));
        RVar[0u].z = intBitsToFloat(floatBitsToInt(_613) + (2));
        RVar[0u].w = intBitsToFloat(floatBitsToInt(_613) + (1));
        RVar[0u].y = _628;
        float _641 = RVar[1u].z;
        float _645 = intBitsToFloat(floatBitsToInt(_641) * (3));
        RVar[8u].x = intBitsToFloat(floatBitsToInt(_628) + (1));
        RVar[3u].w = intBitsToFloat(floatBitsToInt(_628) + (2));
        RVar[8u].z = _645;
        float _659 = RVar[1u].w;
        RVar[1u].x = intBitsToFloat(floatBitsToInt(_645) + (2));
        RVar[1u].y = intBitsToFloat(floatBitsToInt(_645) + (1));
        RVar[1u].w = intBitsToFloat(floatBitsToInt(_659) * (3));
    }
    if (stateVar == 0)
    {
        RVar[9u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].x)];
        RVar[11u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].w)];
        RVar[10u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].z)];
        RVar[12u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].y)];
        RVar[13u] = CBUFFER_2.values[floatBitsToUint(RVar[8u].x)];
        RVar[14u] = CBUFFER_2.values[floatBitsToUint(RVar[3u].w)];
        RVar[15u] = CBUFFER_2.values[floatBitsToUint(RVar[8u].z)];
        RVar[16u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].y)];
    }
    if (stateVar == 0)
    {
        float _736 = RVar[1u].w;
        float _742 = RVar[3u].z;
        float _744 = RVar[11u].z;
        float _747 = RVar[3u].y;
        float _749 = RVar[10u].y;
        float _752 = RVar[3u].z;
        float _754 = RVar[9u].z;
        RVar[8u].x = intBitsToFloat(floatBitsToInt(RVar[1u].w) + (1));
        RVar[1u].y = intBitsToFloat(floatBitsToInt(_736) + (2));
        RVar[8u].z = _742 * _744;
        RVar[0u].w = _747 * _749;
        float _778 = RVar[3u].y;
        float _780 = RVar[9u].y;
        RVar[3u].w = dot(vec4(RVar[4u].x, RVar[4u].y, RVar[4u].z, uintBitsToFloat(2147483648u)), vec4(RVar[9u].x, RVar[9u].y, RVar[9u].z, uintBitsToFloat(0u)));
        RVar[0u].x = (_778 * _780) + (_752 * _754);
    }
    if (stateVar == 0)
    {
        RVar[17u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].x)];
        RVar[18u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].w)];
        RVar[19u] = CBUFFER_2.values[floatBitsToUint(RVar[8u].x)];
        RVar[1u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].y)];
    }
    if (stateVar == 0)
    {
        float _821 = RVar[4u].x;
        float _823 = RVar[4u].y;
        float _825 = RVar[4u].z;
        float _829 = RVar[11u].x;
        float _831 = RVar[11u].y;
        float _833 = RVar[11u].z;
        RVar[127u].z = RVar[9u].w + RVar[3u].w;
        float _844 = RVar[4u].x;
        float _846 = RVar[4u].y;
        float _848 = RVar[4u].z;
        float _852 = RVar[10u].x;
        float _854 = RVar[10u].y;
        float _856 = RVar[10u].z;
        float _861 = RVar[11u].w;
        float _864 = RVar[10u].w;
        float _872 = RVar[2u].x;
        float _875 = RVar[3u].x;
        float _877 = RVar[10u].x;
        float _879 = RVar[0u].w;
        float _883 = RVar[3u].y;
        float _885 = RVar[11u].y;
        float _887 = RVar[8u].z;
        RVar[127u].y = RVar[2u].x * RVar[127u].z;
        RVar[127u].z = _872 * (_861 + dot(vec4(_821, _823, _825, uintBitsToFloat(2147483648u)), vec4(_829, _831, _833, uintBitsToFloat(0u))));
        RVar[0u].w = (_875 * _877) + _879;
        RVar[125u].x = (_883 * _885) + _887;
        float _896 = RVar[4u].x;
        float _898 = RVar[4u].y;
        float _900 = RVar[4u].z;
        float _904 = RVar[12u].x;
        float _906 = RVar[12u].y;
        float _908 = RVar[12u].z;
        RVar[127u].w = RVar[2u].x * (_864 + dot(vec4(_844, _846, _848, uintBitsToFloat(2147483648u)), vec4(_852, _854, _856, uintBitsToFloat(0u))));
        float _917 = RVar[4u].x;
        float _919 = RVar[4u].y;
        float _921 = RVar[4u].z;
        float _925 = RVar[13u].x;
        float _927 = RVar[13u].y;
        float _929 = RVar[13u].z;
        RVar[126u].w = RVar[12u].w + dot(vec4(_896, _898, _900, uintBitsToFloat(2147483648u)), vec4(_904, _906, _908, uintBitsToFloat(0u)));
        float _938 = RVar[4u].x;
        float _940 = RVar[4u].y;
        float _942 = RVar[4u].z;
        float _946 = RVar[14u].x;
        float _948 = RVar[14u].y;
        float _950 = RVar[14u].z;
        RVar[126u].z = RVar[13u].w + dot(vec4(_917, _919, _921, uintBitsToFloat(2147483648u)), vec4(_925, _927, _929, uintBitsToFloat(0u)));
        float _963 = RVar[14u].w;
        float _966 = RVar[127u].w;
        float _970 = RVar[127u].z;
        float _974 = RVar[2u].y;
        float _976 = RVar[126u].w;
        RVar[127u].x = RVar[127u].y + uintBitsToFloat(0u);
        RVar[127u].y = _963 + dot(vec4(_938, _940, _942, uintBitsToFloat(2147483648u)), vec4(_946, _948, _950, uintBitsToFloat(0u)));
        RVar[125u].z = _966 + uintBitsToFloat(0u);
        RVar[127u].w = _970 + uintBitsToFloat(0u);
        RVar[127u].z = _974 * _976;
        float _984 = RVar[4u].x;
        float _986 = RVar[4u].y;
        float _988 = RVar[4u].z;
        float _992 = RVar[15u].x;
        float _994 = RVar[15u].y;
        float _996 = RVar[15u].z;
        RVar[126u].y = RVar[2u].y * RVar[126u].z;
        float _1007 = RVar[4u].x;
        float _1009 = RVar[4u].y;
        float _1011 = RVar[4u].z;
        float _1015 = RVar[16u].x;
        float _1017 = RVar[16u].y;
        float _1019 = RVar[16u].z;
        RVar[126u].x = RVar[15u].w + dot(vec4(_984, _986, _988, uintBitsToFloat(2147483648u)), vec4(_992, _994, _996, uintBitsToFloat(0u)));
        float _1028 = RVar[4u].x;
        float _1030 = RVar[4u].y;
        float _1032 = RVar[4u].z;
        float _1036 = RVar[17u].x;
        float _1038 = RVar[17u].y;
        float _1040 = RVar[17u].z;
        RVar[126u].w = RVar[16u].w + dot(vec4(_1007, _1009, _1011, uintBitsToFloat(2147483648u)), vec4(_1015, _1017, _1019, uintBitsToFloat(0u)));
        float _1049 = RVar[2u].y;
        float _1051 = RVar[127u].y;
        float _1059 = RVar[17u].w;
        float _1062 = RVar[127u].w;
        float _1064 = RVar[126u].y;
        float _1067 = RVar[2u].z;
        float _1069 = RVar[126u].x;
        RVar[127u].y = RVar[127u].x + RVar[127u].z;
        RVar[127u].z = _1059 + dot(vec4(_1028, _1030, _1032, uintBitsToFloat(2147483648u)), vec4(_1036, _1038, _1040, uintBitsToFloat(0u)));
        RVar[125u].w = _1062 + _1064;
        RVar[127u].w = _1067 * _1069;
        float _1076 = RVar[4u].x;
        float _1078 = RVar[4u].y;
        float _1080 = RVar[4u].z;
        float _1084 = RVar[18u].x;
        float _1086 = RVar[18u].y;
        float _1088 = RVar[18u].z;
        RVar[124u].w = RVar[125u].z + (_1049 * _1051);
        float _1098 = RVar[4u].x;
        float _1100 = RVar[4u].y;
        float _1102 = RVar[4u].z;
        float _1106 = RVar[19u].x;
        float _1108 = RVar[19u].y;
        float _1110 = RVar[19u].z;
        RVar[126u].y = RVar[18u].w + dot(vec4(_1076, _1078, _1080, uintBitsToFloat(2147483648u)), vec4(_1084, _1086, _1088, uintBitsToFloat(0u)));
        float _1119 = RVar[4u].x;
        float _1121 = RVar[4u].y;
        float _1123 = RVar[4u].z;
        float _1127 = RVar[1u].x;
        float _1129 = RVar[1u].y;
        float _1131 = RVar[1u].z;
        RVar[125u].y = RVar[19u].w + dot(vec4(_1098, _1100, _1102, uintBitsToFloat(2147483648u)), vec4(_1106, _1108, _1110, uintBitsToFloat(0u)));
        float _1145 = RVar[2u].z;
        float _1147 = RVar[127u].z;
        float _1150 = RVar[2u].z;
        float _1152 = RVar[126u].w;
        float _1155 = RVar[1u].w;
        float _1158 = RVar[3u].x;
        float _1160 = RVar[9u].x;
        float _1162 = RVar[0u].x;
        RVar[127u].x = RVar[127u].y + RVar[127u].w;
        RVar[127u].y = (_1158 * _1160) + _1162;
        float _1168 = RVar[124u].w;
        float _1171 = RVar[125u].w;
        float _1174 = RVar[2u].w;
        float _1176 = RVar[125u].y;
        float _1184 = RVar[2u].w;
        float _1192 = RVar[3u].z;
        float _1194 = RVar[10u].z;
        float _1196 = RVar[0u].w;
        float _1200 = RVar[2u].x;
        float _1202 = RVar[127u].y;
        RVar[20u].x = RVar[127u].x + (RVar[2u].w * RVar[126u].y);
        RVar[20u].y = (_1171 + (_1150 * _1152)) + (_1174 * _1176);
        RVar[20u].z = (_1168 + (_1145 * _1147)) + (_1184 * (_1155 + dot(vec4(_1119, _1121, _1123, uintBitsToFloat(2147483648u)), vec4(_1127, _1129, _1131, uintBitsToFloat(0u)))));
        RVar[124u].w = (_1192 * _1194) + _1196;
        RVar[0u].x = (_1200 * _1202) + uintBitsToFloat(0u);
        float _1212 = RVar[5u].z;
        float _1214 = RVar[9u].z;
        float _1222 = RVar[5u].y;
        float _1224 = RVar[12u].y;
        float _1227 = RVar[3u].x;
        float _1229 = RVar[11u].x;
        float _1231 = RVar[125u].x;
        float _1235 = RVar[5u].z;
        float _1237 = RVar[11u].z;
        RVar[127u].y = RVar[5u].y * RVar[10u].y;
        RVar[127u].z = _1222 * _1224;
        RVar[125u].w = (_1227 * _1229) + _1231;
        float _1257 = RVar[5u].y;
        float _1259 = RVar[11u].y;
        float _1261 = (_1257 * _1259) + (_1235 * _1237);
        RVar[127u].w = dot(vec4(RVar[5u].x, RVar[5u].y, _1212 * _1214, uintBitsToFloat(2147483648u)), vec4(RVar[9u].x, RVar[9u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[122u].x = _1261;
        float _1281 = RVar[5u].x;
        float _1283 = RVar[11u].x;
        float _1285 = (_1281 * _1283) + _1261;
        RVar[126u].w = dot(vec4(RVar[5u].x, RVar[5u].z, RVar[127u].y, uintBitsToFloat(2147483648u)), vec4(RVar[10u].x, RVar[10u].z, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[122u].x = _1285;
        float _1296 = RVar[2u].x;
        float _1298 = RVar[127u].w;
        float _1303 = RVar[2u].x;
        float _1305 = RVar[125u].w;
        float _1310 = RVar[2u].x;
        float _1315 = RVar[5u].z;
        float _1317 = RVar[12u].z;
        float _1319 = RVar[127u].z;
        float _1321 = (_1315 * _1317) + _1319;
        RVar[11u].x = (RVar[2u].x * RVar[124u].w) + uintBitsToFloat(0u);
        RVar[11u].y = (_1296 * _1298) + uintBitsToFloat(0u);
        RVar[10u].z = (_1303 * _1305) + uintBitsToFloat(0u);
        RVar[11u].w = (_1310 * _1285) + uintBitsToFloat(0u);
        RVar[122u].x = _1321;
        float _1334 = RVar[3u].z;
        float _1336 = RVar[13u].z;
        float _1339 = RVar[2u].x;
        float _1341 = RVar[126u].w;
        float _1346 = RVar[3u].y;
        float _1348 = RVar[14u].y;
        float _1351 = RVar[3u].z;
        float _1353 = RVar[12u].z;
        RVar[9u].x = (RVar[5u].x * RVar[12u].x) + _1321;
        RVar[10u].y = _1334 * _1336;
        RVar[11u].z = (_1339 * _1341) + uintBitsToFloat(0u);
        RVar[10u].w = _1346 * _1348;
        RVar[10u].x = _1351 * _1353;
    }
    if (stateVar == 0)
    {
        float _1381 = RVar[3u].z;
        float _1383 = RVar[14u].z;
        float _1385 = RVar[10u].w;
        float _1387 = (_1381 * _1383) + _1385;
        RVar[127u].z = dot(vec4(RVar[3u].x, RVar[3u].y, RVar[10u].x, uintBitsToFloat(2147483648u)), vec4(RVar[12u].x, RVar[12u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[122u].x = _1387;
        float _1407 = RVar[3u].x;
        float _1409 = RVar[14u].x;
        RVar[125u].x = dot(vec4(RVar[3u].x, RVar[3u].y, RVar[10u].y, uintBitsToFloat(2147483648u)), vec4(RVar[13u].x, RVar[13u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[125u].z = (_1407 * _1409) + _1387;
        float _1432 = RVar[2u].y;
        float _1434 = RVar[127u].z;
        float _1436 = RVar[0u].x;
        RVar[127u].z = dot(vec4(RVar[5u].x, RVar[5u].y, RVar[5u].z, uintBitsToFloat(2147483648u)), vec4(RVar[13u].x, RVar[13u].y, RVar[13u].z, uintBitsToFloat(0u)));
        RVar[127u].y = (_1432 * _1434) + _1436;
        float _1442 = RVar[5u].x;
        float _1444 = RVar[5u].y;
        float _1446 = RVar[5u].z;
        float _1450 = RVar[14u].x;
        float _1452 = RVar[14u].y;
        float _1454 = RVar[14u].z;
        RVar[126u].w = (RVar[2u].y * RVar[125u].x) + RVar[10u].z;
        float _1476 = RVar[2u].y;
        float _1478 = RVar[125u].z;
        float _1480 = RVar[11u].x;
        float _1484 = RVar[2u].y;
        float _1486 = RVar[11u].z;
        float _1490 = RVar[2u].y;
        float _1492 = RVar[9u].x;
        float _1494 = RVar[11u].y;
        RVar[125u].x = (RVar[2u].y * RVar[127u].z) + RVar[11u].w;
        RVar[126u].y = (_1476 * _1478) + _1480;
        RVar[127u].z = (_1484 * dot(vec4(_1442, _1444, _1446, uintBitsToFloat(2147483648u)), vec4(_1450, _1452, _1454, uintBitsToFloat(0u)))) + _1486;
        RVar[127u].w = (_1490 * _1492) + _1494;
        float _1519 = RVar[3u].z;
        float _1521 = RVar[16u].z;
        float _1524 = RVar[3u].x;
        float _1526 = RVar[3u].y;
        float _1530 = RVar[16u].x;
        float _1532 = RVar[16u].y;
        RVar[125u].z = (RVar[2u].z * dot(vec4(RVar[3u].x, RVar[3u].y, RVar[3u].z, uintBitsToFloat(2147483648u)), vec4(RVar[15u].x, RVar[15u].y, RVar[15u].z, uintBitsToFloat(0u)))) + RVar[127u].y;
        float _1545 = RVar[3u].x;
        float _1547 = RVar[3u].y;
        float _1549 = RVar[3u].z;
        float _1553 = RVar[17u].x;
        float _1555 = RVar[17u].y;
        float _1557 = RVar[17u].z;
        RVar[124u].x = (RVar[2u].z * dot(vec4(_1524, _1526, _1519 * _1521, uintBitsToFloat(2147483648u)), vec4(_1530, _1532, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)))) + RVar[126u].w;
        float _1569 = RVar[5u].x;
        float _1571 = RVar[5u].y;
        float _1573 = RVar[5u].z;
        float _1577 = RVar[15u].x;
        float _1579 = RVar[15u].y;
        float _1581 = RVar[15u].z;
        RVar[126u].z = (RVar[2u].z * dot(vec4(_1545, _1547, _1549, uintBitsToFloat(2147483648u)), vec4(_1553, _1555, _1557, uintBitsToFloat(0u)))) + RVar[126u].y;
        float _1593 = RVar[5u].x;
        float _1595 = RVar[5u].y;
        float _1597 = RVar[5u].z;
        float _1601 = RVar[16u].x;
        float _1603 = RVar[16u].y;
        float _1605 = RVar[16u].z;
        RVar[127u].x = (RVar[2u].z * dot(vec4(_1569, _1571, _1573, uintBitsToFloat(2147483648u)), vec4(_1577, _1579, _1581, uintBitsToFloat(0u)))) + RVar[127u].w;
        float _1617 = RVar[5u].x;
        float _1619 = RVar[5u].y;
        float _1621 = RVar[5u].z;
        float _1625 = RVar[17u].x;
        float _1627 = RVar[17u].y;
        float _1629 = RVar[17u].z;
        RVar[124u].z = (RVar[2u].z * dot(vec4(_1593, _1595, _1597, uintBitsToFloat(2147483648u)), vec4(_1601, _1603, _1605, uintBitsToFloat(0u)))) + RVar[125u].x;
        float _1647 = RVar[3u].x;
        float _1649 = RVar[19u].x;
        float _1652 = RVar[3u].x;
        float _1654 = RVar[1u].x;
        float _1657 = RVar[3u].y;
        float _1659 = RVar[18u].y;
        RVar[17u].x = (RVar[2u].z * dot(vec4(_1617, _1619, _1621, uintBitsToFloat(2147483648u)), vec4(_1625, _1627, _1629, uintBitsToFloat(0u)))) + RVar[127u].z;
        RVar[127u].z = _1652 * _1654;
        float _1678 = RVar[3u].y;
        float _1680 = RVar[19u].y;
        float _1682 = (_1678 * _1680) + (_1647 * _1649);
        RVar[126u].x = dot(vec4(RVar[3u].x, RVar[3u].z, _1657 * _1659, uintBitsToFloat(2147483648u)), vec4(RVar[18u].x, RVar[18u].z, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[122u].x = _1682;
        float _1694 = RVar[5u].x;
        float _1696 = RVar[19u].x;
        float _1699 = RVar[5u].y;
        float _1701 = RVar[1u].y;
        float _1704 = RVar[3u].z;
        float _1706 = RVar[19u].z;
        float _1710 = RVar[5u].x;
        float _1712 = RVar[18u].x;
        RVar[125u].x = (RVar[3u].y * RVar[1u].y) + RVar[127u].z;
        RVar[127u].z = _1699 * _1701;
        RVar[127u].w = (_1704 * _1706) + _1682;
        float _1718 = RVar[5u].z;
        float _1720 = RVar[5u].y;
        float _1724 = RVar[18u].z;
        float _1726 = RVar[18u].y;
        RVar[18u].x = (RVar[5u].y * RVar[19u].y) + (_1694 * _1696);
        float _1755 = RVar[2u].w;
        float _1757 = RVar[127u].x;
        RVar[127u].x = dot(vec4(RVar[5u].x, RVar[5u].z, RVar[127u].z, uintBitsToFloat(2147483648u)), vec4(RVar[1u].x, RVar[1u].z, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[9u].x = (_1755 * dot(vec4(_1718, _1720, _1710 * _1712, uintBitsToFloat(2147483648u)), vec4(_1724, _1726, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)))) + _1757;
        float _1771 = RVar[2u].w;
        float _1773 = RVar[127u].w;
        float _1775 = RVar[124u].x;
        float _1779 = RVar[3u].z;
        float _1781 = RVar[1u].z;
        float _1783 = RVar[125u].x;
        float _1785 = (_1779 * _1781) + _1783;
        RVar[4u].x = (RVar[2u].w * RVar[126u].x) + RVar[125u].z;
        RVar[4u].y = (_1771 * _1773) + _1775;
        RVar[123u].z = _1785;
        float _1796 = RVar[5u].z;
        float _1798 = RVar[19u].z;
        float _1800 = RVar[18u].x;
        float _1802 = (_1796 * _1798) + _1800;
        RVar[4u].z = (RVar[2u].w * _1785) + RVar[126u].z;
        RVar[123u].w = _1802;
        float _1812 = RVar[2u].w;
        float _1814 = RVar[127u].x;
        float _1816 = RVar[17u].x;
        RVar[9u].y = (RVar[2u].w * _1802) + RVar[124u].z;
        RVar[9u].z = (_1812 * _1814) + _1816;
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
        bool _1851 = floatBitsToInt(RVar[0u].w) == (0);
        predVar = _1851;
        stateVar = _1851 ? 0 : 1;
    }
    if (stateVar == 0)
    {
        float _1860 = RVar[1u].x;
        float _1864 = intBitsToFloat(floatBitsToInt(_1860) * (3));
        RVar[0u].y = _1864;
        float _1875 = RVar[1u].y;
        float _1879 = intBitsToFloat(floatBitsToInt(_1875) * (3));
        RVar[0u].x = intBitsToFloat(floatBitsToInt(_1864) + (1));
        RVar[0u].w = intBitsToFloat(floatBitsToInt(_1864) + (2));
        RVar[0u].z = _1879;
        float _1892 = RVar[1u].z;
        float _1896 = intBitsToFloat(floatBitsToInt(_1892) * (3));
        RVar[1u].x = intBitsToFloat(floatBitsToInt(_1879) + (2));
        RVar[1u].y = intBitsToFloat(floatBitsToInt(_1879) + (1));
        RVar[1u].w = _1896;
        RVar[8u].x = intBitsToFloat(floatBitsToInt(_1896) + (1));
        RVar[8u].y = intBitsToFloat(floatBitsToInt(_1896) + (2));
    }
    if (stateVar == 0)
    {
        RVar[9u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].y)];
        RVar[10u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].x)];
        RVar[11u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].w)];
        RVar[12u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].z)];
        RVar[14u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].y)];
        RVar[13u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].x)];
        RVar[17u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].w)];
        RVar[15u] = CBUFFER_2.values[floatBitsToUint(RVar[8u].x)];
    }
    if (stateVar == 0)
    {
        float _1967 = RVar[4u].x;
        float _1969 = RVar[4u].y;
        float _1971 = RVar[4u].z;
        float _1975 = RVar[9u].x;
        float _1977 = RVar[9u].y;
        float _1979 = RVar[9u].z;
        RVar[8u].x = RVar[3u].z * RVar[9u].z;
        float _2007 = RVar[9u].w;
        RVar[1u].w = dot(vec4(RVar[4u].x, RVar[4u].y, RVar[4u].z, uintBitsToFloat(2147483648u)), vec4(RVar[10u].x, RVar[10u].y, RVar[10u].z, uintBitsToFloat(0u)));
        RVar[0u].w = _2007 + dot(vec4(_1967, _1969, _1971, uintBitsToFloat(2147483648u)), vec4(_1975, _1977, _1979, uintBitsToFloat(0u)));
    }
    if (stateVar == 0)
    {
        RVar[16u] = CBUFFER_2.values[floatBitsToUint(RVar[8u].y)];
    }
    if (stateVar == 0)
    {
        float _2026 = RVar[4u].x;
        float _2028 = RVar[4u].y;
        float _2030 = RVar[4u].z;
        float _2034 = RVar[11u].x;
        float _2036 = RVar[11u].y;
        float _2038 = RVar[11u].z;
        float _2051 = RVar[11u].w;
        float _2054 = RVar[2u].x;
        float _2056 = RVar[0u].w;
        float _2059 = RVar[3u].z;
        float _2061 = RVar[10u].z;
        float _2064 = RVar[3u].y;
        float _2066 = RVar[9u].y;
        float _2068 = RVar[8u].x;
        RVar[127u].x = RVar[2u].x * (RVar[10u].w + RVar[1u].w);
        RVar[127u].z = _2054 * _2056;
        RVar[125u].w = _2059 * _2061;
        RVar[124u].x = (_2064 * _2066) + _2068;
        float _2076 = RVar[4u].x;
        float _2078 = RVar[4u].y;
        float _2080 = RVar[4u].z;
        float _2084 = RVar[12u].x;
        float _2086 = RVar[12u].y;
        float _2088 = RVar[12u].z;
        RVar[126u].x = RVar[2u].x * (_2051 + dot(vec4(_2026, _2028, _2030, uintBitsToFloat(2147483648u)), vec4(_2034, _2036, _2038, uintBitsToFloat(0u))));
        float _2097 = RVar[4u].x;
        float _2099 = RVar[4u].y;
        float _2101 = RVar[4u].z;
        float _2105 = RVar[14u].x;
        float _2107 = RVar[14u].y;
        float _2109 = RVar[14u].z;
        RVar[125u].x = RVar[12u].w + dot(vec4(_2076, _2078, _2080, uintBitsToFloat(2147483648u)), vec4(_2084, _2086, _2088, uintBitsToFloat(0u)));
        float _2118 = RVar[4u].x;
        float _2120 = RVar[4u].y;
        float _2122 = RVar[4u].z;
        float _2126 = RVar[13u].x;
        float _2128 = RVar[13u].y;
        float _2130 = RVar[13u].z;
        RVar[127u].w = RVar[14u].w + dot(vec4(_2097, _2099, _2101, uintBitsToFloat(2147483648u)), vec4(_2105, _2107, _2109, uintBitsToFloat(0u)));
        float _2143 = RVar[127u].z;
        float _2147 = RVar[13u].w;
        float _2150 = RVar[126u].x;
        float _2154 = RVar[2u].y;
        float _2156 = RVar[125u].x;
        RVar[127u].x += uintBitsToFloat(0u);
        RVar[127u].y = _2143 + uintBitsToFloat(0u);
        RVar[127u].z = _2147 + dot(vec4(_2118, _2120, _2122, uintBitsToFloat(2147483648u)), vec4(_2126, _2128, _2130, uintBitsToFloat(0u)));
        RVar[124u].w = _2150 + uintBitsToFloat(0u);
        RVar[126u].w = _2154 * _2156;
        float _2164 = RVar[4u].x;
        float _2166 = RVar[4u].y;
        float _2168 = RVar[4u].z;
        float _2172 = RVar[17u].x;
        float _2174 = RVar[17u].y;
        float _2176 = RVar[17u].z;
        RVar[126u].z = RVar[2u].y * RVar[127u].w;
        float _2187 = RVar[4u].x;
        float _2189 = RVar[4u].y;
        float _2191 = RVar[4u].z;
        float _2195 = RVar[15u].x;
        float _2197 = RVar[15u].y;
        float _2199 = RVar[15u].z;
        RVar[126u].y = RVar[17u].w + dot(vec4(_2164, _2166, _2168, uintBitsToFloat(2147483648u)), vec4(_2172, _2174, _2176, uintBitsToFloat(0u)));
        float _2208 = RVar[4u].x;
        float _2210 = RVar[4u].y;
        float _2212 = RVar[4u].z;
        float _2216 = RVar[16u].x;
        float _2218 = RVar[16u].y;
        float _2220 = RVar[16u].z;
        RVar[125u].y = RVar[15u].w + dot(vec4(_2187, _2189, _2191, uintBitsToFloat(2147483648u)), vec4(_2195, _2197, _2199, uintBitsToFloat(0u)));
        float _2234 = RVar[2u].y;
        float _2236 = RVar[127u].z;
        float _2239 = RVar[127u].y;
        float _2241 = RVar[126u].w;
        float _2244 = RVar[16u].w;
        float _2247 = RVar[3u].x;
        float _2249 = RVar[10u].x;
        float _2251 = RVar[125u].w;
        RVar[127u].x += RVar[126u].z;
        RVar[127u].z = _2239 + _2241;
        RVar[126u].x = (_2247 * _2249) + _2251;
        float _2258 = RVar[124u].w;
        float _2261 = RVar[2u].z;
        float _2263 = RVar[125u].y;
        float _2266 = RVar[2u].z;
        float _2269 = RVar[2u].z;
        float _2271 = RVar[126u].y;
        float _2274 = RVar[3u].x;
        float _2276 = RVar[9u].x;
        float _2278 = RVar[124u].x;
        float _2280 = (_2274 * _2276) + _2278;
        RVar[122u].x = _2280;
        float _2286 = RVar[127u].x;
        float _2290 = RVar[3u].y;
        float _2292 = RVar[10u].y;
        float _2294 = RVar[126u].x;
        float _2296 = (_2290 * _2292) + _2294;
        float _2298 = RVar[2u].x;
        RVar[20u].x = RVar[127u].z + (_2269 * _2271);
        RVar[20u].y = _2286 + (_2261 * _2263);
        RVar[20u].z = (_2258 + (_2234 * _2236)) + (_2266 * (_2244 + dot(vec4(_2208, _2210, _2212, uintBitsToFloat(2147483648u)), vec4(_2216, _2218, _2220, uintBitsToFloat(0u)))));
        RVar[123u].w = _2296;
        RVar[125u].y = (_2298 * _2280) + uintBitsToFloat(0u);
        float _2308 = RVar[3u].x;
        float _2310 = RVar[3u].y;
        float _2312 = RVar[3u].z;
        float _2316 = RVar[11u].x;
        float _2318 = RVar[11u].y;
        float _2320 = RVar[11u].z;
        RVar[126u].w = (RVar[2u].x * _2296) + uintBitsToFloat(0u);
        float _2331 = RVar[5u].x;
        float _2333 = RVar[5u].y;
        float _2335 = RVar[5u].z;
        float _2339 = RVar[9u].x;
        float _2341 = RVar[9u].y;
        float _2343 = RVar[9u].z;
        RVar[127u].y = (RVar[2u].x * dot(vec4(_2308, _2310, _2312, uintBitsToFloat(2147483648u)), vec4(_2316, _2318, _2320, uintBitsToFloat(0u)))) + uintBitsToFloat(0u);
        float _2354 = RVar[5u].x;
        float _2356 = RVar[5u].y;
        float _2358 = RVar[5u].z;
        float _2362 = RVar[10u].x;
        float _2364 = RVar[10u].y;
        float _2366 = RVar[10u].z;
        RVar[10u].w = (RVar[2u].x * dot(vec4(_2331, _2333, _2335, uintBitsToFloat(2147483648u)), vec4(_2339, _2341, _2343, uintBitsToFloat(0u)))) + uintBitsToFloat(0u);
        float _2377 = RVar[5u].x;
        float _2379 = RVar[5u].y;
        float _2381 = RVar[5u].z;
        float _2385 = RVar[11u].x;
        float _2387 = RVar[11u].y;
        float _2389 = RVar[11u].z;
        RVar[10u].y = (RVar[2u].x * dot(vec4(_2354, _2356, _2358, uintBitsToFloat(2147483648u)), vec4(_2362, _2364, _2366, uintBitsToFloat(0u)))) + uintBitsToFloat(0u);
        float _2400 = RVar[3u].z;
        float _2402 = RVar[12u].z;
        float _2410 = RVar[5u].x;
        float _2412 = RVar[12u].x;
        float _2415 = RVar[2u].x;
        float _2420 = RVar[3u].z;
        float _2422 = RVar[14u].z;
        RVar[126u].y = RVar[3u].y * RVar[13u].y;
        RVar[11u].w = (_2415 * dot(vec4(_2377, _2379, _2381, uintBitsToFloat(2147483648u)), vec4(_2385, _2387, _2389, uintBitsToFloat(0u)))) + uintBitsToFloat(0u);
        RVar[127u].x = _2420 * _2422;
        float _2442 = RVar[3u].y;
        float _2444 = RVar[12u].y;
        float _2446 = (_2442 * _2444) + (_2400 * _2402);
        RVar[11u].y = dot(vec4(RVar[5u].z, RVar[5u].y, _2410 * _2412, uintBitsToFloat(2147483648u)), vec4(RVar[12u].z, RVar[12u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[122u].x = _2446;
        float _2458 = RVar[5u].z;
        float _2460 = RVar[13u].z;
        float _2463 = RVar[3u].x;
        float _2465 = RVar[12u].x;
        float _2469 = RVar[3u].z;
        float _2471 = RVar[13u].z;
        float _2473 = RVar[126u].y;
        float _2475 = (_2469 * _2471) + _2473;
        RVar[127u].x = (RVar[3u].y * RVar[14u].y) + RVar[127u].x;
        RVar[124u].w = (_2463 * _2465) + _2446;
        RVar[122u].x = _2475;
        float _2494 = RVar[3u].x;
        float _2496 = RVar[13u].x;
        float _2498 = (_2494 * _2496) + _2475;
        RVar[13u].y = dot(vec4(RVar[5u].x, RVar[5u].y, _2458 * _2460, uintBitsToFloat(2147483648u)), vec4(RVar[13u].x, RVar[13u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[122u].x = _2498;
        float _2508 = RVar[3u].x;
        float _2510 = RVar[14u].x;
        float _2512 = RVar[127u].x;
        float _2514 = (_2508 * _2510) + _2512;
        float _2516 = RVar[2u].y;
        float _2518 = RVar[124u].w;
        float _2520 = RVar[125u].y;
        float _2524 = RVar[5u].z;
        float _2526 = RVar[17u].z;
        float _2529 = RVar[5u].z;
        float _2531 = RVar[14u].z;
        RVar[13u].x = (RVar[2u].y * _2498) + RVar[127u].y;
        RVar[123u].y = _2514;
        RVar[13u].z = (_2516 * _2518) + _2520;
        RVar[13u].w = _2524 * _2526;
        float _2552 = RVar[2u].y;
        float _2554 = RVar[126u].w;
        RVar[14u].w = dot(vec4(RVar[5u].x, RVar[5u].y, _2529 * _2531, uintBitsToFloat(2147483648u)), vec4(RVar[14u].x, RVar[14u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[14u].x = (_2552 * _2514) + _2554;
    }
    if (stateVar == 0)
    {
        float _2572 = RVar[3u].z;
        float _2574 = RVar[17u].z;
        float _2577 = RVar[2u].y;
        float _2579 = RVar[14u].w;
        float _2581 = RVar[10u].y;
        float _2585 = RVar[3u].z;
        float _2587 = RVar[15u].z;
        float _2590 = RVar[5u].x;
        float _2592 = RVar[17u].x;
        float _2594 = RVar[13u].w;
        RVar[126u].x = (RVar[2u].y * RVar[11u].y) + RVar[10u].w;
        RVar[126u].z = (_2577 * _2579) + _2581;
        RVar[127u].x = (_2590 * _2592) + _2594;
        float _2609 = RVar[3u].x;
        float _2611 = RVar[15u].x;
        float _2615 = RVar[3u].z;
        float _2617 = RVar[16u].z;
        float _2620 = RVar[5u].z;
        float _2622 = RVar[16u].z;
        float _2625 = RVar[3u].x;
        float _2627 = RVar[17u].x;
        float _2629 = (_2625 * _2627) + (_2572 * _2574);
        RVar[125u].x = (RVar[2u].y * RVar[13u].y) + RVar[11u].w;
        RVar[127u].y = (_2609 * _2611) + (_2585 * _2587);
        RVar[126u].w = _2620 * _2622;
        RVar[122u].x = _2629;
        float _2649 = RVar[3u].y;
        float _2651 = RVar[17u].y;
        float _2653 = (_2649 * _2651) + _2629;
        RVar[127u].z = dot(vec4(RVar[3u].x, RVar[3u].y, _2615 * _2617, uintBitsToFloat(2147483648u)), vec4(RVar[16u].x, RVar[16u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[122u].x = _2653;
        float _2657 = RVar[5u].x;
        float _2659 = RVar[16u].x;
        float _2661 = RVar[126u].w;
        float _2663 = (_2657 * _2659) + _2661;
        float _2665 = RVar[5u].x;
        float _2667 = RVar[15u].x;
        float _2670 = RVar[3u].y;
        float _2672 = RVar[15u].y;
        float _2674 = RVar[127u].y;
        float _2678 = RVar[2u].z;
        float _2680 = RVar[13u].z;
        RVar[123u].x = _2663;
        RVar[126u].w = (_2670 * _2672) + _2674;
        RVar[4u].x = (_2678 * _2653) + _2680;
        float _2701 = RVar[5u].y;
        float _2703 = RVar[16u].y;
        RVar[124u].w = dot(vec4(RVar[5u].z, RVar[5u].y, _2665 * _2667, uintBitsToFloat(2147483648u)), vec4(RVar[15u].z, RVar[15u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[124u].x = (_2701 * _2703) + _2663;
        float _2709 = RVar[5u].y;
        float _2711 = RVar[17u].y;
        float _2713 = RVar[127u].x;
        float _2715 = (_2709 * _2711) + _2713;
        float _2717 = RVar[2u].z;
        float _2719 = RVar[127u].z;
        float _2721 = RVar[13u].x;
        float _2725 = RVar[2u].z;
        float _2727 = RVar[126u].w;
        float _2729 = RVar[14u].x;
        RVar[123u].y = _2715;
        RVar[4u].z = (_2717 * _2719) + _2721;
        RVar[4u].y = (_2725 * _2727) + _2729;
        float _2742 = RVar[2u].z;
        float _2744 = RVar[124u].w;
        float _2746 = RVar[126u].z;
        float _2750 = RVar[2u].z;
        float _2752 = RVar[124u].x;
        float _2754 = RVar[125u].x;
        RVar[9u].x = (RVar[2u].z * _2715) + RVar[126u].x;
        RVar[9u].y = (_2742 * _2744) + _2746;
        RVar[9u].z = (_2750 * _2752) + _2754;
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
        bool _2790 = floatBitsToInt(RVar[0u].w) == (0);
        predVar = _2790;
        stateVar = _2790 ? 0 : 1;
    }
    if (stateVar == 0)
    {
        float _2799 = RVar[1u].x;
        float _2803 = intBitsToFloat(floatBitsToInt(_2799) * (3));
        RVar[0u].z = _2803;
        float _2814 = RVar[1u].y;
        float _2818 = intBitsToFloat(floatBitsToInt(_2814) * (3));
        RVar[1u].x = intBitsToFloat(floatBitsToInt(_2803) + (2));
        RVar[1u].y = intBitsToFloat(floatBitsToInt(_2803) + (1));
        RVar[1u].w = _2818;
        RVar[0u].x = intBitsToFloat(floatBitsToInt(_2818) + (1));
        RVar[0u].y = intBitsToFloat(floatBitsToInt(_2818) + (2));
    }
    if (stateVar == 0)
    {
        RVar[8u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].z)];
        RVar[9u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].y)];
        RVar[10u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].x)];
        RVar[11u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].w)];
        RVar[1u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].x)];
        RVar[0u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].y)];
    }
    if (stateVar == 0)
    {
        float _2877 = RVar[4u].x;
        float _2879 = RVar[4u].y;
        float _2881 = RVar[4u].z;
        float _2885 = RVar[8u].x;
        float _2887 = RVar[8u].y;
        float _2889 = RVar[8u].z;
        RVar[126u].x = RVar[3u].z * RVar[8u].z;
        float _2900 = RVar[4u].x;
        float _2902 = RVar[4u].y;
        float _2904 = RVar[4u].z;
        float _2908 = RVar[9u].x;
        float _2910 = RVar[9u].y;
        float _2912 = RVar[9u].z;
        RVar[127u].x = RVar[8u].w + dot(vec4(_2877, _2879, _2881, uintBitsToFloat(2147483648u)), vec4(_2885, _2887, _2889, uintBitsToFloat(0u)));
        float _2921 = RVar[4u].x;
        float _2923 = RVar[4u].y;
        float _2925 = RVar[4u].z;
        float _2929 = RVar[10u].x;
        float _2931 = RVar[10u].y;
        float _2933 = RVar[10u].z;
        float _2944 = RVar[3u].z;
        float _2946 = RVar[9u].z;
        float _2949 = RVar[10u].w;
        float _2952 = RVar[2u].x;
        float _2954 = RVar[127u].x;
        float _2957 = RVar[3u].y;
        float _2959 = RVar[8u].y;
        float _2961 = RVar[126u].x;
        RVar[127u].x = RVar[2u].x * (RVar[9u].w + dot(vec4(_2900, _2902, _2904, uintBitsToFloat(2147483648u)), vec4(_2908, _2910, _2912, uintBitsToFloat(0u))));
        RVar[124u].y = _2944 * _2946;
        RVar[127u].w = _2952 * _2954;
        RVar[126u].x = (_2957 * _2959) + _2961;
        float _2969 = RVar[4u].x;
        float _2971 = RVar[4u].y;
        float _2973 = RVar[4u].z;
        float _2977 = RVar[11u].x;
        float _2979 = RVar[11u].y;
        float _2981 = RVar[11u].z;
        RVar[127u].y = RVar[2u].x * (_2949 + dot(vec4(_2921, _2923, _2925, uintBitsToFloat(2147483648u)), vec4(_2929, _2931, _2933, uintBitsToFloat(0u))));
        float _2990 = RVar[4u].x;
        float _2992 = RVar[4u].y;
        float _2994 = RVar[4u].z;
        float _2998 = RVar[1u].x;
        float _3000 = RVar[1u].y;
        float _3002 = RVar[1u].z;
        RVar[126u].y = RVar[11u].w + dot(vec4(_2969, _2971, _2973, uintBitsToFloat(2147483648u)), vec4(_2977, _2979, _2981, uintBitsToFloat(0u)));
        float _3011 = RVar[4u].x;
        float _3013 = RVar[4u].y;
        float _3015 = RVar[4u].z;
        float _3019 = RVar[0u].x;
        float _3021 = RVar[0u].y;
        float _3023 = RVar[0u].z;
        RVar[125u].y = RVar[1u].w + dot(vec4(_2990, _2992, _2994, uintBitsToFloat(2147483648u)), vec4(_2998, _3000, _3002, uintBitsToFloat(0u)));
        float _3036 = RVar[127u].x;
        float _3040 = RVar[127u].w;
        float _3044 = RVar[0u].w;
        float _3047 = RVar[2u].y;
        float _3049 = RVar[126u].y;
        RVar[127u].x = RVar[127u].y + uintBitsToFloat(0u);
        RVar[127u].y = _3036 + uintBitsToFloat(0u);
        float _3055 = RVar[2u].y;
        float _3058 = RVar[3u].x;
        float _3060 = RVar[8u].x;
        float _3062 = RVar[126u].x;
        float _3066 = RVar[2u].y;
        float _3068 = RVar[125u].y;
        float _3071 = RVar[3u].z;
        float _3073 = RVar[10u].z;
        RVar[20u].x = (_3040 + uintBitsToFloat(0u)) + (_3047 * _3049);
        RVar[126u].z = (_3058 * _3060) + _3062;
        RVar[126u].x = _3071 * _3073;
        float _3087 = RVar[127u].y;
        float _3090 = RVar[127u].x;
        float _3093 = RVar[5u].z;
        float _3095 = RVar[9u].z;
        float _3098 = RVar[5u].z;
        float _3100 = RVar[8u].z;
        RVar[127u].x = (RVar[3u].x * RVar[9u].x) + RVar[124u].y;
        RVar[20u].y = _3087 + (_3066 * _3068);
        RVar[20u].z = _3090 + (_3055 * (_3044 + dot(vec4(_3011, _3013, _3015, uintBitsToFloat(2147483648u)), vec4(_3019, _3021, _3023, uintBitsToFloat(0u)))));
        float _3120 = RVar[5u].y;
        float _3122 = RVar[9u].y;
        float _3124 = (_3120 * _3122) + (_3093 * _3095);
        RVar[124u].y = dot(vec4(RVar[5u].x, RVar[5u].y, _3098 * _3100, uintBitsToFloat(2147483648u)), vec4(RVar[8u].x, RVar[8u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[122u].x = _3124;
        float _3128 = RVar[5u].z;
        float _3130 = RVar[10u].z;
        float _3141 = RVar[5u].z;
        float _3143 = RVar[11u].z;
        float _3146 = RVar[5u].x;
        float _3148 = RVar[9u].x;
        float _3152 = RVar[3u].y;
        float _3154 = RVar[11u].y;
        RVar[127u].y = (RVar[3u].y * RVar[9u].y) + RVar[127u].x;
        RVar[127u].z = _3141 * _3143;
        RVar[127u].w = (_3146 * _3148) + _3124;
        RVar[127u].x = _3152 * _3154;
        float _3161 = RVar[3u].x;
        float _3163 = RVar[3u].y;
        float _3165 = RVar[126u].x;
        float _3169 = RVar[10u].x;
        float _3171 = RVar[10u].y;
        float _3177 = RVar[5u].y;
        float _3179 = RVar[10u].y;
        float _3181 = (_3177 * _3179) + (_3128 * _3130);
        RVar[122u].x = _3181;
        float _3192 = RVar[5u].x;
        float _3194 = RVar[10u].x;
        float _3196 = (_3192 * _3194) + _3181;
        float _3198 = RVar[2u].x;
        float _3200 = RVar[126u].z;
        float _3205 = RVar[2u].x;
        float _3207 = RVar[127u].y;
        float _3212 = RVar[2u].x;
        RVar[126u].x = (RVar[5u].y * RVar[11u].y) + RVar[127u].z;
        RVar[123u].y = _3196;
        RVar[127u].z = (_3198 * _3200) + uintBitsToFloat(0u);
        RVar[126u].w = (_3205 * _3207) + uintBitsToFloat(0u);
        RVar[125u].z = (_3212 * dot(vec4(_3161, _3163, _3165, uintBitsToFloat(2147483648u)), vec4(_3169, _3171, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)))) + uintBitsToFloat(0u);
        float _3229 = RVar[2u].x;
        float _3234 = RVar[2u].x;
        float _3236 = RVar[127u].w;
        float _3241 = RVar[3u].z;
        float _3243 = RVar[1u].z;
        float _3246 = RVar[3u].z;
        float _3248 = RVar[11u].z;
        float _3250 = RVar[127u].x;
        float _3252 = (_3246 * _3248) + _3250;
        RVar[124u].x = (RVar[2u].x * RVar[124u].y) + uintBitsToFloat(0u);
        RVar[124u].y = (_3229 * _3196) + uintBitsToFloat(0u);
        RVar[124u].z = (_3234 * _3236) + uintBitsToFloat(0u);
        RVar[122u].x = _3252;
        float _3264 = RVar[3u].z;
        float _3266 = RVar[0u].z;
        float _3269 = RVar[5u].y;
        float _3271 = RVar[1u].y;
        float _3274 = RVar[5u].z;
        float _3276 = RVar[0u].z;
        float _3279 = RVar[3u].y;
        float _3281 = RVar[1u].y;
        RVar[125u].x = (RVar[3u].x * RVar[11u].x) + _3252;
        RVar[127u].w = _3274 * _3276;
        RVar[127u].x = (_3279 * _3281) + (_3241 * _3243);
        float _3302 = RVar[5u].z;
        float _3304 = RVar[1u].z;
        float _3306 = (_3302 * _3304) + (_3269 * _3271);
        RVar[126u].z = dot(vec4(RVar[3u].x, RVar[3u].y, _3264 * _3266, uintBitsToFloat(2147483648u)), vec4(RVar[0u].x, RVar[0u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[122u].x = _3306;
        float _3326 = RVar[5u].x;
        float _3328 = RVar[1u].x;
        RVar[0u].x = dot(vec4(RVar[5u].x, RVar[5u].y, RVar[127u].w, uintBitsToFloat(2147483648u)), vec4(RVar[0u].x, RVar[0u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[125u].w = (_3326 * _3328) + _3306;
        RVar[127u].w = (RVar[3u].x * RVar[1u].x) + RVar[127u].x;
        float _3343 = RVar[5u].x;
        float _3345 = RVar[11u].x;
        float _3347 = RVar[126u].x;
        float _3349 = (_3343 * _3345) + _3347;
        RVar[123u].y = _3349;
        float _3360 = RVar[2u].y;
        float _3362 = RVar[127u].w;
        float _3364 = RVar[126u].w;
        float _3368 = RVar[2u].y;
        float _3370 = RVar[126u].z;
        float _3372 = RVar[125u].z;
        float _3376 = RVar[2u].y;
        float _3378 = RVar[124u].x;
        RVar[4u].x = (RVar[2u].y * RVar[125u].x) + RVar[127u].z;
        RVar[4u].y = (_3360 * _3362) + _3364;
        RVar[4u].z = (_3368 * _3370) + _3372;
        RVar[9u].x = (_3376 * _3349) + _3378;
        float _3394 = RVar[2u].y;
        float _3396 = RVar[0u].x;
        float _3398 = RVar[124u].y;
        RVar[9u].y = (RVar[2u].y * RVar[125u].w) + RVar[124u].z;
        RVar[9u].z = (_3394 * _3396) + _3398;
    }
    if (stackVar[stackIdxVar - 1] == 0)
    {
        stateVar = int(stateVar == 0);
    }
    if (stateVar == 0)
    {
        float _3420 = RVar[9u].y;
        float _3422 = RVar[9u].z;
        RVar[20u].x = RVar[9u].x;
        RVar[20u].y = _3420;
        RVar[20u].z = _3422;
        float _3429 = RVar[9u].y;
        float _3431 = RVar[9u].z;
        RVar[4u].x = RVar[9u].x;
        RVar[4u].y = _3429;
        RVar[4u].z = _3431;
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
        RVar[127u].y = dot(vec4(RVar[20u].x, RVar[20u].y, RVar[20u].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[3].x, CBUFFER_3.values[3].y, CBUFFER_3.values[3].z, uintBitsToFloat(0u)));
        RVar[2u].z = uintBitsToFloat(1065353216u);
        RVar[127u].w = dot(vec4(RVar[20u].x, RVar[20u].y, RVar[20u].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[4].x, CBUFFER_3.values[4].y, CBUFFER_3.values[4].z, uintBitsToFloat(0u)));
        RVar[3u].z = uintBitsToFloat(1065353216u);
        float _3513 = RVar[4u].z;
        float _3515 = RVar[4u].z;
        RVar[126u].w = dot(vec4(RVar[20u].x, RVar[20u].y, RVar[20u].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[5].x, CBUFFER_3.values[5].y, CBUFFER_3.values[5].z, uintBitsToFloat(0u)));
        float _3537 = RVar[4u].y;
        float _3539 = RVar[4u].y;
        float _3541 = (_3537 * _3539) + (_3513 * _3515);
        RVar[125u].w = dot(vec4(RVar[20u].x, RVar[20u].y, RVar[20u].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[6].x, CBUFFER_3.values[6].y, CBUFFER_3.values[6].z, uintBitsToFloat(0u)));
        RVar[122u].x = _3541;
        float _3552 = RVar[127u].w;
        float _3555 = RVar[4u].x;
        float _3557 = RVar[4u].x;
        float _3559 = (_3555 * _3557) + _3541;
        float _3561 = RVar[9u].z;
        float _3563 = RVar[9u].z;
        RVar[1u].x = CBUFFER_3.values[3].w + RVar[127u].y;
        RVar[1u].y = CBUFFER_3.values[4].w + _3552;
        RVar[123u].z = _3559;
        float _3569 = RVar[9u].y;
        float _3571 = RVar[9u].y;
        float _3573 = (_3569 * _3571) + (_3561 * _3563);
        float _3577 = RVar[126u].w;
        float _3582 = RVar[125u].w;
        float _3585 = inversesqrt(_3559);
        RVar[123u].x = _3573;
        RVar[1u].z = CBUFFER_3.values[5].w + _3577;
        RVar[1u].w = CBUFFER_3.values[6].w + _3582;
        RVar[2u].w = _3585;
        float _3608 = RVar[9u].x;
        float _3610 = RVar[9u].x;
        float _3621 = RVar[4u].x;
        RVar[0u].x = intBitsToFloat(floatBitsToInt(CBUFFER_4.values[0].x) + (25));
        RVar[0u].y = intBitsToFloat(floatBitsToInt(CBUFFER_4.values[0].x) + (41));
        RVar[0u].z = (_3608 * _3610) + _3573;
        RVar[0u].w = intBitsToFloat(floatBitsToInt(CBUFFER_4.values[0].x) + (33));
        RVar[4u].x = _3621 * _3585;
    }
    if (stateVar == 0)
    {
        RVar[2u] = vec4(CBUFFER_3.values[floatBitsToUint(RVar[0u].w)].x, RVar[2u].y, RVar[2u].z, RVar[2u].w);
        RVar[3u] = vec4(CBUFFER_3.values[floatBitsToUint(RVar[0u].y)].x, RVar[3u].y, RVar[3u].z, RVar[3u].w);
        uint _3650 = floatBitsToUint(RVar[0u].x);
        RVar[8u] = vec4(CBUFFER_3.values[_3650].x, CBUFFER_3.values[_3650].y, CBUFFER_3.values[_3650].z, RVar[8u].w);
    }
    vec4 _3672 = (RVar[1u] * vec4(VS_PUSH.posMulAdd.xy, 1.0, 1.0)) + vec4(VS_PUSH.posMulAdd.zw, 0.0, 0.0);
    vec4 _3675 = _3672;
    _3675.y = -_3672.y;
    vec4 _3683 = _3675;
    _3683.z = (_3675.z + (_3675.w * VS_PUSH.zSpaceMul.x)) * VS_PUSH.zSpaceMul.y;
    gl_Position = _3683;
    if (stateVar == 0)
    {
        float _3689 = RVar[20u].z;
        float _3699 = RVar[4u].z;
        float _3701 = RVar[2u].w;
        float _3705 = RVar[6u].y;
        float _3710 = RVar[0u].z;
        float _3711 = inversesqrt(_3710);
        RVar[125u].y = RVar[4u].y * RVar[2u].w;
        RVar[126u].z = _3699 * _3701;
        float _3715 = RVar[9u].x;
        float _3716 = _3715 * _3711;
        float _3718 = RVar[9u].y;
        float _3719 = _3718 * _3711;
        float _3721 = RVar[9u].z;
        float _3722 = _3721 * _3711;
        float _3724 = RVar[2u].z;
        float _3728 = (_3724 * CBUFFER_4.values[1].z) + (_3705 * CBUFFER_4.values[1].y);
        float _3730 = RVar[20u].y;
        float _3734 = (_3730 * CBUFFER_3.values[2].y) + (_3689 * CBUFFER_3.values[2].z);
        RVar[126u].x = _3716;
        RVar[127u].y = _3719;
        RVar[127u].z = _3722;
        RVar[123u].w = _3728;
        RVar[122u].x = _3734;
        float _3741 = RVar[126u].z;
        float _3744 = RVar[125u].y;
        float _3747 = RVar[4u].x;
        float _3750 = RVar[20u].x;
        float _3754 = (_3750 * CBUFFER_3.values[2].x) + _3734;
        float _3756 = RVar[2u].z;
        float _3760 = (_3756 * CBUFFER_4.values[1].w) + _3728;
        RVar[123u].w = _3754;
        RVar[122u].x = _3760;
        float _3764 = RVar[126u].x;
        float _3767 = RVar[125u].y;
        float _3769 = ((-_3764) * _3767) + (_3747 * _3719);
        float _3771 = RVar[127u].z;
        float _3774 = RVar[4u].x;
        float _3776 = ((-_3771) * _3774) + (_3741 * _3716);
        float _3778 = RVar[127u].y;
        float _3781 = RVar[126u].z;
        float _3783 = ((-_3778) * _3781) + (_3744 * _3722);
        float _3788 = RVar[6u].x;
        RVar[123u].x = _3769;
        RVar[123u].y = _3776;
        RVar[123u].z = _3783;
        RVar[0u].x = (_3788 * CBUFFER_4.values[1].x) + _3760;
        float _3801 = RVar[5u].w;
        float _3805 = RVar[2u].x;
        float _3809 = RVar[5u].w;
        float _3812 = RVar[127u].z;
        RVar[125u].x = RVar[5u].w * _3783;
        RVar[126u].y = _3801 * _3776;
        RVar[126u].w = _3809 * _3769;
        RVar[127u].x = _3812 * CBUFFER_3.values[0].z;
        float _3833 = RVar[3u].x;
        RVar[0u].y = dot(vec4(RVar[6u].x, RVar[6u].y, RVar[2u].z, RVar[2u].z), CBUFFER_4.values[2]);
        RVar[8u].w = clamp(((-(CBUFFER_3.values[2].w + _3754)) + (-_3805)) * _3833, 0.0, 1.0);
        RVar[1u].x = dot(vec4(RVar[7u].x, RVar[7u].y, RVar[3u].z, RVar[3u].z), CBUFFER_4.values[4]);
        RVar[1u].y = dot(vec4(RVar[7u].x, RVar[7u].y, RVar[3u].z, RVar[3u].z), CBUFFER_4.values[5]);
        float _3882 = RVar[126u].w;
        RVar[2u].x = dot(vec4(RVar[126u].x, RVar[127u].y, RVar[127u].x, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[0].x, CBUFFER_3.values[0].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        float _3902 = RVar[126u].z;
        RVar[2u].y = dot(vec4(RVar[125u].x, RVar[126u].y, _3882 * CBUFFER_3.values[0].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[0].x, CBUFFER_3.values[0].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        float _3922 = RVar[127u].z;
        RVar[2u].z = dot(vec4(RVar[4u].x, RVar[125u].y, _3902 * CBUFFER_3.values[0].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[0].x, CBUFFER_3.values[0].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        float _3942 = RVar[126u].w;
        RVar[3u].x = dot(vec4(RVar[126u].x, RVar[127u].y, _3922 * CBUFFER_3.values[1].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[1].x, CBUFFER_3.values[1].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        float _3962 = RVar[126u].z;
        RVar[3u].y = dot(vec4(RVar[125u].x, RVar[126u].y, _3942 * CBUFFER_3.values[1].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[1].x, CBUFFER_3.values[1].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        float _3982 = RVar[127u].z;
        RVar[3u].z = dot(vec4(RVar[4u].x, RVar[125u].y, _3962 * CBUFFER_3.values[1].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[1].x, CBUFFER_3.values[1].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        float _4002 = RVar[126u].w;
        RVar[5u].x = dot(vec4(RVar[126u].x, RVar[127u].y, _3982 * CBUFFER_3.values[2].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[2].x, CBUFFER_3.values[2].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        float _4022 = RVar[126u].z;
        RVar[5u].y = dot(vec4(RVar[125u].x, RVar[126u].y, _4002 * CBUFFER_3.values[2].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[2].x, CBUFFER_3.values[2].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[5u].z = dot(vec4(RVar[4u].x, RVar[125u].y, _4022 * CBUFFER_3.values[2].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[2].x, CBUFFER_3.values[2].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
    }
    PARAM_0 = RVar[8u];
    PARAM_1 = RVar[3u];
    PARAM_2 = RVar[5u];
    PARAM_3 = RVar[2u];
    PARAM_4 = vec4(RVar[0u].x, RVar[0u].y, RVar[0u].z, RVar[0u].z);
    PARAM_5 = vec4(RVar[1u].x, RVar[1u].y, RVar[1u].z, RVar[1u].z);
    if (stateVar == 0)
    {
    }
}

 