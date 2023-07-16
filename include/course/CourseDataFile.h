#pragma once

#include <course/Constants.h>

#include <array>
#include <vector>

#include <span>

struct CourseDataFileHeader
{
    struct Block
    {
        u32 offset;
        u32 size;
    };

    const void* getBlock(u32 index) const
    {
        RIO_ASSERT(index < CD_FILE_BLOCK_NUM);

        u32 size = CD_FILE_READ_32_BE(blocks[index].size);
        if (size == 0)
            return nullptr;

        u32 offset = CD_FILE_READ_32_BE(blocks[index].offset);
        return (const void*)((uintptr_t)this + offset);
    }

    u32 getBlockOffset(u32 index) const
    {
        RIO_ASSERT(index < CD_FILE_BLOCK_NUM);
        return CD_FILE_READ_32_BE(blocks[index].offset);
    }

    u32 getBlockSize(u32 index) const
    {
        RIO_ASSERT(index < CD_FILE_BLOCK_NUM);
        return CD_FILE_READ_32_BE(blocks[index].size);
    }

    union
    {
        Block blocks[CD_FILE_BLOCK_NUM];
        struct
        {
            Block   environment;        // 1
            Block   options;            // 2
            Block   scroll_data;        // 3
            Block   _block4;            // 4
            Block   distant_view_data;  // 5
            Block   _block6;            // 6
            Block   next_goto;          // 7
            Block   sprite;             // 8
            Block   sprite_load_res;    // 9
            Block   area_data;          // 10
            Block   location;           // 11
            Block   _block12;           // 12
            Block   _block13;           // 13
            Block   rail;               // 14
            Block   rail_point;         // 15
        };
    };

    // Blocks' data...
};
static_assert(sizeof(CourseDataFileHeader) == 0x78);

struct Environment
{
    // Some functions in the game call it environment.

    char tileset_name[CD_FILE_ENV_MAX_NUM][CD_FILE_TS_NAME_MAX_LEN];
};
static_assert(sizeof(Environment) == 0x80);

struct Options
{
    // Official name not known, but is called area options by the modding community.

    u32 def_events[2];  // Not u64
    u16 loop;
    u16 time_0;
    u8  _unused0[4];
    u8  start_next_goto;
    u8  _unused1[2];
    u8  start_next_goto_coin_boost;
    u16 time_1;
    u16 time_2;
};
static_assert(sizeof(Options) == 0x18);

struct ScrollData
{
    // Is the official name. Called bounding by the modding community.

    struct
    {
        s32 upper;
        s32 lower;
    }   bound[2];       // 0: Main, 1: Lakitu
    u16 id;
    u16 flag;           // 0-14: Multiplayer Screen Height Adjust, 15: Enable Upward Scrolling
    struct
    {
        s16 upper;
        s16 lower;
    }   mp_bound_adjust;
    u8  _unused0[4];
};
static_assert(sizeof(ScrollData) == 0x1C);

struct DistantViewData
{
    // Not certain if official name, but official name in NSMBW is Bg (which is conflicting with tile layers)

    u16     id;
    struct
    {
        s16 x;
        s16 y;
        s16 z;
    }       offset;                             // Unused
    char    name[CD_FILE_DV_NAME_MAX_LEN + 1];
    u8      parallax_mode;                      // Unused
    u8      _pad[2];
};
static_assert(sizeof(DistantViewData) == 0x1C);

struct NextGoto
{
    // Is the official name. Called entrance by the modding community.

    struct
    {
        u16 x;
        u16 y;
    }   offset;
    struct
    {
        u16 x;
        u16 y;
    }   camera_offset;
    u8  id;
    struct
    {
        u8  file;
        u8  next_goto;
    }   destination;
    u8  type;
    u8  mp_spawn_flag;
    u8  area;
    u8  _unused0;
    u8  mp_inner_gap;
    u16 flag;
    u8  chibi_yoshi_next_goto;
    u8  coin_edit_priority;
    struct
    {
        u8 info;
        u8 point;
    } rail;
    u8  wipe_type;
    u8  _pad[1];
};
static_assert(sizeof(NextGoto) == 0x18);

