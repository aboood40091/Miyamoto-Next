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
layout(location = 0) in uvec4 aBlendIndex_0_0;
layout(location = 1) in uvec4 aBlendWeight_0_0;
layout(location = 2) in uvec3 aNormal_0_0;
layout(location = 3) in uvec3 aPosition_0_0;
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
        RVar[0u].x = intBitsToFloat((floatBitsToInt(CBUFFER_1.values[3].x) != (0)) ? (-1) : 0);
        RVar[3u].w = uintBitsToFloat(1065353216u);
        RVar[18u].w = uintBitsToFloat(1065353216u);
        RVar[19u].w = uintBitsToFloat(0u);
        bool _90 = floatBitsToInt(RVar[0u].x) == (0);
        predVar = _90;
        stateVar = _90 ? 0 : 1;
    }
    if (stateVar == 0)
    {
        float _117 = RVar[3u].z;
        RVar[18u].x = dot(vec4(RVar[4u].x, RVar[4u].y, RVar[4u].z, RVar[3u].w), CBUFFER_1.values[0]);
        RVar[127u].x = _117 * CBUFFER_1.values[0].z;
        RVar[18u].y = dot(vec4(RVar[4u].x, RVar[4u].y, RVar[4u].z, RVar[3u].w), CBUFFER_1.values[1]);
        RVar[18u].z = dot(vec4(RVar[4u].x, RVar[4u].y, RVar[4u].z, RVar[3u].w), CBUFFER_1.values[2]);
        float _168 = RVar[3u].z;
        RVar[19u].x = dot(vec4(RVar[3u].x, RVar[3u].y, RVar[127u].x, uintBitsToFloat(2147483648u)), vec4(CBUFFER_1.values[0].x, CBUFFER_1.values[0].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        float _188 = RVar[3u].z;
        RVar[19u].y = dot(vec4(RVar[3u].x, RVar[3u].y, _168 * CBUFFER_1.values[1].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_1.values[1].x, CBUFFER_1.values[1].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[19u].z = dot(vec4(RVar[3u].x, RVar[3u].y, _188 * CBUFFER_1.values[2].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_1.values[2].x, CBUFFER_1.values[2].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
    }
    if (stackVar[stackIdxVar - 1] == 0)
    {
        stateVar = int(stateVar == 0);
    }
    stackVar[stackIdxVar] = stateVar;
    stackIdxVar++;
    if (stateVar == 0)
    {
        RVar[0u].y = intBitsToFloat((floatBitsToInt(CBUFFER_1.values[3].x) != (1)) ? (-1) : 0);
        bool _238 = floatBitsToInt(RVar[0u].y) == (0);
        predVar = _238;
        stateVar = _238 ? 0 : 1;
    }
    if (stateVar == 0)
    {
        float _247 = RVar[1u].x;
        float _251 = intBitsToFloat(floatBitsToInt(_247) * (3));
        RVar[1u].y = _251;
        RVar[1u].x = intBitsToFloat(floatBitsToInt(_251) + (1));
        RVar[1u].w = intBitsToFloat(floatBitsToInt(_251) + (2));
    }
    if (stateVar == 0)
    {
        RVar[0u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].y)];
        RVar[2u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].x)];
        RVar[1u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].w)];
    }
    if (stateVar == 0)
    {
        float _305 = RVar[3u].z;
        float _307 = RVar[0u].z;
        RVar[18u].x = dot(vec4(RVar[4u].x, RVar[4u].y, RVar[4u].z, RVar[3u].w), RVar[0u]);
        RVar[127u].x = _305 * _307;
        RVar[18u].y = dot(vec4(RVar[4u].x, RVar[4u].y, RVar[4u].z, RVar[3u].w), RVar[2u]);
        RVar[18u].z = dot(vec4(RVar[4u].x, RVar[4u].y, RVar[4u].z, RVar[3u].w), RVar[1u]);
        float _354 = RVar[3u].z;
        float _356 = RVar[2u].z;
        RVar[19u].x = dot(vec4(RVar[3u].x, RVar[3u].y, RVar[127u].x, uintBitsToFloat(2147483648u)), vec4(RVar[0u].x, RVar[0u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        float _374 = RVar[3u].z;
        float _376 = RVar[1u].z;
        RVar[19u].y = dot(vec4(RVar[3u].x, RVar[3u].y, _354 * _356, uintBitsToFloat(2147483648u)), vec4(RVar[2u].x, RVar[2u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[19u].z = dot(vec4(RVar[3u].x, RVar[3u].y, _374 * _376, uintBitsToFloat(2147483648u)), vec4(RVar[1u].x, RVar[1u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
    }
    if (stackVar[stackIdxVar - 1] == 0)
    {
        stateVar = int(stateVar == 0);
    }
    stackVar[stackIdxVar] = stateVar;
    stackIdxVar++;
    if (stateVar == 0)
    {
        RVar[0u].y = intBitsToFloat((floatBitsToInt(CBUFFER_1.values[3].x) != (2)) ? (-1) : 0);
        bool _424 = floatBitsToInt(RVar[0u].y) == (0);
        predVar = _424;
        stateVar = _424 ? 0 : 1;
    }
    if (stateVar == 0)
    {
        float _433 = RVar[1u].x;
        float _437 = intBitsToFloat(floatBitsToInt(_433) * (3));
        RVar[0u].x = _437;
        float _448 = RVar[1u].y;
        float _452 = intBitsToFloat(floatBitsToInt(_448) * (3));
        RVar[1u].x = intBitsToFloat(floatBitsToInt(_437) + (1));
        RVar[1u].y = intBitsToFloat(floatBitsToInt(_437) + (2));
        RVar[1u].z = _452;
        RVar[5u].x = intBitsToFloat(floatBitsToInt(_452) + (2));
        RVar[1u].w = intBitsToFloat(floatBitsToInt(_452) + (1));
    }
    if (stateVar == 0)
    {
        RVar[0u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].x)];
        RVar[7u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].x)];
        RVar[6u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].y)];
        RVar[8u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].z)];
        RVar[1u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].w)];
        RVar[5u] = CBUFFER_2.values[floatBitsToUint(RVar[5u].x)];
    }
    if (stateVar == 0)
    {
        float _515 = RVar[4u].x;
        float _517 = RVar[4u].y;
        float _519 = RVar[4u].z;
        float _521 = RVar[3u].w;
        vec4 _524 = RVar[0u];
        RVar[127u].x = RVar[3u].z * RVar[0u].z;
        float _533 = RVar[4u].x;
        float _535 = RVar[4u].y;
        float _537 = RVar[4u].z;
        float _539 = RVar[3u].w;
        vec4 _542 = RVar[7u];
        RVar[127u].z = RVar[2u].x * dot(vec4(_515, _517, _519, _521), _524);
        float _549 = RVar[4u].x;
        float _551 = RVar[4u].y;
        float _553 = RVar[4u].z;
        float _555 = RVar[3u].w;
        vec4 _558 = RVar[6u];
        float _566 = RVar[127u].z;
        float _570 = RVar[2u].x;
        float _573 = RVar[3u].z;
        float _575 = RVar[7u].z;
        float _578 = RVar[3u].y;
        float _580 = RVar[0u].y;
        float _582 = RVar[127u].x;
        RVar[127u].x = (RVar[2u].x * dot(vec4(_533, _535, _537, _539), _542)) + uintBitsToFloat(0u);
        RVar[126u].y = _566 + uintBitsToFloat(0u);
        RVar[127u].w = _573 * _575;
        RVar[126u].x = (_578 * _580) + _582;
        RVar[127u].y = dot(vec4(RVar[4u].x, RVar[4u].y, RVar[4u].z, RVar[3u].w), RVar[8u]);
        RVar[124u].y = (_570 * dot(vec4(_549, _551, _553, _555), _558)) + uintBitsToFloat(0u);
        float _608 = RVar[4u].x;
        float _610 = RVar[4u].y;
        float _612 = RVar[4u].z;
        float _614 = RVar[3u].w;
        vec4 _617 = RVar[1u];
        RVar[124u].x = RVar[3u].z * RVar[1u].z;
        float _626 = RVar[4u].x;
        float _628 = RVar[4u].y;
        float _630 = RVar[4u].z;
        float _632 = RVar[3u].w;
        vec4 _635 = RVar[5u];
        RVar[125u].y = RVar[2u].y * dot(vec4(_608, _610, _612, _614), _617);
        float _643 = RVar[2u].y;
        float _645 = RVar[127u].y;
        float _648 = RVar[3u].z;
        float _650 = RVar[6u].z;
        float _653 = RVar[2u].y;
        float _661 = RVar[3u].x;
        float _663 = RVar[7u].x;
        float _665 = RVar[127u].w;
        RVar[127u].w = RVar[3u].z * RVar[8u].z;
        RVar[125u].x = (_661 * _663) + _665;
        float _674 = RVar[127u].x;
        float _676 = RVar[125u].y;
        float _679 = RVar[124u].y;
        float _682 = RVar[3u].z;
        float _684 = RVar[5u].z;
        float _687 = RVar[3u].x;
        float _689 = RVar[6u].x;
        float _691 = (_687 * _689) + (_648 * _650);
        RVar[18u].x = RVar[126u].y + (_643 * _645);
        RVar[18u].y = _674 + _676;
        RVar[18u].z = _679 + (_653 * dot(vec4(_626, _628, _630, _632), _635));
        RVar[126u].w = _682 * _684;
        RVar[122u].x = _691;
        float _699 = RVar[3u].x;
        float _701 = RVar[0u].x;
        float _703 = RVar[126u].x;
        float _705 = (_699 * _701) + _703;
        float _707 = RVar[3u].y;
        float _709 = RVar[6u].y;
        float _711 = (_707 * _709) + _691;
        float _713 = RVar[3u].y;
        float _715 = RVar[8u].y;
        float _717 = RVar[127u].w;
        RVar[123u].x = _705;
        RVar[123u].y = _711;
        RVar[126u].x = (_713 * _715) + _717;
        float _725 = RVar[3u].y;
        float _727 = RVar[1u].y;
        float _729 = RVar[124u].x;
        float _731 = (_725 * _727) + _729;
        float _733 = RVar[2u].x;
        float _738 = RVar[3u].y;
        float _740 = RVar[7u].y;
        float _742 = RVar[125u].x;
        float _746 = RVar[2u].x;
        RVar[123u].x = _731;
        RVar[126u].y = (_733 * _711) + uintBitsToFloat(0u);
        RVar[127u].z = (_738 * _740) + _742;
        RVar[127u].w = (_746 * _705) + uintBitsToFloat(0u);
        float _771 = RVar[3u].x;
        float _773 = RVar[1u].x;
        RVar[125u].x = dot(vec4(RVar[3u].x, RVar[3u].y, RVar[126u].w, uintBitsToFloat(2147483648u)), vec4(RVar[5u].x, RVar[5u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[126u].w = (_771 * _773) + _731;
        float _779 = RVar[3u].x;
        float _781 = RVar[8u].x;
        float _783 = RVar[126u].x;
        float _785 = (_779 * _781) + _783;
        RVar[123u].y = _785;
        float _794 = RVar[2u].x;
        float _796 = RVar[127u].z;
        float _799 = (_794 * _796) + uintBitsToFloat(0u);
        RVar[19u].x = (RVar[2u].y * _785) + RVar[127u].w;
        RVar[123u].y = _799;
        float _809 = RVar[2u].y;
        float _811 = RVar[125u].x;
        float _813 = RVar[126u].y;
        RVar[19u].y = (RVar[2u].y * RVar[126u].w) + _799;
        RVar[19u].z = (_809 * _811) + _813;
    }
    if (stackVar[stackIdxVar - 1] == 0)
    {
        stateVar = int(stateVar == 0);
    }
    stackVar[stackIdxVar] = stateVar;
    stackIdxVar++;
    if (stateVar == 0)
    {
        RVar[0u].x = intBitsToFloat((floatBitsToInt(CBUFFER_1.values[3].x) != (3)) ? (-1) : 0);
        bool _848 = floatBitsToInt(RVar[0u].x) == (0);
        predVar = _848;
        stateVar = _848 ? 0 : 1;
    }
    if (stateVar == 0)
    {
        float _857 = RVar[1u].x;
        float _861 = intBitsToFloat(floatBitsToInt(_857) * (3));
        RVar[0u].z = _861;
        float _872 = RVar[1u].y;
        float _876 = intBitsToFloat(floatBitsToInt(_872) * (3));
        RVar[0u].x = intBitsToFloat(floatBitsToInt(_861) + (2));
        RVar[5u].z = intBitsToFloat(floatBitsToInt(_861) + (1));
        RVar[5u].x = _876;
        float _889 = RVar[1u].z;
        float _893 = intBitsToFloat(floatBitsToInt(_889) * (3));
        RVar[1u].x = intBitsToFloat(floatBitsToInt(_876) + (1));
        RVar[1u].y = intBitsToFloat(floatBitsToInt(_876) + (2));
        RVar[1u].z = _893;
        RVar[6u].x = intBitsToFloat(floatBitsToInt(_893) + (2));
        RVar[1u].w = intBitsToFloat(floatBitsToInt(_893) + (1));
    }
    if (stateVar == 0)
    {
        RVar[7u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].z)];
        RVar[8u] = CBUFFER_2.values[floatBitsToUint(RVar[5u].z)];
        RVar[0u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].x)];
        RVar[9u] = CBUFFER_2.values[floatBitsToUint(RVar[5u].x)];
        RVar[10u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].x)];
        RVar[11u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].y)];
        RVar[12u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].z)];
        RVar[13u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].w)];
    }
    if (stateVar == 0)
    {
        float _969 = RVar[4u].x;
        float _971 = RVar[4u].y;
        float _973 = RVar[4u].z;
        float _975 = RVar[3u].w;
        vec4 _978 = RVar[7u];
        RVar[5u].x = RVar[3u].z * RVar[7u].z;
        float _999 = RVar[2u].x;
        RVar[1u].y = dot(vec4(RVar[4u].x, RVar[4u].y, RVar[4u].z, RVar[3u].w), RVar[8u]);
        RVar[1u].x = _999 * dot(vec4(_969, _971, _973, _975), _978);
    }
    if (stateVar == 0)
    {
        RVar[6u] = CBUFFER_2.values[floatBitsToUint(RVar[6u].x)];
    }
    if (stateVar == 0)
    {
        float _1018 = RVar[4u].x;
        float _1020 = RVar[4u].y;
        float _1022 = RVar[4u].z;
        float _1024 = RVar[3u].w;
        vec4 _1027 = RVar[0u];
        float _1035 = RVar[2u].x;
        float _1040 = RVar[3u].z;
        float _1042 = RVar[8u].z;
        float _1045 = RVar[1u].x;
        float _1049 = RVar[3u].y;
        float _1051 = RVar[7u].y;
        float _1053 = RVar[5u].x;
        RVar[127u].y = (RVar[2u].x * RVar[1u].y) + uintBitsToFloat(0u);
        RVar[126u].z = _1040 * _1042;
        RVar[127u].w = _1045 + uintBitsToFloat(0u);
        RVar[127u].x = (_1049 * _1051) + _1053;
        float _1061 = RVar[4u].x;
        float _1063 = RVar[4u].y;
        float _1065 = RVar[4u].z;
        float _1067 = RVar[3u].w;
        vec4 _1070 = RVar[9u];
        RVar[126u].w = (_1035 * dot(vec4(_1018, _1020, _1022, _1024), _1027)) + uintBitsToFloat(0u);
        float _1076 = RVar[4u].x;
        float _1078 = RVar[4u].y;
        float _1080 = RVar[4u].z;
        float _1082 = RVar[3u].w;
        vec4 _1085 = RVar[10u];
        RVar[127u].z = RVar[2u].y * dot(vec4(_1061, _1063, _1065, _1067), _1070);
        float _1092 = RVar[4u].x;
        float _1094 = RVar[4u].y;
        float _1096 = RVar[4u].z;
        float _1098 = RVar[3u].w;
        vec4 _1101 = RVar[11u];
        float _1110 = RVar[127u].w;
        float _1112 = RVar[127u].z;
        float _1115 = RVar[2u].y;
        float _1118 = RVar[3u].x;
        float _1120 = RVar[0u].x;
        float _1123 = RVar[3u].x;
        float _1125 = RVar[8u].x;
        float _1127 = RVar[126u].z;
        RVar[126u].x = RVar[127u].y + (RVar[2u].y * dot(vec4(_1076, _1078, _1080, _1082), _1085));
        RVar[127u].y = _1110 + _1112;
        RVar[127u].w = _1118 * _1120;
        RVar[125u].x = (_1123 * _1125) + _1127;
        float _1135 = RVar[4u].x;
        float _1137 = RVar[4u].y;
        float _1139 = RVar[4u].z;
        float _1141 = RVar[3u].w;
        vec4 _1144 = RVar[12u];
        RVar[126u].y = RVar[126u].w + (_1115 * dot(vec4(_1092, _1094, _1096, _1098), _1101));
        float _1163 = RVar[2u].z;
        RVar[127u].z = dot(vec4(RVar[4u].x, RVar[4u].y, RVar[4u].z, RVar[3u].w), RVar[13u]);
        float _1167 = RVar[4u].x;
        float _1169 = RVar[4u].y;
        float _1171 = RVar[4u].z;
        float _1173 = RVar[3u].w;
        vec4 _1176 = RVar[6u];
        RVar[18u].x = RVar[127u].y + (_1163 * dot(vec4(_1135, _1137, _1139, _1141), _1144));
        float _1183 = RVar[3u].y;
        float _1185 = RVar[0u].y;
        float _1187 = RVar[127u].w;
        float _1189 = (_1183 * _1185) + _1187;
        float _1191 = RVar[2u].z;
        float _1193 = RVar[127u].z;
        float _1196 = RVar[2u].z;
        float _1199 = RVar[3u].x;
        float _1201 = RVar[7u].x;
        float _1203 = RVar[127u].x;
        float _1207 = RVar[3u].y;
        float _1209 = RVar[9u].y;
        RVar[123u].x = _1189;
        RVar[127u].w = (_1199 * _1201) + _1203;
        float _1214 = RVar[3u].y;
        float _1216 = RVar[8u].y;
        float _1218 = RVar[125u].x;
        float _1220 = (_1214 * _1216) + _1218;
        float _1222 = RVar[126u].x;
        float _1225 = RVar[126u].y;
        float _1228 = RVar[3u].z;
        float _1230 = RVar[0u].z;
        float _1232 = (_1228 * _1230) + _1189;
        float _1234 = RVar[3u].z;
        float _1236 = RVar[9u].z;
        float _1238 = (_1234 * _1236) + (_1207 * _1209);
        RVar[123u].x = _1220;
        RVar[18u].y = _1222 + (_1191 * _1193);
        RVar[18u].z = _1225 + (_1196 * dot(vec4(_1167, _1169, _1171, _1173), _1176));
        RVar[123u].w = _1232;
        RVar[122u].x = _1238;
        float _1245 = RVar[3u].x;
        float _1247 = RVar[9u].x;
        float _1249 = (_1245 * _1247) + _1238;
        float _1251 = RVar[2u].x;
        float _1253 = RVar[127u].w;
        float _1256 = (_1251 * _1253) + uintBitsToFloat(0u);
        float _1258 = RVar[2u].x;
        float _1263 = RVar[2u].x;
        float _1268 = RVar[3u].z;
        float _1270 = RVar[10u].z;
        RVar[123u].x = _1249;
        RVar[123u].y = _1256;
        RVar[127u].z = (_1258 * _1232) + uintBitsToFloat(0u);
        RVar[127u].w = (_1263 * _1220) + uintBitsToFloat(0u);
        float _1277 = RVar[3u].x;
        float _1279 = RVar[3u].y;
        float _1283 = RVar[10u].x;
        float _1285 = RVar[10u].y;
        RVar[126u].w = (RVar[2u].y * _1249) + _1256;
        float _1296 = RVar[3u].x;
        float _1298 = RVar[3u].y;
        float _1300 = RVar[3u].z;
        float _1304 = RVar[11u].x;
        float _1306 = RVar[11u].y;
        float _1308 = RVar[11u].z;
        RVar[125u].y = (RVar[2u].y * dot(vec4(_1277, _1279, _1268 * _1270, uintBitsToFloat(2147483648u)), vec4(_1283, _1285, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)))) + RVar[127u].w;
        float _1320 = RVar[3u].z;
        float _1322 = RVar[12u].z;
        float _1330 = RVar[2u].y;
        float _1332 = RVar[127u].z;
        float _1336 = RVar[3u].y;
        float _1338 = RVar[13u].y;
        RVar[126u].y = RVar[3u].x * RVar[6u].x;
        RVar[127u].w = (_1330 * dot(vec4(_1296, _1298, _1300, uintBitsToFloat(2147483648u)), vec4(_1304, _1306, _1308, uintBitsToFloat(0u)))) + _1332;
        float _1357 = RVar[3u].z;
        float _1359 = RVar[13u].z;
        float _1361 = (_1357 * _1359) + (_1336 * _1338);
        RVar[127u].y = dot(vec4(RVar[3u].x, RVar[3u].y, _1320 * _1322, uintBitsToFloat(2147483648u)), vec4(RVar[12u].x, RVar[12u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[122u].x = _1361;
        float _1365 = RVar[3u].y;
        float _1367 = RVar[6u].y;
        float _1369 = RVar[126u].y;
        float _1371 = (_1365 * _1367) + _1369;
        float _1373 = RVar[3u].x;
        float _1375 = RVar[13u].x;
        float _1377 = (_1373 * _1375) + _1361;
        RVar[123u].x = _1371;
        RVar[123u].w = _1377;
        float _1381 = RVar[3u].z;
        float _1383 = RVar[6u].z;
        float _1385 = (_1381 * _1383) + _1371;
        float _1387 = RVar[2u].z;
        float _1389 = RVar[125u].y;
        float _1393 = RVar[2u].z;
        float _1395 = RVar[127u].y;
        float _1397 = RVar[126u].w;
        RVar[123u].x = _1385;
        RVar[19u].y = (_1387 * _1377) + _1389;
        RVar[19u].x = (_1393 * _1395) + _1397;
        RVar[19u].z = (RVar[2u].z * _1385) + RVar[127u].w;
    }
    if (stackVar[stackIdxVar - 1] == 0)
    {
        stateVar = int(stateVar == 0);
    }
    stackVar[stackIdxVar] = stateVar;
    stackIdxVar++;
    if (stateVar == 0)
    {
        RVar[0u].y = intBitsToFloat((floatBitsToInt(CBUFFER_1.values[3].x) != (4)) ? (-1) : 0);
        bool _1441 = floatBitsToInt(RVar[0u].y) == (0);
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
        RVar[5u].x = intBitsToFloat(floatBitsToInt(_1454) + (1));
        RVar[0u].y = intBitsToFloat(floatBitsToInt(_1454) + (2));
        RVar[0u].z = _1469;
        float _1482 = RVar[1u].z;
        float _1486 = intBitsToFloat(floatBitsToInt(_1482) * (3));
        RVar[6u].x = intBitsToFloat(floatBitsToInt(_1469) + (2));
        RVar[5u].z = intBitsToFloat(floatBitsToInt(_1469) + (1));
        RVar[7u].x = _1486;
        float _1499 = RVar[1u].w;
        RVar[1u].x = intBitsToFloat(floatBitsToInt(_1486) + (1));
        RVar[1u].y = intBitsToFloat(floatBitsToInt(_1486) + (2));
        RVar[1u].z = intBitsToFloat(floatBitsToInt(_1499) * (3));
    }
    if (stateVar == 0)
    {
        RVar[8u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].x)];
        RVar[10u] = CBUFFER_2.values[floatBitsToUint(RVar[5u].x)];
        RVar[9u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].y)];
        RVar[12u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].z)];
        RVar[11u] = CBUFFER_2.values[floatBitsToUint(RVar[5u].z)];
        RVar[6u] = CBUFFER_2.values[floatBitsToUint(RVar[6u].x)];
        RVar[14u] = CBUFFER_2.values[floatBitsToUint(RVar[7u].x)];
        RVar[15u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].x)];
    }
    if (stateVar == 0)
    {
        float _1572 = RVar[3u].y;
        float _1574 = RVar[10u].y;
        float _1577 = RVar[3u].y;
        float _1579 = RVar[9u].y;
        float _1582 = RVar[1u].z;
        float _1588 = RVar[3u].z;
        float _1590 = RVar[8u].z;
        RVar[1u].x = intBitsToFloat(floatBitsToInt(RVar[1u].z) + (2));
        RVar[0u].y = _1572 * _1574;
        RVar[5u].z = _1577 * _1579;
        RVar[1u].w = intBitsToFloat(floatBitsToInt(_1582) + (1));
        float _1609 = RVar[3u].y;
        float _1611 = RVar[8u].y;
        RVar[0u].w = dot(vec4(RVar[4u].x, RVar[4u].y, RVar[4u].z, RVar[3u].w), RVar[8u]);
        RVar[7u].x = (_1609 * _1611) + (_1588 * _1590);
    }
    if (stateVar == 0)
    {
        RVar[16u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].y)];
        RVar[13u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].z)];
        RVar[17u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].w)];
        RVar[1u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].x)];
    }
    if (stateVar == 0)
    {
        float _1650 = RVar[4u].x;
        float _1652 = RVar[4u].y;
        float _1654 = RVar[4u].z;
        float _1656 = RVar[3u].w;
        vec4 _1659 = RVar[10u];
        RVar[127u].z = RVar[2u].x * RVar[0u].w;
        float _1668 = RVar[4u].x;
        float _1670 = RVar[4u].y;
        float _1672 = RVar[4u].z;
        float _1674 = RVar[3u].w;
        vec4 _1677 = RVar[9u];
        float _1685 = RVar[127u].z;
        float _1689 = RVar[2u].x;
        float _1692 = RVar[3u].y;
        float _1694 = RVar[12u].y;
        float _1697 = RVar[3u].z;
        float _1699 = RVar[10u].z;
        float _1701 = RVar[0u].y;
        RVar[127u].x = (RVar[2u].x * dot(vec4(_1650, _1652, _1654, _1656), _1659)) + uintBitsToFloat(0u);
        RVar[124u].y = _1685 + uintBitsToFloat(0u);
        RVar[127u].w = _1692 * _1694;
        RVar[126u].x = (_1697 * _1699) + _1701;
        RVar[127u].y = dot(vec4(RVar[4u].x, RVar[4u].y, RVar[4u].z, RVar[3u].w), RVar[12u]);
        RVar[0u].y = (_1689 * dot(vec4(_1668, _1670, _1672, _1674), _1677)) + uintBitsToFloat(0u);
        float _1737 = RVar[3u].z;
        float _1739 = RVar[11u].z;
        RVar[126u].y = dot(vec4(RVar[4u].x, RVar[4u].y, RVar[4u].z, RVar[3u].w), RVar[11u]);
        RVar[125u].x = _1737 * _1739;
        float _1756 = RVar[3u].z;
        float _1758 = RVar[6u].z;
        RVar[125u].y = dot(vec4(RVar[4u].x, RVar[4u].y, RVar[4u].z, RVar[3u].w), RVar[6u]);
        RVar[124u].x = _1756 * _1758;
        float _1763 = RVar[2u].y;
        float _1765 = RVar[127u].y;
        float _1768 = RVar[2u].y;
        float _1770 = RVar[126u].y;
        float _1781 = RVar[3u].z;
        float _1783 = RVar[9u].z;
        float _1785 = RVar[5u].z;
        float _1787 = (_1781 * _1783) + _1785;
        RVar[126u].z = (RVar[3u].x * RVar[8u].x) + RVar[7u].x;
        RVar[122u].x = _1787;
        float _1791 = RVar[2u].y;
        float _1793 = RVar[125u].y;
        float _1799 = RVar[3u].x;
        float _1801 = RVar[9u].x;
        float _1805 = RVar[124u].y;
        float _1808 = RVar[3u].z;
        float _1810 = RVar[12u].z;
        float _1812 = RVar[127u].w;
        RVar[125u].y = RVar[127u].x + (_1768 * _1770);
        RVar[125u].z = (_1799 * _1801) + _1787;
        RVar[127u].w = _1805 + (_1763 * _1765);
        RVar[9u].x = (_1808 * _1810) + _1812;
        float _1820 = RVar[4u].x;
        float _1822 = RVar[4u].y;
        float _1824 = RVar[4u].z;
        float _1826 = RVar[3u].w;
        vec4 _1829 = RVar[14u];
        RVar[126u].w = RVar[0u].y + (_1791 * _1793);
        float _1836 = RVar[4u].x;
        float _1838 = RVar[4u].y;
        float _1840 = RVar[4u].z;
        float _1842 = RVar[3u].w;
        vec4 _1845 = RVar[15u];
        RVar[127u].z = RVar[2u].z * dot(vec4(_1820, _1822, _1824, _1826), _1829);
        float _1852 = RVar[4u].x;
        float _1854 = RVar[4u].y;
        float _1856 = RVar[4u].z;
        float _1858 = RVar[3u].w;
        vec4 _1861 = RVar[16u];
        float _1870 = RVar[127u].w;
        float _1872 = RVar[127u].z;
        float _1875 = RVar[2u].z;
        float _1878 = RVar[3u].x;
        float _1880 = RVar[10u].x;
        float _1882 = RVar[126u].x;
        float _1886 = RVar[3u].y;
        float _1888 = RVar[14u].y;
        RVar[127u].x = RVar[125u].y + (RVar[2u].z * dot(vec4(_1836, _1838, _1840, _1842), _1845));
        RVar[125u].y = _1870 + _1872;
        RVar[125u].w = (_1878 * _1880) + _1882;
        RVar[10u].x = _1886 * _1888;
        float _1895 = RVar[4u].x;
        float _1897 = RVar[4u].y;
        float _1899 = RVar[4u].z;
        float _1901 = RVar[3u].w;
        vec4 _1904 = RVar[13u];
        RVar[124u].y = RVar[126u].w + (_1875 * dot(vec4(_1852, _1854, _1856, _1858), _1861));
        float _1911 = RVar[4u].x;
        float _1913 = RVar[4u].y;
        float _1915 = RVar[4u].z;
        float _1917 = RVar[3u].w;
        vec4 _1920 = RVar[17u];
        RVar[126u].x = RVar[2u].w * dot(vec4(_1895, _1897, _1899, _1901), _1904);
        float _1927 = RVar[4u].x;
        float _1929 = RVar[4u].y;
        float _1931 = RVar[4u].z;
        float _1933 = RVar[3u].w;
        vec4 _1936 = RVar[1u];
        float _1939 = RVar[2u].w;
        float _1947 = RVar[127u].x;
        float _1950 = RVar[2u].w;
        float _1953 = RVar[3u].z;
        float _1955 = RVar[15u].z;
        float _1958 = RVar[3u].y;
        float _1960 = RVar[11u].y;
        float _1962 = RVar[125u].x;
        float _1964 = (_1958 * _1960) + _1962;
        RVar[18u].x = RVar[125u].y + RVar[126u].x;
        RVar[18u].y = _1947 + (_1939 * dot(vec4(_1911, _1913, _1915, _1917), _1920));
        RVar[126u].w = _1953 * _1955;
        RVar[122u].x = _1964;
        float _1978 = RVar[3u].x;
        float _1980 = RVar[11u].x;
        float _1984 = RVar[124u].y;
        float _1987 = RVar[3u].z;
        float _1989 = RVar[13u].z;
        float _1992 = RVar[3u].z;
        float _1994 = RVar[16u].z;
        RVar[124u].x = (RVar[3u].y * RVar[6u].y) + RVar[124u].x;
        RVar[124u].y = (_1978 * _1980) + _1964;
        RVar[18u].z = _1984 + (_1950 * dot(vec4(_1927, _1929, _1931, _1933), _1936));
        RVar[127u].w = _1987 * _1989;
        float _2009 = RVar[3u].z;
        float _2011 = RVar[17u].z;
        float _2014 = RVar[3u].x;
        float _2016 = RVar[12u].x;
        float _2018 = RVar[9u].x;
        float _2022 = RVar[3u].z;
        float _2024 = RVar[1u].z;
        float _2027 = RVar[3u].y;
        float _2029 = RVar[16u].y;
        RVar[127u].x = (RVar[3u].y * RVar[15u].y) + RVar[126u].w;
        RVar[127u].z = (_2014 * _2016) + _2018;
        RVar[126u].w = _2022 * _2024;
        RVar[126u].x = (_2027 * _2029) + (_1992 * _1994);
        float _2037 = RVar[3u].y;
        float _2039 = RVar[13u].y;
        float _2041 = RVar[127u].w;
        float _2043 = (_2037 * _2039) + _2041;
        float _2045 = RVar[3u].x;
        float _2047 = RVar[6u].x;
        float _2049 = RVar[124u].x;
        float _2053 = RVar[3u].y;
        float _2055 = RVar[17u].y;
        RVar[123u].x = _2043;
        RVar[124u].z = (_2045 * _2047) + _2049;
        RVar[125u].x = (_2053 * _2055) + (_2009 * _2011);
        float _2069 = RVar[2u].x;
        float _2071 = RVar[125u].w;
        float _2076 = RVar[3u].x;
        float _2078 = RVar[13u].x;
        float _2082 = RVar[2u].x;
        float _2084 = RVar[126u].z;
        float _2087 = (_2082 * _2084) + uintBitsToFloat(0u);
        float _2089 = RVar[3u].y;
        float _2091 = RVar[1u].y;
        float _2093 = RVar[126u].w;
        RVar[124u].x = (RVar[2u].x * RVar[125u].z) + uintBitsToFloat(0u);
        RVar[125u].y = (_2069 * _2071) + uintBitsToFloat(0u);
        RVar[126u].z = (_2076 * _2078) + _2043;
        RVar[123u].w = _2087;
        RVar[13u].x = (_2089 * _2091) + _2093;
        float _2102 = RVar[3u].x;
        float _2104 = RVar[3u].z;
        float _2106 = RVar[10u].x;
        float _2110 = RVar[14u].x;
        float _2112 = RVar[14u].z;
        float _2118 = RVar[2u].y;
        float _2120 = RVar[127u].z;
        float _2122 = (_2118 * _2120) + _2087;
        RVar[122u].x = _2122;
        float _2125 = RVar[2u].z;
        float _2127 = (_2125 * dot(vec4(_2102, _2104, _2106, uintBitsToFloat(2147483648u)), vec4(_2110, _2112, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)))) + _2122;
        float _2129 = RVar[2u].y;
        float _2131 = RVar[124u].z;
        float _2133 = RVar[124u].x;
        float _2137 = RVar[2u].y;
        float _2139 = RVar[124u].y;
        float _2141 = RVar[125u].y;
        RVar[123u].x = _2127;
        RVar[125u].y = (_2129 * _2131) + _2133;
        RVar[126u].w = (_2137 * _2139) + _2141;
        float _2154 = RVar[3u].x;
        float _2156 = RVar[15u].x;
        float _2158 = RVar[127u].x;
        float _2160 = (_2154 * _2156) + _2158;
        RVar[19u].x = (RVar[2u].w * RVar[126u].z) + _2127;
        RVar[123u].z = _2160;
        float _2164 = RVar[3u].x;
        float _2166 = RVar[16u].x;
        float _2168 = RVar[126u].x;
        float _2170 = (_2164 * _2166) + _2168;
        float _2172 = RVar[2u].z;
        float _2174 = RVar[126u].w;
        RVar[123u].x = _2170;
        RVar[124u].y = (_2172 * _2160) + _2174;
        float _2180 = RVar[3u].x;
        float _2182 = RVar[17u].x;
        float _2184 = RVar[125u].x;
        float _2186 = (_2180 * _2182) + _2184;
        float _2188 = RVar[2u].z;
        float _2190 = RVar[125u].y;
        RVar[123u].x = _2186;
        RVar[126u].w = (_2188 * _2170) + _2190;
        float _2196 = RVar[3u].x;
        float _2198 = RVar[1u].x;
        float _2200 = RVar[13u].x;
        float _2202 = (_2196 * _2198) + _2200;
        float _2204 = RVar[2u].w;
        float _2206 = RVar[124u].y;
        RVar[123u].x = _2202;
        RVar[19u].y = (_2204 * _2186) + _2206;
        RVar[19u].z = (RVar[2u].w * _2202) + RVar[126u].w;
    }
    if (stackVar[stackIdxVar - 1] == 0)
    {
        stateVar = int(stateVar == 0);
    }
    if (stateVar == 0)
    {
        RVar[18u].x = uintBitsToFloat(0u);
        RVar[18u].y = uintBitsToFloat(0u);
        RVar[18u].z = uintBitsToFloat(0u);
        RVar[18u].w = uintBitsToFloat(1065353216u);
        RVar[8u].x = uintBitsToFloat(0u);
        RVar[19u].x = uintBitsToFloat(0u);
        RVar[19u].y = uintBitsToFloat(0u);
        RVar[19u].z = uintBitsToFloat(0u);
        RVar[19u].w = uintBitsToFloat(0u);
    }
    stackVar[stackIdxVar] = stateVar;
    stackIdxVar++;
    do
    {
        int _2258 = stateVar;
        if (_2258 == 3)
        {
            stateVar = 0;
        }
        if (_2258 == 1)
        {
            stateVar = 2;
        }
        if (stateVar == 0)
        {
            RVar[0u].y = intBitsToFloat((floatBitsToInt(CBUFFER_1.values[3].x) > floatBitsToInt(RVar[8u].x)) ? (-1) : 0);
            bool _2283 = floatBitsToInt(RVar[0u].y) != (0);
            predVar = _2283;
            stateVar = _2283 ? 0 : 1;
        }
        if (stateVar == 1)
        {
            stateVar = 2;
        }
        if (stateVar == 0)
        {
            float _2307 = RVar[8u].x;
            float _2310 = intBitsToFloat((-1) + floatBitsToInt(_2307));
            float _2314 = RVar[8u].x;
            float _2317 = intBitsToFloat((-2) + floatBitsToInt(_2314));
            float _2321 = RVar[8u].x;
            float _2324 = intBitsToFloat((-3) + floatBitsToInt(_2321));
            float _2326 = RVar[8u].x;
            float _2329 = RVar[2u].x;
            RVar[127u].x = intBitsToFloat((floatBitsToInt(RVar[8u].x) == int(0u)) ? floatBitsToInt(RVar[1u].x) : (0));
            RVar[0u].y = _2310;
            RVar[0u].z = _2317;
            RVar[0u].w = _2324;
            RVar[127u].y = intBitsToFloat((floatBitsToInt(_2326) == int(0u)) ? floatBitsToInt(_2329) : (0));
            float _2342 = RVar[1u].y;
            float _2347 = intBitsToFloat((floatBitsToInt(_2310) == int(0u)) ? floatBitsToInt(_2342) : (0));
            float _2350 = RVar[2u].y;
            float _2355 = intBitsToFloat((floatBitsToInt(_2310) == int(0u)) ? floatBitsToInt(_2350) : (0));
            float _2358 = RVar[1u].w;
            float _2366 = RVar[1u].z;
            float _2374 = RVar[2u].z;
            RVar[123u].x = _2347;
            RVar[123u].y = _2355;
            RVar[127u].z = intBitsToFloat((floatBitsToInt(_2324) == int(0u)) ? floatBitsToInt(_2358) : (0));
            RVar[127u].w = intBitsToFloat((floatBitsToInt(_2317) == int(0u)) ? floatBitsToInt(_2366) : (0));
            RVar[126u].w = intBitsToFloat((floatBitsToInt(_2317) == int(0u)) ? floatBitsToInt(_2374) : (0));
            float _2386 = RVar[127u].y;
            float _2389 = RVar[127u].x;
            float _2405 = RVar[8u].x;
            RVar[126u].z = intBitsToFloat((floatBitsToInt(RVar[0u].w) == int(0u)) ? floatBitsToInt(RVar[2u].w) : (0));
            RVar[8u].x = intBitsToFloat(floatBitsToInt(_2405) + (1));
            float _2413 = RVar[127u].w;
            float _2425 = RVar[127u].z;
            RVar[7u].x = RVar[126u].z + (RVar[126u].w + (_2386 + _2355));
            float _2434 = intBitsToFloat(floatBitsToInt(intBitsToFloat(floatBitsToInt(_2425) + floatBitsToInt(intBitsToFloat(floatBitsToInt(_2413) + floatBitsToInt(intBitsToFloat(floatBitsToInt(_2389) + floatBitsToInt(_2347))))))) * (3));
            RVar[0u].z = _2434;
            RVar[0u].y = intBitsToFloat(floatBitsToInt(_2434) + (2));
            RVar[0u].w = intBitsToFloat(floatBitsToInt(_2434) + (1));
        }
        if (stateVar == 0)
        {
            RVar[5u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].z)];
            RVar[6u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].w)];
            RVar[0u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].y)];
        }
        if (stateVar == 0)
        {
            float _2473 = RVar[4u].x;
            float _2475 = RVar[4u].y;
            float _2477 = RVar[4u].z;
            float _2479 = RVar[3u].w;
            vec4 _2482 = RVar[5u];
            RVar[127u].x = RVar[3u].z * RVar[5u].z;
            float _2491 = RVar[4u].x;
            float _2493 = RVar[4u].y;
            float _2495 = RVar[4u].z;
            float _2497 = RVar[3u].w;
            vec4 _2500 = RVar[6u];
            RVar[127u].y = RVar[7u].x * dot(vec4(_2473, _2475, _2477, _2479), _2482);
            float _2507 = RVar[4u].x;
            float _2509 = RVar[4u].y;
            float _2511 = RVar[4u].z;
            float _2513 = RVar[3u].w;
            vec4 _2516 = RVar[0u];
            float _2522 = RVar[7u].x;
            float _2528 = RVar[3u].z;
            float _2530 = RVar[6u].z;
            float _2533 = RVar[3u].z;
            float _2535 = RVar[0u].z;
            float _2538 = RVar[18u].x;
            float _2540 = RVar[127u].y;
            RVar[7u].y = RVar[18u].y + (RVar[7u].x * dot(vec4(_2491, _2493, _2495, _2497), _2500));
            RVar[9u].x = _2538 + _2540;
            float _2545 = RVar[3u].y;
            float _2547 = RVar[5u].y;
            float _2549 = RVar[127u].x;
            float _2551 = (_2545 * _2547) + _2549;
            float _2553 = RVar[3u].x;
            float _2555 = RVar[0u].x;
            float _2557 = (_2553 * _2555) + (_2533 * _2535);
            float _2559 = RVar[18u].z;
            float _2562 = RVar[3u].y;
            float _2564 = RVar[6u].y;
            float _2566 = (_2562 * _2564) + (_2528 * _2530);
            RVar[123u].x = _2551;
            RVar[123u].y = _2557;
            RVar[0u].z = _2559 + (_2522 * dot(vec4(_2507, _2509, _2511, _2513), _2516));
            RVar[122u].x = _2566;
            float _2572 = RVar[3u].y;
            float _2574 = RVar[0u].y;
            float _2576 = (_2572 * _2574) + _2557;
            float _2578 = RVar[3u].x;
            float _2580 = RVar[5u].x;
            float _2582 = (_2578 * _2580) + _2551;
            float _2584 = RVar[3u].x;
            float _2586 = RVar[6u].x;
            float _2588 = (_2584 * _2586) + _2566;
            RVar[123u].y = _2576;
            RVar[123u].z = _2582;
            RVar[123u].w = _2588;
            float _2599 = RVar[7u].x;
            float _2601 = RVar[19u].y;
            float _2605 = RVar[7u].x;
            float _2607 = RVar[19u].z;
            RVar[0u].x = (RVar[7u].x * _2582) + RVar[19u].x;
            RVar[0u].y = (_2599 * _2588) + _2601;
            RVar[5u].z = (_2605 * _2576) + _2607;
            float _2616 = RVar[19u].y;
            float _2618 = RVar[19u].z;
            float _2620 = RVar[19u].w;
            RVar[6u].x = RVar[19u].x;
            RVar[6u].y = _2616;
            RVar[6u].z = _2618;
            RVar[6u].w = _2620;
            float _2628 = RVar[0u].y;
            float _2630 = RVar[5u].z;
            float _2632 = RVar[19u].w;
            RVar[19u].x = RVar[0u].x;
            RVar[19u].y = _2628;
            RVar[19u].z = _2630;
            RVar[19u].w = _2632;
            float _2640 = RVar[18u].y;
            float _2642 = RVar[18u].z;
            float _2644 = RVar[18u].w;
            RVar[5u].x = RVar[18u].x;
            RVar[5u].y = _2640;
            RVar[5u].z = _2642;
            RVar[5u].w = _2644;
            float _2652 = RVar[7u].y;
            float _2654 = RVar[0u].z;
            float _2656 = RVar[18u].w;
            RVar[18u].x = RVar[9u].x;
            RVar[18u].y = _2652;
            RVar[18u].z = _2654;
            RVar[18u].w = _2656;
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
        RVar[0u].x = dot(RVar[18u], CBUFFER_3.values[3]);
        RVar[5u].z = uintBitsToFloat(1065353216u);
        float _2700 = RVar[19u].w;
        float _2702 = RVar[19u].w;
        RVar[0u].y = dot(RVar[18u], CBUFFER_3.values[4]);
        float _2712 = RVar[19u].z;
        float _2714 = RVar[19u].z;
        float _2716 = (_2712 * _2714) + (_2700 * _2702);
        RVar[0u].z = dot(RVar[18u], CBUFFER_3.values[5]);
        RVar[122u].x = _2716;
        float _2726 = RVar[19u].y;
        float _2728 = RVar[19u].y;
        float _2730 = (_2726 * _2728) + _2716;
        RVar[0u].w = dot(RVar[18u], CBUFFER_3.values[6]);
        RVar[122u].x = _2730;
        float _2741 = RVar[19u].x;
        float _2743 = RVar[19u].x;
        float _2745 = (_2741 * _2743) + _2730;
        RVar[1u].x = CBUFFER_3.values[25].x;
        RVar[1u].y = CBUFFER_3.values[25].y;
        RVar[1u].z = CBUFFER_3.values[25].z;
        RVar[123u].w = _2745;
        vec4 _2751 = RVar[18u];
        float _2756 = inversesqrt(_2745);
        float _2758 = RVar[19u].x;
        float _2759 = _2758 * _2756;
        float _2761 = RVar[19u].y;
        float _2762 = _2761 * _2756;
        float _2764 = RVar[19u].z;
        float _2765 = _2764 * _2756;
        float _2767 = RVar[19u].w;
        float _2768 = _2767 * _2756;
        RVar[127u].x = _2759;
        RVar[127u].y = _2762;
        RVar[127u].z = _2765;
        RVar[127u].w = _2768;
        RVar[126u].x = (-dot(_2751, CBUFFER_3.values[2])) + (-CBUFFER_3.values[33].x);
        float _2783 = dot(vec4(_2759, _2762, _2765, _2768), CBUFFER_3.values[0]);
        RVar[2u].x = _2783;
        RVar[6u].x = _2759;
        vec4 _2787 = RVar[127u];
        float _2790 = dot(_2787, CBUFFER_3.values[1]);
        RVar[2u].y = _2790;
        RVar[4u].x = (_2783 * uintBitsToFloat(1056964608u)) + uintBitsToFloat(1056964608u);
        vec4 _2799 = RVar[127u];
        float _2802 = dot(_2799, CBUFFER_3.values[2]);
        RVar[2u].z = _2802;
        RVar[4u].y = ((-_2790) * uintBitsToFloat(1056964608u)) + uintBitsToFloat(1056964608u);
        float _2811 = RVar[2u].x;
        float _2813 = RVar[2u].y;
        RVar[6u].y = RVar[127u].y;
        float _2830 = RVar[2u].z;
        float _2847 = RVar[127u].z;
        RVar[1u].w = clamp(RVar[126u].x * CBUFFER_3.values[41].x, 0.0, 1.0);
        RVar[6u].z = _2847;
        float _2851 = RVar[2u].x;
        float _2853 = RVar[2u].y;
        float _2865 = min(max(-dot(vec4(_2811, _2813, _2802, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[7].x, CBUFFER_3.values[7].y, CBUFFER_3.values[7].z, uintBitsToFloat(0u))), uintBitsToFloat(0u)), uintBitsToFloat(1065353216u));
        RVar[126u].x = (_2865 * CBUFFER_3.values[15].x) + uintBitsToFloat(0u);
        RVar[127u].y = (_2865 * CBUFFER_3.values[15].y) + uintBitsToFloat(0u);
        RVar[127u].z = (_2865 * CBUFFER_3.values[15].z) + uintBitsToFloat(0u);
        RVar[126u].y = (_2865 * CBUFFER_3.values[15].w) + uintBitsToFloat(0u);
        float _2895 = RVar[2u].x;
        float _2897 = RVar[2u].y;
        float _2899 = RVar[2u].z;
        float _2913 = min(max(-dot(vec4(_2851, _2853, _2830 * CBUFFER_3.values[8].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[8].x, CBUFFER_3.values[8].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u))), uintBitsToFloat(0u)), uintBitsToFloat(1065353216u));
        float _2927 = RVar[127u].y;
        float _2933 = RVar[127u].z;
        float _2939 = RVar[126u].y;
        RVar[127u].y = (_2913 * CBUFFER_3.values[16].x) + RVar[126u].x;
        RVar[127u].z = (_2913 * CBUFFER_3.values[16].y) + _2927;
        RVar[127u].w = (_2913 * CBUFFER_3.values[16].z) + _2933;
        RVar[126u].z = (_2913 * CBUFFER_3.values[16].w) + _2939;
        float _2947 = RVar[2u].x;
        float _2949 = RVar[2u].y;
        float _2951 = RVar[2u].z;
        float _2965 = min(max(-dot(vec4(_2895, _2897, _2899, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[9].x, CBUFFER_3.values[9].y, CBUFFER_3.values[9].z, uintBitsToFloat(0u))), uintBitsToFloat(0u)), uintBitsToFloat(1065353216u));
        float _2979 = RVar[127u].y;
        float _2985 = RVar[127u].w;
        float _2991 = RVar[126u].z;
        RVar[126u].x = (_2965 * CBUFFER_3.values[17].y) + RVar[127u].z;
        RVar[127u].z = (_2965 * CBUFFER_3.values[17].x) + _2979;
        RVar[127u].w = (_2965 * CBUFFER_3.values[17].z) + _2985;
        RVar[126u].w = (_2965 * CBUFFER_3.values[17].w) + _2991;
        float _2999 = RVar[2u].x;
        float _3001 = RVar[2u].y;
        float _3003 = RVar[2u].z;
        float _3017 = min(max(-dot(vec4(_2947, _2949, _2951, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[10].x, CBUFFER_3.values[10].y, CBUFFER_3.values[10].z, uintBitsToFloat(0u))), uintBitsToFloat(0u)), uintBitsToFloat(1065353216u));
        float _3028 = RVar[127u].w;
        float _3037 = RVar[127u].z;
        float _3043 = RVar[126u].w;
        RVar[126u].x = (_3017 * CBUFFER_3.values[18].y) + RVar[126u].x;
        RVar[127u].y = (_3017 * CBUFFER_3.values[18].z) + _3028;
        RVar[127u].w = (_3017 * CBUFFER_3.values[18].x) + _3037;
        RVar[127u].x = (_3017 * CBUFFER_3.values[18].w) + _3043;
        float _3051 = RVar[2u].x;
        float _3053 = RVar[2u].y;
        float _3055 = RVar[2u].z;
        float _3069 = min(max(-dot(vec4(_2999, _3001, _3003, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[11].x, CBUFFER_3.values[11].y, CBUFFER_3.values[11].z, uintBitsToFloat(0u))), uintBitsToFloat(0u)), uintBitsToFloat(1065353216u));
        float _3080 = RVar[126u].x;
        float _3086 = RVar[127u].y;
        float _3095 = RVar[127u].x;
        RVar[127u].x = (_3069 * CBUFFER_3.values[19].x) + RVar[127u].w;
        RVar[127u].y = (_3069 * CBUFFER_3.values[19].y) + _3080;
        RVar[127u].z = (_3069 * CBUFFER_3.values[19].z) + _3086;
        RVar[126u].y = (_3069 * CBUFFER_3.values[19].w) + _3095;
        float _3121 = min(max(-dot(vec4(_3051, _3053, _3055, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[12].x, CBUFFER_3.values[12].y, CBUFFER_3.values[12].z, uintBitsToFloat(0u))), uintBitsToFloat(0u)), uintBitsToFloat(1065353216u));
        float _3129 = RVar[127u].x;
        float _3135 = RVar[127u].y;
        float _3141 = RVar[127u].z;
        float _3147 = RVar[126u].y;
        RVar[3u].x = max(-dot(vec4(RVar[2u].x, RVar[2u].y, RVar[2u].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[13].x, CBUFFER_3.values[13].y, CBUFFER_3.values[13].z, uintBitsToFloat(0u))), uintBitsToFloat(0u));
        RVar[3u].y = (_3121 * CBUFFER_3.values[20].x) + _3129;
        RVar[3u].z = (_3121 * CBUFFER_3.values[20].y) + _3135;
        RVar[2u].w = (_3121 * CBUFFER_3.values[20].z) + _3141;
        RVar[4u].z = (_3121 * CBUFFER_3.values[20].w) + _3147;
    }
    vec4 _3170 = (RVar[0u] * vec4(VS_PUSH.posMulAdd.xy, 1.0, 1.0)) + vec4(VS_PUSH.posMulAdd.zw, 0.0, 0.0);
    vec4 _3173 = _3170;
    _3173.y = -_3170.y;
    vec4 _3181 = _3173;
    _3181.z = (_3173.z + (_3173.w * VS_PUSH.zSpaceMul.x)) * VS_PUSH.zSpaceMul.y;
    gl_Position = _3181;
    PARAM_0 = RVar[1u];
    PARAM_1 = RVar[6u];
    if (stateVar == 0)
    {
        float _3195 = RVar[2u].x;
        float _3197 = RVar[2u].y;
        float _3199 = RVar[2u].z;
        float _3213 = RVar[3u].x;
        float _3215 = min(_3213, uintBitsToFloat(1065353216u));
        float _3229 = RVar[3u].y;
        float _3235 = RVar[2u].w;
        float _3241 = RVar[4u].z;
        RVar[127u].x = (_3215 * CBUFFER_3.values[21].y) + RVar[3u].z;
        RVar[127u].z = (_3215 * CBUFFER_3.values[21].x) + _3229;
        RVar[127u].w = (_3215 * CBUFFER_3.values[21].z) + _3235;
        RVar[126u].w = (_3215 * CBUFFER_3.values[21].w) + _3241;
        float _3249 = min(max(-dot(vec4(_3195, _3197, _3199, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[14].x, CBUFFER_3.values[14].y, CBUFFER_3.values[14].z, uintBitsToFloat(0u))), uintBitsToFloat(0u)), uintBitsToFloat(1065353216u));
        float _3259 = RVar[5u].z;
        RVar[126u].y = RVar[5u].z * CBUFFER_4.values[20].w;
        RVar[126u].x = _3259 * CBUFFER_4.values[17].w;
        float _3276 = RVar[127u].w;
        float _3283 = RVar[127u].x;
        float _3286 = clamp((_3249 * CBUFFER_3.values[22].y) + _3283, 0.0, 1.0);
        float _3290 = RVar[127u].z;
        float _3293 = clamp((_3249 * CBUFFER_3.values[22].x) + _3290, 0.0, 1.0);
        RVar[127u].x = clamp((_3249 * CBUFFER_3.values[22].w) + RVar[126u].w, 0.0, 1.0);
        RVar[127u].y = clamp((_3249 * CBUFFER_3.values[22].z) + _3276, 0.0, 1.0);
        RVar[123u].z = _3286;
        RVar[123u].w = _3293;
        float _3305 = clamp((CBUFFER_4.values[2].y * CBUFFER_3.values[23].y) + _3286, 0.0, 1.0);
        float _3312 = clamp((CBUFFER_4.values[2].x * CBUFFER_3.values[23].x) + _3293, 0.0, 1.0);
        RVar[123u].z = _3305;
        RVar[123u].w = _3312;
        float _3322 = RVar[127u].y;
        float _3325 = clamp((CBUFFER_4.values[2].z * CBUFFER_3.values[23].z) + _3322, 0.0, 1.0);
        float _3329 = RVar[127u].x;
        RVar[123u].y = _3325;
        float _3346 = RVar[5u].z;
        float _3350 = RVar[126u].x;
        float _3352 = (_3346 * CBUFFER_4.values[17].z) + _3350;
        RVar[2u].x = max(_3312, uintBitsToFloat(1065353216u)) * CBUFFER_4.values[0].x;
        RVar[2u].y = max(_3305, uintBitsToFloat(1065353216u)) * CBUFFER_4.values[0].y;
        RVar[122u].x = _3352;
        float _3357 = RVar[4u].y;
        float _3361 = (_3357 * CBUFFER_4.values[17].y) + _3352;
        RVar[123u].x = _3361;
        RVar[2u].z = max(_3325, uintBitsToFloat(1065353216u)) * CBUFFER_4.values[0].z;
        RVar[2u].w = CBUFFER_4.values[0].w * max(clamp(_3329 + CBUFFER_4.values[2].w, 0.0, 1.0), uintBitsToFloat(0u));
        float _3378 = RVar[5u].z;
        float _3382 = RVar[126u].y;
        RVar[0u].x = (RVar[4u].x * CBUFFER_4.values[17].x) + _3361;
        RVar[126u].x = (_3378 * CBUFFER_4.values[20].z) + _3382;
        RVar[0u].y = dot(vec4(RVar[4u].x, RVar[4u].y, RVar[5u].z, RVar[5u].z), CBUFFER_4.values[18]);
        float _3417 = RVar[5u].z;
        RVar[1u].x = dot(vec4(RVar[4u].x, RVar[4u].y, RVar[126u].x, uintBitsToFloat(0u)), vec4(CBUFFER_4.values[20].x, CBUFFER_4.values[20].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[1u].y = dot(vec4(RVar[4u].x, RVar[4u].y, RVar[5u].z, _3417 * CBUFFER_4.values[21].w), vec4(CBUFFER_4.values[21].x, CBUFFER_4.values[21].y, CBUFFER_4.values[21].z, uintBitsToFloat(1065353216u)));
        RVar[3u].x = dot(vec4(RVar[4u].x, RVar[4u].y, RVar[5u].z, RVar[5u].z), CBUFFER_4.values[23]);
        RVar[3u].y = dot(vec4(RVar[4u].x, RVar[4u].y, RVar[5u].z, RVar[5u].z), CBUFFER_4.values[24]);
    }
    PARAM_2 = RVar[2u];
    PARAM_3 = vec4(RVar[0u].x, RVar[0u].y, RVar[0u].z, RVar[0u].z);
    PARAM_4 = vec4(RVar[1u].x, RVar[1u].y, RVar[1u].z, RVar[1u].z);
    PARAM_5 = vec4(RVar[3u].x, RVar[3u].y, RVar[3u].z, RVar[3u].z);
    if (stateVar == 0)
    {
    }
}

 