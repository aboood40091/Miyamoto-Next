#pragma once

#include <misc/rio_Types.h>

enum LayerID
{
    LAYER_ID_GATHER         =  0,

    // BgTexMgr & CoinOrigin
    LAYER_ID_BG_PREPARE     = -1,

    // CourseView
    LAYER_ID_DISTANT_VIEW   = -2,
    LAYER_ID_3D             = -3,

    LAYER_ID_DISPOSE        = -4
};