struct Sprite
{
    // Official name not known.

    u16 id;
    struct
    {
        u16 x;
        u16 y;
    }   offset;
    u16 event_id;       // Lower byte: event id 2, higher byte: event id 1.
    u32 settings[2];    // Not u64
    u8  area;
    u8  layer;
    u8  movement_id;
    u8  link_id;
    u8  init_state;
    u8  _pad[3];
};
static_assert(sizeof(Sprite) == 0x18);

struct AreaData
{
    // Is the official name. Called zone by the modding community.

    // NSMBW
    struct
    {
        u16 x;
        u16 y;
    }   offset;
    struct
    {
        u16 x;
        u16 y;
    }   size;
    u16 color_obj;      // "Theme", unused.
    u16 color_bg;       // "Terrain", unused.
    u8  id;
    u8  scroll;
    u8  zoom_type;
    u8  zoom_id;
    u8  zoom_change;
    u8  mask;
    u8  bg2;            // 1st BG id in NSMBW, DV ID in NSMBU.
    u8  bg3;            // 2nd BG id in NSMBW, unused.
    u8  direction;
    u8  _15;
    u8  bgm;
    u8  bgm_mode;

    // NSMB2
    u8  dv;             // DV ID in NSMB2, unused.

    // NSMBU
    u8  flag;
    u8  _pad[2];
};
static_assert(sizeof(AreaData) == 0x1C);

struct Location
{
    // Official name not known.

    struct
    {
        u16 x;
        u16 y;
    }   offset;
    struct
    {
        u16 x;
        u16 y;
    }   size;
    u8  id;
    u8  _pad[3];
};
static_assert(sizeof(Location) == 0xC);

struct RailInfo
{
    // Not certain if official name.

    u8  id;
    s8  _1;
    struct
    {
        u16 start;
        u16 num;
    }   point;
    u16 flag;
    u32 _8;
};
static_assert(sizeof(RailInfo) == 0xC);

struct RailPoint
{
    // Official name not known.

    struct
    {
        u16 x;
        u16 y;
    }   offset;
    f32 speed;
    f32 accel;
    s16 delay;

    // Nabbit-related
    u16 _e;
    u8  _10;
    u8  _11;
    u8  _12;
    u8  _pad[1];
};
static_assert(sizeof(RailPoint) == 0x14);

struct BgCourseData
{
    u16 type;
    struct
    {
        u16 x;
        u16 y;
    }   offset;
    struct
    {
        u16 x;
        u16 y;
    }   size;
    u8  flag;
    u8  _pad[5];
};
static_assert(sizeof(BgCourseData) == 0x10);

class CourseDataFile
{
    // Is the official name. Called area by the modding community.

public:
    CourseDataFile();
    ~CourseDataFile();

    void load(
        u32 id,
        const void* file,
        const void* bgdat_L0 = nullptr,
        const void* bgdat_L1 = nullptr,
        const void* bgdat_L2 = nullptr
    );

    std::array<std::span<u8>, 4> save() const
    {
        return {
            saveFile_(),
            saveBgDat_(LAYER_0),
            saveBgDat_(LAYER_1),
            saveBgDat_(LAYER_2)
        };
    }

private:
    void loadFile_(const CourseDataFileHeader* p_header);
    void loadBgDat_(u8 layer, const BgCourseData* bgdat);

    std::span<u8> saveFile_() const;
    std::span<u8> saveBgDat_(u8 layer) const;

public:
    void clear();

    bool isValid() const
    {
        return mID >= 0 && mID < CD_FILE_MAX_NUM;
    }

    s32 getID() const
    {
        return mID;
    }

