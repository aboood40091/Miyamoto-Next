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
layout(location = 6) out vec4 PARAM_6;
layout(location = 7) out vec4 PARAM_7;
layout(location = 0) in uvec4 aBlendIndex_0_0;
layout(location = 1) in uvec4 aBlendWeight_0_0;
layout(location = 2) in uvec4 aColor0_0_0;
layout(location = 3) in uvec3 aNormal_0_0;
layout(location = 4) in uvec3 aPosition_0_0;
layout(location = 5) in uvec4 aTangent_0_0;
layout(location = 6) in uvec2 aTexCoord0_0_0;
layout(location = 7) in uvec2 aTexCoordNormal_0_0;
layout(location = 8) in uvec2 aTexCoordSpecMask_0_0;
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
        RVar[6u] = vec4(uintBitsToFloat(aTangent_0_0.x), uintBitsToFloat(aTangent_0_0.y), uintBitsToFloat(aTangent_0_0.z), uintBitsToFloat(aTangent_0_0.w));
        RVar[7u] = vec4(vec4(uintBitsToFloat(aTexCoord0_0_0.x), uintBitsToFloat(aTexCoord0_0_0.y), 0.0, 1.0).xy, 0.0, 1.0);
        RVar[8u] = vec4(vec4(uintBitsToFloat(aTexCoordNormal_0_0.x), uintBitsToFloat(aTexCoordNormal_0_0.y), 0.0, 1.0).xy, 0.0, 1.0);
        RVar[9u] = vec4(vec4(uintBitsToFloat(aTexCoordSpecMask_0_0.x), uintBitsToFloat(aTexCoordSpecMask_0_0.y), 0.0, 1.0).xy, 0.0, 1.0);
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
        RVar[10u].x = uintBitsToFloat(0u);
        RVar[10u].y = uintBitsToFloat(0u);
        RVar[10u].z = uintBitsToFloat(0u);
        RVar[0u].w = intBitsToFloat((floatBitsToInt(CBUFFER_1.values[3].x) != (0)) ? (-1) : 0);
        bool _90 = floatBitsToInt(RVar[0u].w) == (0);
        predVar = _90;
        stateVar = _90 ? 0 : 1;
    }
    if (stateVar == 0)
    {
        float _124 = RVar[4u].z;
        RVar[127u].w = dot(vec4(RVar[5u].x, RVar[5u].y, RVar[5u].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_2.values[0].x, CBUFFER_2.values[0].y, CBUFFER_2.values[0].z, uintBitsToFloat(0u)));
        RVar[126u].x = _124 * CBUFFER_2.values[0].z;
        RVar[127u].x = dot(vec4(RVar[5u].x, RVar[5u].y, RVar[5u].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_2.values[1].x, CBUFFER_2.values[1].y, CBUFFER_2.values[1].z, uintBitsToFloat(0u)));
        RVar[126u].w = dot(vec4(RVar[5u].x, RVar[5u].y, RVar[5u].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_2.values[2].x, CBUFFER_2.values[2].y, CBUFFER_2.values[2].z, uintBitsToFloat(0u)));
        float _176 = RVar[127u].x;
        float _180 = RVar[6u].z;
        RVar[22u].x = CBUFFER_2.values[0].w + RVar[127u].w;
        RVar[22u].y = CBUFFER_2.values[1].w + _176;
        float _188 = RVar[4u].y;
        float _192 = RVar[126u].x;
        float _194 = (_188 * CBUFFER_2.values[0].y) + _192;
        float _198 = RVar[126u].w;
        float _201 = RVar[6u].y;
        float _205 = (_201 * CBUFFER_2.values[0].y) + (_180 * CBUFFER_2.values[0].z);
        RVar[123u].x = _194;
        RVar[22u].z = CBUFFER_2.values[2].w + _198;
        RVar[122u].x = _205;
        float _218 = RVar[4u].z;
        float _223 = RVar[6u].z;
        float _228 = RVar[6u].x;
        RVar[11u].x = (RVar[4u].x * CBUFFER_2.values[0].x) + _194;
        RVar[10u].x = (_228 * CBUFFER_2.values[0].x) + _205;
        float _252 = RVar[6u].y;
        RVar[11u].y = dot(vec4(RVar[4u].x, RVar[4u].y, _218 * CBUFFER_2.values[1].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_2.values[1].x, CBUFFER_2.values[1].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[126u].x = (_252 * CBUFFER_2.values[1].y) + (_223 * CBUFFER_2.values[1].z);
        RVar[11u].z = dot(vec4(RVar[4u].x, RVar[4u].y, RVar[4u].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_2.values[2].x, CBUFFER_2.values[2].y, CBUFFER_2.values[2].z, uintBitsToFloat(0u)));
        float _278 = RVar[6u].z;
        RVar[10u].y = (RVar[6u].x * CBUFFER_2.values[1].x) + RVar[126u].x;
        RVar[10u].z = dot(vec4(RVar[6u].x, RVar[6u].y, _278 * CBUFFER_2.values[2].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_2.values[2].x, CBUFFER_2.values[2].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
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
        bool _336 = floatBitsToInt(RVar[0u].w) == (0);
        predVar = _336;
        stateVar = _336 ? 0 : 1;
    }
    if (stateVar == 0)
    {
        float _345 = RVar[1u].x;
        float _349 = intBitsToFloat(floatBitsToInt(_345) * (3));
        RVar[1u].w = _349;
        RVar[1u].x = intBitsToFloat(floatBitsToInt(_349) + (2));
        RVar[1u].y = intBitsToFloat(floatBitsToInt(_349) + (1));
    }
    if (stateVar == 0)
    {
        RVar[0u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].w)];
        RVar[2u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].y)];
        RVar[1u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].x)];
    }
    if (stateVar == 0)
    {
        float _389 = RVar[5u].x;
        float _391 = RVar[5u].y;
        float _393 = RVar[5u].z;
        float _397 = RVar[0u].x;
        float _399 = RVar[0u].y;
        float _401 = RVar[0u].z;
        RVar[127u].x = RVar[4u].z * RVar[0u].z;
        float _412 = RVar[5u].x;
        float _414 = RVar[5u].y;
        float _416 = RVar[5u].z;
        float _420 = RVar[2u].x;
        float _422 = RVar[2u].y;
        float _424 = RVar[2u].z;
        RVar[22u].x = RVar[0u].w + dot(vec4(_389, _391, _393, uintBitsToFloat(2147483648u)), vec4(_397, _399, _401, uintBitsToFloat(0u)));
        float _433 = RVar[5u].x;
        float _435 = RVar[5u].y;
        float _437 = RVar[5u].z;
        float _441 = RVar[1u].x;
        float _443 = RVar[1u].y;
        float _445 = RVar[1u].z;
        RVar[22u].y = RVar[2u].w + dot(vec4(_412, _414, _416, uintBitsToFloat(2147483648u)), vec4(_420, _422, _424, uintBitsToFloat(0u)));
        float _454 = RVar[4u].y;
        float _456 = RVar[0u].y;
        float _458 = RVar[127u].x;
        float _460 = (_454 * _456) + _458;
        float _462 = RVar[1u].w;
        float _465 = RVar[6u].z;
        float _467 = RVar[0u].z;
        RVar[123u].x = _460;
        RVar[22u].z = _462 + dot(vec4(_433, _435, _437, uintBitsToFloat(2147483648u)), vec4(_441, _443, _445, uintBitsToFloat(0u)));
        float _486 = RVar[4u].x;
        float _488 = RVar[0u].x;
        RVar[10u].x = dot(vec4(RVar[6u].x, RVar[6u].y, _465 * _467, uintBitsToFloat(2147483648u)), vec4(RVar[0u].x, RVar[0u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[11u].x = (_486 * _488) + _460;
        float _511 = RVar[4u].z;
        float _513 = RVar[1u].z;
        RVar[11u].y = dot(vec4(RVar[4u].x, RVar[4u].y, RVar[4u].z, uintBitsToFloat(2147483648u)), vec4(RVar[2u].x, RVar[2u].y, RVar[2u].z, uintBitsToFloat(0u)));
        float _531 = RVar[6u].z;
        float _533 = RVar[2u].z;
        RVar[11u].z = dot(vec4(RVar[4u].x, RVar[4u].y, _511 * _513, uintBitsToFloat(2147483648u)), vec4(RVar[1u].x, RVar[1u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        float _551 = RVar[6u].z;
        float _553 = RVar[1u].z;
        RVar[10u].y = dot(vec4(RVar[6u].x, RVar[6u].y, _531 * _533, uintBitsToFloat(2147483648u)), vec4(RVar[2u].x, RVar[2u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[10u].z = dot(vec4(RVar[6u].x, RVar[6u].y, _551 * _553, uintBitsToFloat(2147483648u)), vec4(RVar[1u].x, RVar[1u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
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
        bool _602 = floatBitsToInt(RVar[0u].w) == (0);
        predVar = _602;
        stateVar = _602 ? 0 : 1;
    }
    if (stateVar == 0)
    {
        float _611 = RVar[1u].x;
        float _615 = intBitsToFloat(floatBitsToInt(_611) * (3));
        RVar[0u].x = _615;
        float _626 = RVar[1u].y;
        float _630 = intBitsToFloat(floatBitsToInt(_626) * (3));
        RVar[0u].z = intBitsToFloat(floatBitsToInt(_615) + (2));
        RVar[0u].w = intBitsToFloat(floatBitsToInt(_615) + (1));
        RVar[0u].y = _630;
        float _643 = RVar[1u].z;
        float _647 = intBitsToFloat(floatBitsToInt(_643) * (3));
        RVar[10u].x = intBitsToFloat(floatBitsToInt(_630) + (1));
        RVar[4u].w = intBitsToFloat(floatBitsToInt(_630) + (2));
        RVar[10u].z = _647;
        float _660 = RVar[1u].w;
        RVar[1u].x = intBitsToFloat(floatBitsToInt(_647) + (2));
        RVar[1u].y = intBitsToFloat(floatBitsToInt(_647) + (1));
        RVar[1u].w = intBitsToFloat(floatBitsToInt(_660) * (3));
    }
    if (stateVar == 0)
    {
        RVar[11u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].x)];
        RVar[13u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].w)];
        RVar[12u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].z)];
        RVar[14u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].y)];
        RVar[15u] = CBUFFER_2.values[floatBitsToUint(RVar[10u].x)];
        RVar[16u] = CBUFFER_2.values[floatBitsToUint(RVar[4u].w)];
        RVar[17u] = CBUFFER_2.values[floatBitsToUint(RVar[10u].z)];
        RVar[18u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].y)];
    }
    if (stateVar == 0)
    {
        float _737 = RVar[1u].w;
        float _743 = RVar[4u].z;
        float _745 = RVar[13u].z;
        float _748 = RVar[4u].y;
        float _750 = RVar[12u].y;
        float _753 = RVar[4u].z;
        float _755 = RVar[11u].z;
        RVar[10u].x = intBitsToFloat(floatBitsToInt(RVar[1u].w) + (1));
        RVar[1u].y = intBitsToFloat(floatBitsToInt(_737) + (2));
        RVar[10u].z = _743 * _745;
        RVar[0u].w = _748 * _750;
        float _779 = RVar[4u].y;
        float _781 = RVar[11u].y;
        RVar[4u].w = dot(vec4(RVar[5u].x, RVar[5u].y, RVar[5u].z, uintBitsToFloat(2147483648u)), vec4(RVar[11u].x, RVar[11u].y, RVar[11u].z, uintBitsToFloat(0u)));
        RVar[0u].x = (_779 * _781) + (_753 * _755);
    }
    if (stateVar == 0)
    {
        RVar[19u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].x)];
        RVar[20u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].w)];
        RVar[21u] = CBUFFER_2.values[floatBitsToUint(RVar[10u].x)];
        RVar[1u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].y)];
    }
    if (stateVar == 0)
    {
        float _822 = RVar[5u].x;
        float _824 = RVar[5u].y;
        float _826 = RVar[5u].z;
        float _830 = RVar[13u].x;
        float _832 = RVar[13u].y;
        float _834 = RVar[13u].z;
        RVar[127u].z = RVar[11u].w + RVar[4u].w;
        float _845 = RVar[5u].x;
        float _847 = RVar[5u].y;
        float _849 = RVar[5u].z;
        float _853 = RVar[12u].x;
        float _855 = RVar[12u].y;
        float _857 = RVar[12u].z;
        float _862 = RVar[13u].w;
        float _865 = RVar[12u].w;
        float _873 = RVar[2u].x;
        float _876 = RVar[4u].x;
        float _878 = RVar[12u].x;
        float _880 = RVar[0u].w;
        float _884 = RVar[4u].y;
        float _886 = RVar[13u].y;
        float _888 = RVar[10u].z;
        RVar[127u].y = RVar[2u].x * RVar[127u].z;
        RVar[127u].z = _873 * (_862 + dot(vec4(_822, _824, _826, uintBitsToFloat(2147483648u)), vec4(_830, _832, _834, uintBitsToFloat(0u))));
        RVar[0u].w = (_876 * _878) + _880;
        RVar[125u].x = (_884 * _886) + _888;
        float _897 = RVar[5u].x;
        float _899 = RVar[5u].y;
        float _901 = RVar[5u].z;
        float _905 = RVar[14u].x;
        float _907 = RVar[14u].y;
        float _909 = RVar[14u].z;
        RVar[127u].w = RVar[2u].x * (_865 + dot(vec4(_845, _847, _849, uintBitsToFloat(2147483648u)), vec4(_853, _855, _857, uintBitsToFloat(0u))));
        float _918 = RVar[5u].x;
        float _920 = RVar[5u].y;
        float _922 = RVar[5u].z;
        float _926 = RVar[15u].x;
        float _928 = RVar[15u].y;
        float _930 = RVar[15u].z;
        RVar[126u].w = RVar[14u].w + dot(vec4(_897, _899, _901, uintBitsToFloat(2147483648u)), vec4(_905, _907, _909, uintBitsToFloat(0u)));
        float _939 = RVar[5u].x;
        float _941 = RVar[5u].y;
        float _943 = RVar[5u].z;
        float _947 = RVar[16u].x;
        float _949 = RVar[16u].y;
        float _951 = RVar[16u].z;
        RVar[126u].z = RVar[15u].w + dot(vec4(_918, _920, _922, uintBitsToFloat(2147483648u)), vec4(_926, _928, _930, uintBitsToFloat(0u)));
        float _964 = RVar[16u].w;
        float _967 = RVar[127u].w;
        float _971 = RVar[127u].z;
        float _975 = RVar[2u].y;
        float _977 = RVar[126u].w;
        RVar[127u].x = RVar[127u].y + uintBitsToFloat(0u);
        RVar[127u].y = _964 + dot(vec4(_939, _941, _943, uintBitsToFloat(2147483648u)), vec4(_947, _949, _951, uintBitsToFloat(0u)));
        RVar[125u].z = _967 + uintBitsToFloat(0u);
        RVar[127u].w = _971 + uintBitsToFloat(0u);
        RVar[127u].z = _975 * _977;
        float _985 = RVar[5u].x;
        float _987 = RVar[5u].y;
        float _989 = RVar[5u].z;
        float _993 = RVar[17u].x;
        float _995 = RVar[17u].y;
        float _997 = RVar[17u].z;
        RVar[126u].y = RVar[2u].y * RVar[126u].z;
        float _1008 = RVar[5u].x;
        float _1010 = RVar[5u].y;
        float _1012 = RVar[5u].z;
        float _1016 = RVar[18u].x;
        float _1018 = RVar[18u].y;
        float _1020 = RVar[18u].z;
        RVar[126u].x = RVar[17u].w + dot(vec4(_985, _987, _989, uintBitsToFloat(2147483648u)), vec4(_993, _995, _997, uintBitsToFloat(0u)));
        float _1029 = RVar[5u].x;
        float _1031 = RVar[5u].y;
        float _1033 = RVar[5u].z;
        float _1037 = RVar[19u].x;
        float _1039 = RVar[19u].y;
        float _1041 = RVar[19u].z;
        RVar[126u].w = RVar[18u].w + dot(vec4(_1008, _1010, _1012, uintBitsToFloat(2147483648u)), vec4(_1016, _1018, _1020, uintBitsToFloat(0u)));
        float _1050 = RVar[2u].y;
        float _1052 = RVar[127u].y;
        float _1060 = RVar[19u].w;
        float _1063 = RVar[127u].w;
        float _1065 = RVar[126u].y;
        float _1068 = RVar[2u].z;
        float _1070 = RVar[126u].x;
        RVar[127u].y = RVar[127u].x + RVar[127u].z;
        RVar[127u].z = _1060 + dot(vec4(_1029, _1031, _1033, uintBitsToFloat(2147483648u)), vec4(_1037, _1039, _1041, uintBitsToFloat(0u)));
        RVar[125u].w = _1063 + _1065;
        RVar[127u].w = _1068 * _1070;
        float _1077 = RVar[5u].x;
        float _1079 = RVar[5u].y;
        float _1081 = RVar[5u].z;
        float _1085 = RVar[20u].x;
        float _1087 = RVar[20u].y;
        float _1089 = RVar[20u].z;
        RVar[124u].w = RVar[125u].z + (_1050 * _1052);
        float _1099 = RVar[5u].x;
        float _1101 = RVar[5u].y;
        float _1103 = RVar[5u].z;
        float _1107 = RVar[21u].x;
        float _1109 = RVar[21u].y;
        float _1111 = RVar[21u].z;
        RVar[126u].y = RVar[20u].w + dot(vec4(_1077, _1079, _1081, uintBitsToFloat(2147483648u)), vec4(_1085, _1087, _1089, uintBitsToFloat(0u)));
        float _1120 = RVar[5u].x;
        float _1122 = RVar[5u].y;
        float _1124 = RVar[5u].z;
        float _1128 = RVar[1u].x;
        float _1130 = RVar[1u].y;
        float _1132 = RVar[1u].z;
        RVar[125u].y = RVar[21u].w + dot(vec4(_1099, _1101, _1103, uintBitsToFloat(2147483648u)), vec4(_1107, _1109, _1111, uintBitsToFloat(0u)));
        float _1146 = RVar[2u].z;
        float _1148 = RVar[127u].z;
        float _1151 = RVar[2u].z;
        float _1153 = RVar[126u].w;
        float _1156 = RVar[1u].w;
        float _1159 = RVar[4u].x;
        float _1161 = RVar[11u].x;
        float _1163 = RVar[0u].x;
        RVar[127u].x = RVar[127u].y + RVar[127u].w;
        RVar[127u].y = (_1159 * _1161) + _1163;
        float _1169 = RVar[124u].w;
        float _1172 = RVar[125u].w;
        float _1175 = RVar[2u].w;
        float _1177 = RVar[125u].y;
        float _1185 = RVar[2u].w;
        float _1193 = RVar[4u].z;
        float _1195 = RVar[12u].z;
        float _1197 = RVar[0u].w;
        float _1201 = RVar[2u].x;
        float _1203 = RVar[127u].y;
        RVar[22u].x = RVar[127u].x + (RVar[2u].w * RVar[126u].y);
        RVar[22u].y = (_1172 + (_1151 * _1153)) + (_1175 * _1177);
        RVar[22u].z = (_1169 + (_1146 * _1148)) + (_1185 * (_1156 + dot(vec4(_1120, _1122, _1124, uintBitsToFloat(2147483648u)), vec4(_1128, _1130, _1132, uintBitsToFloat(0u)))));
        RVar[124u].w = (_1193 * _1195) + _1197;
        RVar[0u].x = (_1201 * _1203) + uintBitsToFloat(0u);
        float _1213 = RVar[6u].z;
        float _1215 = RVar[11u].z;
        float _1223 = RVar[6u].y;
        float _1225 = RVar[14u].y;
        float _1228 = RVar[4u].x;
        float _1230 = RVar[13u].x;
        float _1232 = RVar[125u].x;
        float _1236 = RVar[6u].z;
        float _1238 = RVar[13u].z;
        RVar[127u].y = RVar[6u].y * RVar[12u].y;
        RVar[127u].z = _1223 * _1225;
        RVar[125u].w = (_1228 * _1230) + _1232;
        float _1258 = RVar[6u].y;
        float _1260 = RVar[13u].y;
        float _1262 = (_1258 * _1260) + (_1236 * _1238);
        RVar[127u].w = dot(vec4(RVar[6u].x, RVar[6u].y, _1213 * _1215, uintBitsToFloat(2147483648u)), vec4(RVar[11u].x, RVar[11u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[122u].x = _1262;
        float _1282 = RVar[6u].x;
        float _1284 = RVar[13u].x;
        float _1286 = (_1282 * _1284) + _1262;
        RVar[126u].w = dot(vec4(RVar[6u].x, RVar[6u].z, RVar[127u].y, uintBitsToFloat(2147483648u)), vec4(RVar[12u].x, RVar[12u].z, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[122u].x = _1286;
        float _1297 = RVar[2u].x;
        float _1299 = RVar[127u].w;
        float _1304 = RVar[2u].x;
        float _1306 = RVar[125u].w;
        float _1311 = RVar[2u].x;
        float _1316 = RVar[6u].z;
        float _1318 = RVar[14u].z;
        float _1320 = RVar[127u].z;
        float _1322 = (_1316 * _1318) + _1320;
        RVar[13u].x = (RVar[2u].x * RVar[124u].w) + uintBitsToFloat(0u);
        RVar[13u].y = (_1297 * _1299) + uintBitsToFloat(0u);
        RVar[12u].z = (_1304 * _1306) + uintBitsToFloat(0u);
        RVar[13u].w = (_1311 * _1286) + uintBitsToFloat(0u);
        RVar[122u].x = _1322;
        float _1335 = RVar[4u].z;
        float _1337 = RVar[15u].z;
        float _1340 = RVar[2u].x;
        float _1342 = RVar[126u].w;
        float _1347 = RVar[4u].y;
        float _1349 = RVar[16u].y;
        float _1352 = RVar[4u].z;
        float _1354 = RVar[14u].z;
        RVar[11u].x = (RVar[6u].x * RVar[14u].x) + _1322;
        RVar[12u].y = _1335 * _1337;
        RVar[13u].z = (_1340 * _1342) + uintBitsToFloat(0u);
        RVar[12u].w = _1347 * _1349;
        RVar[12u].x = _1352 * _1354;
    }
    if (stateVar == 0)
    {
        float _1382 = RVar[4u].z;
        float _1384 = RVar[16u].z;
        float _1386 = RVar[12u].w;
        float _1388 = (_1382 * _1384) + _1386;
        RVar[127u].z = dot(vec4(RVar[4u].x, RVar[4u].y, RVar[12u].x, uintBitsToFloat(2147483648u)), vec4(RVar[14u].x, RVar[14u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[122u].x = _1388;
        float _1408 = RVar[4u].x;
        float _1410 = RVar[16u].x;
        RVar[125u].x = dot(vec4(RVar[4u].x, RVar[4u].y, RVar[12u].y, uintBitsToFloat(2147483648u)), vec4(RVar[15u].x, RVar[15u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[125u].z = (_1408 * _1410) + _1388;
        float _1433 = RVar[2u].y;
        float _1435 = RVar[127u].z;
        float _1437 = RVar[0u].x;
        RVar[127u].z = dot(vec4(RVar[6u].x, RVar[6u].y, RVar[6u].z, uintBitsToFloat(2147483648u)), vec4(RVar[15u].x, RVar[15u].y, RVar[15u].z, uintBitsToFloat(0u)));
        RVar[127u].y = (_1433 * _1435) + _1437;
        float _1443 = RVar[6u].x;
        float _1445 = RVar[6u].y;
        float _1447 = RVar[6u].z;
        float _1451 = RVar[16u].x;
        float _1453 = RVar[16u].y;
        float _1455 = RVar[16u].z;
        RVar[126u].w = (RVar[2u].y * RVar[125u].x) + RVar[12u].z;
        float _1477 = RVar[2u].y;
        float _1479 = RVar[125u].z;
        float _1481 = RVar[13u].x;
        float _1485 = RVar[2u].y;
        float _1487 = RVar[13u].z;
        float _1491 = RVar[2u].y;
        float _1493 = RVar[11u].x;
        float _1495 = RVar[13u].y;
        RVar[125u].x = (RVar[2u].y * RVar[127u].z) + RVar[13u].w;
        RVar[126u].y = (_1477 * _1479) + _1481;
        RVar[127u].z = (_1485 * dot(vec4(_1443, _1445, _1447, uintBitsToFloat(2147483648u)), vec4(_1451, _1453, _1455, uintBitsToFloat(0u)))) + _1487;
        RVar[127u].w = (_1491 * _1493) + _1495;
        float _1520 = RVar[4u].z;
        float _1522 = RVar[18u].z;
        float _1525 = RVar[4u].x;
        float _1527 = RVar[4u].y;
        float _1531 = RVar[18u].x;
        float _1533 = RVar[18u].y;
        RVar[125u].z = (RVar[2u].z * dot(vec4(RVar[4u].x, RVar[4u].y, RVar[4u].z, uintBitsToFloat(2147483648u)), vec4(RVar[17u].x, RVar[17u].y, RVar[17u].z, uintBitsToFloat(0u)))) + RVar[127u].y;
        float _1546 = RVar[4u].x;
        float _1548 = RVar[4u].y;
        float _1550 = RVar[4u].z;
        float _1554 = RVar[19u].x;
        float _1556 = RVar[19u].y;
        float _1558 = RVar[19u].z;
        RVar[124u].x = (RVar[2u].z * dot(vec4(_1525, _1527, _1520 * _1522, uintBitsToFloat(2147483648u)), vec4(_1531, _1533, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)))) + RVar[126u].w;
        float _1570 = RVar[6u].x;
        float _1572 = RVar[6u].y;
        float _1574 = RVar[6u].z;
        float _1578 = RVar[17u].x;
        float _1580 = RVar[17u].y;
        float _1582 = RVar[17u].z;
        RVar[126u].z = (RVar[2u].z * dot(vec4(_1546, _1548, _1550, uintBitsToFloat(2147483648u)), vec4(_1554, _1556, _1558, uintBitsToFloat(0u)))) + RVar[126u].y;
        float _1594 = RVar[6u].x;
        float _1596 = RVar[6u].y;
        float _1598 = RVar[6u].z;
        float _1602 = RVar[18u].x;
        float _1604 = RVar[18u].y;
        float _1606 = RVar[18u].z;
        RVar[127u].x = (RVar[2u].z * dot(vec4(_1570, _1572, _1574, uintBitsToFloat(2147483648u)), vec4(_1578, _1580, _1582, uintBitsToFloat(0u)))) + RVar[127u].w;
        float _1618 = RVar[6u].x;
        float _1620 = RVar[6u].y;
        float _1622 = RVar[6u].z;
        float _1626 = RVar[19u].x;
        float _1628 = RVar[19u].y;
        float _1630 = RVar[19u].z;
        RVar[124u].z = (RVar[2u].z * dot(vec4(_1594, _1596, _1598, uintBitsToFloat(2147483648u)), vec4(_1602, _1604, _1606, uintBitsToFloat(0u)))) + RVar[125u].x;
        float _1648 = RVar[4u].x;
        float _1650 = RVar[21u].x;
        float _1653 = RVar[4u].x;
        float _1655 = RVar[1u].x;
        float _1658 = RVar[4u].y;
        float _1660 = RVar[20u].y;
        RVar[19u].x = (RVar[2u].z * dot(vec4(_1618, _1620, _1622, uintBitsToFloat(2147483648u)), vec4(_1626, _1628, _1630, uintBitsToFloat(0u)))) + RVar[127u].z;
        RVar[127u].z = _1653 * _1655;
        float _1679 = RVar[4u].y;
        float _1681 = RVar[21u].y;
        float _1683 = (_1679 * _1681) + (_1648 * _1650);
        RVar[126u].x = dot(vec4(RVar[4u].x, RVar[4u].z, _1658 * _1660, uintBitsToFloat(2147483648u)), vec4(RVar[20u].x, RVar[20u].z, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[122u].x = _1683;
        float _1695 = RVar[6u].x;
        float _1697 = RVar[21u].x;
        float _1700 = RVar[6u].y;
        float _1702 = RVar[1u].y;
        float _1705 = RVar[4u].z;
        float _1707 = RVar[21u].z;
        float _1711 = RVar[6u].x;
        float _1713 = RVar[20u].x;
        RVar[125u].x = (RVar[4u].y * RVar[1u].y) + RVar[127u].z;
        RVar[127u].z = _1700 * _1702;
        RVar[127u].w = (_1705 * _1707) + _1683;
        float _1719 = RVar[6u].z;
        float _1721 = RVar[6u].y;
        float _1725 = RVar[20u].z;
        float _1727 = RVar[20u].y;
        RVar[20u].x = (RVar[6u].y * RVar[21u].y) + (_1695 * _1697);
        float _1756 = RVar[2u].w;
        float _1758 = RVar[127u].x;
        RVar[127u].x = dot(vec4(RVar[6u].x, RVar[6u].z, RVar[127u].z, uintBitsToFloat(2147483648u)), vec4(RVar[1u].x, RVar[1u].z, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[10u].x = (_1756 * dot(vec4(_1719, _1721, _1711 * _1713, uintBitsToFloat(2147483648u)), vec4(_1725, _1727, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)))) + _1758;
        float _1772 = RVar[2u].w;
        float _1774 = RVar[127u].w;
        float _1776 = RVar[124u].x;
        float _1780 = RVar[4u].z;
        float _1782 = RVar[1u].z;
        float _1784 = RVar[125u].x;
        float _1786 = (_1780 * _1782) + _1784;
        RVar[11u].x = (RVar[2u].w * RVar[126u].x) + RVar[125u].z;
        RVar[11u].y = (_1772 * _1774) + _1776;
        RVar[123u].z = _1786;
        float _1797 = RVar[6u].z;
        float _1799 = RVar[21u].z;
        float _1801 = RVar[20u].x;
        float _1803 = (_1797 * _1799) + _1801;
        RVar[11u].z = (RVar[2u].w * _1786) + RVar[126u].z;
        RVar[123u].w = _1803;
        float _1813 = RVar[2u].w;
        float _1815 = RVar[127u].x;
        float _1817 = RVar[19u].x;
        RVar[10u].y = (RVar[2u].w * _1803) + RVar[124u].z;
        RVar[10u].z = (_1813 * _1815) + _1817;
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
        bool _1852 = floatBitsToInt(RVar[0u].w) == (0);
        predVar = _1852;
        stateVar = _1852 ? 0 : 1;
    }
    if (stateVar == 0)
    {
        float _1861 = RVar[1u].x;
        float _1865 = intBitsToFloat(floatBitsToInt(_1861) * (3));
        RVar[0u].y = _1865;
        float _1876 = RVar[1u].y;
        float _1880 = intBitsToFloat(floatBitsToInt(_1876) * (3));
        RVar[0u].x = intBitsToFloat(floatBitsToInt(_1865) + (1));
        RVar[0u].w = intBitsToFloat(floatBitsToInt(_1865) + (2));
        RVar[0u].z = _1880;
        float _1893 = RVar[1u].z;
        float _1897 = intBitsToFloat(floatBitsToInt(_1893) * (3));
        RVar[1u].x = intBitsToFloat(floatBitsToInt(_1880) + (2));
        RVar[1u].y = intBitsToFloat(floatBitsToInt(_1880) + (1));
        RVar[1u].w = _1897;
        RVar[10u].x = intBitsToFloat(floatBitsToInt(_1897) + (1));
        RVar[10u].y = intBitsToFloat(floatBitsToInt(_1897) + (2));
    }
    if (stateVar == 0)
    {
        RVar[11u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].y)];
        RVar[12u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].x)];
        RVar[13u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].w)];
        RVar[14u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].z)];
        RVar[16u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].y)];
        RVar[15u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].x)];
        RVar[19u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].w)];
        RVar[17u] = CBUFFER_2.values[floatBitsToUint(RVar[10u].x)];
    }
    if (stateVar == 0)
    {
        float _1968 = RVar[5u].x;
        float _1970 = RVar[5u].y;
        float _1972 = RVar[5u].z;
        float _1976 = RVar[11u].x;
        float _1978 = RVar[11u].y;
        float _1980 = RVar[11u].z;
        RVar[10u].x = RVar[4u].z * RVar[11u].z;
        float _2008 = RVar[11u].w;
        RVar[1u].w = dot(vec4(RVar[5u].x, RVar[5u].y, RVar[5u].z, uintBitsToFloat(2147483648u)), vec4(RVar[12u].x, RVar[12u].y, RVar[12u].z, uintBitsToFloat(0u)));
        RVar[0u].w = _2008 + dot(vec4(_1968, _1970, _1972, uintBitsToFloat(2147483648u)), vec4(_1976, _1978, _1980, uintBitsToFloat(0u)));
    }
    if (stateVar == 0)
    {
        RVar[18u] = CBUFFER_2.values[floatBitsToUint(RVar[10u].y)];
    }
    if (stateVar == 0)
    {
        float _2027 = RVar[5u].x;
        float _2029 = RVar[5u].y;
        float _2031 = RVar[5u].z;
        float _2035 = RVar[13u].x;
        float _2037 = RVar[13u].y;
        float _2039 = RVar[13u].z;
        float _2052 = RVar[13u].w;
        float _2055 = RVar[2u].x;
        float _2057 = RVar[0u].w;
        float _2060 = RVar[4u].z;
        float _2062 = RVar[12u].z;
        float _2065 = RVar[4u].y;
        float _2067 = RVar[11u].y;
        float _2069 = RVar[10u].x;
        RVar[127u].x = RVar[2u].x * (RVar[12u].w + RVar[1u].w);
        RVar[127u].z = _2055 * _2057;
        RVar[125u].w = _2060 * _2062;
        RVar[124u].x = (_2065 * _2067) + _2069;
        float _2077 = RVar[5u].x;
        float _2079 = RVar[5u].y;
        float _2081 = RVar[5u].z;
        float _2085 = RVar[14u].x;
        float _2087 = RVar[14u].y;
        float _2089 = RVar[14u].z;
        RVar[126u].x = RVar[2u].x * (_2052 + dot(vec4(_2027, _2029, _2031, uintBitsToFloat(2147483648u)), vec4(_2035, _2037, _2039, uintBitsToFloat(0u))));
        float _2098 = RVar[5u].x;
        float _2100 = RVar[5u].y;
        float _2102 = RVar[5u].z;
        float _2106 = RVar[16u].x;
        float _2108 = RVar[16u].y;
        float _2110 = RVar[16u].z;
        RVar[125u].x = RVar[14u].w + dot(vec4(_2077, _2079, _2081, uintBitsToFloat(2147483648u)), vec4(_2085, _2087, _2089, uintBitsToFloat(0u)));
        float _2119 = RVar[5u].x;
        float _2121 = RVar[5u].y;
        float _2123 = RVar[5u].z;
        float _2127 = RVar[15u].x;
        float _2129 = RVar[15u].y;
        float _2131 = RVar[15u].z;
        RVar[127u].w = RVar[16u].w + dot(vec4(_2098, _2100, _2102, uintBitsToFloat(2147483648u)), vec4(_2106, _2108, _2110, uintBitsToFloat(0u)));
        float _2144 = RVar[127u].z;
        float _2148 = RVar[15u].w;
        float _2151 = RVar[126u].x;
        float _2155 = RVar[2u].y;
        float _2157 = RVar[125u].x;
        RVar[127u].x += uintBitsToFloat(0u);
        RVar[127u].y = _2144 + uintBitsToFloat(0u);
        RVar[127u].z = _2148 + dot(vec4(_2119, _2121, _2123, uintBitsToFloat(2147483648u)), vec4(_2127, _2129, _2131, uintBitsToFloat(0u)));
        RVar[124u].w = _2151 + uintBitsToFloat(0u);
        RVar[126u].w = _2155 * _2157;
        float _2165 = RVar[5u].x;
        float _2167 = RVar[5u].y;
        float _2169 = RVar[5u].z;
        float _2173 = RVar[19u].x;
        float _2175 = RVar[19u].y;
        float _2177 = RVar[19u].z;
        RVar[126u].z = RVar[2u].y * RVar[127u].w;
        float _2188 = RVar[5u].x;
        float _2190 = RVar[5u].y;
        float _2192 = RVar[5u].z;
        float _2196 = RVar[17u].x;
        float _2198 = RVar[17u].y;
        float _2200 = RVar[17u].z;
        RVar[126u].y = RVar[19u].w + dot(vec4(_2165, _2167, _2169, uintBitsToFloat(2147483648u)), vec4(_2173, _2175, _2177, uintBitsToFloat(0u)));
        float _2209 = RVar[5u].x;
        float _2211 = RVar[5u].y;
        float _2213 = RVar[5u].z;
        float _2217 = RVar[18u].x;
        float _2219 = RVar[18u].y;
        float _2221 = RVar[18u].z;
        RVar[125u].y = RVar[17u].w + dot(vec4(_2188, _2190, _2192, uintBitsToFloat(2147483648u)), vec4(_2196, _2198, _2200, uintBitsToFloat(0u)));
        float _2235 = RVar[2u].y;
        float _2237 = RVar[127u].z;
        float _2240 = RVar[127u].y;
        float _2242 = RVar[126u].w;
        float _2245 = RVar[18u].w;
        float _2248 = RVar[4u].x;
        float _2250 = RVar[12u].x;
        float _2252 = RVar[125u].w;
        RVar[127u].x += RVar[126u].z;
        RVar[127u].z = _2240 + _2242;
        RVar[126u].x = (_2248 * _2250) + _2252;
        float _2259 = RVar[124u].w;
        float _2262 = RVar[2u].z;
        float _2264 = RVar[125u].y;
        float _2267 = RVar[2u].z;
        float _2270 = RVar[2u].z;
        float _2272 = RVar[126u].y;
        float _2275 = RVar[4u].x;
        float _2277 = RVar[11u].x;
        float _2279 = RVar[124u].x;
        float _2281 = (_2275 * _2277) + _2279;
        RVar[122u].x = _2281;
        float _2287 = RVar[127u].x;
        float _2291 = RVar[4u].y;
        float _2293 = RVar[12u].y;
        float _2295 = RVar[126u].x;
        float _2297 = (_2291 * _2293) + _2295;
        float _2299 = RVar[2u].x;
        RVar[22u].x = RVar[127u].z + (_2270 * _2272);
        RVar[22u].y = _2287 + (_2262 * _2264);
        RVar[22u].z = (_2259 + (_2235 * _2237)) + (_2267 * (_2245 + dot(vec4(_2209, _2211, _2213, uintBitsToFloat(2147483648u)), vec4(_2217, _2219, _2221, uintBitsToFloat(0u)))));
        RVar[123u].w = _2297;
        RVar[125u].y = (_2299 * _2281) + uintBitsToFloat(0u);
        float _2309 = RVar[4u].x;
        float _2311 = RVar[4u].y;
        float _2313 = RVar[4u].z;
        float _2317 = RVar[13u].x;
        float _2319 = RVar[13u].y;
        float _2321 = RVar[13u].z;
        RVar[126u].w = (RVar[2u].x * _2297) + uintBitsToFloat(0u);
        float _2332 = RVar[6u].x;
        float _2334 = RVar[6u].y;
        float _2336 = RVar[6u].z;
        float _2340 = RVar[11u].x;
        float _2342 = RVar[11u].y;
        float _2344 = RVar[11u].z;
        RVar[127u].y = (RVar[2u].x * dot(vec4(_2309, _2311, _2313, uintBitsToFloat(2147483648u)), vec4(_2317, _2319, _2321, uintBitsToFloat(0u)))) + uintBitsToFloat(0u);
        float _2355 = RVar[6u].x;
        float _2357 = RVar[6u].y;
        float _2359 = RVar[6u].z;
        float _2363 = RVar[12u].x;
        float _2365 = RVar[12u].y;
        float _2367 = RVar[12u].z;
        RVar[12u].w = (RVar[2u].x * dot(vec4(_2332, _2334, _2336, uintBitsToFloat(2147483648u)), vec4(_2340, _2342, _2344, uintBitsToFloat(0u)))) + uintBitsToFloat(0u);
        float _2378 = RVar[6u].x;
        float _2380 = RVar[6u].y;
        float _2382 = RVar[6u].z;
        float _2386 = RVar[13u].x;
        float _2388 = RVar[13u].y;
        float _2390 = RVar[13u].z;
        RVar[12u].y = (RVar[2u].x * dot(vec4(_2355, _2357, _2359, uintBitsToFloat(2147483648u)), vec4(_2363, _2365, _2367, uintBitsToFloat(0u)))) + uintBitsToFloat(0u);
        float _2401 = RVar[4u].z;
        float _2403 = RVar[14u].z;
        float _2411 = RVar[6u].x;
        float _2413 = RVar[14u].x;
        float _2416 = RVar[2u].x;
        float _2421 = RVar[4u].z;
        float _2423 = RVar[16u].z;
        RVar[126u].y = RVar[4u].y * RVar[15u].y;
        RVar[13u].w = (_2416 * dot(vec4(_2378, _2380, _2382, uintBitsToFloat(2147483648u)), vec4(_2386, _2388, _2390, uintBitsToFloat(0u)))) + uintBitsToFloat(0u);
        RVar[127u].x = _2421 * _2423;
        float _2443 = RVar[4u].y;
        float _2445 = RVar[14u].y;
        float _2447 = (_2443 * _2445) + (_2401 * _2403);
        RVar[13u].y = dot(vec4(RVar[6u].z, RVar[6u].y, _2411 * _2413, uintBitsToFloat(2147483648u)), vec4(RVar[14u].z, RVar[14u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[122u].x = _2447;
        float _2459 = RVar[6u].z;
        float _2461 = RVar[15u].z;
        float _2464 = RVar[4u].x;
        float _2466 = RVar[14u].x;
        float _2470 = RVar[4u].z;
        float _2472 = RVar[15u].z;
        float _2474 = RVar[126u].y;
        float _2476 = (_2470 * _2472) + _2474;
        RVar[127u].x = (RVar[4u].y * RVar[16u].y) + RVar[127u].x;
        RVar[124u].w = (_2464 * _2466) + _2447;
        RVar[122u].x = _2476;
        float _2495 = RVar[4u].x;
        float _2497 = RVar[15u].x;
        float _2499 = (_2495 * _2497) + _2476;
        RVar[15u].y = dot(vec4(RVar[6u].x, RVar[6u].y, _2459 * _2461, uintBitsToFloat(2147483648u)), vec4(RVar[15u].x, RVar[15u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[122u].x = _2499;
        float _2509 = RVar[4u].x;
        float _2511 = RVar[16u].x;
        float _2513 = RVar[127u].x;
        float _2515 = (_2509 * _2511) + _2513;
        float _2517 = RVar[2u].y;
        float _2519 = RVar[124u].w;
        float _2521 = RVar[125u].y;
        float _2525 = RVar[6u].z;
        float _2527 = RVar[19u].z;
        float _2530 = RVar[6u].z;
        float _2532 = RVar[16u].z;
        RVar[15u].x = (RVar[2u].y * _2499) + RVar[127u].y;
        RVar[123u].y = _2515;
        RVar[15u].z = (_2517 * _2519) + _2521;
        RVar[15u].w = _2525 * _2527;
        float _2553 = RVar[2u].y;
        float _2555 = RVar[126u].w;
        RVar[16u].w = dot(vec4(RVar[6u].x, RVar[6u].y, _2530 * _2532, uintBitsToFloat(2147483648u)), vec4(RVar[16u].x, RVar[16u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[16u].x = (_2553 * _2515) + _2555;
    }
    if (stateVar == 0)
    {
        float _2573 = RVar[4u].z;
        float _2575 = RVar[19u].z;
        float _2578 = RVar[2u].y;
        float _2580 = RVar[16u].w;
        float _2582 = RVar[12u].y;
        float _2586 = RVar[4u].z;
        float _2588 = RVar[17u].z;
        float _2591 = RVar[6u].x;
        float _2593 = RVar[19u].x;
        float _2595 = RVar[15u].w;
        RVar[126u].x = (RVar[2u].y * RVar[13u].y) + RVar[12u].w;
        RVar[126u].z = (_2578 * _2580) + _2582;
        RVar[127u].x = (_2591 * _2593) + _2595;
        float _2610 = RVar[4u].x;
        float _2612 = RVar[17u].x;
        float _2616 = RVar[4u].z;
        float _2618 = RVar[18u].z;
        float _2621 = RVar[6u].z;
        float _2623 = RVar[18u].z;
        float _2626 = RVar[4u].x;
        float _2628 = RVar[19u].x;
        float _2630 = (_2626 * _2628) + (_2573 * _2575);
        RVar[125u].x = (RVar[2u].y * RVar[15u].y) + RVar[13u].w;
        RVar[127u].y = (_2610 * _2612) + (_2586 * _2588);
        RVar[126u].w = _2621 * _2623;
        RVar[122u].x = _2630;
        float _2650 = RVar[4u].y;
        float _2652 = RVar[19u].y;
        float _2654 = (_2650 * _2652) + _2630;
        RVar[127u].z = dot(vec4(RVar[4u].x, RVar[4u].y, _2616 * _2618, uintBitsToFloat(2147483648u)), vec4(RVar[18u].x, RVar[18u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[122u].x = _2654;
        float _2658 = RVar[6u].x;
        float _2660 = RVar[18u].x;
        float _2662 = RVar[126u].w;
        float _2664 = (_2658 * _2660) + _2662;
        float _2666 = RVar[6u].x;
        float _2668 = RVar[17u].x;
        float _2671 = RVar[4u].y;
        float _2673 = RVar[17u].y;
        float _2675 = RVar[127u].y;
        float _2679 = RVar[2u].z;
        float _2681 = RVar[15u].z;
        RVar[123u].x = _2664;
        RVar[126u].w = (_2671 * _2673) + _2675;
        RVar[11u].x = (_2679 * _2654) + _2681;
        float _2702 = RVar[6u].y;
        float _2704 = RVar[18u].y;
        RVar[124u].w = dot(vec4(RVar[6u].z, RVar[6u].y, _2666 * _2668, uintBitsToFloat(2147483648u)), vec4(RVar[17u].z, RVar[17u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[124u].x = (_2702 * _2704) + _2664;
        float _2710 = RVar[6u].y;
        float _2712 = RVar[19u].y;
        float _2714 = RVar[127u].x;
        float _2716 = (_2710 * _2712) + _2714;
        float _2718 = RVar[2u].z;
        float _2720 = RVar[127u].z;
        float _2722 = RVar[15u].x;
        float _2726 = RVar[2u].z;
        float _2728 = RVar[126u].w;
        float _2730 = RVar[16u].x;
        RVar[123u].y = _2716;
        RVar[11u].z = (_2718 * _2720) + _2722;
        RVar[11u].y = (_2726 * _2728) + _2730;
        float _2743 = RVar[2u].z;
        float _2745 = RVar[124u].w;
        float _2747 = RVar[126u].z;
        float _2751 = RVar[2u].z;
        float _2753 = RVar[124u].x;
        float _2755 = RVar[125u].x;
        RVar[10u].x = (RVar[2u].z * _2716) + RVar[126u].x;
        RVar[10u].y = (_2743 * _2745) + _2747;
        RVar[10u].z = (_2751 * _2753) + _2755;
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
        bool _2791 = floatBitsToInt(RVar[0u].w) == (0);
        predVar = _2791;
        stateVar = _2791 ? 0 : 1;
    }
    if (stateVar == 0)
    {
        float _2800 = RVar[1u].x;
        float _2804 = intBitsToFloat(floatBitsToInt(_2800) * (3));
        RVar[0u].z = _2804;
        float _2815 = RVar[1u].y;
        float _2819 = intBitsToFloat(floatBitsToInt(_2815) * (3));
        RVar[1u].x = intBitsToFloat(floatBitsToInt(_2804) + (2));
        RVar[1u].y = intBitsToFloat(floatBitsToInt(_2804) + (1));
        RVar[1u].w = _2819;
        RVar[0u].x = intBitsToFloat(floatBitsToInt(_2819) + (1));
        RVar[0u].y = intBitsToFloat(floatBitsToInt(_2819) + (2));
    }
    if (stateVar == 0)
    {
        RVar[10u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].z)];
        RVar[11u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].y)];
        RVar[12u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].x)];
        RVar[13u] = CBUFFER_2.values[floatBitsToUint(RVar[1u].w)];
        RVar[1u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].x)];
        RVar[0u] = CBUFFER_2.values[floatBitsToUint(RVar[0u].y)];
    }
    if (stateVar == 0)
    {
        float _2878 = RVar[5u].x;
        float _2880 = RVar[5u].y;
        float _2882 = RVar[5u].z;
        float _2886 = RVar[10u].x;
        float _2888 = RVar[10u].y;
        float _2890 = RVar[10u].z;
        RVar[126u].x = RVar[4u].z * RVar[10u].z;
        float _2901 = RVar[5u].x;
        float _2903 = RVar[5u].y;
        float _2905 = RVar[5u].z;
        float _2909 = RVar[11u].x;
        float _2911 = RVar[11u].y;
        float _2913 = RVar[11u].z;
        RVar[127u].x = RVar[10u].w + dot(vec4(_2878, _2880, _2882, uintBitsToFloat(2147483648u)), vec4(_2886, _2888, _2890, uintBitsToFloat(0u)));
        float _2922 = RVar[5u].x;
        float _2924 = RVar[5u].y;
        float _2926 = RVar[5u].z;
        float _2930 = RVar[12u].x;
        float _2932 = RVar[12u].y;
        float _2934 = RVar[12u].z;
        float _2945 = RVar[4u].z;
        float _2947 = RVar[11u].z;
        float _2950 = RVar[12u].w;
        float _2953 = RVar[2u].x;
        float _2955 = RVar[127u].x;
        float _2958 = RVar[4u].y;
        float _2960 = RVar[10u].y;
        float _2962 = RVar[126u].x;
        RVar[127u].x = RVar[2u].x * (RVar[11u].w + dot(vec4(_2901, _2903, _2905, uintBitsToFloat(2147483648u)), vec4(_2909, _2911, _2913, uintBitsToFloat(0u))));
        RVar[124u].y = _2945 * _2947;
        RVar[127u].w = _2953 * _2955;
        RVar[126u].x = (_2958 * _2960) + _2962;
        float _2970 = RVar[5u].x;
        float _2972 = RVar[5u].y;
        float _2974 = RVar[5u].z;
        float _2978 = RVar[13u].x;
        float _2980 = RVar[13u].y;
        float _2982 = RVar[13u].z;
        RVar[127u].y = RVar[2u].x * (_2950 + dot(vec4(_2922, _2924, _2926, uintBitsToFloat(2147483648u)), vec4(_2930, _2932, _2934, uintBitsToFloat(0u))));
        float _2991 = RVar[5u].x;
        float _2993 = RVar[5u].y;
        float _2995 = RVar[5u].z;
        float _2999 = RVar[1u].x;
        float _3001 = RVar[1u].y;
        float _3003 = RVar[1u].z;
        RVar[126u].y = RVar[13u].w + dot(vec4(_2970, _2972, _2974, uintBitsToFloat(2147483648u)), vec4(_2978, _2980, _2982, uintBitsToFloat(0u)));
        float _3012 = RVar[5u].x;
        float _3014 = RVar[5u].y;
        float _3016 = RVar[5u].z;
        float _3020 = RVar[0u].x;
        float _3022 = RVar[0u].y;
        float _3024 = RVar[0u].z;
        RVar[125u].y = RVar[1u].w + dot(vec4(_2991, _2993, _2995, uintBitsToFloat(2147483648u)), vec4(_2999, _3001, _3003, uintBitsToFloat(0u)));
        float _3037 = RVar[127u].x;
        float _3041 = RVar[127u].w;
        float _3045 = RVar[0u].w;
        float _3048 = RVar[2u].y;
        float _3050 = RVar[126u].y;
        RVar[127u].x = RVar[127u].y + uintBitsToFloat(0u);
        RVar[127u].y = _3037 + uintBitsToFloat(0u);
        float _3056 = RVar[2u].y;
        float _3059 = RVar[4u].x;
        float _3061 = RVar[10u].x;
        float _3063 = RVar[126u].x;
        float _3067 = RVar[2u].y;
        float _3069 = RVar[125u].y;
        float _3072 = RVar[4u].z;
        float _3074 = RVar[12u].z;
        RVar[22u].x = (_3041 + uintBitsToFloat(0u)) + (_3048 * _3050);
        RVar[126u].z = (_3059 * _3061) + _3063;
        RVar[126u].x = _3072 * _3074;
        float _3088 = RVar[127u].y;
        float _3091 = RVar[127u].x;
        float _3094 = RVar[6u].z;
        float _3096 = RVar[11u].z;
        float _3099 = RVar[6u].z;
        float _3101 = RVar[10u].z;
        RVar[127u].x = (RVar[4u].x * RVar[11u].x) + RVar[124u].y;
        RVar[22u].y = _3088 + (_3067 * _3069);
        RVar[22u].z = _3091 + (_3056 * (_3045 + dot(vec4(_3012, _3014, _3016, uintBitsToFloat(2147483648u)), vec4(_3020, _3022, _3024, uintBitsToFloat(0u)))));
        float _3121 = RVar[6u].y;
        float _3123 = RVar[11u].y;
        float _3125 = (_3121 * _3123) + (_3094 * _3096);
        RVar[124u].y = dot(vec4(RVar[6u].x, RVar[6u].y, _3099 * _3101, uintBitsToFloat(2147483648u)), vec4(RVar[10u].x, RVar[10u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[122u].x = _3125;
        float _3129 = RVar[6u].z;
        float _3131 = RVar[12u].z;
        float _3142 = RVar[6u].z;
        float _3144 = RVar[13u].z;
        float _3147 = RVar[6u].x;
        float _3149 = RVar[11u].x;
        float _3153 = RVar[4u].y;
        float _3155 = RVar[13u].y;
        RVar[127u].y = (RVar[4u].y * RVar[11u].y) + RVar[127u].x;
        RVar[127u].z = _3142 * _3144;
        RVar[127u].w = (_3147 * _3149) + _3125;
        RVar[127u].x = _3153 * _3155;
        float _3162 = RVar[4u].x;
        float _3164 = RVar[4u].y;
        float _3166 = RVar[126u].x;
        float _3170 = RVar[12u].x;
        float _3172 = RVar[12u].y;
        float _3178 = RVar[6u].y;
        float _3180 = RVar[12u].y;
        float _3182 = (_3178 * _3180) + (_3129 * _3131);
        RVar[122u].x = _3182;
        float _3193 = RVar[6u].x;
        float _3195 = RVar[12u].x;
        float _3197 = (_3193 * _3195) + _3182;
        float _3199 = RVar[2u].x;
        float _3201 = RVar[126u].z;
        float _3206 = RVar[2u].x;
        float _3208 = RVar[127u].y;
        float _3213 = RVar[2u].x;
        RVar[126u].x = (RVar[6u].y * RVar[13u].y) + RVar[127u].z;
        RVar[123u].y = _3197;
        RVar[127u].z = (_3199 * _3201) + uintBitsToFloat(0u);
        RVar[126u].w = (_3206 * _3208) + uintBitsToFloat(0u);
        RVar[125u].z = (_3213 * dot(vec4(_3162, _3164, _3166, uintBitsToFloat(2147483648u)), vec4(_3170, _3172, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)))) + uintBitsToFloat(0u);
        float _3230 = RVar[2u].x;
        float _3235 = RVar[2u].x;
        float _3237 = RVar[127u].w;
        float _3242 = RVar[4u].z;
        float _3244 = RVar[1u].z;
        float _3247 = RVar[4u].z;
        float _3249 = RVar[13u].z;
        float _3251 = RVar[127u].x;
        float _3253 = (_3247 * _3249) + _3251;
        RVar[124u].x = (RVar[2u].x * RVar[124u].y) + uintBitsToFloat(0u);
        RVar[124u].y = (_3230 * _3197) + uintBitsToFloat(0u);
        RVar[124u].z = (_3235 * _3237) + uintBitsToFloat(0u);
        RVar[122u].x = _3253;
        float _3265 = RVar[4u].z;
        float _3267 = RVar[0u].z;
        float _3270 = RVar[6u].y;
        float _3272 = RVar[1u].y;
        float _3275 = RVar[6u].z;
        float _3277 = RVar[0u].z;
        float _3280 = RVar[4u].y;
        float _3282 = RVar[1u].y;
        RVar[125u].x = (RVar[4u].x * RVar[13u].x) + _3253;
        RVar[127u].w = _3275 * _3277;
        RVar[127u].x = (_3280 * _3282) + (_3242 * _3244);
        float _3303 = RVar[6u].z;
        float _3305 = RVar[1u].z;
        float _3307 = (_3303 * _3305) + (_3270 * _3272);
        RVar[126u].z = dot(vec4(RVar[4u].x, RVar[4u].y, _3265 * _3267, uintBitsToFloat(2147483648u)), vec4(RVar[0u].x, RVar[0u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[122u].x = _3307;
        float _3327 = RVar[6u].x;
        float _3329 = RVar[1u].x;
        RVar[0u].x = dot(vec4(RVar[6u].x, RVar[6u].y, RVar[127u].w, uintBitsToFloat(2147483648u)), vec4(RVar[0u].x, RVar[0u].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[125u].w = (_3327 * _3329) + _3307;
        RVar[127u].w = (RVar[4u].x * RVar[1u].x) + RVar[127u].x;
        float _3344 = RVar[6u].x;
        float _3346 = RVar[13u].x;
        float _3348 = RVar[126u].x;
        float _3350 = (_3344 * _3346) + _3348;
        RVar[123u].y = _3350;
        float _3361 = RVar[2u].y;
        float _3363 = RVar[127u].w;
        float _3365 = RVar[126u].w;
        float _3369 = RVar[2u].y;
        float _3371 = RVar[126u].z;
        float _3373 = RVar[125u].z;
        float _3377 = RVar[2u].y;
        float _3379 = RVar[124u].x;
        RVar[11u].x = (RVar[2u].y * RVar[125u].x) + RVar[127u].z;
        RVar[11u].y = (_3361 * _3363) + _3365;
        RVar[11u].z = (_3369 * _3371) + _3373;
        RVar[10u].x = (_3377 * _3350) + _3379;
        float _3395 = RVar[2u].y;
        float _3397 = RVar[0u].x;
        float _3399 = RVar[124u].y;
        RVar[10u].y = (RVar[2u].y * RVar[125u].w) + RVar[124u].z;
        RVar[10u].z = (_3395 * _3397) + _3399;
    }
    if (stackVar[stackIdxVar - 1] == 0)
    {
        stateVar = int(stateVar == 0);
    }
    if (stateVar == 0)
    {
        float _3421 = RVar[10u].y;
        float _3423 = RVar[10u].z;
        RVar[22u].x = RVar[10u].x;
        RVar[22u].y = _3421;
        RVar[22u].z = _3423;
        float _3430 = RVar[10u].y;
        float _3432 = RVar[10u].z;
        RVar[11u].x = RVar[10u].x;
        RVar[11u].y = _3430;
        RVar[11u].z = _3432;
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
        RVar[127u].y = dot(vec4(RVar[22u].x, RVar[22u].y, RVar[22u].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[3].x, CBUFFER_3.values[3].y, CBUFFER_3.values[3].z, uintBitsToFloat(0u)));
        RVar[2u].z = uintBitsToFloat(1065353216u);
        RVar[127u].w = dot(vec4(RVar[22u].x, RVar[22u].y, RVar[22u].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[4].x, CBUFFER_3.values[4].y, CBUFFER_3.values[4].z, uintBitsToFloat(0u)));
        RVar[4u].z = uintBitsToFloat(1065353216u);
        RVar[126u].w = dot(vec4(RVar[22u].x, RVar[22u].y, RVar[22u].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[5].x, CBUFFER_3.values[5].y, CBUFFER_3.values[5].z, uintBitsToFloat(0u)));
        RVar[6u].z = uintBitsToFloat(1065353216u);
        float _3535 = RVar[11u].z;
        float _3537 = RVar[11u].z;
        RVar[125u].w = dot(vec4(RVar[22u].x, RVar[22u].y, RVar[22u].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[6].x, CBUFFER_3.values[6].y, CBUFFER_3.values[6].z, uintBitsToFloat(0u)));
        float _3548 = RVar[127u].w;
        float _3551 = RVar[10u].z;
        float _3553 = RVar[10u].z;
        float _3556 = RVar[11u].y;
        float _3558 = RVar[11u].y;
        float _3560 = (_3556 * _3558) + (_3535 * _3537);
        RVar[1u].x = CBUFFER_3.values[3].w + RVar[127u].y;
        RVar[1u].y = CBUFFER_3.values[4].w + _3548;
        RVar[122u].x = _3560;
        float _3565 = RVar[11u].x;
        float _3567 = RVar[11u].x;
        float _3569 = (_3565 * _3567) + _3560;
        float _3573 = RVar[126u].w;
        float _3578 = RVar[125u].w;
        float _3581 = RVar[10u].y;
        float _3583 = RVar[10u].y;
        float _3585 = (_3581 * _3583) + (_3551 * _3553);
        RVar[123u].x = _3569;
        RVar[1u].z = CBUFFER_3.values[5].w + _3573;
        RVar[1u].w = CBUFFER_3.values[6].w + _3578;
        RVar[122u].x = _3585;
        float _3608 = RVar[10u].x;
        float _3610 = RVar[10u].x;
        RVar[0u].x = intBitsToFloat(floatBitsToInt(CBUFFER_4.values[0].x) + (25));
        RVar[0u].y = intBitsToFloat(floatBitsToInt(CBUFFER_4.values[0].x) + (41));
        RVar[0u].z = (_3608 * _3610) + _3585;
        RVar[0u].w = intBitsToFloat(floatBitsToInt(CBUFFER_4.values[0].x) + (33));
        RVar[2u].w = inversesqrt(_3569);
    }
    if (stateVar == 0)
    {
        RVar[2u] = vec4(CBUFFER_3.values[floatBitsToUint(RVar[0u].w)].x, RVar[2u].y, RVar[2u].z, RVar[2u].w);
        RVar[4u] = vec4(CBUFFER_3.values[floatBitsToUint(RVar[0u].y)].x, RVar[4u].y, RVar[4u].z, RVar[4u].w);
        uint _3649 = floatBitsToUint(RVar[0u].x);
        RVar[5u] = vec4(CBUFFER_3.values[_3649].x, CBUFFER_3.values[_3649].y, CBUFFER_3.values[_3649].z, RVar[5u].w);
    }
    vec4 _3671 = (RVar[1u] * vec4(VS_PUSH.posMulAdd.xy, 1.0, 1.0)) + vec4(VS_PUSH.posMulAdd.zw, 0.0, 0.0);
    vec4 _3674 = _3671;
    _3674.y = -_3671.y;
    vec4 _3682 = _3674;
    _3682.z = (_3674.z + (_3674.w * VS_PUSH.zSpaceMul.x)) * VS_PUSH.zSpaceMul.y;
    gl_Position = _3682;
    PARAM_0 = RVar[3u];
    if (stateVar == 0)
    {
        float _3697 = RVar[11u].y;
        float _3699 = RVar[2u].w;
        float _3702 = RVar[11u].z;
        float _3704 = RVar[2u].w;
        float _3707 = RVar[22u].z;
        float _3712 = RVar[0u].z;
        float _3713 = inversesqrt(_3712);
        RVar[125u].x = RVar[11u].x * RVar[2u].w;
        RVar[125u].y = _3697 * _3699;
        RVar[126u].z = _3702 * _3704;
        float _3718 = RVar[10u].x;
        float _3719 = _3718 * _3713;
        float _3721 = RVar[10u].y;
        float _3722 = _3721 * _3713;
        float _3724 = RVar[10u].z;
        float _3725 = _3724 * _3713;
        float _3727 = RVar[2u].z;
        float _3732 = RVar[22u].y;
        float _3736 = (_3732 * CBUFFER_3.values[2].y) + (_3707 * CBUFFER_3.values[2].z);
        RVar[127u].x = _3719;
        RVar[127u].y = _3722;
        RVar[127u].z = _3725;
        RVar[122u].x = _3736;
        float _3742 = RVar[125u].y;
        float _3745 = RVar[126u].z;
        float _3748 = RVar[125u].x;
        float _3751 = RVar[22u].x;
        float _3755 = (_3751 * CBUFFER_3.values[2].x) + _3736;
        float _3757 = RVar[2u].z;
        float _3761 = (_3757 * CBUFFER_4.values[1].z) + (_3727 * CBUFFER_4.values[1].w);
        RVar[123u].w = _3755;
        RVar[122u].x = _3761;
        float _3765 = RVar[127u].z;
        float _3768 = RVar[125u].x;
        float _3770 = ((-_3765) * _3768) + (_3745 * _3719);
        float _3772 = RVar[127u].y;
        float _3775 = RVar[126u].z;
        float _3777 = ((-_3772) * _3775) + (_3742 * _3725);
        float _3782 = RVar[127u].x;
        float _3785 = RVar[125u].y;
        float _3787 = ((-_3782) * _3785) + (_3748 * _3722);
        float _3790 = RVar[7u].y;
        float _3794 = (_3790 * CBUFFER_4.values[1].y) + _3761;
        RVar[123u].x = _3770;
        RVar[123u].y = _3777;
        RVar[123u].w = _3787;
        RVar[122u].x = _3794;
        float _3803 = RVar[6u].w;
        float _3807 = RVar[2u].x;
        float _3811 = RVar[6u].w;
        float _3814 = RVar[7u].x;
        RVar[126u].x = RVar[6u].w * _3777;
        RVar[126u].y = _3803 * _3770;
        RVar[126u].w = _3811 * _3787;
        RVar[0u].x = (_3814 * CBUFFER_4.values[1].x) + _3794;
        float _3836 = RVar[4u].x;
        RVar[0u].y = dot(vec4(RVar[7u].x, RVar[7u].y, RVar[2u].z, RVar[2u].z), CBUFFER_4.values[2]);
        RVar[5u].w = clamp(((-(CBUFFER_3.values[2].w + _3755)) + (-_3807)) * _3836, 0.0, 1.0);
        RVar[1u].x = dot(vec4(RVar[8u].x, RVar[8u].y, RVar[4u].z, RVar[4u].z), CBUFFER_4.values[4]);
        RVar[1u].y = dot(vec4(RVar[8u].x, RVar[8u].y, RVar[4u].z, RVar[4u].z), CBUFFER_4.values[5]);
        RVar[2u].x = dot(vec4(RVar[9u].x, RVar[9u].y, RVar[6u].z, RVar[6u].z), CBUFFER_4.values[7]);
        RVar[2u].y = dot(vec4(RVar[9u].x, RVar[9u].y, RVar[6u].z, RVar[6u].z), CBUFFER_4.values[8]);
        float _3915 = RVar[126u].w;
        RVar[3u].x = dot(vec4(RVar[127u].x, RVar[127u].y, RVar[127u].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[0].x, CBUFFER_3.values[0].y, CBUFFER_3.values[0].z, uintBitsToFloat(0u)));
        float _3935 = RVar[126u].z;
        RVar[3u].y = dot(vec4(RVar[126u].x, RVar[126u].y, _3915 * CBUFFER_3.values[0].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[0].x, CBUFFER_3.values[0].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        float _3955 = RVar[127u].z;
        RVar[3u].z = dot(vec4(RVar[125u].x, RVar[125u].y, _3935 * CBUFFER_3.values[0].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[0].x, CBUFFER_3.values[0].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        float _3975 = RVar[126u].w;
        RVar[4u].x = dot(vec4(RVar[127u].x, RVar[127u].y, _3955 * CBUFFER_3.values[1].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[1].x, CBUFFER_3.values[1].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        float _3995 = RVar[126u].z;
        RVar[4u].y = dot(vec4(RVar[126u].x, RVar[126u].y, _3975 * CBUFFER_3.values[1].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[1].x, CBUFFER_3.values[1].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        float _4015 = RVar[127u].z;
        RVar[4u].z = dot(vec4(RVar[125u].x, RVar[125u].y, _3995 * CBUFFER_3.values[1].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[1].x, CBUFFER_3.values[1].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        float _4035 = RVar[126u].w;
        RVar[6u].x = dot(vec4(RVar[127u].x, RVar[127u].y, _4015 * CBUFFER_3.values[2].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[2].x, CBUFFER_3.values[2].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        float _4055 = RVar[126u].z;
        RVar[6u].y = dot(vec4(RVar[126u].x, RVar[126u].y, _4035 * CBUFFER_3.values[2].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[2].x, CBUFFER_3.values[2].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
        RVar[6u].z = dot(vec4(RVar[125u].x, RVar[125u].y, _4055 * CBUFFER_3.values[2].z, uintBitsToFloat(2147483648u)), vec4(CBUFFER_3.values[2].x, CBUFFER_3.values[2].y, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)));
    }
    PARAM_1 = RVar[5u];
    PARAM_2 = RVar[4u];
    PARAM_3 = RVar[6u];
    PARAM_4 = RVar[3u];
    PARAM_5 = vec4(RVar[0u].x, RVar[0u].y, RVar[0u].z, RVar[0u].z);
    PARAM_6 = vec4(RVar[1u].x, RVar[1u].y, RVar[1u].z, RVar[1u].z);
    PARAM_7 = vec4(RVar[2u].x, RVar[2u].y, RVar[2u].z, RVar[2u].z);
    if (stateVar == 0)
    {
    }
}

 