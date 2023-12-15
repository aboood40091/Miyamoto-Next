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
    vec4 values[41];
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
layout(location = 0) in uvec4 aBlendIndex_0_0;
layout(location = 1) in uvec4 aBlendWeight_0_0;
layout(location = 2) in uvec4 aColor0_0_0;
layout(location = 3) in uvec3 aNormal_0_0;
layout(location = 4) in uvec3 aPosition_0_0;
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
        RVar[3u].w = uintBitsToFloat(1065353216u);
        RVar[19u].w = uintBitsToFloat(1065353216u);
        RVar[0u].w = intBitsToFloat((floatBitsToInt(CBUFFER_1.values[3].x) != (0)) ? (-1) : 0);
        RVar[20u].w = uintBitsToFloat(0u);
        bool _90 = floatBitsToInt(RVar[0u].w) == (0);
        predVar = _90;
        stateVar = _90 ? 0 : 1;
    }
    if (stateVar == 0)
    {
        float _118 = RVar[4u].z;
        RVar[19u].x = dot(vec4(RVar[5u].x, RVar[5u].y, RVar[5u].z, RVar[3u].w), CBUFFER_1.values[0]);
        RVar[127u].x = _118 * CBUFFER_1.values[0].z;
        RVar[19u].y = dot(vec4(RVar[5u].x, RVar[5u].y, RVar[5u].z, RVar[3u].w), CBUFFER_1.values[1]);
        RVar[19u].z = dot(vec4(RVar[5u].x, RVar[5u].y, RVar[5u].z, RVar[3u].w), CBUFFER_1.values[2]);
        float _169 = RVar[4u].z;
        RVar[20u].x = dot(vec4(RVar[4u].x, RVar[4u].y, RVar[127u].x, uintBitsToFloat(2147483648u)), vec4(CBUFFER_1.values[0].x, CBUFFER_1.values[0].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        float _189 = RVar[4u].z;
        RVar[20u].y = dot(vec4(RVar[4u].x, RVar[4u].y, _169 * CBUFFER_1.values[1].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_1.values[1].x, CBUFFER_1.values[1].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[20u].z = dot(vec4(RVar[4u].x, RVar[4u].y, _189 * CBUFFER_1.values[2].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_1.values[2].x, CBUFFER_1.values[2].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
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
        bool _239 = floatBitsToInt(RVar[0u].w) == (0);
        predVar = _239;
        stateVar = _239 ? 0 : 1;
    }
    if (stateVar == 0)
    {
        float _248 = RVar[1u].x;
        float _252 = intBitsToFloat(floatBitsToInt(_248) * (3));
        RVar[1u].y = _252;
        RVar[1u].x = intBitsToFloat(floatBitsToInt(_252) + (1));
        RVar[1u].w = intBitsToFloat(floatBitsToInt(_252) + (2));
    }
    if (stateVar == 0)
    {
        RVar[0u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].y)];
        RVar[2u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].x)];
        RVar[1u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].w)];
    }
    if (stateVar == 0)
    {
        float _306 = RVar[4u].z;
        float _308 = RVar[0u].z;
        RVar[19u].x = dot(vec4(RVar[5u].x, RVar[5u].y, RVar[5u].z, RVar[3u].w), RVar[0u]);
        RVar[127u].x = _306 * _308;
        RVar[19u].y = dot(vec4(RVar[5u].x, RVar[5u].y, RVar[5u].z, RVar[3u].w), RVar[2u]);
        RVar[19u].z = dot(vec4(RVar[5u].x, RVar[5u].y, RVar[5u].z, RVar[3u].w), RVar[1u]);
        float _355 = RVar[4u].z;
        float _357 = RVar[2u].z;
        RVar[20u].x = dot(vec4(RVar[4u].x, RVar[4u].y, RVar[127u].x, uintBitsToFloat(2147483648u)), vec4(RVar[0u].x, RVar[0u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        float _375 = RVar[4u].z;
        float _377 = RVar[1u].z;
        RVar[20u].y = dot(vec4(RVar[4u].x, RVar[4u].y, _355 * _357, uintBitsToFloat(2147483648u)), vec4(RVar[2u].x, RVar[2u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[20u].z = dot(vec4(RVar[4u].x, RVar[4u].y, _375 * _377, uintBitsToFloat(2147483648u)), vec4(RVar[1u].x, RVar[1u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
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
        bool _425 = floatBitsToInt(RVar[0u].w) == (0);
        predVar = _425;
        stateVar = _425 ? 0 : 1;
    }
    if (stateVar == 0)
    {
        float _434 = RVar[1u].x;
        float _438 = intBitsToFloat(floatBitsToInt(_434) * (3));
        RVar[0u].x = _438;
        float _449 = RVar[1u].y;
        float _453 = intBitsToFloat(floatBitsToInt(_449) * (3));
        RVar[1u].x = intBitsToFloat(floatBitsToInt(_438) + (1));
        RVar[1u].y = intBitsToFloat(floatBitsToInt(_438) + (2));
        RVar[1u].z = _453;
        RVar[6u].x = intBitsToFloat(floatBitsToInt(_453) + (2));
        RVar[1u].w = intBitsToFloat(floatBitsToInt(_453) + (1));
    }
    if (stateVar == 0)
    {
        RVar[0u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].x)];
        RVar[8u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].x)];
        RVar[7u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].y)];
        RVar[9u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].z)];
        RVar[1u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].w)];
        RVar[6u] = CBUFFER_2.values[floatBitsToUint(RVar[6u].x)];
    }
    if (stateVar == 0)
    {
        float _516 = RVar[5u].x;
        float _518 = RVar[5u].y;
        float _520 = RVar[5u].z;
        float _522 = RVar[3u].w;
        vec4 _525 = RVar[0u];
        RVar[127u].x = RVar[4u].z * RVar[0u].z;
        float _534 = RVar[5u].x;
        float _536 = RVar[5u].y;
        float _538 = RVar[5u].z;
        float _540 = RVar[3u].w;
        vec4 _543 = RVar[8u];
        RVar[127u].z = RVar[2u].x * dot(vec4(_516, _518, _520, _522), _525);
        float _550 = RVar[5u].x;
        float _552 = RVar[5u].y;
        float _554 = RVar[5u].z;
        float _556 = RVar[3u].w;
        vec4 _559 = RVar[7u];
        float _567 = RVar[127u].z;
        float _571 = RVar[2u].x;
        float _574 = RVar[4u].z;
        float _576 = RVar[8u].z;
        float _579 = RVar[4u].y;
        float _581 = RVar[0u].y;
        float _583 = RVar[127u].x;
        RVar[127u].x = (RVar[2u].x * dot(vec4(_534, _536, _538, _540), _543)) + uintBitsToFloat(0u);
        RVar[126u].y = _567 + uintBitsToFloat(0u);
        RVar[127u].w = _574 * _576;
        RVar[126u].x = (_579 * _581) + _583;
        RVar[127u].y = dot(vec4(RVar[5u].x, RVar[5u].y, RVar[5u].z, RVar[3u].w), RVar[9u]);
        RVar[124u].y = (_571 * dot(vec4(_550, _552, _554, _556), _559)) + uintBitsToFloat(0u);
        float _609 = RVar[5u].x;
        float _611 = RVar[5u].y;
        float _613 = RVar[5u].z;
        float _615 = RVar[3u].w;
        vec4 _618 = RVar[1u];
        RVar[124u].x = RVar[4u].z * RVar[1u].z;
        float _627 = RVar[5u].x;
        float _629 = RVar[5u].y;
        float _631 = RVar[5u].z;
        float _633 = RVar[3u].w;
        vec4 _636 = RVar[6u];
        RVar[125u].y = RVar[2u].y * dot(vec4(_609, _611, _613, _615), _618);
        float _644 = RVar[2u].y;
        float _646 = RVar[127u].y;
        float _649 = RVar[4u].z;
        float _651 = RVar[7u].z;
        float _654 = RVar[2u].y;
        float _662 = RVar[4u].x;
        float _664 = RVar[8u].x;
        float _666 = RVar[127u].w;
        RVar[127u].w = RVar[4u].z * RVar[9u].z;
        RVar[125u].x = (_662 * _664) + _666;
        float _675 = RVar[127u].x;
        float _677 = RVar[125u].y;
        float _680 = RVar[124u].y;
        float _683 = RVar[4u].z;
        float _685 = RVar[6u].z;
        float _688 = RVar[4u].x;
        float _690 = RVar[7u].x;
        float _692 = (_688 * _690) + (_649 * _651);
        RVar[19u].x = RVar[126u].y + (_644 * _646);
        RVar[19u].y = _675 + _677;
        RVar[19u].z = _680 + (_654 * dot(vec4(_627, _629, _631, _633), _636));
        RVar[126u].w = _683 * _685;
        RVar[122u].x = _692;
        float _700 = RVar[4u].x;
        float _702 = RVar[0u].x;
        float _704 = RVar[126u].x;
        float _706 = (_700 * _702) + _704;
        float _708 = RVar[4u].y;
        float _710 = RVar[7u].y;
        float _712 = (_708 * _710) + _692;
        float _714 = RVar[4u].y;
        float _716 = RVar[9u].y;
        float _718 = RVar[127u].w;
        RVar[123u].x = _706;
        RVar[123u].y = _712;
        RVar[126u].x = (_714 * _716) + _718;
        float _726 = RVar[4u].y;
        float _728 = RVar[1u].y;
        float _730 = RVar[124u].x;
        float _732 = (_726 * _728) + _730;
        float _734 = RVar[2u].x;
        float _739 = RVar[4u].y;
        float _741 = RVar[8u].y;
        float _743 = RVar[125u].x;
        float _747 = RVar[2u].x;
        RVar[123u].x = _732;
        RVar[126u].y = (_734 * _712) + uintBitsToFloat(0u);
        RVar[127u].z = (_739 * _741) + _743;
        RVar[127u].w = (_747 * _706) + uintBitsToFloat(0u);
        float _772 = RVar[4u].x;
        float _774 = RVar[1u].x;
        RVar[125u].x = dot(vec4(RVar[4u].x, RVar[4u].y, RVar[126u].w, uintBitsToFloat(2147483648u)), vec4(RVar[6u].x, RVar[6u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[126u].w = (_772 * _774) + _732;
        float _780 = RVar[4u].x;
        float _782 = RVar[9u].x;
        float _784 = RVar[126u].x;
        float _786 = (_780 * _782) + _784;
        RVar[123u].y = _786;
        float _795 = RVar[2u].x;
        float _797 = RVar[127u].z;
        float _800 = (_795 * _797) + uintBitsToFloat(0u);
        RVar[20u].x = (RVar[2u].y * _786) + RVar[127u].w;
        RVar[123u].y = _800;
        float _810 = RVar[2u].y;
        float _812 = RVar[125u].x;
        float _814 = RVar[126u].y;
        RVar[20u].y = (RVar[2u].y * RVar[126u].w) + _800;
        RVar[20u].z = (_810 * _812) + _814;
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
        bool _849 = floatBitsToInt(RVar[0u].w) == (0);
        predVar = _849;
        stateVar = _849 ? 0 : 1;
    }
    if (stateVar == 0)
    {
        float _858 = RVar[1u].x;
        float _862 = intBitsToFloat(floatBitsToInt(_858) * (3));
        RVar[0u].z = _862;
        float _873 = RVar[1u].y;
        float _877 = intBitsToFloat(floatBitsToInt(_873) * (3));
        RVar[0u].x = intBitsToFloat(floatBitsToInt(_862) + (2));
        RVar[6u].z = intBitsToFloat(floatBitsToInt(_862) + (1));
        RVar[6u].x = _877;
        float _890 = RVar[1u].z;
        float _894 = intBitsToFloat(floatBitsToInt(_890) * (3));
        RVar[1u].x = intBitsToFloat(floatBitsToInt(_877) + (1));
        RVar[1u].y = intBitsToFloat(floatBitsToInt(_877) + (2));
        RVar[1u].z = _894;
        RVar[7u].x = intBitsToFloat(floatBitsToInt(_894) + (2));
        RVar[1u].w = intBitsToFloat(floatBitsToInt(_894) + (1));
    }
    if (stateVar == 0)
    {
        RVar[8u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].z)];
        RVar[9u] = CBUFFER_2.values[floatBitsToUint(RVar[6u].z)];
        RVar[0u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].x)];
        RVar[10u] = CBUFFER_2.values[floatBitsToUint(RVar[6u].x)];
        RVar[11u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].x)];
        RVar[12u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].y)];
        RVar[13u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].z)];
        RVar[14u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].w)];
    }
    if (stateVar == 0)
    {
        float _970 = RVar[5u].x;
        float _972 = RVar[5u].y;
        float _974 = RVar[5u].z;
        float _976 = RVar[3u].w;
        vec4 _979 = RVar[8u];
        RVar[6u].x = RVar[4u].z * RVar[8u].z;
        float _1000 = RVar[2u].x;
        RVar[1u].y = dot(vec4(RVar[5u].x, RVar[5u].y, RVar[5u].z, RVar[3u].w), RVar[9u]);
        RVar[1u].x = _1000 * dot(vec4(_970, _972, _974, _976), _979);
    }
    if (stateVar == 0)
    {
        RVar[7u] = CBUFFER_2.values[floatBitsToUint(RVar[7u].x)];
    }
    if (stateVar == 0)
    {
        float _1019 = RVar[5u].x;
        float _1021 = RVar[5u].y;
        float _1023 = RVar[5u].z;
        float _1025 = RVar[3u].w;
        vec4 _1028 = RVar[0u];
        float _1036 = RVar[2u].x;
        float _1041 = RVar[4u].z;
        float _1043 = RVar[9u].z;
        float _1046 = RVar[1u].x;
        float _1050 = RVar[4u].y;
        float _1052 = RVar[8u].y;
        float _1054 = RVar[6u].x;
        RVar[127u].y = (RVar[2u].x * RVar[1u].y) + uintBitsToFloat(0u);
        RVar[126u].z = _1041 * _1043;
        RVar[127u].w = _1046 + uintBitsToFloat(0u);
        RVar[127u].x = (_1050 * _1052) + _1054;
        float _1062 = RVar[5u].x;
        float _1064 = RVar[5u].y;
        float _1066 = RVar[5u].z;
        float _1068 = RVar[3u].w;
        vec4 _1071 = RVar[10u];
        RVar[126u].w = (_1036 * dot(vec4(_1019, _1021, _1023, _1025), _1028)) + uintBitsToFloat(0u);
        float _1077 = RVar[5u].x;
        float _1079 = RVar[5u].y;
        float _1081 = RVar[5u].z;
        float _1083 = RVar[3u].w;
        vec4 _1086 = RVar[11u];
        RVar[127u].z = RVar[2u].y * dot(vec4(_1062, _1064, _1066, _1068), _1071);
        float _1093 = RVar[5u].x;
        float _1095 = RVar[5u].y;
        float _1097 = RVar[5u].z;
        float _1099 = RVar[3u].w;
        vec4 _1102 = RVar[12u];
        float _1111 = RVar[127u].w;
        float _1113 = RVar[127u].z;
        float _1116 = RVar[2u].y;
        float _1119 = RVar[4u].x;
        float _1121 = RVar[0u].x;
        float _1124 = RVar[4u].x;
        float _1126 = RVar[9u].x;
        float _1128 = RVar[126u].z;
        RVar[126u].x = RVar[127u].y + (RVar[2u].y * dot(vec4(_1077, _1079, _1081, _1083), _1086));
        RVar[127u].y = _1111 + _1113;
        RVar[127u].w = _1119 * _1121;
        RVar[125u].x = (_1124 * _1126) + _1128;
        float _1136 = RVar[5u].x;
        float _1138 = RVar[5u].y;
        float _1140 = RVar[5u].z;
        float _1142 = RVar[3u].w;
        vec4 _1145 = RVar[13u];
        RVar[126u].y = RVar[126u].w + (_1116 * dot(vec4(_1093, _1095, _1097, _1099), _1102));
        float _1164 = RVar[2u].z;
        RVar[127u].z = dot(vec4(RVar[5u].x, RVar[5u].y, RVar[5u].z, RVar[3u].w), RVar[14u]);
        float _1168 = RVar[5u].x;
        float _1170 = RVar[5u].y;
        float _1172 = RVar[5u].z;
        float _1174 = RVar[3u].w;
        vec4 _1177 = RVar[7u];
        RVar[19u].x = RVar[127u].y + (_1164 * dot(vec4(_1136, _1138, _1140, _1142), _1145));
        float _1184 = RVar[4u].y;
        float _1186 = RVar[0u].y;
        float _1188 = RVar[127u].w;
        float _1190 = (_1184 * _1186) + _1188;
        float _1192 = RVar[2u].z;
        float _1194 = RVar[127u].z;
        float _1197 = RVar[2u].z;
        float _1200 = RVar[4u].x;
        float _1202 = RVar[8u].x;
        float _1204 = RVar[127u].x;
        float _1208 = RVar[4u].y;
        float _1210 = RVar[10u].y;
        RVar[123u].x = _1190;
        RVar[127u].w = (_1200 * _1202) + _1204;
        float _1215 = RVar[4u].y;
        float _1217 = RVar[9u].y;
        float _1219 = RVar[125u].x;
        float _1221 = (_1215 * _1217) + _1219;
        float _1223 = RVar[126u].x;
        float _1226 = RVar[126u].y;
        float _1229 = RVar[4u].z;
        float _1231 = RVar[0u].z;
        float _1233 = (_1229 * _1231) + _1190;
        float _1235 = RVar[4u].z;
        float _1237 = RVar[10u].z;
        float _1239 = (_1235 * _1237) + (_1208 * _1210);
        RVar[123u].x = _1221;
        RVar[19u].y = _1223 + (_1192 * _1194);
        RVar[19u].z = _1226 + (_1197 * dot(vec4(_1168, _1170, _1172, _1174), _1177));
        RVar[123u].w = _1233;
        RVar[122u].x = _1239;
        float _1246 = RVar[4u].x;
        float _1248 = RVar[10u].x;
        float _1250 = (_1246 * _1248) + _1239;
        float _1252 = RVar[2u].x;
        float _1254 = RVar[127u].w;
        float _1257 = (_1252 * _1254) + uintBitsToFloat(0u);
        float _1259 = RVar[2u].x;
        float _1264 = RVar[2u].x;
        float _1269 = RVar[4u].z;
        float _1271 = RVar[11u].z;
        RVar[123u].x = _1250;
        RVar[123u].y = _1257;
        RVar[127u].z = (_1259 * _1233) + uintBitsToFloat(0u);
        RVar[127u].w = (_1264 * _1221) + uintBitsToFloat(0u);
        float _1278 = RVar[4u].x;
        float _1280 = RVar[4u].y;
        float _1284 = RVar[11u].x;
        float _1286 = RVar[11u].y;
        RVar[126u].w = (RVar[2u].y * _1250) + _1257;
        float _1297 = RVar[4u].x;
        float _1299 = RVar[4u].y;
        float _1301 = RVar[4u].z;
        float _1305 = RVar[12u].x;
        float _1307 = RVar[12u].y;
        float _1309 = RVar[12u].z;
        RVar[125u].y = (RVar[2u].y * dot(vec4(_1278, _1280, _1269 * _1271, uintBitsToFloat(2147483648u)), vec4(_1284, _1286, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)))) + RVar[127u].w;
        float _1321 = RVar[4u].z;
        float _1323 = RVar[13u].z;
        float _1331 = RVar[2u].y;
        float _1333 = RVar[127u].z;
        float _1337 = RVar[4u].y;
        float _1339 = RVar[14u].y;
        RVar[126u].y = RVar[4u].x * RVar[7u].x;
        RVar[127u].w = (_1331 * dot(vec4(_1297, _1299, _1301, uintBitsToFloat(2147483648u)), vec4(_1305, _1307, _1309, uintBitsToFloat(0u)))) + _1333;
        float _1358 = RVar[4u].z;
        float _1360 = RVar[14u].z;
        float _1362 = (_1358 * _1360) + (_1337 * _1339);
        RVar[127u].y = dot(vec4(RVar[4u].x, RVar[4u].y, _1321 * _1323, uintBitsToFloat(2147483648u)), vec4(RVar[13u].x, RVar[13u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[122u].x = _1362;
        float _1366 = RVar[4u].y;
        float _1368 = RVar[7u].y;
        float _1370 = RVar[126u].y;
        float _1372 = (_1366 * _1368) + _1370;
        float _1374 = RVar[4u].x;
        float _1376 = RVar[14u].x;
        float _1378 = (_1374 * _1376) + _1362;
        RVar[123u].x = _1372;
        RVar[123u].w = _1378;
        float _1382 = RVar[4u].z;
        float _1384 = RVar[7u].z;
        float _1386 = (_1382 * _1384) + _1372;
        float _1388 = RVar[2u].z;
        float _1390 = RVar[125u].y;
        float _1394 = RVar[2u].z;
        float _1396 = RVar[127u].y;
        float _1398 = RVar[126u].w;
        RVar[123u].x = _1386;
        RVar[20u].y = (_1388 * _1378) + _1390;
        RVar[20u].x = (_1394 * _1396) + _1398;
        RVar[20u].z = (RVar[2u].z * _1386) + RVar[127u].w;
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
        bool _1442 = floatBitsToInt(RVar[0u].w) == (0);
        predVar = _1442;
        stateVar = _1442 ? 0 : 1;
    }
    if (stateVar == 0)
    {
        float _1451 = RVar[1u].x;
        float _1455 = intBitsToFloat(floatBitsToInt(_1451) * (3));
        RVar[0u].x = _1455;
        float _1466 = RVar[1u].y;
        float _1470 = intBitsToFloat(floatBitsToInt(_1466) * (3));
        RVar[6u].x = intBitsToFloat(floatBitsToInt(_1455) + (1));
        RVar[0u].y = intBitsToFloat(floatBitsToInt(_1455) + (2));
        RVar[0u].z = _1470;
        float _1483 = RVar[1u].z;
        float _1487 = intBitsToFloat(floatBitsToInt(_1483) * (3));
        RVar[7u].x = intBitsToFloat(floatBitsToInt(_1470) + (2));
        RVar[6u].z = intBitsToFloat(floatBitsToInt(_1470) + (1));
        RVar[8u].x = _1487;
        float _1500 = RVar[1u].w;
        RVar[1u].x = intBitsToFloat(floatBitsToInt(_1487) + (1));
        RVar[1u].y = intBitsToFloat(floatBitsToInt(_1487) + (2));
        RVar[1u].z = intBitsToFloat(floatBitsToInt(_1500) * (3));
    }
    if (stateVar == 0)
    {
        RVar[9u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].x)];
        RVar[11u] = CBUFFER_2.values[floatBitsToUint(RVar[6u].x)];
        RVar[10u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].y)];
        RVar[13u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].z)];
        RVar[12u] = CBUFFER_2.values[floatBitsToUint(RVar[6u].z)];
        RVar[7u] = CBUFFER_2.values[floatBitsToUint(RVar[7u].x)];
        RVar[15u] = CBUFFER_2.values[floatBitsToUint(RVar[8u].x)];
        RVar[16u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].x)];
    }
    if (stateVar == 0)
    {
        float _1572 = RVar[4u].y;
        float _1574 = RVar[11u].y;
        float _1577 = RVar[4u].y;
        float _1579 = RVar[10u].y;
        float _1582 = RVar[1u].z;
        float _1588 = RVar[4u].z;
        float _1590 = RVar[9u].z;
        RVar[1u].x = intBitsToFloat(floatBitsToInt(RVar[1u].z) + (2));
        RVar[0u].y = _1572 * _1574;
        RVar[6u].z = _1577 * _1579;
        RVar[1u].w = intBitsToFloat(floatBitsToInt(_1582) + (1));
        float _1609 = RVar[4u].y;
        float _1611 = RVar[9u].y;
        RVar[0u].w = dot(vec4(RVar[5u].x, RVar[5u].y, RVar[5u].z, RVar[3u].w), RVar[9u]);
        RVar[8u].x = (_1609 * _1611) + (_1588 * _1590);
    }
    if (stateVar == 0)
    {
        RVar[17u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].y)];
        RVar[14u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].z)];
        RVar[18u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].w)];
        RVar[1u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].x)];
    }
    if (stateVar == 0)
    {
        float _1651 = RVar[5u].x;
        float _1653 = RVar[5u].y;
        float _1655 = RVar[5u].z;
        float _1657 = RVar[3u].w;
        vec4 _1660 = RVar[11u];
        RVar[127u].z = RVar[2u].x * RVar[0u].w;
        float _1669 = RVar[5u].x;
        float _1671 = RVar[5u].y;
        float _1673 = RVar[5u].z;
        float _1675 = RVar[3u].w;
        vec4 _1678 = RVar[10u];
        float _1686 = RVar[127u].z;
        float _1690 = RVar[2u].x;
        float _1693 = RVar[4u].y;
        float _1695 = RVar[13u].y;
        float _1698 = RVar[4u].z;
        float _1700 = RVar[11u].z;
        float _1702 = RVar[0u].y;
        RVar[127u].x = (RVar[2u].x * dot(vec4(_1651, _1653, _1655, _1657), _1660)) + uintBitsToFloat(0u);
        RVar[124u].y = _1686 + uintBitsToFloat(0u);
        RVar[127u].w = _1693 * _1695;
        RVar[126u].x = (_1698 * _1700) + _1702;
        RVar[127u].y = dot(vec4(RVar[5u].x, RVar[5u].y, RVar[5u].z, RVar[3u].w), RVar[13u]);
        RVar[0u].y = (_1690 * dot(vec4(_1669, _1671, _1673, _1675), _1678)) + uintBitsToFloat(0u);
        float _1738 = RVar[4u].z;
        float _1740 = RVar[12u].z;
        RVar[126u].y = dot(vec4(RVar[5u].x, RVar[5u].y, RVar[5u].z, RVar[3u].w), RVar[12u]);
        RVar[125u].x = _1738 * _1740;
        float _1757 = RVar[4u].z;
        float _1759 = RVar[7u].z;
        RVar[125u].y = dot(vec4(RVar[5u].x, RVar[5u].y, RVar[5u].z, RVar[3u].w), RVar[7u]);
        RVar[124u].x = _1757 * _1759;
        float _1764 = RVar[2u].y;
        float _1766 = RVar[127u].y;
        float _1769 = RVar[2u].y;
        float _1771 = RVar[126u].y;
        float _1782 = RVar[4u].z;
        float _1784 = RVar[10u].z;
        float _1786 = RVar[6u].z;
        float _1788 = (_1782 * _1784) + _1786;
        RVar[126u].z = (RVar[4u].x * RVar[9u].x) + RVar[8u].x;
        RVar[122u].x = _1788;
        float _1792 = RVar[2u].y;
        float _1794 = RVar[125u].y;
        float _1800 = RVar[4u].x;
        float _1802 = RVar[10u].x;
        float _1806 = RVar[124u].y;
        float _1809 = RVar[4u].z;
        float _1811 = RVar[13u].z;
        float _1813 = RVar[127u].w;
        RVar[125u].y = RVar[127u].x + (_1769 * _1771);
        RVar[125u].z = (_1800 * _1802) + _1788;
        RVar[127u].w = _1806 + (_1764 * _1766);
        RVar[10u].x = (_1809 * _1811) + _1813;
        float _1821 = RVar[5u].x;
        float _1823 = RVar[5u].y;
        float _1825 = RVar[5u].z;
        float _1827 = RVar[3u].w;
        vec4 _1830 = RVar[15u];
        RVar[126u].w = RVar[0u].y + (_1792 * _1794);
        float _1837 = RVar[5u].x;
        float _1839 = RVar[5u].y;
        float _1841 = RVar[5u].z;
        float _1843 = RVar[3u].w;
        vec4 _1846 = RVar[16u];
        RVar[127u].z = RVar[2u].z * dot(vec4(_1821, _1823, _1825, _1827), _1830);
        float _1853 = RVar[5u].x;
        float _1855 = RVar[5u].y;
        float _1857 = RVar[5u].z;
        float _1859 = RVar[3u].w;
        vec4 _1862 = RVar[17u];
        float _1871 = RVar[127u].w;
        float _1873 = RVar[127u].z;
        float _1876 = RVar[2u].z;
        float _1879 = RVar[4u].x;
        float _1881 = RVar[11u].x;
        float _1883 = RVar[126u].x;
        float _1887 = RVar[4u].y;
        float _1889 = RVar[15u].y;
        RVar[127u].x = RVar[125u].y + (RVar[2u].z * dot(vec4(_1837, _1839, _1841, _1843), _1846));
        RVar[125u].y = _1871 + _1873;
        RVar[125u].w = (_1879 * _1881) + _1883;
        RVar[11u].x = _1887 * _1889;
        float _1896 = RVar[5u].x;
        float _1898 = RVar[5u].y;
        float _1900 = RVar[5u].z;
        float _1902 = RVar[3u].w;
        vec4 _1905 = RVar[14u];
        RVar[124u].y = RVar[126u].w + (_1876 * dot(vec4(_1853, _1855, _1857, _1859), _1862));
        float _1912 = RVar[5u].x;
        float _1914 = RVar[5u].y;
        float _1916 = RVar[5u].z;
        float _1918 = RVar[3u].w;
        vec4 _1921 = RVar[18u];
        RVar[126u].x = RVar[2u].w * dot(vec4(_1896, _1898, _1900, _1902), _1905);
        float _1928 = RVar[5u].x;
        float _1930 = RVar[5u].y;
        float _1932 = RVar[5u].z;
        float _1934 = RVar[3u].w;
        vec4 _1937 = RVar[1u];
        float _1940 = RVar[2u].w;
        float _1948 = RVar[127u].x;
        float _1951 = RVar[2u].w;
        float _1954 = RVar[4u].z;
        float _1956 = RVar[16u].z;
        float _1959 = RVar[4u].y;
        float _1961 = RVar[12u].y;
        float _1963 = RVar[125u].x;
        float _1965 = (_1959 * _1961) + _1963;
        RVar[19u].x = RVar[125u].y + RVar[126u].x;
        RVar[19u].y = _1948 + (_1940 * dot(vec4(_1912, _1914, _1916, _1918), _1921));
        RVar[126u].w = _1954 * _1956;
        RVar[122u].x = _1965;
        float _1979 = RVar[4u].x;
        float _1981 = RVar[12u].x;
        float _1985 = RVar[124u].y;
        float _1988 = RVar[4u].z;
        float _1990 = RVar[14u].z;
        float _1993 = RVar[4u].z;
        float _1995 = RVar[17u].z;
        RVar[124u].x = (RVar[4u].y * RVar[7u].y) + RVar[124u].x;
        RVar[124u].y = (_1979 * _1981) + _1965;
        RVar[19u].z = _1985 + (_1951 * dot(vec4(_1928, _1930, _1932, _1934), _1937));
        RVar[127u].w = _1988 * _1990;
        float _2010 = RVar[4u].z;
        float _2012 = RVar[18u].z;
        float _2015 = RVar[4u].x;
        float _2017 = RVar[13u].x;
        float _2019 = RVar[10u].x;
        float _2023 = RVar[4u].z;
        float _2025 = RVar[1u].z;
        float _2028 = RVar[4u].y;
        float _2030 = RVar[17u].y;
        RVar[127u].x = (RVar[4u].y * RVar[16u].y) + RVar[126u].w;
        RVar[127u].z = (_2015 * _2017) + _2019;
        RVar[126u].w = _2023 * _2025;
        RVar[126u].x = (_2028 * _2030) + (_1993 * _1995);
        float _2038 = RVar[4u].y;
        float _2040 = RVar[14u].y;
        float _2042 = RVar[127u].w;
        float _2044 = (_2038 * _2040) + _2042;
        float _2046 = RVar[4u].x;
        float _2048 = RVar[7u].x;
        float _2050 = RVar[124u].x;
        float _2054 = RVar[4u].y;
        float _2056 = RVar[18u].y;
        RVar[123u].x = _2044;
        RVar[124u].z = (_2046 * _2048) + _2050;
        RVar[125u].x = (_2054 * _2056) + (_2010 * _2012);
        float _2070 = RVar[2u].x;
        float _2072 = RVar[125u].w;
        float _2077 = RVar[4u].x;
        float _2079 = RVar[14u].x;
        float _2083 = RVar[2u].x;
        float _2085 = RVar[126u].z;
        float _2088 = (_2083 * _2085) + uintBitsToFloat(0u);
        float _2090 = RVar[4u].y;
        float _2092 = RVar[1u].y;
        float _2094 = RVar[126u].w;
        RVar[124u].x = (RVar[2u].x * RVar[125u].z) + uintBitsToFloat(0u);
        RVar[125u].y = (_2070 * _2072) + uintBitsToFloat(0u);
        RVar[126u].z = (_2077 * _2079) + _2044;
        RVar[123u].w = _2088;
        RVar[14u].x = (_2090 * _2092) + _2094;
        float _2103 = RVar[4u].x;
        float _2105 = RVar[4u].z;
        float _2107 = RVar[11u].x;
        float _2111 = RVar[15u].x;
        float _2113 = RVar[15u].z;
        float _2119 = RVar[2u].y;
        float _2121 = RVar[127u].z;
        float _2123 = (_2119 * _2121) + _2088;
        RVar[122u].x = _2123;
        float _2126 = RVar[2u].z;
        float _2128 = (_2126 * dot(vec4(_2103, _2105, _2107, uintBitsToFloat(2147483648u)), vec4(_2111, _2113, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)))) + _2123;
        float _2130 = RVar[2u].y;
        float _2132 = RVar[124u].z;
        float _2134 = RVar[124u].x;
        float _2138 = RVar[2u].y;
        float _2140 = RVar[124u].y;
        float _2142 = RVar[125u].y;
        RVar[123u].x = _2128;
        RVar[125u].y = (_2130 * _2132) + _2134;
        RVar[126u].w = (_2138 * _2140) + _2142;
        float _2155 = RVar[4u].x;
        float _2157 = RVar[16u].x;
        float _2159 = RVar[127u].x;
        float _2161 = (_2155 * _2157) + _2159;
        RVar[20u].x = (RVar[2u].w * RVar[126u].z) + _2128;
        RVar[123u].z = _2161;
        float _2165 = RVar[4u].x;
        float _2167 = RVar[17u].x;
        float _2169 = RVar[126u].x;
        float _2171 = (_2165 * _2167) + _2169;
        float _2173 = RVar[2u].z;
        float _2175 = RVar[126u].w;
        RVar[123u].x = _2171;
        RVar[124u].y = (_2173 * _2161) + _2175;
        float _2181 = RVar[4u].x;
        float _2183 = RVar[18u].x;
        float _2185 = RVar[125u].x;
        float _2187 = (_2181 * _2183) + _2185;
        float _2189 = RVar[2u].z;
        float _2191 = RVar[125u].y;
        RVar[123u].x = _2187;
        RVar[126u].w = (_2189 * _2171) + _2191;
        float _2197 = RVar[4u].x;
        float _2199 = RVar[1u].x;
        float _2201 = RVar[14u].x;
        float _2203 = (_2197 * _2199) + _2201;
        float _2205 = RVar[2u].w;
        float _2207 = RVar[124u].y;
        RVar[123u].x = _2203;
        RVar[20u].y = (_2205 * _2187) + _2207;
        RVar[20u].z = (RVar[2u].w * _2203) + RVar[126u].w;
    }
    if (stackVar[stackIdxVar - 1] == 0)
    {
        stateVar = int(stateVar == 0);
    }
    if (stateVar == 0)
    {
        RVar[19u].x = uintBitsToFloat(0u);
        RVar[19u].y = uintBitsToFloat(0u);
        RVar[19u].z = uintBitsToFloat(0u);
        RVar[19u].w = uintBitsToFloat(1065353216u);
        RVar[9u].x = uintBitsToFloat(0u);
        RVar[20u].x = uintBitsToFloat(0u);
        RVar[20u].y = uintBitsToFloat(0u);
        RVar[20u].z = uintBitsToFloat(0u);
        RVar[20u].w = uintBitsToFloat(0u);
    }
    stackVar[stackIdxVar] = stateVar;
    stackIdxVar++;
    do
    {
        int _2259 = stateVar;
        if (_2259 == 3)
        {
            stateVar = 0;
        }
        if (_2259 == 1)
        {
            stateVar = 2;
        }
        if (stateVar == 0)
        {
            RVar[0u].w = intBitsToFloat((floatBitsToInt(CBUFFER_1.values[3].x) > floatBitsToInt(RVar[9u].x)) ? (-1) : 0);
            bool _2284 = floatBitsToInt(RVar[0u].w) != (0);
            predVar = _2284;
            stateVar = _2284 ? 0 : 1;
        }
        if (stateVar == 1)
        {
            stateVar = 2;
        }
        if (stateVar == 0)
        {
            float _2308 = RVar[9u].x;
            float _2311 = intBitsToFloat((-1) + floatBitsToInt(_2308));
            float _2315 = RVar[9u].x;
            float _2318 = intBitsToFloat((-2) + floatBitsToInt(_2315));
            float _2322 = RVar[9u].x;
            float _2325 = intBitsToFloat((-3) + floatBitsToInt(_2322));
            float _2327 = RVar[9u].x;
            float _2330 = RVar[2u].x;
            RVar[127u].x = intBitsToFloat((floatBitsToInt(RVar[9u].x) == int(0u)) ? floatBitsToInt(RVar[1u].x) : (0));
            RVar[0u].y = _2311;
            RVar[0u].z = _2318;
            RVar[0u].w = _2325;
            RVar[127u].y = intBitsToFloat((floatBitsToInt(_2327) == int(0u)) ? floatBitsToInt(_2330) : (0));
            float _2343 = RVar[1u].y;
            float _2348 = intBitsToFloat((floatBitsToInt(_2311) == int(0u)) ? floatBitsToInt(_2343) : (0));
            float _2351 = RVar[2u].y;
            float _2356 = intBitsToFloat((floatBitsToInt(_2311) == int(0u)) ? floatBitsToInt(_2351) : (0));
            float _2359 = RVar[1u].w;
            float _2367 = RVar[1u].z;
            float _2375 = RVar[2u].z;
            RVar[123u].x = _2348;
            RVar[123u].y = _2356;
            RVar[127u].z = intBitsToFloat((floatBitsToInt(_2325) == int(0u)) ? floatBitsToInt(_2359) : (0));
            RVar[127u].w = intBitsToFloat((floatBitsToInt(_2318) == int(0u)) ? floatBitsToInt(_2367) : (0));
            RVar[126u].w = intBitsToFloat((floatBitsToInt(_2318) == int(0u)) ? floatBitsToInt(_2375) : (0));
            float _2387 = RVar[127u].y;
            float _2390 = RVar[127u].x;
            float _2406 = RVar[9u].x;
            RVar[126u].z = intBitsToFloat((floatBitsToInt(RVar[0u].w) == int(0u)) ? floatBitsToInt(RVar[2u].w) : (0));
            RVar[9u].x = intBitsToFloat(floatBitsToInt(_2406) + (1));
            float _2414 = RVar[127u].w;
            float _2426 = RVar[127u].z;
            RVar[8u].x = RVar[126u].z + (RVar[126u].w + (_2387 + _2356));
            float _2435 = intBitsToFloat(floatBitsToInt(intBitsToFloat(floatBitsToInt(_2426) + floatBitsToInt(intBitsToFloat(floatBitsToInt(_2414) + floatBitsToInt(intBitsToFloat(floatBitsToInt(_2390) + floatBitsToInt(_2348))))))) * (3));
            RVar[0u].z = _2435;
            RVar[0u].y = intBitsToFloat(floatBitsToInt(_2435) + (2));
            RVar[0u].w = intBitsToFloat(floatBitsToInt(_2435) + (1));
        }
        if (stateVar == 0)
        {
            RVar[6u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].z)];
            RVar[7u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].w)];
            RVar[0u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].y)];
        }
        if (stateVar == 0)
        {
            float _2474 = RVar[5u].x;
            float _2476 = RVar[5u].y;
            float _2478 = RVar[5u].z;
            float _2480 = RVar[3u].w;
            vec4 _2483 = RVar[6u];
            RVar[127u].x = RVar[4u].z * RVar[6u].z;
            float _2492 = RVar[5u].x;
            float _2494 = RVar[5u].y;
            float _2496 = RVar[5u].z;
            float _2498 = RVar[3u].w;
            vec4 _2501 = RVar[7u];
            RVar[127u].y = RVar[8u].x * dot(vec4(_2474, _2476, _2478, _2480), _2483);
            float _2508 = RVar[5u].x;
            float _2510 = RVar[5u].y;
            float _2512 = RVar[5u].z;
            float _2514 = RVar[3u].w;
            vec4 _2517 = RVar[0u];
            float _2523 = RVar[8u].x;
            float _2529 = RVar[4u].z;
            float _2531 = RVar[7u].z;
            float _2534 = RVar[4u].z;
            float _2536 = RVar[0u].z;
            float _2539 = RVar[19u].x;
            float _2541 = RVar[127u].y;
            RVar[8u].y = RVar[19u].y + (RVar[8u].x * dot(vec4(_2492, _2494, _2496, _2498), _2501));
            RVar[10u].x = _2539 + _2541;
            float _2546 = RVar[4u].y;
            float _2548 = RVar[6u].y;
            float _2550 = RVar[127u].x;
            float _2552 = (_2546 * _2548) + _2550;
            float _2554 = RVar[4u].x;
            float _2556 = RVar[0u].x;
            float _2558 = (_2554 * _2556) + (_2534 * _2536);
            float _2560 = RVar[19u].z;
            float _2563 = RVar[4u].y;
            float _2565 = RVar[7u].y;
            float _2567 = (_2563 * _2565) + (_2529 * _2531);
            RVar[123u].x = _2552;
            RVar[123u].y = _2558;
            RVar[0u].z = _2560 + (_2523 * dot(vec4(_2508, _2510, _2512, _2514), _2517));
            RVar[122u].x = _2567;
            float _2573 = RVar[4u].y;
            float _2575 = RVar[0u].y;
            float _2577 = (_2573 * _2575) + _2558;
            float _2579 = RVar[4u].x;
            float _2581 = RVar[6u].x;
            float _2583 = (_2579 * _2581) + _2552;
            float _2585 = RVar[4u].x;
            float _2587 = RVar[7u].x;
            float _2589 = (_2585 * _2587) + _2567;
            RVar[123u].y = _2577;
            RVar[123u].z = _2583;
            RVar[123u].w = _2589;
            float _2600 = RVar[8u].x;
            float _2602 = RVar[20u].y;
            float _2606 = RVar[8u].x;
            float _2608 = RVar[20u].z;
            RVar[0u].x = (RVar[8u].x * _2583) + RVar[20u].x;
            RVar[0u].y = (_2600 * _2589) + _2602;
            RVar[6u].z = (_2606 * _2577) + _2608;
            float _2617 = RVar[20u].y;
            float _2619 = RVar[20u].z;
            float _2621 = RVar[20u].w;
            RVar[7u].x = RVar[20u].x;
            RVar[7u].y = _2617;
            RVar[7u].z = _2619;
            RVar[7u].w = _2621;
            float _2629 = RVar[0u].y;
            float _2631 = RVar[6u].z;
            float _2633 = RVar[20u].w;
            RVar[20u].x = RVar[0u].x;
            RVar[20u].y = _2629;
            RVar[20u].z = _2631;
            RVar[20u].w = _2633;
            float _2641 = RVar[19u].y;
            float _2643 = RVar[19u].z;
            float _2645 = RVar[19u].w;
            RVar[6u].x = RVar[19u].x;
            RVar[6u].y = _2641;
            RVar[6u].z = _2643;
            RVar[6u].w = _2645;
            float _2653 = RVar[8u].y;
            float _2655 = RVar[0u].z;
            float _2657 = RVar[19u].w;
            RVar[19u].x = RVar[10u].x;
            RVar[19u].y = _2653;
            RVar[19u].z = _2655;
            RVar[19u].w = _2657;
        }
    } while (stateVar != 2);
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
    int stackIdx_3 = stackIdxVar;
    int newStackIdx_3 = stackIdx_3 - 1;
    stackIdxVar = newStackIdx_3;
    stateVar = stackVar[newStackIdx_3];
    if (stateVar == 0)
    {
        RVar[0u].x = dot(RVar[19u], CBUFFER_3.values[3]);
        RVar[5u].z = uintBitsToFloat(1065353216u);
        float _2701 = RVar[20u].w;
        float _2703 = RVar[20u].w;
        RVar[0u].y = dot(RVar[19u], CBUFFER_3.values[4]);
        float _2713 = RVar[20u].z;
        float _2715 = RVar[20u].z;
        float _2717 = (_2713 * _2715) + (_2701 * _2703);
        RVar[0u].z = dot(RVar[19u], CBUFFER_3.values[5]);
        RVar[122u].x = _2717;
        float _2727 = RVar[20u].y;
        float _2729 = RVar[20u].y;
        float _2731 = (_2727 * _2729) + _2717;
        RVar[0u].w = dot(RVar[19u], CBUFFER_3.values[6]);
        RVar[122u].x = _2731;
        float _2742 = RVar[20u].x;
        float _2744 = RVar[20u].x;
        float _2746 = (_2742 * _2744) + _2731;
        RVar[1u].x = CBUFFER_3.values[26].x;
        RVar[1u].y = CBUFFER_3.values[26].y;
        RVar[1u].z = CBUFFER_3.values[26].z;
        RVar[123u].w = _2746;
        vec4 _2752 = RVar[19u];
        float _2757 = inversesqrt(_2746);
        float _2759 = RVar[20u].x;
        float _2760 = _2759 * _2757;
        float _2762 = RVar[20u].y;
        float _2763 = _2762 * _2757;
        float _2765 = RVar[20u].z;
        float _2766 = _2765 * _2757;
        float _2768 = RVar[20u].w;
        float _2769 = _2768 * _2757;
        RVar[127u].x = _2760;
        RVar[127u].y = _2763;
        RVar[127u].z = _2766;
        RVar[127u].w = _2769;
        RVar[126u].x = (-dot(_2752, CBUFFER_3.values[2])) + (-CBUFFER_3.values[34].x);
        float _2784 = dot(vec4(_2760, _2763, _2766, _2769), CBUFFER_3.values[0]);
        RVar[2u].x = _2784;
        RVar[7u].x = _2760;
        vec4 _2788 = RVar[127u];
        float _2791 = dot(_2788, CBUFFER_3.values[1]);
        RVar[2u].y = _2791;
        RVar[6u].x = (_2784 * uintBitsToFloat(1056964608u)) + uintBitsToFloat(1056964608u);
        vec4 _2800 = RVar[127u];
        float _2803 = dot(_2800, CBUFFER_3.values[2]);
        RVar[2u].z = _2803;
        RVar[5u].y = ((-_2791) * uintBitsToFloat(1056964608u)) + uintBitsToFloat(1056964608u);
        float _2812 = RVar[2u].x;
        float _2814 = RVar[2u].y;
        RVar[7u].y = RVar[127u].y;
        float _2836 = RVar[126u].x;
        float _2844 = RVar[2u].z;
        RVar[7u].z = RVar[127u].z;
        RVar[1u].w = clamp(_2836 * CBUFFER_3.values[42].x, 0.0, 1.0);
        float _2852 = RVar[2u].x;
        float _2854 = RVar[2u].y;
        float _2866 = min(max(-dot(vec4(_2812, _2814, _2803, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[7].x, CBUFFER_3.values[7].y, CBUFFER_3.values[7].z, uintBitsToFloat(0u))), uintBitsToFloat(0u)), uintBitsToFloat(1065353216u));
        RVar[126u].x = (_2866 * CBUFFER_3.values[15].y) + uintBitsToFloat(0u);
        RVar[127u].z = (_2866 * CBUFFER_3.values[15].x) + uintBitsToFloat(0u);
        RVar[127u].w = (_2866 * CBUFFER_3.values[15].z) + uintBitsToFloat(0u);
        RVar[126u].w = (_2866 * CBUFFER_3.values[15].w) + uintBitsToFloat(0u);
        float _2896 = RVar[2u].x;
        float _2898 = RVar[2u].y;
        float _2900 = RVar[2u].z;
        float _2914 = min(max(-dot(vec4(_2852, _2854, _2844 * CBUFFER_3.values[8].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[8].x, CBUFFER_3.values[8].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u))), uintBitsToFloat(0u)), uintBitsToFloat(1065353216u));
        float _2925 = RVar[127u].w;
        float _2934 = RVar[127u].z;
        float _2940 = RVar[126u].w;
        RVar[126u].x = (_2914 * CBUFFER_3.values[16].y) + RVar[126u].x;
        RVar[127u].y = (_2914 * CBUFFER_3.values[16].z) + _2925;
        RVar[127u].w = (_2914 * CBUFFER_3.values[16].x) + _2934;
        RVar[127u].x = (_2914 * CBUFFER_3.values[16].w) + _2940;
        float _2948 = RVar[2u].x;
        float _2950 = RVar[2u].y;
        float _2952 = RVar[2u].z;
        float _2966 = min(max(-dot(vec4(_2896, _2898, _2900, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[9].x, CBUFFER_3.values[9].y, CBUFFER_3.values[9].z, uintBitsToFloat(0u))), uintBitsToFloat(0u)), uintBitsToFloat(1065353216u));
        float _2977 = RVar[126u].x;
        float _2983 = RVar[127u].y;
        float _2992 = RVar[127u].x;
        RVar[127u].x = (_2966 * CBUFFER_3.values[17].x) + RVar[127u].w;
        RVar[127u].y = (_2966 * CBUFFER_3.values[17].y) + _2977;
        RVar[127u].z = (_2966 * CBUFFER_3.values[17].z) + _2983;
        RVar[126u].y = (_2966 * CBUFFER_3.values[17].w) + _2992;
        float _3000 = RVar[2u].x;
        float _3002 = RVar[2u].y;
        float _3004 = RVar[2u].z;
        float _3018 = min(max(-dot(vec4(_2948, _2950, _2952, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[10].x, CBUFFER_3.values[10].y, CBUFFER_3.values[10].z, uintBitsToFloat(0u))), uintBitsToFloat(0u)), uintBitsToFloat(1065353216u));
        float _3032 = RVar[127u].y;
        float _3038 = RVar[127u].z;
        float _3044 = RVar[126u].y;
        RVar[127u].y = (_3018 * CBUFFER_3.values[18].x) + RVar[127u].x;
        RVar[127u].z = (_3018 * CBUFFER_3.values[18].y) + _3032;
        RVar[127u].w = (_3018 * CBUFFER_3.values[18].z) + _3038;
        RVar[126u].z = (_3018 * CBUFFER_3.values[18].w) + _3044;
        float _3052 = RVar[2u].x;
        float _3054 = RVar[2u].y;
        float _3056 = RVar[2u].z;
        float _3070 = min(max(-dot(vec4(_3000, _3002, _3004, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[11].x, CBUFFER_3.values[11].y, CBUFFER_3.values[11].z, uintBitsToFloat(0u))), uintBitsToFloat(0u)), uintBitsToFloat(1065353216u));
        float _3084 = RVar[127u].y;
        float _3090 = RVar[127u].w;
        float _3096 = RVar[126u].z;
        RVar[127u].x = (_3070 * CBUFFER_3.values[19].y) + RVar[127u].z;
        RVar[127u].z = (_3070 * CBUFFER_3.values[19].x) + _3084;
        RVar[127u].w = (_3070 * CBUFFER_3.values[19].z) + _3090;
        RVar[126u].w = (_3070 * CBUFFER_3.values[19].w) + _3096;
        float _3104 = RVar[2u].x;
        float _3106 = RVar[2u].y;
        float _3108 = RVar[2u].z;
        float _3122 = min(max(-dot(vec4(_3052, _3054, _3056, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[12].x, CBUFFER_3.values[12].y, CBUFFER_3.values[12].z, uintBitsToFloat(0u))), uintBitsToFloat(0u)), uintBitsToFloat(1065353216u));
        float _3133 = RVar[127u].w;
        float _3142 = RVar[127u].z;
        float _3148 = RVar[126u].w;
        RVar[4u].x = (_3122 * CBUFFER_3.values[20].y) + RVar[127u].x;
        RVar[4u].y = (_3122 * CBUFFER_3.values[20].z) + _3133;
        RVar[4u].z = max(-dot(vec4(_3104, _3106, _3108, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[13].x, CBUFFER_3.values[13].y, CBUFFER_3.values[13].z, uintBitsToFloat(0u))), uintBitsToFloat(0u));
        RVar[2u].w = (_3122 * CBUFFER_3.values[20].x) + _3142;
        RVar[5u].x = (_3122 * CBUFFER_3.values[20].w) + _3148;
    }
    vec4 _3171 = (RVar[0u] * vec4(VS_PUSH.posMulAdd.xy, 1.0, 1.0)) + vec4(VS_PUSH.posMulAdd.zw, 0.0, 0.0);
    vec4 _3174 = _3171;
    _3174.y = -_3171.y;
    vec4 _3182 = _3174;
    _3182.z = (_3174.z + (_3174.w * VS_PUSH.zSpaceMul.x)) * VS_PUSH.zSpaceMul.y;
    gl_Position = _3182;
    PARAM_0 = RVar[1u];
    PARAM_1 = RVar[7u];
    if (stateVar == 0)
    {
        float _3196 = RVar[2u].x;
        float _3198 = RVar[2u].y;
        float _3200 = RVar[2u].z;
        float _3214 = RVar[4u].z;
        float _3216 = min(_3214, uintBitsToFloat(1065353216u));
        float _3227 = RVar[4u].x;
        float _3233 = RVar[4u].y;
        float _3242 = RVar[5u].x;
        RVar[127u].x = (_3216 * CBUFFER_3.values[21].x) + RVar[2u].w;
        RVar[127u].y = (_3216 * CBUFFER_3.values[21].y) + _3227;
        RVar[127u].z = (_3216 * CBUFFER_3.values[21].z) + _3233;
        RVar[126u].y = (_3216 * CBUFFER_3.values[21].w) + _3242;
        float _3258 = min(max(-dot(vec4(_3196, _3198, _3200, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[14].x, CBUFFER_3.values[14].y, CBUFFER_3.values[14].z, uintBitsToFloat(0u))), uintBitsToFloat(0u)), uintBitsToFloat(1065353216u));
        float _3260 = RVar[5u].z;
        RVar[126u].x = RVar[5u].z * CBUFFER_4.values[17].w;
        RVar[125u].x = _3260 * CBUFFER_4.values[20].w;
        float _3270 = RVar[127u].y;
        float _3273 = clamp((_3258 * CBUFFER_3.values[22].y) + _3270, 0.0, 1.0);
        float _3277 = RVar[127u].x;
        float _3280 = clamp((_3258 * CBUFFER_3.values[22].x) + _3277, 0.0, 1.0);
        float _3284 = RVar[126u].y;
        float _3291 = RVar[127u].z;
        RVar[123u].x = _3273;
        RVar[123u].y = _3280;
        RVar[127u].z = clamp((_3258 * CBUFFER_3.values[22].w) + _3284, 0.0, 1.0);
        RVar[127u].w = clamp((_3258 * CBUFFER_3.values[22].z) + _3291, 0.0, 1.0);
        float _3306 = clamp((CBUFFER_4.values[2].y * CBUFFER_3.values[23].y) + _3273, 0.0, 1.0);
        float _3313 = clamp((CBUFFER_4.values[2].x * CBUFFER_3.values[23].x) + _3280, 0.0, 1.0);
        RVar[123u].x = _3306;
        RVar[123u].y = _3313;
        float _3321 = RVar[127u].z;
        float _3331 = RVar[127u].w;
        float _3334 = clamp((CBUFFER_4.values[2].z * CBUFFER_3.values[23].z) + _3331, 0.0, 1.0);
        RVar[123u].w = _3334;
        float _3340 = RVar[3u].y;
        float _3347 = RVar[5u].z;
        float _3351 = RVar[126u].x;
        float _3353 = (_3347 * CBUFFER_4.values[17].z) + _3351;
        RVar[2u].x = RVar[3u].x * max(_3313, uintBitsToFloat(1065353216u));
        RVar[2u].y = _3340 * max(_3306, uintBitsToFloat(1065353216u));
        RVar[122u].x = _3353;
        float _3358 = RVar[5u].y;
        float _3362 = (_3358 * CBUFFER_4.values[17].y) + _3353;
        float _3364 = RVar[3u].z;
        RVar[123u].x = _3362;
        RVar[2u].z = _3364 * max(_3334, uintBitsToFloat(1065353216u));
        RVar[2u].w = max(clamp(_3321 + CBUFFER_4.values[2].w, 0.0, 1.0), uintBitsToFloat(0u)) * CBUFFER_4.values[0].w;
        float _3379 = RVar[5u].z;
        float _3383 = RVar[125u].x;
        RVar[0u].x = (RVar[6u].x * CBUFFER_4.values[17].x) + _3362;
        RVar[125u].x = (_3379 * CBUFFER_4.values[20].z) + _3383;
        RVar[0u].y = dot(vec4(RVar[6u].x, RVar[5u].y, RVar[5u].z, RVar[5u].z), CBUFFER_4.values[18]);
        float _3418 = RVar[5u].z;
        RVar[1u].x = dot(vec4(RVar[6u].x, RVar[5u].y, RVar[125u].x, uintBitsToFloat(0u)), vec4(CBUFFER_4.values[20].x, CBUFFER_4.values[20].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[1u].y = dot(vec4(RVar[6u].x, RVar[5u].y, RVar[5u].z, _3418 * CBUFFER_4.values[21].w), vec4(CBUFFER_4.values[21].x, CBUFFER_4.values[21].y, CBUFFER_4.values[21].z, uintBitsToFloat(1065353216u)));
    }
    PARAM_2 = RVar[2u];
    PARAM_3 = vec4(RVar[0u].x, RVar[0u].y, RVar[0u].z, RVar[0u].z);
    PARAM_4 = vec4(RVar[1u].x, RVar[1u].y, RVar[1u].z, RVar[1u].z);
    if (stateVar == 0)
    {
    }
}

 