    const char* getEnvironment(u32 index) const
    {
        RIO_ASSERT(index < CD_FILE_ENV_MAX_NUM);
        return mEnvironment.tileset_name[index];
    }
    void setEnvironment(u32 index, const char* name);

    Options& getOptions()
    {
        return mOptions;
    }
    const Options& getOptions() const
    {
        return mOptions;
    }

    std::vector<ScrollData>& getScrollData()
    {
        return mScrollData;
    }
    const std::vector<ScrollData>& getScrollData() const
    {
        return mScrollData;
    }

    std::vector<DistantViewData>& getDistantViewData()
    {
        return mDistantViewData;
    }
    const std::vector<DistantViewData>& getDistantViewData() const
    {
        return mDistantViewData;
    }

    std::vector<NextGoto>& getNextGoto()
    {
        return mNextGoto;
    }
    const std::vector<NextGoto>& getNextGoto() const
    {
        return mNextGoto;
    }

    std::vector<Sprite>& getSprite()
    {
        return mSprite;
    }
    const std::vector<Sprite>& getSprite() const
    {
        return mSprite;
    }

    /*
    u8 getAreaID(u8 area) const
    u8 getAreaScroll(u8 area) const
    u8 getAreaZoomType(u8 area) const
    u8 getAreaZoomID(u8 area) const
    u8 getAreaZoomChange(u8 area) const
    u8 getAreaBgm(u8 area) const
    u8 getAreaBgmMode(u8 area) const
    u8 getAreaMaskNo(u8 area) const
    u8 getAreaBg2(u8 area) const
    u8 getAreaBg3(u8 area) const
    u16 getAreaColorOBJ(u8 area) const
    u16 getAreaColorBG(u8 area) const
    u8 getAreaDirection(u8 area) const
    u16 getAreaOffsetX(u8 area) const
    u16 getAreaOffsetY(u8 area) const
    u16 getAreaSizeX(u8 area) const
    u16 getAreaSizeY(u8 area) const
    */
    std::vector<AreaData>& getAreaData()
    {
        return mAreaData;
    }
    const std::vector<AreaData>& getAreaData() const
    {
        return mAreaData;
    }

    std::vector<Location>& getLocation()
    {
        return mLocation;
    }
    const std::vector<Location>& getLocation() const
    {
        return mLocation;
    }

    std::vector<RailInfo>& getRailInfo()
    {
        return mRailInfo;
    }
    const std::vector<RailInfo>& getRailInfo() const
    {
        return mRailInfo;
    }

    std::vector<RailPoint>& getRailPoint()
    {
        return mRailPoint;
    }
    const std::vector<RailPoint>& getRailPoint() const
    {
        return mRailPoint;
    }

    std::vector<BgCourseData>& getBgData(u8 layer)
    {
        RIO_ASSERT(layer < CD_FILE_LAYER_MAX_NUM);
        return mBgData[layer];
    }
    const std::vector<BgCourseData>& getBgData(u8 layer) const
    {
        RIO_ASSERT(layer < CD_FILE_LAYER_MAX_NUM);
        return mBgData[layer];
    }

private:
    s32 mID;

    // Bg data for each layer
    std::array<std::vector<BgCourseData>, CD_FILE_LAYER_MAX_NUM> mBgData;

    // Blocks
    Environment                     mEnvironment;       // 1
    Options                         mOptions;           // 2
    std::vector<ScrollData>         mScrollData;        // 3
                                                        // 4
    std::vector<DistantViewData>    mDistantViewData;   // 5
                                                        // 6
    std::vector<NextGoto>           mNextGoto;          // 7
    std::vector<Sprite>             mSprite;            // 8
                                                        // 9 (List of used sprites' ids)
    std::vector<AreaData>           mAreaData;          // 10
    std::vector<Location>           mLocation;          // 11
                                                        // 12
                                                        // 13
    std::vector<RailInfo>           mRailInfo;          // 14
    std::vector<RailPoint>          mRailPoint;         // 15
};
