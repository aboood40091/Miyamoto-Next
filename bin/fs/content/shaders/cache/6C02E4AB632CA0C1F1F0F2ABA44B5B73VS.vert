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
layout(location = 0) in uvec4 aBlendIndex_0_0;
layout(location = 1) in uvec4 aBlendWeight_0_0;
layout(location = 2) in uvec4 aColor0_0_0;
layout(location = 3) in uvec3 aNormal_0_0;
layout(location = 4) in uvec3 aPosition_0_0;
layout(location = 5) in uvec2 aTexCoord0_0_0;
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
        RVar[3u] = vec4(uintBitsToFloat(aColor0_0_0.x), uintBitsToFloat(aColor0_0_0.y), uintBitsToFloat(aColor0_0_0.z), uintBitsToFloat(aColor0_0_0.w));
        RVar[4u] = vec4(vec4(uintBitsToFloat(aNormal_0_0.x), uintBitsToFloat(aNormal_0_0.y), uintBitsToFloat(aNormal_0_0.z), 1.0).xyz, 1.0);
        RVar[5u] = vec4(vec4(uintBitsToFloat(aPosition_0_0.x), uintBitsToFloat(aPosition_0_0.y), uintBitsToFloat(aPosition_0_0.z), 1.0).xyz, 1.0);
        RVar[6u] = vec4(vec4(uintBitsToFloat(aTexCoord0_0_0.x), uintBitsToFloat(aTexCoord0_0_0.y), 0.0, 1.0).xy, 0.0, 1.0);
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
        RVar[7u].x = uintBitsToFloat(0u);
        RVar[7u].y = uintBitsToFloat(0u);
        RVar[7u].z = uintBitsToFloat(0u);
        RVar[0u].w = intBitsToFloat((floatBitsToInt(CBUFFER_1.values[3].x) != (0)) ? (-1) : 0);
        bool _90 = floatBitsToInt(RVar[0u].w) == (0);
        predVar = _90;
        stateVar = _90 ? 0 : 1;
    }
    if (stateVar == 0)
    {
        float _124 = RVar[4u].z;
        RVar[127u].y = dot(vec4(RVar[5u].x, RVar[5u].y, RVar[5u].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_2.values[0].x, CBUFFER_2.values[0].y, CBUFFER_2.values[0].z, uintBitsToFloat(0u)));
        RVar[126u].x = _124 * CBUFFER_2.values[0].z;
        RVar[127u].x = dot(vec4(RVar[5u].x, RVar[5u].y, RVar[5u].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_2.values[1].x, CBUFFER_2.values[1].y, CBUFFER_2.values[1].z, uintBitsToFloat(0u)));
        RVar[127u].w = dot(vec4(RVar[5u].x, RVar[5u].y, RVar[5u].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_2.values[2].x, CBUFFER_2.values[2].y, CBUFFER_2.values[2].z, uintBitsToFloat(0u)));
        float _176 = RVar[127u].x;
        RVar[20u].x = CBUFFER_2.values[0].w + RVar[127u].y;
        RVar[20u].y = CBUFFER_2.values[1].w + _176;
        float _182 = RVar[4u].y;
        float _186 = RVar[126u].x;
        float _188 = (_182 * CBUFFER_2.values[0].y) + _186;
        float _192 = RVar[127u].w;
        RVar[123u].x = _188;
        RVar[20u].z = CBUFFER_2.values[2].w + _192;
        float _204 = RVar[4u].z;
        RVar[7u].x = (RVar[4u].x * CBUFFER_2.values[0].x) + _188;
        float _225 = RVar[4u].z;
        RVar[7u].y = dot(vec4(RVar[4u].x, RVar[4u].y, _204 * CBUFFER_2.values[1].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_2.values[1].x, CBUFFER_2.values[1].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[7u].z = dot(vec4(RVar[4u].x, RVar[4u].y, _225 * CBUFFER_2.values[2].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_2.values[2].x, CBUFFER_2.values[2].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
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
        bool _275 = floatBitsToInt(RVar[0u].w) == (0);
        predVar = _275;
        stateVar = _275 ? 0 : 1;
    }
    if (stateVar == 0)
    {
        float _284 = RVar[1u].x;
        float _288 = intBitsToFloat(floatBitsToInt(_284) * (3));
        RVar[1u].x = _288;
        RVar[0u].x = intBitsToFloat(floatBitsToInt(_288) + (2));
        RVar[1u].z = intBitsToFloat(floatBitsToInt(_288) + (1));
    }
    if (stateVar == 0)
    {
        RVar[2u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].x)];
        RVar[1u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].z)];
        RVar[0u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].x)];
    }
    if (stateVar == 0)
    {
        float _328 = RVar[5u].x;
        float _330 = RVar[5u].y;
        float _332 = RVar[5u].z;
        float _336 = RVar[2u].x;
        float _338 = RVar[2u].y;
        float _340 = RVar[2u].z;
        RVar[127u].x = RVar[4u].z * RVar[2u].z;
        float _351 = RVar[5u].x;
        float _353 = RVar[5u].y;
        float _355 = RVar[5u].z;
        float _359 = RVar[1u].x;
        float _361 = RVar[1u].y;
        float _363 = RVar[1u].z;
        RVar[20u].x = RVar[2u].w + dot(vec4(_328, _330, _332, uintBitsToFloat(2147483648u)), vec4(_336, _338, _340, uintBitsToFloat(0u)));
        float _372 = RVar[5u].x;
        float _374 = RVar[5u].y;
        float _376 = RVar[5u].z;
        float _380 = RVar[0u].x;
        float _382 = RVar[0u].y;
        float _384 = RVar[0u].z;
        RVar[20u].y = RVar[1u].w + dot(vec4(_351, _353, _355, uintBitsToFloat(2147483648u)), vec4(_359, _361, _363, uintBitsToFloat(0u)));
        float _393 = RVar[4u].y;
        float _395 = RVar[2u].y;
        float _397 = RVar[127u].x;
        float _399 = (_393 * _395) + _397;
        float _401 = RVar[0u].w;
        RVar[123u].x = _399;
        RVar[20u].z = _401 + dot(vec4(_372, _374, _376, uintBitsToFloat(2147483648u)), vec4(_380, _382, _384, uintBitsToFloat(0u)));
        float _412 = RVar[4u].z;
        float _414 = RVar[1u].z;
        RVar[7u].x = (RVar[4u].x * RVar[2u].x) + _399;
        float _432 = RVar[4u].z;
        float _434 = RVar[0u].z;
        RVar[7u].y = dot(vec4(RVar[4u].x, RVar[4u].y, _412 * _414, uintBitsToFloat(2147483648u)), vec4(RVar[1u].x, RVar[1u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[7u].z = dot(vec4(RVar[4u].x, RVar[4u].y, _432 * _434, uintBitsToFloat(2147483648u)), vec4(RVar[0u].x, RVar[0u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
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
        bool _483 = floatBitsToInt(RVar[0u].w) == (0);
        predVar = _483;
        stateVar = _483 ? 0 : 1;
    }
    if (stateVar == 0)
    {
        float _492 = RVar[1u].x;
        float _496 = intBitsToFloat(floatBitsToInt(_492) * (3));
        RVar[0u].x = _496;
        float _507 = RVar[1u].y;
        float _511 = intBitsToFloat(floatBitsToInt(_507) * (3));
        RVar[0u].z = intBitsToFloat(floatBitsToInt(_496) + (2));
        RVar[0u].w = intBitsToFloat(floatBitsToInt(_496) + (1));
        RVar[4u].w = _511;
        float _524 = RVar[1u].z;
        float _528 = intBitsToFloat(floatBitsToInt(_524) * (3));
        RVar[0u].y = intBitsToFloat(floatBitsToInt(_511) + (2));
        RVar[7u].z = intBitsToFloat(floatBitsToInt(_511) + (1));
        RVar[8u].z = _528;
        float _542 = RVar[1u].w;
        RVar[1u].x = intBitsToFloat(floatBitsToInt(_528) + (2));
        RVar[1u].y = intBitsToFloat(floatBitsToInt(_528) + (1));
        RVar[7u].y = intBitsToFloat(floatBitsToInt(_542) * (3));
    }
    if (stateVar == 0)
    {
        RVar[9u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].x)];
        RVar[11u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].w)];
        RVar[10u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].z)];
        RVar[12u] = CBUFFER_2.values[floatBitsToUint(RVar[4u].w)];
        RVar[14u] = CBUFFER_2.values[floatBitsToUint(RVar[7u].z)];
        RVar[13u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].y)];
        RVar[16u] = CBUFFER_2.values[floatBitsToUint(RVar[8u].z)];
        RVar[15u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].y)];
    }
    if (stateVar == 0)
    {
        float _620 = RVar[7u].y;
        float _626 = RVar[4u].z;
        float _628 = RVar[11u].z;
        float _631 = RVar[4u].y;
        float _633 = RVar[10u].y;
        float _636 = RVar[4u].z;
        float _638 = RVar[9u].z;
        RVar[0u].x = intBitsToFloat(floatBitsToInt(RVar[7u].y) + (2));
        RVar[1u].y = intBitsToFloat(floatBitsToInt(_620) + (1));
        RVar[8u].z = _626 * _628;
        RVar[0u].w = _631 * _633;
        float _662 = RVar[4u].y;
        float _664 = RVar[9u].y;
        RVar[4u].w = dot(vec4(RVar[5u].x, RVar[5u].y, RVar[5u].z, uintBitsToFloat(2147483648u)), vec4(RVar[9u].x, RVar[9u].y, RVar[9u].z, uintBitsToFloat(0u)));
        RVar[7u].x = (_662 * _664) + (_636 * _638);
    }
    if (stateVar == 0)
    {
        RVar[17u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].x)];
        RVar[18u] = CBUFFER_2.values[floatBitsToUint(RVar[7u].y)];
        RVar[19u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].y)];
        RVar[1u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].x)];
    }
    if (stateVar == 0)
    {
        float _705 = RVar[5u].x;
        float _707 = RVar[5u].y;
        float _709 = RVar[5u].z;
        float _713 = RVar[11u].x;
        float _715 = RVar[11u].y;
        float _717 = RVar[11u].z;
        RVar[127u].z = RVar[9u].w + RVar[4u].w;
        float _728 = RVar[5u].x;
        float _730 = RVar[5u].y;
        float _732 = RVar[5u].z;
        float _736 = RVar[10u].x;
        float _738 = RVar[10u].y;
        float _740 = RVar[10u].z;
        float _745 = RVar[11u].w;
        float _748 = RVar[10u].w;
        float _756 = RVar[2u].x;
        float _759 = RVar[4u].x;
        float _761 = RVar[10u].x;
        float _763 = RVar[0u].w;
        float _767 = RVar[4u].y;
        float _769 = RVar[11u].y;
        float _771 = RVar[8u].z;
        RVar[127u].y = RVar[2u].x * RVar[127u].z;
        RVar[127u].z = _756 * (_745 + dot(vec4(_705, _707, _709, uintBitsToFloat(2147483648u)), vec4(_713, _715, _717, uintBitsToFloat(0u))));
        RVar[125u].w = (_759 * _761) + _763;
        RVar[124u].x = (_767 * _769) + _771;
        float _781 = RVar[5u].x;
        float _783 = RVar[5u].y;
        float _785 = RVar[5u].z;
        float _789 = RVar[12u].x;
        float _791 = RVar[12u].y;
        float _793 = RVar[12u].z;
        RVar[127u].w = RVar[2u].x * (_748 + dot(vec4(_728, _730, _732, uintBitsToFloat(2147483648u)), vec4(_736, _738, _740, uintBitsToFloat(0u))));
        float _802 = RVar[5u].x;
        float _804 = RVar[5u].y;
        float _806 = RVar[5u].z;
        float _810 = RVar[14u].x;
        float _812 = RVar[14u].y;
        float _814 = RVar[14u].z;
        RVar[126u].y = RVar[12u].w + dot(vec4(_781, _783, _785, uintBitsToFloat(2147483648u)), vec4(_789, _791, _793, uintBitsToFloat(0u)));
        float _823 = RVar[5u].x;
        float _825 = RVar[5u].y;
        float _827 = RVar[5u].z;
        float _831 = RVar[13u].x;
        float _833 = RVar[13u].y;
        float _835 = RVar[13u].z;
        RVar[127u].x = RVar[14u].w + dot(vec4(_802, _804, _806, uintBitsToFloat(2147483648u)), vec4(_810, _812, _814, uintBitsToFloat(0u)));
        float _848 = RVar[127u].z;
        float _852 = RVar[127u].w;
        float _856 = RVar[13u].w;
        float _859 = RVar[2u].y;
        float _861 = RVar[126u].y;
        RVar[126u].x = RVar[127u].y + uintBitsToFloat(0u);
        RVar[127u].y = _848 + uintBitsToFloat(0u);
        RVar[127u].z = _852 + uintBitsToFloat(0u);
        RVar[127u].w = _856 + dot(vec4(_823, _825, _827, uintBitsToFloat(2147483648u)), vec4(_831, _833, _835, uintBitsToFloat(0u)));
        RVar[125u].x = _859 * _861;
        float _869 = RVar[5u].x;
        float _871 = RVar[5u].y;
        float _873 = RVar[5u].z;
        float _877 = RVar[16u].x;
        float _879 = RVar[16u].y;
        float _881 = RVar[16u].z;
        RVar[126u].w = RVar[2u].y * RVar[127u].x;
        float _892 = RVar[5u].x;
        float _894 = RVar[5u].y;
        float _896 = RVar[5u].z;
        float _900 = RVar[15u].x;
        float _902 = RVar[15u].y;
        float _904 = RVar[15u].z;
        RVar[127u].x = RVar[16u].w + dot(vec4(_869, _871, _873, uintBitsToFloat(2147483648u)), vec4(_877, _879, _881, uintBitsToFloat(0u)));
        float _913 = RVar[5u].x;
        float _915 = RVar[5u].y;
        float _917 = RVar[5u].z;
        float _921 = RVar[17u].x;
        float _923 = RVar[17u].y;
        float _925 = RVar[17u].z;
        float _930 = RVar[15u].w;
        float _938 = RVar[2u].z;
        float _940 = RVar[127u].x;
        float _943 = RVar[17u].w;
        float _946 = RVar[126u].x;
        float _948 = RVar[125u].x;
        float _951 = RVar[2u].z;
        RVar[127u].x = RVar[2u].y * RVar[127u].w;
        RVar[126u].y = _938 * _940;
        RVar[126u].z = _943 + dot(vec4(_913, _915, _917, uintBitsToFloat(2147483648u)), vec4(_921, _923, _925, uintBitsToFloat(0u)));
        RVar[127u].w = _946 + _948;
        RVar[124u].z = _951 * (_930 + dot(vec4(_892, _894, _896, uintBitsToFloat(2147483648u)), vec4(_900, _902, _904, uintBitsToFloat(0u))));
        float _976 = RVar[127u].y;
        float _978 = RVar[126u].w;
        RVar[126u].x = dot(vec4(RVar[5u].x, RVar[5u].y, RVar[5u].z, uintBitsToFloat(2147483648u)), vec4(RVar[18u].x, RVar[18u].y, RVar[18u].z, uintBitsToFloat(0u)));
        RVar[125u].z = _976 + _978;
        float _1000 = RVar[127u].z;
        float _1002 = RVar[127u].x;
        RVar[127u].x = dot(vec4(RVar[5u].x, RVar[5u].y, RVar[5u].z, uintBitsToFloat(2147483648u)), vec4(RVar[19u].x, RVar[19u].y, RVar[19u].z, uintBitsToFloat(0u)));
        RVar[127u].y = _1000 + _1002;
        float _1007 = RVar[5u].x;
        float _1009 = RVar[5u].y;
        float _1011 = RVar[5u].z;
        float _1015 = RVar[1u].x;
        float _1017 = RVar[1u].y;
        float _1019 = RVar[1u].z;
        RVar[126u].w = RVar[18u].w + RVar[126u].x;
        float _1030 = RVar[1u].w;
        float _1033 = RVar[2u].z;
        float _1035 = RVar[126u].z;
        float _1043 = RVar[19u].w;
        float _1045 = RVar[127u].x;
        float _1048 = RVar[4u].y;
        float _1050 = RVar[12u].y;
        RVar[126u].z = RVar[127u].w + RVar[126u].y;
        RVar[127u].x = _1048 * _1050;
        float _1055 = RVar[127u].y;
        float _1058 = RVar[125u].z;
        float _1060 = RVar[124u].z;
        float _1068 = RVar[2u].w;
        float _1071 = RVar[2u].w;
        float _1079 = RVar[4u].x;
        float _1081 = RVar[9u].x;
        float _1083 = RVar[7u].x;
        float _1087 = RVar[4u].z;
        float _1089 = RVar[10u].z;
        float _1091 = RVar[125u].w;
        RVar[20u].x = RVar[126u].z + (RVar[2u].w * RVar[126u].w);
        RVar[20u].y = (_1058 + _1060) + (_1068 * (_1043 + _1045));
        RVar[20u].z = (_1055 + (_1033 * _1035)) + (_1071 * (_1030 + dot(vec4(_1007, _1009, _1011, uintBitsToFloat(2147483648u)), vec4(_1015, _1017, _1019, uintBitsToFloat(0u)))));
        RVar[125u].w = (_1079 * _1081) + _1083;
        RVar[126u].y = (_1087 * _1089) + _1091;
        float _1100 = RVar[4u].z;
        float _1102 = RVar[14u].z;
        float _1110 = RVar[4u].y;
        float _1112 = RVar[15u].y;
        float _1115 = RVar[4u].x;
        float _1117 = RVar[11u].x;
        float _1119 = RVar[124u].x;
        float _1123 = RVar[4u].z;
        float _1125 = RVar[13u].z;
        RVar[127u].y = RVar[4u].y * RVar[16u].y;
        RVar[126u].z = _1110 * _1112;
        RVar[126u].w = (_1115 * _1117) + _1119;
        RVar[124u].x = _1123 * _1125;
        float _1148 = RVar[4u].y;
        float _1150 = RVar[14u].y;
        RVar[12u].x = dot(vec4(RVar[4u].x, RVar[4u].z, RVar[127u].x, uintBitsToFloat(2147483648u)), vec4(RVar[12u].x, RVar[12u].z, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[127u].x = (_1148 * _1150) + (_1100 * _1102);
        float _1172 = RVar[4u].z;
        float _1174 = RVar[16u].z;
        float _1176 = RVar[127u].y;
        RVar[13u].x = dot(vec4(RVar[4u].x, RVar[4u].y, RVar[124u].x, uintBitsToFloat(2147483648u)), vec4(RVar[13u].x, RVar[13u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[11u].x = (_1172 * _1174) + _1176;
        float _1182 = RVar[4u].z;
        float _1184 = RVar[15u].z;
        float _1186 = RVar[126u].z;
        float _1188 = (_1182 * _1184) + _1186;
        float _1190 = RVar[4u].y;
        float _1192 = RVar[18u].y;
        float _1195 = RVar[4u].x;
        float _1197 = RVar[14u].x;
        float _1199 = RVar[127u].x;
        float _1203 = RVar[4u].y;
        float _1205 = RVar[17u].y;
        RVar[123u].x = _1188;
        RVar[14u].y = _1190 * _1192;
        RVar[14u].z = (_1195 * _1197) + _1199;
        float _1218 = RVar[2u].x;
        float _1220 = RVar[126u].y;
        float _1225 = RVar[2u].x;
        float _1227 = RVar[126u].w;
        float _1232 = RVar[4u].x;
        float _1234 = RVar[15u].x;
        float _1238 = RVar[4u].z;
        float _1240 = RVar[17u].z;
        RVar[15u].x = (RVar[2u].x * RVar[125u].w) + uintBitsToFloat(0u);
        RVar[15u].y = (_1218 * _1220) + uintBitsToFloat(0u);
        RVar[15u].z = (_1225 * _1227) + uintBitsToFloat(0u);
        RVar[15u].w = (_1232 * _1234) + _1188;
        RVar[14u].x = (_1238 * _1240) + (_1203 * _1205);
    }
    if (stateVar == 0)
    {
        float _1261 = RVar[2u].y;
        float _1263 = RVar[14u].z;
        float _1265 = RVar[15u].z;
        float _1267 = (_1261 * _1263) + _1265;
        float _1269 = RVar[2u].y;
        float _1271 = RVar[12u].x;
        float _1273 = RVar[15u].x;
        RVar[127u].x = (RVar[2u].y * RVar[13u].x) + RVar[15u].y;
        RVar[123u].y = _1267;
        RVar[126u].w = (_1269 * _1271) + _1273;
        float _1288 = RVar[2u].z;
        float _1290 = RVar[15u].w;
        float _1294 = RVar[4u].x;
        float _1296 = RVar[16u].x;
        float _1298 = RVar[11u].x;
        float _1300 = (_1294 * _1296) + _1298;
        float _1302 = RVar[4u].y;
        float _1304 = RVar[19u].y;
        RVar[124u].x = (RVar[4u].z * RVar[18u].z) + RVar[14u].y;
        RVar[126u].y = (_1288 * _1290) + _1267;
        RVar[123u].w = _1300;
        float _1316 = RVar[2u].z;
        float _1318 = RVar[126u].w;
        float _1322 = RVar[4u].x;
        float _1324 = RVar[17u].x;
        float _1326 = RVar[14u].x;
        float _1328 = (_1322 * _1324) + _1326;
        float _1330 = RVar[4u].y;
        float _1332 = RVar[1u].y;
        RVar[126u].x = (RVar[4u].z * RVar[19u].z) + (_1302 * _1304);
        RVar[126u].z = (_1316 * _1300) + _1318;
        RVar[123u].w = _1328;
        float _1352 = RVar[2u].z;
        float _1354 = RVar[127u].x;
        RVar[127u].x = dot(vec4(RVar[4u].x, RVar[4u].z, _1330 * _1332, uintBitsToFloat(2147483648u)), vec4(RVar[1u].x, RVar[1u].z, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[125u].z = (_1352 * _1328) + _1354;
        float _1360 = RVar[4u].x;
        float _1362 = RVar[18u].x;
        float _1364 = RVar[124u].x;
        float _1366 = (_1360 * _1362) + _1364;
        RVar[123u].y = _1366;
        float _1375 = RVar[4u].x;
        float _1377 = RVar[19u].x;
        float _1379 = RVar[126u].x;
        float _1381 = (_1375 * _1377) + _1379;
        RVar[7u].x = (RVar[2u].w * _1366) + RVar[126u].z;
        RVar[123u].w = _1381;
        float _1391 = RVar[2u].w;
        float _1393 = RVar[127u].x;
        float _1395 = RVar[125u].z;
        RVar[7u].y = (RVar[2u].w * _1381) + RVar[126u].y;
        RVar[7u].z = (_1391 * _1393) + _1395;
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
        bool _1430 = floatBitsToInt(RVar[0u].w) == (0);
        predVar = _1430;
        stateVar = _1430 ? 0 : 1;
    }
    if (stateVar == 0)
    {
        float _1439 = RVar[1u].x;
        float _1443 = intBitsToFloat(floatBitsToInt(_1439) * (3));
        RVar[0u].w = _1443;
        float _1454 = RVar[1u].y;
        float _1458 = intBitsToFloat(floatBitsToInt(_1454) * (3));
        RVar[0u].y = intBitsToFloat(floatBitsToInt(_1443) + (2));
        RVar[0u].z = intBitsToFloat(floatBitsToInt(_1443) + (1));
        RVar[7u].z = _1458;
        float _1471 = RVar[1u].z;
        float _1475 = intBitsToFloat(floatBitsToInt(_1471) * (3));
        RVar[1u].x = intBitsToFloat(floatBitsToInt(_1458) + (2));
        RVar[1u].y = intBitsToFloat(floatBitsToInt(_1458) + (1));
        RVar[7u].y = _1475;
        RVar[0u].x = intBitsToFloat(floatBitsToInt(_1475) + (2));
        RVar[8u].y = intBitsToFloat(floatBitsToInt(_1475) + (1));
    }
    if (stateVar == 0)
    {
        RVar[9u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].w)];
        RVar[10u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].z)];
        RVar[11u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].y)];
        RVar[12u] = CBUFFER_2.values[floatBitsToUint(RVar[7u].z)];
        RVar[14u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].y)];
        RVar[13u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].x)];
        RVar[16u] = CBUFFER_2.values[floatBitsToUint(RVar[7u].y)];
        RVar[15u] = CBUFFER_2.values[floatBitsToUint(RVar[8u].y)];
    }
    if (stateVar == 0)
    {
        float _1546 = RVar[5u].x;
        float _1548 = RVar[5u].y;
        float _1550 = RVar[5u].z;
        float _1554 = RVar[9u].x;
        float _1556 = RVar[9u].y;
        float _1558 = RVar[9u].z;
        RVar[1u].x = RVar[4u].z * RVar[9u].z;
        float _1586 = RVar[9u].w;
        RVar[8u].y = dot(vec4(RVar[5u].x, RVar[5u].y, RVar[5u].z, uintBitsToFloat(2147483648u)), vec4(RVar[10u].x, RVar[10u].y, RVar[10u].z, uintBitsToFloat(0u)));
        RVar[7u].y = _1586 + dot(vec4(_1546, _1548, _1550, uintBitsToFloat(2147483648u)), vec4(_1554, _1556, _1558, uintBitsToFloat(0u)));
    }
    if (stateVar == 0)
    {
        RVar[0u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].x)];
    }
    if (stateVar == 0)
    {
        float _1605 = RVar[5u].x;
        float _1607 = RVar[5u].y;
        float _1609 = RVar[5u].z;
        float _1613 = RVar[11u].x;
        float _1615 = RVar[11u].y;
        float _1617 = RVar[11u].z;
        float _1622 = RVar[10u].w;
        float _1624 = RVar[8u].y;
        float _1632 = RVar[2u].x;
        float _1635 = RVar[4u].z;
        float _1637 = RVar[10u].z;
        float _1640 = RVar[11u].w;
        float _1643 = RVar[4u].y;
        float _1645 = RVar[9u].y;
        float _1647 = RVar[1u].x;
        RVar[127u].x = RVar[2u].x * RVar[7u].y;
        RVar[127u].y = _1632 * (_1622 + _1624);
        RVar[125u].z = _1635 * _1637;
        RVar[125u].x = (_1643 * _1645) + _1647;
        float _1655 = RVar[5u].x;
        float _1657 = RVar[5u].y;
        float _1659 = RVar[5u].z;
        float _1663 = RVar[12u].x;
        float _1665 = RVar[12u].y;
        float _1667 = RVar[12u].z;
        RVar[127u].z = RVar[2u].x * (_1640 + dot(vec4(_1605, _1607, _1609, uintBitsToFloat(2147483648u)), vec4(_1613, _1615, _1617, uintBitsToFloat(0u))));
        float _1676 = RVar[5u].x;
        float _1678 = RVar[5u].y;
        float _1680 = RVar[5u].z;
        float _1684 = RVar[14u].x;
        float _1686 = RVar[14u].y;
        float _1688 = RVar[14u].z;
        RVar[126u].x = RVar[12u].w + dot(vec4(_1655, _1657, _1659, uintBitsToFloat(2147483648u)), vec4(_1663, _1665, _1667, uintBitsToFloat(0u)));
        float _1697 = RVar[5u].x;
        float _1699 = RVar[5u].y;
        float _1701 = RVar[5u].z;
        float _1705 = RVar[13u].x;
        float _1707 = RVar[13u].y;
        float _1709 = RVar[13u].z;
        RVar[127u].w = RVar[14u].w + dot(vec4(_1676, _1678, _1680, uintBitsToFloat(2147483648u)), vec4(_1684, _1686, _1688, uintBitsToFloat(0u)));
        float _1722 = RVar[127u].z;
        float _1726 = RVar[13u].w;
        float _1729 = RVar[127u].x;
        float _1733 = RVar[2u].y;
        float _1735 = RVar[126u].x;
        RVar[127u].x = RVar[127u].y + uintBitsToFloat(0u);
        RVar[127u].y = _1722 + uintBitsToFloat(0u);
        RVar[127u].z = _1726 + dot(vec4(_1697, _1699, _1701, uintBitsToFloat(2147483648u)), vec4(_1705, _1707, _1709, uintBitsToFloat(0u)));
        RVar[126u].w = _1729 + uintBitsToFloat(0u);
        RVar[125u].w = _1733 * _1735;
        float _1743 = RVar[5u].x;
        float _1745 = RVar[5u].y;
        float _1747 = RVar[5u].z;
        float _1751 = RVar[16u].x;
        float _1753 = RVar[16u].y;
        float _1755 = RVar[16u].z;
        RVar[126u].z = RVar[2u].y * RVar[127u].w;
        float _1766 = RVar[5u].x;
        float _1768 = RVar[5u].y;
        float _1770 = RVar[5u].z;
        float _1774 = RVar[15u].x;
        float _1776 = RVar[15u].y;
        float _1778 = RVar[15u].z;
        RVar[127u].w = RVar[16u].w + dot(vec4(_1743, _1745, _1747, uintBitsToFloat(2147483648u)), vec4(_1751, _1753, _1755, uintBitsToFloat(0u)));
        float _1787 = RVar[5u].x;
        float _1789 = RVar[5u].y;
        float _1791 = RVar[5u].z;
        float _1795 = RVar[0u].x;
        float _1797 = RVar[0u].y;
        float _1799 = RVar[0u].z;
        float _1804 = RVar[15u].w;
        float _1812 = RVar[2u].y;
        float _1814 = RVar[127u].z;
        float _1817 = RVar[126u].w;
        float _1819 = RVar[125u].w;
        float _1822 = RVar[0u].w;
        float _1825 = RVar[2u].z;
        RVar[127u].x += RVar[126u].z;
        RVar[127u].z = _1817 + _1819;
        RVar[126u].z = _1825 * (_1804 + dot(vec4(_1766, _1768, _1770, uintBitsToFloat(2147483648u)), vec4(_1774, _1776, _1778, uintBitsToFloat(0u))));
        float _1831 = RVar[127u].y;
        float _1834 = RVar[2u].z;
        float _1837 = RVar[2u].z;
        float _1839 = RVar[127u].w;
        float _1850 = RVar[4u].y;
        float _1852 = RVar[10u].y;
        float _1854 = RVar[125u].z;
        float _1856 = (_1850 * _1852) + _1854;
        RVar[127u].w = (RVar[4u].x * RVar[9u].x) + RVar[125u].x;
        RVar[122u].x = _1856;
        float _1864 = RVar[127u].x;
        float _1866 = RVar[126u].z;
        float _1870 = RVar[4u].x;
        float _1872 = RVar[10u].x;
        float _1876 = RVar[4u].y;
        float _1878 = RVar[11u].y;
        RVar[20u].x = RVar[127u].z + (_1837 * _1839);
        RVar[20u].y = _1864 + _1866;
        RVar[20u].z = (_1831 + (_1812 * _1814)) + (_1834 * (_1822 + dot(vec4(_1787, _1789, _1791, uintBitsToFloat(2147483648u)), vec4(_1795, _1797, _1799, uintBitsToFloat(0u)))));
        RVar[126u].w = (_1870 * _1872) + _1856;
        float _1885 = RVar[4u].x;
        float _1887 = RVar[4u].z;
        float _1891 = RVar[11u].x;
        float _1893 = RVar[11u].z;
        RVar[127u].w = (RVar[2u].x * RVar[127u].w) + uintBitsToFloat(0u);
        float _1907 = RVar[4u].z;
        float _1909 = RVar[12u].z;
        float _1919 = RVar[4u].y;
        float _1921 = RVar[13u].y;
        float _1924 = RVar[2u].x;
        float _1929 = RVar[4u].z;
        float _1931 = RVar[14u].z;
        RVar[127u].y = (RVar[2u].x * RVar[126u].w) + uintBitsToFloat(0u);
        RVar[127u].z = _1919 * _1921;
        RVar[124u].w = (_1924 * dot(vec4(_1885, _1887, _1876 * _1878, uintBitsToFloat(2147483648u)), vec4(_1891, _1893, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)))) + uintBitsToFloat(0u);
        float _1951 = RVar[4u].y;
        float _1953 = RVar[14u].y;
        float _1955 = (_1951 * _1953) + (_1929 * _1931);
        RVar[126u].w = dot(vec4(RVar[4u].x, RVar[4u].y, _1907 * _1909, uintBitsToFloat(2147483648u)), vec4(RVar[12u].x, RVar[12u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[122u].x = _1955;
        float _1975 = RVar[4u].x;
        float _1977 = RVar[14u].x;
        float _1979 = (_1975 * _1977) + _1955;
        RVar[125u].w = dot(vec4(RVar[4u].x, RVar[4u].z, RVar[127u].z, uintBitsToFloat(2147483648u)), vec4(RVar[13u].x, RVar[13u].z, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[122u].x = _1979;
        float _1989 = RVar[4u].z;
        float _1991 = RVar[15u].z;
        float _1994 = RVar[2u].y;
        float _1996 = RVar[126u].w;
        float _1998 = RVar[127u].w;
        float _2002 = RVar[4u].x;
        float _2004 = RVar[0u].x;
        float _2007 = RVar[4u].z;
        float _2009 = RVar[16u].z;
        RVar[127u].x = (RVar[2u].y * _1979) + RVar[127u].y;
        RVar[127u].y = _1989 * _1991;
        RVar[127u].z = (_1994 * _1996) + _1998;
        float _2029 = RVar[4u].y;
        float _2031 = RVar[16u].y;
        float _2033 = (_2029 * _2031) + (_2007 * _2009);
        RVar[125u].x = dot(vec4(RVar[4u].z, RVar[4u].y, _2002 * _2004, uintBitsToFloat(2147483648u)), vec4(RVar[0u].z, RVar[0u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[122u].x = _2033;
        float _2037 = RVar[4u].x;
        float _2039 = RVar[4u].y;
        float _2041 = RVar[127u].y;
        float _2045 = RVar[15u].x;
        float _2047 = RVar[15u].y;
        float _2053 = RVar[4u].x;
        float _2055 = RVar[16u].x;
        float _2057 = (_2053 * _2055) + _2033;
        RVar[122u].x = _2057;
        float _2066 = RVar[2u].z;
        float _2068 = RVar[127u].x;
        float _2072 = RVar[2u].y;
        float _2074 = RVar[125u].w;
        float _2076 = RVar[124u].w;
        float _2078 = (_2072 * _2074) + _2076;
        RVar[7u].x = (RVar[2u].z * _2057) + RVar[127u].z;
        RVar[7u].y = (_2066 * dot(vec4(_2037, _2039, _2041, uintBitsToFloat(2147483648u)), vec4(_2045, _2047, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)))) + _2068;
        RVar[123u].z = _2078;
        RVar[7u].z = (RVar[2u].z * RVar[125u].x) + _2078;
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
        bool _2119 = floatBitsToInt(RVar[0u].w) == (0);
        predVar = _2119;
        stateVar = _2119 ? 0 : 1;
    }
    if (stateVar == 0)
    {
        float _2128 = RVar[1u].x;
        float _2132 = intBitsToFloat(floatBitsToInt(_2128) * (3));
        RVar[0u].z = _2132;
        float _2143 = RVar[1u].y;
        float _2147 = intBitsToFloat(floatBitsToInt(_2143) * (3));
        RVar[1u].x = intBitsToFloat(floatBitsToInt(_2132) + (2));
        RVar[1u].y = intBitsToFloat(floatBitsToInt(_2132) + (1));
        RVar[0u].y = _2147;
        RVar[0u].x = intBitsToFloat(floatBitsToInt(_2147) + (2));
        RVar[7u].y = intBitsToFloat(floatBitsToInt(_2147) + (1));
    }
    if (stateVar == 0)
    {
        RVar[8u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].z)];
        RVar[9u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].y)];
        RVar[1u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].x)];
        RVar[10u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].y)];
        RVar[7u] = CBUFFER_2.values[floatBitsToUint(RVar[7u].y)];
        RVar[0u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].x)];
    }
    if (stateVar == 0)
    {
        float _2206 = RVar[5u].x;
        float _2208 = RVar[5u].y;
        float _2210 = RVar[5u].z;
        float _2214 = RVar[8u].x;
        float _2216 = RVar[8u].y;
        float _2218 = RVar[8u].z;
        RVar[126u].x = RVar[4u].z * RVar[8u].z;
        float _2229 = RVar[5u].x;
        float _2231 = RVar[5u].y;
        float _2233 = RVar[5u].z;
        float _2237 = RVar[9u].x;
        float _2239 = RVar[9u].y;
        float _2241 = RVar[9u].z;
        RVar[127u].x = RVar[8u].w + dot(vec4(_2206, _2208, _2210, uintBitsToFloat(2147483648u)), vec4(_2214, _2216, _2218, uintBitsToFloat(0u)));
        float _2250 = RVar[5u].x;
        float _2252 = RVar[5u].y;
        float _2254 = RVar[5u].z;
        float _2258 = RVar[1u].x;
        float _2260 = RVar[1u].y;
        float _2262 = RVar[1u].z;
        float _2273 = RVar[4u].z;
        float _2275 = RVar[9u].z;
        float _2278 = RVar[1u].w;
        float _2281 = RVar[2u].x;
        float _2283 = RVar[127u].x;
        float _2286 = RVar[4u].y;
        float _2288 = RVar[8u].y;
        float _2290 = RVar[126u].x;
        RVar[127u].x = RVar[2u].x * (RVar[9u].w + dot(vec4(_2229, _2231, _2233, uintBitsToFloat(2147483648u)), vec4(_2237, _2239, _2241, uintBitsToFloat(0u))));
        RVar[126u].y = _2273 * _2275;
        RVar[127u].w = _2281 * _2283;
        RVar[126u].x = (_2286 * _2288) + _2290;
        float _2298 = RVar[5u].x;
        float _2300 = RVar[5u].y;
        float _2302 = RVar[5u].z;
        float _2306 = RVar[10u].x;
        float _2308 = RVar[10u].y;
        float _2310 = RVar[10u].z;
        RVar[127u].y = RVar[2u].x * (_2278 + dot(vec4(_2250, _2252, _2254, uintBitsToFloat(2147483648u)), vec4(_2258, _2260, _2262, uintBitsToFloat(0u))));
        float _2319 = RVar[5u].x;
        float _2321 = RVar[5u].y;
        float _2323 = RVar[5u].z;
        float _2327 = RVar[7u].x;
        float _2329 = RVar[7u].y;
        float _2331 = RVar[7u].z;
        RVar[126u].w = RVar[10u].w + dot(vec4(_2298, _2300, _2302, uintBitsToFloat(2147483648u)), vec4(_2306, _2308, _2310, uintBitsToFloat(0u)));
        float _2340 = RVar[5u].x;
        float _2342 = RVar[5u].y;
        float _2344 = RVar[5u].z;
        float _2348 = RVar[0u].x;
        float _2350 = RVar[0u].y;
        float _2352 = RVar[0u].z;
        RVar[125u].w = RVar[7u].w + dot(vec4(_2319, _2321, _2323, uintBitsToFloat(2147483648u)), vec4(_2327, _2329, _2331, uintBitsToFloat(0u)));
        float _2365 = RVar[127u].x;
        float _2369 = RVar[127u].w;
        float _2373 = RVar[0u].w;
        float _2376 = RVar[2u].y;
        float _2378 = RVar[126u].w;
        RVar[127u].x = RVar[127u].y + uintBitsToFloat(0u);
        RVar[127u].y = _2365 + uintBitsToFloat(0u);
        float _2383 = RVar[2u].y;
        float _2394 = RVar[2u].y;
        float _2396 = RVar[125u].w;
        float _2399 = RVar[4u].z;
        float _2401 = RVar[1u].z;
        RVar[126u].y = (RVar[4u].x * RVar[9u].x) + RVar[126u].y;
        RVar[20u].x = (_2369 + uintBitsToFloat(0u)) + (_2376 * _2378);
        float _2413 = RVar[127u].y;
        float _2416 = RVar[127u].x;
        float _2419 = RVar[4u].z;
        float _2421 = RVar[7u].z;
        float _2424 = RVar[4u].z;
        float _2426 = RVar[10u].z;
        RVar[127u].x = (RVar[4u].y * RVar[1u].y) + (_2399 * _2401);
        RVar[20u].y = _2413 + (_2394 * _2396);
        RVar[20u].z = _2416 + (_2383 * (_2373 + dot(vec4(_2340, _2342, _2344, uintBitsToFloat(2147483648u)), vec4(_2348, _2350, _2352, uintBitsToFloat(0u)))));
        RVar[125u].w = _2419 * _2421;
        RVar[125u].x = _2424 * _2426;
        float _2434 = RVar[4u].z;
        float _2436 = RVar[0u].z;
        float _2447 = RVar[4u].x;
        float _2449 = RVar[8u].x;
        float _2451 = RVar[126u].x;
        RVar[126u].y = (RVar[4u].y * RVar[9u].y) + RVar[126u].y;
        RVar[127u].w = (_2447 * _2449) + _2451;
        float _2465 = RVar[4u].x;
        float _2467 = RVar[1u].x;
        float _2469 = RVar[127u].x;
        float _2473 = RVar[4u].y;
        float _2475 = RVar[0u].y;
        RVar[127u].x = (RVar[4u].y * RVar[7u].y) + RVar[125u].w;
        RVar[125u].w = (_2465 * _2467) + _2469;
        RVar[126u].x = (_2473 * _2475) + (_2434 * _2436);
        RVar[127u].y = dot(vec4(RVar[4u].x, RVar[4u].y, RVar[125u].x, uintBitsToFloat(2147483648u)), vec4(RVar[10u].x, RVar[10u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[126u].w = (RVar[4u].x * RVar[7u].x) + RVar[127u].x;
        RVar[126u].x = (RVar[4u].x * RVar[0u].x) + RVar[126u].x;
        float _2517 = RVar[2u].x;
        float _2519 = RVar[126u].y;
        float _2522 = (_2517 * _2519) + uintBitsToFloat(0u);
        float _2524 = RVar[2u].x;
        float _2526 = RVar[125u].w;
        float _2529 = (_2524 * _2526) + uintBitsToFloat(0u);
        float _2531 = RVar[2u].x;
        float _2533 = RVar[127u].w;
        float _2536 = (_2531 * _2533) + uintBitsToFloat(0u);
        RVar[123u].x = _2522;
        RVar[123u].y = _2529;
        RVar[123u].z = _2536;
        float _2547 = RVar[2u].y;
        float _2549 = RVar[126u].w;
        float _2553 = RVar[2u].y;
        float _2555 = RVar[126u].x;
        RVar[7u].x = (RVar[2u].y * RVar[127u].y) + _2536;
        RVar[7u].y = (_2547 * _2549) + _2522;
        RVar[7u].z = (_2553 * _2555) + _2529;
    }
    if (stackVar[stackIdxVar - 1] == 0)
    {
        stateVar = int(stateVar == 0);
    }
    if (stateVar == 0)
    {
        float _2578 = RVar[7u].y;
        float _2580 = RVar[7u].z;
        RVar[20u].x = RVar[7u].x;
        RVar[20u].y = _2578;
        RVar[20u].z = _2580;
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
        RVar[127u].w = dot(vec4(RVar[20u].x, RVar[20u].y, RVar[20u].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[3].x, CBUFFER_3.values[3].y, CBUFFER_3.values[3].z, uintBitsToFloat(0u)));
        RVar[2u].z = uintBitsToFloat(1065353216u);
        float _2641 = RVar[7u].z;
        float _2643 = RVar[7u].z;
        RVar[127u].z = dot(vec4(RVar[20u].x, RVar[20u].y, RVar[20u].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[4].x, CBUFFER_3.values[4].y, CBUFFER_3.values[4].z, uintBitsToFloat(0u)));
        float _2665 = RVar[7u].y;
        float _2667 = RVar[7u].y;
        float _2669 = (_2665 * _2667) + (_2641 * _2643);
        RVar[127u].y = dot(vec4(RVar[20u].x, RVar[20u].y, RVar[20u].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[5].x, CBUFFER_3.values[5].y, CBUFFER_3.values[5].z, uintBitsToFloat(0u)));
        RVar[122u].x = _2669;
        float _2691 = RVar[7u].x;
        float _2693 = RVar[7u].x;
        float _2695 = (_2691 * _2693) + _2669;
        RVar[126u].w = dot(vec4(RVar[20u].x, RVar[20u].y, RVar[20u].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[6].x, CBUFFER_3.values[6].y, CBUFFER_3.values[6].z, uintBitsToFloat(0u)));
        RVar[122u].x = _2695;
        float _2706 = RVar[127u].z;
        float _2709 = inversesqrt(_2695);
        RVar[1u].x = CBUFFER_3.values[3].w + RVar[127u].w;
        RVar[1u].y = CBUFFER_3.values[4].w + _2706;
        float _2716 = RVar[7u].y;
        float _2721 = RVar[127u].y;
        float _2726 = RVar[126u].w;
        float _2729 = RVar[7u].z;
        RVar[7u].x *= _2709;
        RVar[2u].y = _2716 * _2709;
        RVar[1u].z = CBUFFER_3.values[5].w + _2721;
        RVar[1u].w = CBUFFER_3.values[6].w + _2726;
        RVar[0u].z = _2729 * _2709;
        float _2761 = RVar[20u].z;
        RVar[0u].x = intBitsToFloat(floatBitsToInt(CBUFFER_4.values[0].x) + (25));
        RVar[0u].y = intBitsToFloat(floatBitsToInt(CBUFFER_4.values[0].x) + (41));
        RVar[0u].w = intBitsToFloat(floatBitsToInt(CBUFFER_4.values[0].x) + (33));
        RVar[2u].x = _2761 * CBUFFER_3.values[2].z;
    }
    if (stateVar == 0)
    {
        RVar[4u] = vec4(CBUFFER_3.values[floatBitsToUint(RVar[0u].w)].x, RVar[4u].y, RVar[4u].z, RVar[4u].w);
        RVar[5u] = vec4(CBUFFER_3.values[floatBitsToUint(RVar[0u].y)].x, RVar[5u].y, RVar[5u].z, RVar[5u].w);
        uint _2791 = floatBitsToUint(RVar[0u].x);
        RVar[8u] = vec4(CBUFFER_3.values[_2791].x, CBUFFER_3.values[_2791].y, CBUFFER_3.values[_2791].z, RVar[8u].w);
    }
    vec4 _2813 = (RVar[1u] * vec4(VS_PUSH.posMulAdd.xy, 1.0, 1.0)) + vec4(VS_PUSH.posMulAdd.zw, 0.0, 0.0);
    vec4 _2816 = _2813;
    _2816.y = -_2813.y;
    vec4 _2824 = _2816;
    _2824.z = (_2816.z + (_2816.w * VS_PUSH.zSpaceMul.x)) * VS_PUSH.zSpaceMul.y;
    gl_Position = _2824;
    PARAM_0 = RVar[3u];
    if (stateVar == 0)
    {
        float _2834 = RVar[20u].x;
        float _2836 = RVar[20u].y;
        float _2838 = RVar[2u].x;
        float _2850 = RVar[0u].z;
        float _2858 = RVar[2u].y;
        float _2862 = (_2858 * CBUFFER_3.values[0].y) + (_2850 * CBUFFER_3.values[0].z);
        RVar[122u].x = _2862;
        float _2872 = RVar[4u].x;
        float _2876 = RVar[0u].z;
        RVar[0u].x = (RVar[7u].x * CBUFFER_3.values[0].x) + _2862;
        float _2888 = RVar[5u].x;
        float _2892 = RVar[2u].z;
        RVar[127u].x = (RVar[2u].y * CBUFFER_3.values[1].y) + (_2876 * CBUFFER_3.values[1].z);
        RVar[8u].w = clamp(((-(CBUFFER_3.values[2].w + dot(vec4(_2834, _2836, _2838, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[2].x, CBUFFER_3.values[2].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u))))) + (-_2872)) * _2888, 0.0, 1.0);
        RVar[1u].x = dot(vec4(RVar[6u].x, RVar[6u].y, RVar[2u].z, _2892 * CBUFFER_4.values[1].w), vec4(CBUFFER_4.values[1].x, CBUFFER_4.values[1].y, CBUFFER_4.values[1].z, uintBitsToFloat(1065353216u)));
        RVar[1u].y = dot(vec4(RVar[6u].x, RVar[6u].y, RVar[2u].z, RVar[2u].z), CBUFFER_4.values[2]);
        float _2930 = RVar[0u].z;
        RVar[0u].y = (RVar[7u].x * CBUFFER_3.values[1].x) + RVar[127u].x;
        RVar[0u].z = dot(vec4(RVar[7u].x, RVar[2u].y, _2930 * CBUFFER_3.values[2].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[2].x, CBUFFER_3.values[2].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
    }
    PARAM_1 = RVar[8u];
    PARAM_2 = RVar[0u];
    PARAM_3 = vec4(RVar[1u].x, RVar[1u].y, RVar[1u].z, RVar[1u].z);
    if (stateVar == 0)
    {
    }
}

 