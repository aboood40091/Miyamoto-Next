#pragma once

#include <misc/rio_Types.h>

enum LayerID
{
    LAYER_ID_GATHER         =  0,

    // BgTexMgr & CoinOrigin
    LAYER_ID_BG_PREPARE     = -1,

    // CourseView
    LAYER_ID_DISTANT_VIEW_0 = -2,
    LAYER_ID_3D             = -66, // -(2 + 64)

    LAYER_ID_DISPOSE        = -67
};
