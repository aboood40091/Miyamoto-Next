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
layout(location = 5) out vec4 PARAM_5;
layout(location = 6) out vec4 PARAM_6;
layout(location = 7) out vec4 PARAM_7;
layout(location = 8) out vec4 PARAM_8;
layout(location = 0) in uvec4 aBlendIndex_0_0;
layout(location = 1) in uvec4 aBlendWeight_0_0;
layout(location = 2) in uvec4 aColor0_0_0;
layout(location = 3) in uvec3 aNormal_0_0;
layout(location = 4) in uvec3 aPosition_0_0;
layout(location = 5) in uvec2 aTexCoord0_0_0;
layout(location = 6) in uvec2 aTexCoord1_0_0;
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
        RVar[7u] = vec4(vec4(uintBitsToFloat(aTexCoord1_0_0.x), uintBitsToFloat(aTexCoord1_0_0.y), 0.0, 1.0).xy, 0.0, 1.0);
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
        RVar[0u].z = intBitsToFloat((floatBitsToInt(CBUFFER_1.values[3].x) != (0)) ? (-1) : 0);
        RVar[4u].w = uintBitsToFloat(1065353216u);
        RVar[21u].w = uintBitsToFloat(1065353216u);
        RVar[22u].w = uintBitsToFloat(0u);
        bool _92 = floatBitsToInt(RVar[0u].z) == (0);
        predVar = _92;
        stateVar = _92 ? 0 : 1;
    }
    if (stateVar == 0)
    {
        float _118 = RVar[4u].z;
        RVar[21u].x = dot(vec4(RVar[5u].x, RVar[5u].y, RVar[5u].z, RVar[4u].w), CBUFFER_1.values[0]);
        RVar[127u].x = _118 * CBUFFER_1.values[0].z;
        RVar[21u].y = dot(vec4(RVar[5u].x, RVar[5u].y, RVar[5u].z, RVar[4u].w), CBUFFER_1.values[1]);
        RVar[21u].z = dot(vec4(RVar[5u].x, RVar[5u].y, RVar[5u].z, RVar[4u].w), CBUFFER_1.values[2]);
        float _169 = RVar[4u].z;
        RVar[22u].x = dot(vec4(RVar[4u].x, RVar[4u].y, RVar[127u].x, uintBitsToFloat(2147483648u)), vec4(CBUFFER_1.values[0].x, CBUFFER_1.values[0].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        float _189 = RVar[4u].z;
        RVar[22u].y = dot(vec4(RVar[4u].x, RVar[4u].y, _169 * CBUFFER_1.values[1].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_1.values[1].x, CBUFFER_1.values[1].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[22u].z = dot(vec4(RVar[4u].x, RVar[4u].y, _189 * CBUFFER_1.values[2].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_1.values[2].x, CBUFFER_1.values[2].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
    }
    if (stackVar[stackIdxVar - 1] == 0)
    {
        stateVar = int(stateVar == 0);
    }
    stackVar[stackIdxVar] = stateVar;
    stackIdxVar++;
    if (stateVar == 0)
    {
        RVar[0u].z = intBitsToFloat((floatBitsToInt(CBUFFER_1.values[3].x) != (1)) ? (-1) : 0);
        bool _239 = floatBitsToInt(RVar[0u].z) == (0);
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
        RVar[21u].x = dot(vec4(RVar[5u].x, RVar[5u].y, RVar[5u].z, RVar[4u].w), RVar[0u]);
        RVar[127u].x = _306 * _308;
        RVar[21u].y = dot(vec4(RVar[5u].x, RVar[5u].y, RVar[5u].z, RVar[4u].w), RVar[2u]);
        RVar[21u].z = dot(vec4(RVar[5u].x, RVar[5u].y, RVar[5u].z, RVar[4u].w), RVar[1u]);
        float _355 = RVar[4u].z;
        float _357 = RVar[2u].z;
        RVar[22u].x = dot(vec4(RVar[4u].x, RVar[4u].y, RVar[127u].x, uintBitsToFloat(2147483648u)), vec4(RVar[0u].x, RVar[0u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        float _375 = RVar[4u].z;
        float _377 = RVar[1u].z;
        RVar[22u].y = dot(vec4(RVar[4u].x, RVar[4u].y, _355 * _357, uintBitsToFloat(2147483648u)), vec4(RVar[2u].x, RVar[2u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[22u].z = dot(vec4(RVar[4u].x, RVar[4u].y, _375 * _377, uintBitsToFloat(2147483648u)), vec4(RVar[1u].x, RVar[1u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
    }
    if (stackVar[stackIdxVar - 1] == 0)
    {
        stateVar = int(stateVar == 0);
    }
    stackVar[stackIdxVar] = stateVar;
    stackIdxVar++;
    if (stateVar == 0)
    {
        RVar[0u].z = intBitsToFloat((floatBitsToInt(CBUFFER_1.values[3].x) != (2)) ? (-1) : 0);
        bool _425 = floatBitsToInt(RVar[0u].z) == (0);
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
        RVar[8u].x = intBitsToFloat(floatBitsToInt(_453) + (2));
        RVar[1u].w = intBitsToFloat(floatBitsToInt(_453) + (1));
    }
    if (stateVar == 0)
    {
        RVar[0u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].x)];
        RVar[10u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].x)];
        RVar[9u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].y)];
        RVar[11u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].z)];
        RVar[1u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].w)];
        RVar[8u] = CBUFFER_2.values[floatBitsToUint(RVar[8u].x)];
    }
    if (stateVar == 0)
    {
        float _516 = RVar[5u].x;
        float _518 = RVar[5u].y;
        float _520 = RVar[5u].z;
        float _522 = RVar[4u].w;
        vec4 _525 = RVar[0u];
        RVar[127u].x = RVar[4u].z * RVar[0u].z;
        float _534 = RVar[5u].x;
        float _536 = RVar[5u].y;
        float _538 = RVar[5u].z;
        float _540 = RVar[4u].w;
        vec4 _543 = RVar[10u];
        RVar[127u].z = RVar[2u].x * dot(vec4(_516, _518, _520, _522), _525);
        float _550 = RVar[5u].x;
        float _552 = RVar[5u].y;
        float _554 = RVar[5u].z;
        float _556 = RVar[4u].w;
        vec4 _559 = RVar[9u];
        float _567 = RVar[127u].z;
        float _571 = RVar[2u].x;
        float _574 = RVar[4u].z;
        float _576 = RVar[10u].z;
        float _579 = RVar[4u].y;
        float _581 = RVar[0u].y;
        float _583 = RVar[127u].x;
        RVar[127u].x = (RVar[2u].x * dot(vec4(_534, _536, _538, _540), _543)) + uintBitsToFloat(0u);
        RVar[126u].y = _567 + uintBitsToFloat(0u);
        RVar[127u].w = _574 * _576;
        RVar[126u].x = (_579 * _581) + _583;
        RVar[127u].y = dot(vec4(RVar[5u].x, RVar[5u].y, RVar[5u].z, RVar[4u].w), RVar[11u]);
        RVar[124u].y = (_571 * dot(vec4(_550, _552, _554, _556), _559)) + uintBitsToFloat(0u);
        float _609 = RVar[5u].x;
        float _611 = RVar[5u].y;
        float _613 = RVar[5u].z;
        float _615 = RVar[4u].w;
        vec4 _618 = RVar[1u];
        RVar[124u].x = RVar[4u].z * RVar[1u].z;
        float _627 = RVar[5u].x;
        float _629 = RVar[5u].y;
        float _631 = RVar[5u].z;
        float _633 = RVar[4u].w;
        vec4 _636 = RVar[8u];
        RVar[125u].y = RVar[2u].y * dot(vec4(_609, _611, _613, _615), _618);
        float _644 = RVar[2u].y;
        float _646 = RVar[127u].y;
        float _649 = RVar[4u].z;
        float _651 = RVar[9u].z;
        float _654 = RVar[2u].y;
        float _662 = RVar[4u].x;
        float _664 = RVar[10u].x;
        float _666 = RVar[127u].w;
        RVar[127u].w = RVar[4u].z * RVar[11u].z;
        RVar[125u].x = (_662 * _664) + _666;
        float _675 = RVar[127u].x;
        float _677 = RVar[125u].y;
        float _680 = RVar[124u].y;
        float _683 = RVar[4u].z;
        float _685 = RVar[8u].z;
        float _688 = RVar[4u].x;
        float _690 = RVar[9u].x;
        float _692 = (_688 * _690) + (_649 * _651);
        RVar[21u].x = RVar[126u].y + (_644 * _646);
        RVar[21u].y = _675 + _677;
        RVar[21u].z = _680 + (_654 * dot(vec4(_627, _629, _631, _633), _636));
        RVar[126u].w = _683 * _685;
        RVar[122u].x = _692;
        float _700 = RVar[4u].x;
        float _702 = RVar[0u].x;
        float _704 = RVar[126u].x;
        float _706 = (_700 * _702) + _704;
        float _708 = RVar[4u].y;
        float _710 = RVar[9u].y;
        float _712 = (_708 * _710) + _692;
        float _714 = RVar[4u].y;
        float _716 = RVar[11u].y;
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
        float _741 = RVar[10u].y;
        float _743 = RVar[125u].x;
        float _747 = RVar[2u].x;
        RVar[123u].x = _732;
        RVar[126u].y = (_734 * _712) + uintBitsToFloat(0u);
        RVar[127u].z = (_739 * _741) + _743;
        RVar[127u].w = (_747 * _706) + uintBitsToFloat(0u);
        float _772 = RVar[4u].x;
        float _774 = RVar[1u].x;
        RVar[125u].x = dot(vec4(RVar[4u].x, RVar[4u].y, RVar[126u].w, uintBitsToFloat(2147483648u)), vec4(RVar[8u].x, RVar[8u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[126u].w = (_772 * _774) + _732;
        float _780 = RVar[4u].x;
        float _782 = RVar[11u].x;
        float _784 = RVar[126u].x;
        float _786 = (_780 * _782) + _784;
        RVar[123u].y = _786;
        float _795 = RVar[2u].x;
        float _797 = RVar[127u].z;
        float _800 = (_795 * _797) + uintBitsToFloat(0u);
        RVar[22u].x = (RVar[2u].y * _786) + RVar[127u].w;
        RVar[123u].y = _800;
        float _810 = RVar[2u].y;
        float _812 = RVar[125u].x;
        float _814 = RVar[126u].y;
        RVar[22u].y = (RVar[2u].y * RVar[126u].w) + _800;
        RVar[22u].z = (_810 * _812) + _814;
    }
    if (stackVar[stackIdxVar - 1] == 0)
    {
        stateVar = int(stateVar == 0);
    }
    stackVar[stackIdxVar] = stateVar;
    stackIdxVar++;
    if (stateVar == 0)
    {
        RVar[0u].z = intBitsToFloat((floatBitsToInt(CBUFFER_1.values[3].x) != (3)) ? (-1) : 0);
        bool _849 = floatBitsToInt(RVar[0u].z) == (0);
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
        RVar[8u].z = intBitsToFloat(floatBitsToInt(_862) + (1));
        RVar[8u].x = _877;
        float _890 = RVar[1u].z;
        float _894 = intBitsToFloat(floatBitsToInt(_890) * (3));
        RVar[1u].x = intBitsToFloat(floatBitsToInt(_877) + (1));
        RVar[1u].y = intBitsToFloat(floatBitsToInt(_877) + (2));
        RVar[1u].z = _894;
        RVar[9u].x = intBitsToFloat(floatBitsToInt(_894) + (2));
        RVar[1u].w = intBitsToFloat(floatBitsToInt(_894) + (1));
    }
    if (stateVar == 0)
    {
        RVar[10u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].z)];
        RVar[11u] = CBUFFER_2.values[floatBitsToUint(RVar[8u].z)];
        RVar[0u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].x)];
        RVar[12u] = CBUFFER_2.values[floatBitsToUint(RVar[8u].x)];
        RVar[13u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].x)];
        RVar[14u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].y)];
        RVar[15u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].z)];
        RVar[16u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].w)];
    }
    if (stateVar == 0)
    {
        float _969 = RVar[5u].x;
        float _971 = RVar[5u].y;
        float _973 = RVar[5u].z;
        float _975 = RVar[4u].w;
        vec4 _978 = RVar[10u];
        RVar[8u].x = RVar[4u].z * RVar[10u].z;
        float _999 = RVar[2u].x;
        RVar[1u].y = dot(vec4(RVar[5u].x, RVar[5u].y, RVar[5u].z, RVar[4u].w), RVar[11u]);
        RVar[1u].x = _999 * dot(vec4(_969, _971, _973, _975), _978);
    }
    if (stateVar == 0)
    {
        RVar[9u] = CBUFFER_2.values[floatBitsToUint(RVar[9u].x)];
    }
    if (stateVar == 0)
    {
        float _1018 = RVar[5u].x;
        float _1020 = RVar[5u].y;
        float _1022 = RVar[5u].z;
        float _1024 = RVar[4u].w;
        vec4 _1027 = RVar[0u];
        float _1035 = RVar[2u].x;
        float _1040 = RVar[4u].z;
        float _1042 = RVar[11u].z;
        float _1045 = RVar[1u].x;
        float _1049 = RVar[4u].y;
        float _1051 = RVar[10u].y;
        float _1053 = RVar[8u].x;
        RVar[127u].y = (RVar[2u].x * RVar[1u].y) + uintBitsToFloat(0u);
        RVar[126u].z = _1040 * _1042;
        RVar[127u].w = _1045 + uintBitsToFloat(0u);
        RVar[127u].x = (_1049 * _1051) + _1053;
        float _1061 = RVar[5u].x;
        float _1063 = RVar[5u].y;
        float _1065 = RVar[5u].z;
        float _1067 = RVar[4u].w;
        vec4 _1070 = RVar[12u];
        RVar[126u].w = (_1035 * dot(vec4(_1018, _1020, _1022, _1024), _1027)) + uintBitsToFloat(0u);
        float _1076 = RVar[5u].x;
        float _1078 = RVar[5u].y;
        float _1080 = RVar[5u].z;
        float _1082 = RVar[4u].w;
        vec4 _1085 = RVar[13u];
        RVar[127u].z = RVar[2u].y * dot(vec4(_1061, _1063, _1065, _1067), _1070);
        float _1092 = RVar[5u].x;
        float _1094 = RVar[5u].y;
        float _1096 = RVar[5u].z;
        float _1098 = RVar[4u].w;
        vec4 _1101 = RVar[14u];
        float _1110 = RVar[127u].w;
        float _1112 = RVar[127u].z;
        float _1115 = RVar[2u].y;
        float _1118 = RVar[4u].x;
        float _1120 = RVar[0u].x;
        float _1123 = RVar[4u].x;
        float _1125 = RVar[11u].x;
        float _1127 = RVar[126u].z;
        RVar[126u].x = RVar[127u].y + (RVar[2u].y * dot(vec4(_1076, _1078, _1080, _1082), _1085));
        RVar[127u].y = _1110 + _1112;
        RVar[127u].w = _1118 * _1120;
        RVar[125u].x = (_1123 * _1125) + _1127;
        float _1135 = RVar[5u].x;
        float _1137 = RVar[5u].y;
        float _1139 = RVar[5u].z;
        float _1141 = RVar[4u].w;
        vec4 _1144 = RVar[15u];
        RVar[126u].y = RVar[126u].w + (_1115 * dot(vec4(_1092, _1094, _1096, _1098), _1101));
        float _1163 = RVar[2u].z;
        RVar[127u].z = dot(vec4(RVar[5u].x, RVar[5u].y, RVar[5u].z, RVar[4u].w), RVar[16u]);
        float _1167 = RVar[5u].x;
        float _1169 = RVar[5u].y;
        float _1171 = RVar[5u].z;
        float _1173 = RVar[4u].w;
        vec4 _1176 = RVar[9u];
        RVar[21u].x = RVar[127u].y + (_1163 * dot(vec4(_1135, _1137, _1139, _1141), _1144));
        float _1183 = RVar[4u].y;
        float _1185 = RVar[0u].y;
        float _1187 = RVar[127u].w;
        float _1189 = (_1183 * _1185) + _1187;
        float _1191 = RVar[2u].z;
        float _1193 = RVar[127u].z;
        float _1196 = RVar[2u].z;
        float _1199 = RVar[4u].x;
        float _1201 = RVar[10u].x;
        float _1203 = RVar[127u].x;
        float _1207 = RVar[4u].y;
        float _1209 = RVar[12u].y;
        RVar[123u].x = _1189;
        RVar[127u].w = (_1199 * _1201) + _1203;
        float _1214 = RVar[4u].y;
        float _1216 = RVar[11u].y;
        float _1218 = RVar[125u].x;
        float _1220 = (_1214 * _1216) + _1218;
        float _1222 = RVar[126u].x;
        float _1225 = RVar[126u].y;
        float _1228 = RVar[4u].z;
        float _1230 = RVar[0u].z;
        float _1232 = (_1228 * _1230) + _1189;
        float _1234 = RVar[4u].z;
        float _1236 = RVar[12u].z;
        float _1238 = (_1234 * _1236) + (_1207 * _1209);
        RVar[123u].x = _1220;
        RVar[21u].y = _1222 + (_1191 * _1193);
        RVar[21u].z = _1225 + (_1196 * dot(vec4(_1167, _1169, _1171, _1173), _1176));
        RVar[123u].w = _1232;
        RVar[122u].x = _1238;
        float _1245 = RVar[4u].x;
        float _1247 = RVar[12u].x;
        float _1249 = (_1245 * _1247) + _1238;
        float _1251 = RVar[2u].x;
        float _1253 = RVar[127u].w;
        float _1256 = (_1251 * _1253) + uintBitsToFloat(0u);
        float _1258 = RVar[2u].x;
        float _1263 = RVar[2u].x;
        float _1268 = RVar[4u].z;
        float _1270 = RVar[13u].z;
        RVar[123u].x = _1249;
        RVar[123u].y = _1256;
        RVar[127u].z = (_1258 * _1232) + uintBitsToFloat(0u);
        RVar[127u].w = (_1263 * _1220) + uintBitsToFloat(0u);
        float _1277 = RVar[4u].x;
        float _1279 = RVar[4u].y;
        float _1283 = RVar[13u].x;
        float _1285 = RVar[13u].y;
        RVar[126u].w = (RVar[2u].y * _1249) + _1256;
        float _1296 = RVar[4u].x;
        float _1298 = RVar[4u].y;
        float _1300 = RVar[4u].z;
        float _1304 = RVar[14u].x;
        float _1306 = RVar[14u].y;
        float _1308 = RVar[14u].z;
        RVar[125u].y = (RVar[2u].y * dot(vec4(_1277, _1279, _1268 * _1270, uintBitsToFloat(2147483648u)), vec4(_1283, _1285, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)))) + RVar[127u].w;
        float _1320 = RVar[4u].z;
        float _1322 = RVar[15u].z;
        float _1330 = RVar[2u].y;
        float _1332 = RVar[127u].z;
        float _1336 = RVar[4u].y;
        float _1338 = RVar[16u].y;
        RVar[126u].y = RVar[4u].x * RVar[9u].x;
        RVar[127u].w = (_1330 * dot(vec4(_1296, _1298, _1300, uintBitsToFloat(2147483648u)), vec4(_1304, _1306, _1308, uintBitsToFloat(0u)))) + _1332;
        float _1357 = RVar[4u].z;
        float _1359 = RVar[16u].z;
        float _1361 = (_1357 * _1359) + (_1336 * _1338);
        RVar[127u].y = dot(vec4(RVar[4u].x, RVar[4u].y, _1320 * _1322, uintBitsToFloat(2147483648u)), vec4(RVar[15u].x, RVar[15u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[122u].x = _1361;
        float _1365 = RVar[4u].y;
        float _1367 = RVar[9u].y;
        float _1369 = RVar[126u].y;
        float _1371 = (_1365 * _1367) + _1369;
        float _1373 = RVar[4u].x;
        float _1375 = RVar[16u].x;
        float _1377 = (_1373 * _1375) + _1361;
        RVar[123u].x = _1371;
        RVar[123u].w = _1377;
        float _1381 = RVar[4u].z;
        float _1383 = RVar[9u].z;
        float _1385 = (_1381 * _1383) + _1371;
        float _1387 = RVar[2u].z;
        float _1389 = RVar[125u].y;
        float _1393 = RVar[2u].z;
        float _1395 = RVar[127u].y;
        float _1397 = RVar[126u].w;
        RVar[123u].x = _1385;
        RVar[22u].y = (_1387 * _1377) + _1389;
        RVar[22u].x = (_1393 * _1395) + _1397;
        RVar[22u].z = (RVar[2u].z * _1385) + RVar[127u].w;
    }
    if (stackVar[stackIdxVar - 1] == 0)
    {
        stateVar = int(stateVar == 0);
    }
    stackVar[stackIdxVar] = stateVar;
    stackIdxVar++;
    if (stateVar == 0)
    {
        RVar[0u].z = intBitsToFloat((floatBitsToInt(CBUFFER_1.values[3].x) != (4)) ? (-1) : 0);
        bool _1441 = floatBitsToInt(RVar[0u].z) == (0);
        predVar = _1441;
        stateVar = _1441 ? 0 : 1;
    }
    if (stateVar == 0)
    {
        float _1450 = RVar[1u].x;
        float _1454 = intBitsToFloat(floatBitsToInt(_1450) * (3));
        RVar[0u].x = _1454;
        float _1465 = RVar[1u].y;
        float _1469 = intBitsToFloat(floatBitsToInt(_1465) * (3));
        RVar[8u].x = intBitsToFloat(floatBitsToInt(_1454) + (1));
        RVar[0u].y = intBitsToFloat(floatBitsToInt(_1454) + (2));
        RVar[0u].z = _1469;
        float _1482 = RVar[1u].z;
        float _1486 = intBitsToFloat(floatBitsToInt(_1482) * (3));
        RVar[9u].x = intBitsToFloat(floatBitsToInt(_1469) + (2));
        RVar[8u].z = intBitsToFloat(floatBitsToInt(_1469) + (1));
        RVar[10u].x = _1486;
        float _1499 = RVar[1u].w;
        RVar[1u].x = intBitsToFloat(floatBitsToInt(_1486) + (1));
        RVar[1u].y = intBitsToFloat(floatBitsToInt(_1486) + (2));
        RVar[1u].z = intBitsToFloat(floatBitsToInt(_1499) * (3));
    }
    if (stateVar == 0)
    {
        RVar[11u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].x)];
        RVar[13u] = CBUFFER_2.values[floatBitsToUint(RVar[8u].x)];
        RVar[12u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].y)];
        RVar[15u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].z)];
        RVar[14u] = CBUFFER_2.values[floatBitsToUint(RVar[8u].z)];
        RVar[9u] = CBUFFER_2.values[floatBitsToUint(RVar[9u].x)];
        RVar[17u] = CBUFFER_2.values[floatBitsToUint(RVar[10u].x)];
        RVar[18u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].x)];
    }
    if (stateVar == 0)
    {
        float _1572 = RVar[4u].y;
        float _1574 = RVar[13u].y;
        float _1577 = RVar[4u].y;
        float _1579 = RVar[12u].y;
        float _1582 = RVar[1u].z;
        float _1588 = RVar[4u].z;
        float _1590 = RVar[11u].z;
        RVar[1u].x = intBitsToFloat(floatBitsToInt(RVar[1u].z) + (2));
        RVar[0u].y = _1572 * _1574;
        RVar[8u].z = _1577 * _1579;
        RVar[1u].w = intBitsToFloat(floatBitsToInt(_1582) + (1));
        float _1609 = RVar[4u].y;
        float _1611 = RVar[11u].y;
        RVar[0u].w = dot(vec4(RVar[5u].x, RVar[5u].y, RVar[5u].z, RVar[4u].w), RVar[11u]);
        RVar[10u].x = (_1609 * _1611) + (_1588 * _1590);
    }
    if (stateVar == 0)
    {
        RVar[19u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].y)];
        RVar[16u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].z)];
        RVar[20u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].w)];
        RVar[1u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].x)];
    }
    if (stateVar == 0)
    {
        float _1651 = RVar[5u].x;
        float _1653 = RVar[5u].y;
        float _1655 = RVar[5u].z;
        float _1657 = RVar[4u].w;
        vec4 _1660 = RVar[13u];
        RVar[127u].z = RVar[2u].x * RVar[0u].w;
        float _1669 = RVar[5u].x;
        float _1671 = RVar[5u].y;
        float _1673 = RVar[5u].z;
        float _1675 = RVar[4u].w;
        vec4 _1678 = RVar[12u];
        float _1686 = RVar[127u].z;
        float _1690 = RVar[2u].x;
        float _1693 = RVar[4u].y;
        float _1695 = RVar[15u].y;
        float _1698 = RVar[4u].z;
        float _1700 = RVar[13u].z;
        float _1702 = RVar[0u].y;
        RVar[127u].x = (RVar[2u].x * dot(vec4(_1651, _1653, _1655, _1657), _1660)) + uintBitsToFloat(0u);
        RVar[124u].y = _1686 + uintBitsToFloat(0u);
        RVar[127u].w = _1693 * _1695;
        RVar[126u].x = (_1698 * _1700) + _1702;
        RVar[127u].y = dot(vec4(RVar[5u].x, RVar[5u].y, RVar[5u].z, RVar[4u].w), RVar[15u]);
        RVar[0u].y = (_1690 * dot(vec4(_1669, _1671, _1673, _1675), _1678)) + uintBitsToFloat(0u);
        float _1738 = RVar[4u].z;
        float _1740 = RVar[14u].z;
        RVar[126u].y = dot(vec4(RVar[5u].x, RVar[5u].y, RVar[5u].z, RVar[4u].w), RVar[14u]);
        RVar[125u].x = _1738 * _1740;
        float _1757 = RVar[4u].z;
        float _1759 = RVar[9u].z;
        RVar[125u].y = dot(vec4(RVar[5u].x, RVar[5u].y, RVar[5u].z, RVar[4u].w), RVar[9u]);
        RVar[124u].x = _1757 * _1759;
        float _1764 = RVar[2u].y;
        float _1766 = RVar[127u].y;
        float _1769 = RVar[2u].y;
        float _1771 = RVar[126u].y;
        float _1782 = RVar[4u].z;
        float _1784 = RVar[12u].z;
        float _1786 = RVar[8u].z;
        float _1788 = (_1782 * _1784) + _1786;
        RVar[126u].z = (RVar[4u].x * RVar[11u].x) + RVar[10u].x;
        RVar[122u].x = _1788;
        float _1792 = RVar[2u].y;
        float _1794 = RVar[125u].y;
        float _1800 = RVar[4u].x;
        float _1802 = RVar[12u].x;
        float _1806 = RVar[124u].y;
        float _1809 = RVar[4u].z;
        float _1811 = RVar[15u].z;
        float _1813 = RVar[127u].w;
        RVar[125u].y = RVar[127u].x + (_1769 * _1771);
        RVar[125u].z = (_1800 * _1802) + _1788;
        RVar[127u].w = _1806 + (_1764 * _1766);
        RVar[12u].x = (_1809 * _1811) + _1813;
        float _1821 = RVar[5u].x;
        float _1823 = RVar[5u].y;
        float _1825 = RVar[5u].z;
        float _1827 = RVar[4u].w;
        vec4 _1830 = RVar[17u];
        RVar[126u].w = RVar[0u].y + (_1792 * _1794);
        float _1837 = RVar[5u].x;
        float _1839 = RVar[5u].y;
        float _1841 = RVar[5u].z;
        float _1843 = RVar[4u].w;
        vec4 _1846 = RVar[18u];
        RVar[127u].z = RVar[2u].z * dot(vec4(_1821, _1823, _1825, _1827), _1830);
        float _1853 = RVar[5u].x;
        float _1855 = RVar[5u].y;
        float _1857 = RVar[5u].z;
        float _1859 = RVar[4u].w;
        vec4 _1862 = RVar[19u];
        float _1871 = RVar[127u].w;
        float _1873 = RVar[127u].z;
        float _1876 = RVar[2u].z;
        float _1879 = RVar[4u].x;
        float _1881 = RVar[13u].x;
        float _1883 = RVar[126u].x;
        float _1887 = RVar[4u].y;
        float _1889 = RVar[17u].y;
        RVar[127u].x = RVar[125u].y + (RVar[2u].z * dot(vec4(_1837, _1839, _1841, _1843), _1846));
        RVar[125u].y = _1871 + _1873;
        RVar[125u].w = (_1879 * _1881) + _1883;
        RVar[13u].x = _1887 * _1889;
        float _1896 = RVar[5u].x;
        float _1898 = RVar[5u].y;
        float _1900 = RVar[5u].z;
        float _1902 = RVar[4u].w;
        vec4 _1905 = RVar[16u];
        RVar[124u].y = RVar[126u].w + (_1876 * dot(vec4(_1853, _1855, _1857, _1859), _1862));
        float _1912 = RVar[5u].x;
        float _1914 = RVar[5u].y;
        float _1916 = RVar[5u].z;
        float _1918 = RVar[4u].w;
        vec4 _1921 = RVar[20u];
        RVar[126u].x = RVar[2u].w * dot(vec4(_1896, _1898, _1900, _1902), _1905);
        float _1928 = RVar[5u].x;
        float _1930 = RVar[5u].y;
        float _1932 = RVar[5u].z;
        float _1934 = RVar[4u].w;
        vec4 _1937 = RVar[1u];
        float _1940 = RVar[2u].w;
        float _1948 = RVar[127u].x;
        float _1951 = RVar[2u].w;
        float _1954 = RVar[4u].z;
        float _1956 = RVar[18u].z;
        float _1959 = RVar[4u].y;
        float _1961 = RVar[14u].y;
        float _1963 = RVar[125u].x;
        float _1965 = (_1959 * _1961) + _1963;
        RVar[21u].x = RVar[125u].y + RVar[126u].x;
        RVar[21u].y = _1948 + (_1940 * dot(vec4(_1912, _1914, _1916, _1918), _1921));
        RVar[126u].w = _1954 * _1956;
        RVar[122u].x = _1965;
        float _1979 = RVar[4u].x;
        float _1981 = RVar[14u].x;
        float _1985 = RVar[124u].y;
        float _1988 = RVar[4u].z;
        float _1990 = RVar[16u].z;
        float _1993 = RVar[4u].z;
        float _1995 = RVar[19u].z;
        RVar[124u].x = (RVar[4u].y * RVar[9u].y) + RVar[124u].x;
        RVar[124u].y = (_1979 * _1981) + _1965;
        RVar[21u].z = _1985 + (_1951 * dot(vec4(_1928, _1930, _1932, _1934), _1937));
        RVar[127u].w = _1988 * _1990;
        float _2010 = RVar[4u].z;
        float _2012 = RVar[20u].z;
        float _2015 = RVar[4u].x;
        float _2017 = RVar[15u].x;
        float _2019 = RVar[12u].x;
        float _2023 = RVar[4u].z;
        float _2025 = RVar[1u].z;
        float _2028 = RVar[4u].y;
        float _2030 = RVar[19u].y;
        RVar[127u].x = (RVar[4u].y * RVar[18u].y) + RVar[126u].w;
        RVar[127u].z = (_2015 * _2017) + _2019;
        RVar[126u].w = _2023 * _2025;
        RVar[126u].x = (_2028 * _2030) + (_1993 * _1995);
        float _2038 = RVar[4u].y;
        float _2040 = RVar[16u].y;
        float _2042 = RVar[127u].w;
        float _2044 = (_2038 * _2040) + _2042;
        float _2046 = RVar[4u].x;
        float _2048 = RVar[9u].x;
        float _2050 = RVar[124u].x;
        float _2054 = RVar[4u].y;
        float _2056 = RVar[20u].y;
        RVar[123u].x = _2044;
        RVar[124u].z = (_2046 * _2048) + _2050;
        RVar[125u].x = (_2054 * _2056) + (_2010 * _2012);
        float _2070 = RVar[2u].x;
        float _2072 = RVar[125u].w;
        float _2077 = RVar[4u].x;
        float _2079 = RVar[16u].x;
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
        RVar[16u].x = (_2090 * _2092) + _2094;
        float _2103 = RVar[4u].x;
        float _2105 = RVar[4u].z;
        float _2107 = RVar[13u].x;
        float _2111 = RVar[17u].x;
        float _2113 = RVar[17u].z;
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
        float _2157 = RVar[18u].x;
        float _2159 = RVar[127u].x;
        float _2161 = (_2155 * _2157) + _2159;
        RVar[22u].x = (RVar[2u].w * RVar[126u].z) + _2128;
        RVar[123u].z = _2161;
        float _2165 = RVar[4u].x;
        float _2167 = RVar[19u].x;
        float _2169 = RVar[126u].x;
        float _2171 = (_2165 * _2167) + _2169;
        float _2173 = RVar[2u].z;
        float _2175 = RVar[126u].w;
        RVar[123u].x = _2171;
        RVar[124u].y = (_2173 * _2161) + _2175;
        float _2181 = RVar[4u].x;
        float _2183 = RVar[20u].x;
        float _2185 = RVar[125u].x;
        float _2187 = (_2181 * _2183) + _2185;
        float _2189 = RVar[2u].z;
        float _2191 = RVar[125u].y;
        RVar[123u].x = _2187;
        RVar[126u].w = (_2189 * _2171) + _2191;
        float _2197 = RVar[4u].x;
        float _2199 = RVar[1u].x;
        float _2201 = RVar[16u].x;
        float _2203 = (_2197 * _2199) + _2201;
        float _2205 = RVar[2u].w;
        float _2207 = RVar[124u].y;
        RVar[123u].x = _2203;
        RVar[22u].y = (_2205 * _2187) + _2207;
        RVar[22u].z = (RVar[2u].w * _2203) + RVar[126u].w;
    }
    if (stackVar[stackIdxVar - 1] == 0)
    {
        stateVar = int(stateVar == 0);
    }
    if (stateVar == 0)
    {
        RVar[21u].x = uintBitsToFloat(0u);
        RVar[21u].y = uintBitsToFloat(0u);
        RVar[21u].z = uintBitsToFloat(0u);
        RVar[21u].w = uintBitsToFloat(1065353216u);
        RVar[3u].x = uintBitsToFloat(0u);
        RVar[22u].x = uintBitsToFloat(0u);
        RVar[22u].y = uintBitsToFloat(0u);
        RVar[22u].z = uintBitsToFloat(0u);
        RVar[22u].w = uintBitsToFloat(0u);
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
            RVar[0u].z = intBitsToFloat((floatBitsToInt(CBUFFER_1.values[3].x) > floatBitsToInt(RVar[3u].x)) ? (-1) : 0);
            bool _2284 = floatBitsToInt(RVar[0u].z) != (0);
            predVar = _2284;
            stateVar = _2284 ? 0 : 1;
        }
        if (stateVar == 1)
        {
            stateVar = 2;
        }
        if (stateVar == 0)
        {
            float _2308 = RVar[3u].x;
            float _2311 = intBitsToFloat((-1) + floatBitsToInt(_2308));
            float _2315 = RVar[3u].x;
            float _2318 = intBitsToFloat((-2) + floatBitsToInt(_2315));
            float _2322 = RVar[3u].x;
            float _2325 = intBitsToFloat((-3) + floatBitsToInt(_2322));
            float _2327 = RVar[3u].x;
            float _2330 = RVar[2u].x;
            RVar[127u].x = intBitsToFloat((floatBitsToInt(RVar[3u].x) == int(0u)) ? floatBitsToInt(RVar[1u].x) : (0));
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
            float _2406 = RVar[3u].x;
            RVar[126u].z = intBitsToFloat((floatBitsToInt(RVar[0u].w) == int(0u)) ? floatBitsToInt(RVar[2u].w) : (0));
            RVar[3u].x = intBitsToFloat(floatBitsToInt(_2406) + (1));
            float _2414 = RVar[127u].w;
            float _2426 = RVar[127u].z;
            RVar[10u].x = RVar[126u].z + (RVar[126u].w + (_2387 + _2356));
            float _2435 = intBitsToFloat(floatBitsToInt(intBitsToFloat(floatBitsToInt(_2426) + floatBitsToInt(intBitsToFloat(floatBitsToInt(_2414) + floatBitsToInt(intBitsToFloat(floatBitsToInt(_2390) + floatBitsToInt(_2348))))))) * (3));
            RVar[0u].z = _2435;
            RVar[0u].y = intBitsToFloat(floatBitsToInt(_2435) + (2));
            RVar[0u].w = intBitsToFloat(floatBitsToInt(_2435) + (1));
        }
        if (stateVar == 0)
        {
            RVar[8u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].z)];
            RVar[9u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].w)];
            RVar[0u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].y)];
        }
        if (stateVar == 0)
        {
            float _2474 = RVar[5u].x;
            float _2476 = RVar[5u].y;
            float _2478 = RVar[5u].z;
            float _2480 = RVar[4u].w;
            vec4 _2483 = RVar[8u];
            RVar[127u].x = RVar[4u].z * RVar[8u].z;
            float _2492 = RVar[5u].x;
            float _2494 = RVar[5u].y;
            float _2496 = RVar[5u].z;
            float _2498 = RVar[4u].w;
            vec4 _2501 = RVar[9u];
            RVar[127u].y = RVar[10u].x * dot(vec4(_2474, _2476, _2478, _2480), _2483);
            float _2508 = RVar[5u].x;
            float _2510 = RVar[5u].y;
            float _2512 = RVar[5u].z;
            float _2514 = RVar[4u].w;
            vec4 _2517 = RVar[0u];
            float _2523 = RVar[10u].x;
            float _2529 = RVar[4u].z;
            float _2531 = RVar[9u].z;
            float _2534 = RVar[4u].z;
            float _2536 = RVar[0u].z;
            float _2539 = RVar[21u].x;
            float _2541 = RVar[127u].y;
            RVar[3u].y = RVar[21u].y + (RVar[10u].x * dot(vec4(_2492, _2494, _2496, _2498), _2501));
            RVar[11u].x = _2539 + _2541;
            float _2546 = RVar[4u].y;
            float _2548 = RVar[8u].y;
            float _2550 = RVar[127u].x;
            float _2552 = (_2546 * _2548) + _2550;
            float _2554 = RVar[4u].x;
            float _2556 = RVar[0u].x;
            float _2558 = (_2554 * _2556) + (_2534 * _2536);
            float _2560 = RVar[21u].z;
            float _2563 = RVar[4u].y;
            float _2565 = RVar[9u].y;
            float _2567 = (_2563 * _2565) + (_2529 * _2531);
            RVar[123u].x = _2552;
            RVar[123u].y = _2558;
            RVar[0u].z = _2560 + (_2523 * dot(vec4(_2508, _2510, _2512, _2514), _2517));
            RVar[122u].x = _2567;
            float _2573 = RVar[4u].y;
            float _2575 = RVar[0u].y;
            float _2577 = (_2573 * _2575) + _2558;
            float _2579 = RVar[4u].x;
            float _2581 = RVar[8u].x;
            float _2583 = (_2579 * _2581) + _2552;
            float _2585 = RVar[4u].x;
            float _2587 = RVar[9u].x;
            float _2589 = (_2585 * _2587) + _2567;
            RVar[123u].y = _2577;
            RVar[123u].z = _2583;
            RVar[123u].w = _2589;
            float _2600 = RVar[10u].x;
            float _2602 = RVar[22u].y;
            float _2606 = RVar[10u].x;
            float _2608 = RVar[22u].z;
            RVar[0u].x = (RVar[10u].x * _2583) + RVar[22u].x;
            RVar[0u].y = (_2600 * _2589) + _2602;
            RVar[3u].z = (_2606 * _2577) + _2608;
            float _2617 = RVar[22u].y;
            float _2619 = RVar[22u].z;
            float _2621 = RVar[22u].w;
            RVar[8u].x = RVar[22u].x;
            RVar[8u].y = _2617;
            RVar[8u].z = _2619;
            RVar[8u].w = _2621;
            float _2629 = RVar[0u].y;
            float _2631 = RVar[3u].z;
            float _2633 = RVar[22u].w;
            RVar[22u].x = RVar[0u].x;
            RVar[22u].y = _2629;
            RVar[22u].z = _2631;
            RVar[22u].w = _2633;
            float _2641 = RVar[21u].y;
            float _2643 = RVar[21u].z;
            float _2645 = RVar[21u].w;
            RVar[8u].x = RVar[21u].x;
            RVar[8u].y = _2641;
            RVar[8u].z = _2643;
            RVar[8u].w = _2645;
            float _2653 = RVar[3u].y;
            float _2655 = RVar[0u].z;
            float _2657 = RVar[21u].w;
            RVar[21u].x = RVar[11u].x;
            RVar[21u].y = _2653;
            RVar[21u].z = _2655;
            RVar[21u].w = _2657;
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
        RVar[0u].x = dot(RVar[21u], CBUFFER_3.values[3]);
        RVar[3u].z = uintBitsToFloat(1065353216u);
        RVar[0u].y = dot(RVar[21u], CBUFFER_3.values[4]);
        RVar[5u].z = uintBitsToFloat(1065353216u);
        float _2710 = RVar[22u].w;
        float _2712 = RVar[22u].w;
        RVar[0u].z = dot(RVar[21u], CBUFFER_3.values[5]);
        float _2722 = RVar[22u].z;
        float _2724 = RVar[22u].z;
        float _2726 = (_2722 * _2724) + (_2710 * _2712);
        RVar[0u].w = dot(RVar[21u], CBUFFER_3.values[6]);
        RVar[122u].x = _2726;
        float _2730 = RVar[22u].x;
        float _2732 = RVar[22u].y;
        float _2736 = RVar[22u].x;
        float _2738 = RVar[22u].y;
        RVar[4u].x = CBUFFER_3.values[26].x;
        vec4 _2748 = RVar[21u];
        float _2753 = inversesqrt(dot(vec4(_2730, _2732, _2726, uintBitsToFloat(0u)), vec4(_2736, _2738, uintBitsToFloat(1065353216u), uintBitsToFloat(0u))));
        float _2755 = RVar[22u].x;
        float _2756 = _2755 * _2753;
        float _2758 = RVar[22u].y;
        float _2759 = _2758 * _2753;
        float _2761 = RVar[22u].z;
        float _2762 = _2761 * _2753;
        float _2764 = RVar[22u].w;
        float _2765 = _2764 * _2753;
        RVar[127u].x = _2756;
        RVar[127u].y = _2759;
        RVar[127u].z = _2762;
        RVar[127u].w = _2765;
        RVar[3u].x = (-dot(_2748, CBUFFER_3.values[2])) + (-CBUFFER_3.values[34].x);
        RVar[1u].x = dot(vec4(_2756, _2759, _2762, _2765), CBUFFER_3.values[0]);
        RVar[8u].x = _2756;
        float _2789 = RVar[127u].y;
        RVar[1u].y = dot(RVar[127u], CBUFFER_3.values[1]);
        RVar[8u].y = _2789;
        vec4 _2793 = RVar[127u];
        float _2796 = dot(_2793, CBUFFER_3.values[2]);
        float _2798 = RVar[127u].z;
        RVar[1u].z = _2796;
        RVar[8u].z = _2798;
        float _2802 = RVar[1u].x;
        float _2804 = RVar[1u].y;
        RVar[4u].z = CBUFFER_3.values[26].z;
        RVar[4u].y = CBUFFER_3.values[26].y;
        float _2827 = RVar[1u].x;
        float _2829 = RVar[1u].y;
        float _2831 = RVar[1u].z;
        float _2845 = min(max(-dot(vec4(_2802, _2804, _2796, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[7].x, CBUFFER_3.values[7].y, CBUFFER_3.values[7].z, uintBitsToFloat(0u))), uintBitsToFloat(0u)), uintBitsToFloat(1065353216u));
        RVar[127u].x = (_2845 * CBUFFER_3.values[15].y) + uintBitsToFloat(0u);
        RVar[127u].y = (_2845 * CBUFFER_3.values[15].z) + uintBitsToFloat(0u);
        RVar[127u].w = (_2845 * CBUFFER_3.values[15].x) + uintBitsToFloat(0u);
        RVar[126u].x = (_2845 * CBUFFER_3.values[15].w) + uintBitsToFloat(0u);
        float _2875 = RVar[1u].x;
        float _2877 = RVar[1u].y;
        float _2879 = RVar[1u].z;
        float _2893 = min(max(-dot(vec4(_2827, _2829, _2831, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[8].x, CBUFFER_3.values[8].y, CBUFFER_3.values[8].z, uintBitsToFloat(0u))), uintBitsToFloat(0u)), uintBitsToFloat(1065353216u));
        float _2904 = RVar[127u].x;
        float _2910 = RVar[127u].y;
        float _2919 = RVar[126u].x;
        RVar[127u].x = (_2893 * CBUFFER_3.values[16].x) + RVar[127u].w;
        RVar[127u].y = (_2893 * CBUFFER_3.values[16].y) + _2904;
        RVar[127u].z = (_2893 * CBUFFER_3.values[16].z) + _2910;
        RVar[126u].y = (_2893 * CBUFFER_3.values[16].w) + _2919;
        float _2927 = RVar[1u].x;
        float _2929 = RVar[1u].y;
        float _2931 = RVar[1u].z;
        float _2945 = min(max(-dot(vec4(_2875, _2877, _2879, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[9].x, CBUFFER_3.values[9].y, CBUFFER_3.values[9].z, uintBitsToFloat(0u))), uintBitsToFloat(0u)), uintBitsToFloat(1065353216u));
        float _2959 = RVar[127u].y;
        float _2965 = RVar[127u].z;
        float _2971 = RVar[126u].y;
        RVar[127u].y = (_2945 * CBUFFER_3.values[17].x) + RVar[127u].x;
        RVar[127u].z = (_2945 * CBUFFER_3.values[17].y) + _2959;
        RVar[127u].w = (_2945 * CBUFFER_3.values[17].z) + _2965;
        RVar[126u].z = (_2945 * CBUFFER_3.values[17].w) + _2971;
        float _2979 = RVar[1u].x;
        float _2981 = RVar[1u].y;
        float _2983 = RVar[1u].z;
        float _2997 = min(max(-dot(vec4(_2927, _2929, _2931, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[10].x, CBUFFER_3.values[10].y, CBUFFER_3.values[10].z, uintBitsToFloat(0u))), uintBitsToFloat(0u)), uintBitsToFloat(1065353216u));
        float _3011 = RVar[127u].y;
        float _3017 = RVar[127u].w;
        float _3023 = RVar[126u].z;
        RVar[127u].x = (_2997 * CBUFFER_3.values[18].y) + RVar[127u].z;
        RVar[127u].z = (_2997 * CBUFFER_3.values[18].x) + _3011;
        RVar[127u].w = (_2997 * CBUFFER_3.values[18].z) + _3017;
        RVar[126u].w = (_2997 * CBUFFER_3.values[18].w) + _3023;
        float _3031 = RVar[1u].x;
        float _3033 = RVar[1u].y;
        float _3035 = RVar[1u].z;
        float _3049 = min(max(-dot(vec4(_2979, _2981, _2983, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[11].x, CBUFFER_3.values[11].y, CBUFFER_3.values[11].z, uintBitsToFloat(0u))), uintBitsToFloat(0u)), uintBitsToFloat(1065353216u));
        float _3060 = RVar[127u].w;
        float _3069 = RVar[127u].z;
        float _3075 = RVar[126u].w;
        RVar[127u].x = (_3049 * CBUFFER_3.values[19].y) + RVar[127u].x;
        RVar[127u].y = (_3049 * CBUFFER_3.values[19].z) + _3060;
        RVar[127u].w = (_3049 * CBUFFER_3.values[19].x) + _3069;
        RVar[126u].x = (_3049 * CBUFFER_3.values[19].w) + _3075;
        float _3083 = RVar[1u].x;
        float _3085 = RVar[1u].y;
        float _3087 = RVar[1u].z;
        float _3101 = min(max(-dot(vec4(_3031, _3033, _3035, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[12].x, CBUFFER_3.values[12].y, CBUFFER_3.values[12].z, uintBitsToFloat(0u))), uintBitsToFloat(0u)), uintBitsToFloat(1065353216u));
        float _3112 = RVar[127u].x;
        float _3118 = RVar[127u].y;
        float _3127 = RVar[126u].x;
        RVar[2u].x = (_3101 * CBUFFER_3.values[20].x) + RVar[127u].w;
        RVar[2u].y = (_3101 * CBUFFER_3.values[20].y) + _3112;
        RVar[2u].z = (_3101 * CBUFFER_3.values[20].z) + _3118;
        RVar[1u].w = max(-dot(vec4(_3083, _3085, _3087, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[13].x, CBUFFER_3.values[13].y, CBUFFER_3.values[13].z, uintBitsToFloat(0u))), uintBitsToFloat(0u));
        RVar[3u].y = (_3101 * CBUFFER_3.values[20].w) + _3127;
    }
    vec4 _3151 = (RVar[0u] * vec4(VS_PUSH.posMulAdd.xy, 1.0, 1.0)) + vec4(VS_PUSH.posMulAdd.zw, 0.0, 0.0);
    vec4 _3154 = _3151;
    _3154.y = -_3151.y;
    vec4 _3162 = _3154;
    _3162.z = (_3154.z + (_3154.w * VS_PUSH.zSpaceMul.x)) * VS_PUSH.zSpaceMul.y;
    gl_Position = _3162;
    PARAM_0 = RVar[8u];
    if (stateVar == 0)
    {
        float _3172 = RVar[1u].x;
        float _3174 = RVar[1u].y;
        float _3176 = RVar[1u].z;
        float _3190 = RVar[1u].w;
        float _3192 = min(_3190, uintBitsToFloat(1065353216u));
        float _3206 = RVar[2u].y;
        float _3212 = RVar[2u].z;
        float _3218 = RVar[3u].y;
        RVar[127u].y = (_3192 * CBUFFER_3.values[21].x) + RVar[2u].x;
        RVar[127u].z = (_3192 * CBUFFER_3.values[21].y) + _3206;
        RVar[127u].w = (_3192 * CBUFFER_3.values[21].z) + _3212;
        RVar[126u].z = (_3192 * CBUFFER_3.values[21].w) + _3218;
        float _3226 = min(max(-dot(vec4(_3172, _3174, _3176, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[14].x, CBUFFER_3.values[14].y, CBUFFER_3.values[14].z, uintBitsToFloat(0u))), uintBitsToFloat(0u)), uintBitsToFloat(1065353216u));
        RVar[4u].w = clamp(RVar[3u].x * CBUFFER_3.values[42].x, 0.0, 1.0);
        float _3246 = RVar[127u].z;
        float _3253 = RVar[127u].y;
        float _3260 = RVar[126u].z;
        RVar[3u].x = clamp((_3226 * CBUFFER_3.values[22].z) + RVar[127u].w, 0.0, 1.0);
        RVar[2u].y = clamp((_3226 * CBUFFER_3.values[22].y) + _3246, 0.0, 1.0);
        RVar[2u].z = clamp((_3226 * CBUFFER_3.values[22].x) + _3253, 0.0, 1.0);
        RVar[1u].w = clamp((_3226 * CBUFFER_3.values[22].w) + _3260, 0.0, 1.0);
    }
    PARAM_1 = RVar[4u];
    if (stateVar == 0)
    {
        float _3285 = RVar[2u].y;
        float _3288 = clamp((CBUFFER_4.values[2].y * CBUFFER_3.values[23].y) + _3285, 0.0, 1.0);
        float _3294 = RVar[2u].z;
        float _3297 = clamp((CBUFFER_4.values[2].x * CBUFFER_3.values[23].x) + _3294, 0.0, 1.0);
        RVar[123u].y = _3288;
        RVar[123u].z = _3297;
        float _3305 = RVar[1u].w;
        float _3315 = RVar[3u].x;
        float _3318 = clamp((CBUFFER_4.values[2].z * CBUFFER_3.values[23].z) + _3315, 0.0, 1.0);
        RVar[123u].w = _3318;
        float _3326 = RVar[3u].z;
        RVar[1u].y = max(_3288, uintBitsToFloat(1065353216u)) * CBUFFER_4.values[0].y;
        RVar[1u].x = max(_3297, uintBitsToFloat(1065353216u)) * CBUFFER_4.values[0].x;
        float _3338 = RVar[3u].z;
        float _3342 = (_3338 * CBUFFER_4.values[17].z) + (_3326 * CBUFFER_4.values[17].w);
        float _3347 = RVar[3u].w;
        RVar[123u].x = _3342;
        RVar[1u].z = max(_3318, uintBitsToFloat(1065353216u)) * CBUFFER_4.values[0].z;
        RVar[1u].w = _3347 * max(clamp(_3305 + CBUFFER_4.values[2].w, 0.0, 1.0), uintBitsToFloat(0u));
        float _3368 = RVar[3u].z;
        RVar[0u].x = dot(vec4(RVar[6u].x, RVar[6u].y, _3342, uintBitsToFloat(0u)), vec4(CBUFFER_4.values[17].x, CBUFFER_4.values[17].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[0u].y = dot(vec4(RVar[6u].x, RVar[6u].y, RVar[3u].z, _3368 * CBUFFER_4.values[18].w), vec4(CBUFFER_4.values[18].x, CBUFFER_4.values[18].y, CBUFFER_4.values[18].z, uintBitsToFloat(1065353216u)));
        RVar[2u].x = dot(vec4(RVar[6u].x, RVar[6u].y, RVar[3u].z, RVar[3u].z), CBUFFER_4.values[20]);
        RVar[2u].y = dot(vec4(RVar[6u].x, RVar[6u].y, RVar[3u].z, RVar[3u].z), CBUFFER_4.values[21]);
        RVar[3u].x = dot(vec4(RVar[7u].x, RVar[7u].y, RVar[5u].z, RVar[5u].z), CBUFFER_4.values[23]);
        RVar[3u].y = dot(vec4(RVar[7u].x, RVar[7u].y, RVar[5u].z, RVar[5u].z), CBUFFER_4.values[24]);
        RVar[4u].x = dot(vec4(RVar[6u].x, RVar[6u].y, RVar[3u].z, RVar[3u].z), CBUFFER_4.values[26]);
        RVar[4u].y = dot(vec4(RVar[6u].x, RVar[6u].y, RVar[3u].z, RVar[3u].z), CBUFFER_4.values[27]);
        RVar[5u].x = dot(vec4(RVar[6u].x, RVar[6u].y, RVar[3u].z, RVar[3u].z), CBUFFER_4.values[29]);
        RVar[5u].y = dot(vec4(RVar[6u].x, RVar[6u].y, RVar[3u].z, RVar[3u].z), CBUFFER_4.values[30]);
    }
    PARAM_2 = RVar[1u];
    PARAM_3 = vec4(RVar[0u].x, RVar[0u].y, RVar[0u].z, RVar[0u].z);
    PARAM_4 = vec4(RVar[2u].x, RVar[2u].y, RVar[2u].z, RVar[2u].z);
    PARAM_5 = vec4(RVar[3u].x, RVar[3u].y, RVar[3u].z, RVar[3u].z);
    PARAM_6 = vec4(RVar[4u].x, RVar[4u].y, RVar[4u].z, RVar[4u].z);
    PARAM_7 = vec4(RVar[5u].x, RVar[5u].y, RVar[5u].z, RVar[5u].z);
    if (stateVar == 0)
    {
        RVar[0u].x = dot(vec4(RVar[6u].x, RVar[6u].y, RVar[3u].z, RVar[3u].z), CBUFFER_4.values[32]);
        RVar[0u].y = dot(vec4(RVar[6u].x, RVar[6u].y, RVar[3u].z, RVar[3u].z), CBUFFER_4.values[33]);
    }
    PARAM_8 = vec4(RVar[0u].x, RVar[0u].y, RVar[0u].z, RVar[0u].z);
    if (stateVar == 0)
    {
    }
}

 