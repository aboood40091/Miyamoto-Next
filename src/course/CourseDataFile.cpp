#include <course/CourseDataFile.h>

#include <misc/rio_MemUtil.h>

#include <cstring>
#include <set>

namespace {

inline void CD_FILE_COPY_32_BE(void* dst, const void* src)
{
    *static_cast<u32*>(dst) = CD_FILE_READ_32_BE(*static_cast<const u32*>(src));
}

}

CourseDataFile::CourseDataFile()
    : mID(-1)
{
}

void CourseDataFile::load(
    u32 id,
    const void* file,
    const void* bgdat_L0,
    const void* bgdat_L1,
    const void* bgdat_L2
)
{
    RIO_ASSERT(id < CD_FILE_MAX_NUM);

    // Clear it
    clear();

    // If file if nullptr, return
    if (!file)
        return;

    mID = id;

    loadFile_((const CourseDataFileHeader*)file);

    loadBgDat_(LAYER_0, (const BgCourseData*)bgdat_L0);
    loadBgDat_(LAYER_1, (const BgCourseData*)bgdat_L1);
    loadBgDat_(LAYER_2, (const BgCourseData*)bgdat_L2);
}

void CourseDataFile::loadFile_(const CourseDataFileHeader* p_header)
{
    // Block 1
    {
        const Environment* p_src = (const Environment*)p_header->getBlock(CD_FILE_BLOCK_ENVIRONMENT);
        RIO_ASSERT(p_src != nullptr);
        {
            rio::MemUtil::copy(&mEnvironment, p_src, sizeof(Environment));
        }
    }

    // Block 2
    {
        const Options* p_src = (const Options*)p_header->getBlock(CD_FILE_BLOCK_OPTIONS);
        RIO_ASSERT(p_src != nullptr);
        {
            mOptions.def_events[0]              = CD_FILE_READ_32_BE(p_src->def_events[0]);
            mOptions.def_events[1]              = CD_FILE_READ_32_BE(p_src->def_events[1]);
            mOptions.loop                       = CD_FILE_READ_16_BE(p_src->loop);
            mOptions.time_0                     = CD_FILE_READ_16_BE(p_src->time_0);
            mOptions._unused0[0]                = p_src->_unused0[0];
            mOptions._unused0[1]                = p_src->_unused0[1];
            mOptions._unused0[2]                = p_src->_unused0[2];
            mOptions._unused0[3]                = p_src->_unused0[3];
            mOptions.start_next_goto            = p_src->start_next_goto;
            mOptions._unused1[0]                = p_src->_unused1[0];
            mOptions._unused1[1]                = p_src->_unused1[1];
            mOptions.start_next_goto_coin_boost = p_src->start_next_goto_coin_boost;
            mOptions.time_1                     = CD_FILE_READ_16_BE(p_src->time_1);
            mOptions.time_2                     = CD_FILE_READ_16_BE(p_src->time_2);
        }
    }

    // Block 3
    {
        u32 size = p_header->getBlockSize(CD_FILE_BLOCK_SCROLL_DATA);
        RIO_ASSERT(size % sizeof(ScrollData) == 0);
        u32 count = size / sizeof(ScrollData);

        mScrollData.resize(count);

        const ScrollData* p_src = (const ScrollData*)p_header->getBlock(CD_FILE_BLOCK_SCROLL_DATA);

        for (u32 i = 0; i < count; i++)
        {
            const ScrollData&   src = p_src[i];
            ScrollData&         dst = mScrollData[i];

            dst.bound[0].upper         = CD_FILE_READ_32_BE(src.bound[0].upper);
            dst.bound[0].lower         = CD_FILE_READ_32_BE(src.bound[0].lower);
            dst.bound[1].upper         = CD_FILE_READ_32_BE(src.bound[1].upper);
            dst.bound[1].lower         = CD_FILE_READ_32_BE(src.bound[1].lower);
            dst.id                     = CD_FILE_READ_16_BE(src.id);
            dst.flag                   = CD_FILE_READ_16_BE(src.flag);
            dst.mp_bound_adjust.upper  = CD_FILE_READ_16_BE(src.mp_bound_adjust.upper);
            dst.mp_bound_adjust.lower  = CD_FILE_READ_16_BE(src.mp_bound_adjust.lower);
        }
    }

    // Block 5
    {
        u32 size = p_header->getBlockSize(CD_FILE_BLOCK_DISTANT_VIEW_DATA);
        RIO_ASSERT(size % sizeof(DistantViewData) == 0);
        u32 count = size / sizeof(DistantViewData);

        mDistantViewData.resize(count);

        const DistantViewData* p_src = (const DistantViewData*)p_header->getBlock(CD_FILE_BLOCK_DISTANT_VIEW_DATA);

        for (u32 i = 0; i < count; i++)
        {
            const DistantViewData&  src = p_src[i];
            DistantViewData&        dst = mDistantViewData[i];

            dst.id              = CD_FILE_READ_16_BE(src.id);
            dst.offset.x        = CD_FILE_READ_16_BE(src.offset.x);
            dst.offset.y        = CD_FILE_READ_16_BE(src.offset.y);
            dst.offset.z        = CD_FILE_READ_16_BE(src.offset.z);

            rio::MemUtil::copy(dst.name, src.name, CD_FILE_DV_NAME_MAX_LEN);
            dst.name[CD_FILE_DV_NAME_MAX_LEN] = '\0';

            dst.parallax_mode   = src.parallax_mode;
        }
    }

    // Block 7
    {
        u32 size = p_header->getBlockSize(CD_FILE_BLOCK_NEXT_GOTO);
        RIO_ASSERT(size % sizeof(NextGoto) == 0);
        u32 count = size / sizeof(NextGoto);

        mNextGoto.resize(count);

        const NextGoto* p_src = (const NextGoto*)p_header->getBlock(CD_FILE_BLOCK_NEXT_GOTO);

        for (u32 i = 0; i < count; i++)
        {
            const NextGoto& src = p_src[i];
            NextGoto&       dst = mNextGoto[i];

            dst.offset.x                = CD_FILE_READ_16_BE(src.offset.x);
            dst.offset.y                = CD_FILE_READ_16_BE(src.offset.y);
            dst.camera_offset.x         = CD_FILE_READ_16_BE(src.camera_offset.x);
            dst.camera_offset.y         = CD_FILE_READ_16_BE(src.camera_offset.y);
            dst.id                      = src.id;
            dst.destination.file        = src.destination.file;
            dst.destination.next_goto   = src.destination.next_goto;
            dst.type                    = src.type;
            dst.mp_spawn_flag           = src.mp_spawn_flag;
            dst.area                    = src.area;
            dst.mp_inner_gap            = src.mp_inner_gap;
            dst.flag                    = CD_FILE_READ_16_BE(src.flag);
            dst.chibi_yoshi_next_goto   = src.chibi_yoshi_next_goto;
            dst.coin_edit_priority      = src.coin_edit_priority;
            dst.rail.info               = src.rail.info;
            dst.rail.point              = src.rail.point;
            dst.wipe_type               = src.wipe_type;
        }
    }

    // Block 8
    {
        u32 size = p_header->getBlockSize(CD_FILE_BLOCK_SPRITE) - sizeof(u32);
        RIO_ASSERT(size % sizeof(Sprite) == 0);
        u32 count = size / sizeof(Sprite);

        mSprite.resize(count);

        const Sprite* p_src = (const Sprite*)p_header->getBlock(CD_FILE_BLOCK_SPRITE);
        RIO_ASSERT(*(u32*)(p_src + count) == u32(-1));

        for (u32 i = 0; i < count; i++)
        {
            const Sprite&   src = p_src[i];
            Sprite&         dst = mSprite[i];

            dst.id          = CD_FILE_READ_16_BE(src.id);
            dst.offset.x    = CD_FILE_READ_16_BE(src.offset.x);
            dst.offset.y    = CD_FILE_READ_16_BE(src.offset.y);
            dst.event_id    = CD_FILE_READ_16_BE(src.event_id);
            dst.settings[0] = CD_FILE_READ_32_BE(src.settings[0]);
            dst.settings[1] = CD_FILE_READ_32_BE(src.settings[1]);
            dst.area        = src.area;
            dst.layer       = src.layer;
            dst.movement_id = src.movement_id;
            dst.link_id     = src.link_id;
            dst.init_state  = src.init_state;
        }
    }

    // Block 10
    {
        u32 size = p_header->getBlockSize(CD_FILE_BLOCK_AREA_DATA);
        RIO_ASSERT(size % sizeof(AreaData) == 0);
        u32 count = size / sizeof(AreaData);

        mAreaData.resize(count);

        const AreaData* p_src = (const AreaData*)p_header->getBlock(CD_FILE_BLOCK_AREA_DATA);

        for (u32 i = 0; i < count; i++)
        {
            const AreaData& src = p_src[i];
            AreaData&       dst = mAreaData[i];

            dst.offset.x    = CD_FILE_READ_16_BE(src.offset.x);
            dst.offset.y    = CD_FILE_READ_16_BE(src.offset.y);
            dst.size.x      = CD_FILE_READ_16_BE(src.size.x);
            dst.size.y      = CD_FILE_READ_16_BE(src.size.y);
            dst.color_obj   = CD_FILE_READ_16_BE(src.color_obj);
            dst.color_bg    = CD_FILE_READ_16_BE(src.color_bg);
            dst.id          = src.id;
            dst.scroll      = src.scroll;
            dst.zoom_type   = src.zoom_type;
            dst.zoom_id     = src.zoom_id;
            dst.zoom_change = src.zoom_change;
            dst.mask        = src.mask;
            dst.bg2         = src.bg2;
            dst.bg3         = src.bg3;
            dst.direction   = src.direction;
            dst._15         = src._15;
            dst.bgm         = src.bgm;
            dst.bgm_mode    = src.bgm_mode;
            dst.dv          = src.dv;
            dst.flag        = src.flag;
        }
    }

    // Block 11
    {
        u32 size = p_header->getBlockSize(CD_FILE_BLOCK_LOCATION);
        RIO_ASSERT(size % sizeof(Location) == 0);
        u32 count = size / sizeof(Location);

        mLocation.resize(count);

        const Location* p_src = (const Location*)p_header->getBlock(CD_FILE_BLOCK_LOCATION);

        for (u32 i = 0; i < count; i++)
        {
            const Location& src = p_src[i];
            Location&       dst = mLocation[i];

            dst.offset.x    = CD_FILE_READ_16_BE(src.offset.x);
            dst.offset.y    = CD_FILE_READ_16_BE(src.offset.y);
            dst.size.x      = CD_FILE_READ_16_BE(src.size.x);
            dst.size.y      = CD_FILE_READ_16_BE(src.size.y);
            dst.id          = src.id;
        }
    }

    // Block 14
    {
        u32 size = p_header->getBlockSize(CD_FILE_BLOCK_RAIL_INFO);
        RIO_ASSERT(size % sizeof(RailInfo) == 0);
        u32 count = size / sizeof(RailInfo);

        mRailInfo.resize(count);

        const RailInfo* p_src = (const RailInfo*)p_header->getBlock(CD_FILE_BLOCK_RAIL_INFO);

        for (u32 i = 0; i < count; i++)
        {
            const RailInfo& src = p_src[i];
            RailInfo&       dst = mRailInfo[i];

            dst.id          = src.id;
            dst._1          = src._1;
            dst.point.start = CD_FILE_READ_16_BE(src.point.start);
            dst.point.num   = CD_FILE_READ_16_BE(src.point.num);
            dst.flag        = CD_FILE_READ_16_BE(src.flag);
            dst._8          = CD_FILE_READ_32_BE(src._8);
        }
    }

    // Block 15
    {
        u32 size = p_header->getBlockSize(CD_FILE_BLOCK_RAIL_POINT);
        RIO_ASSERT(size % sizeof(RailPoint) == 0);
        u32 count = size / sizeof(RailPoint);

        mRailPoint.resize(count);

        const RailPoint* p_src = (const RailPoint*)p_header->getBlock(CD_FILE_BLOCK_RAIL_POINT);

        for (u32 i = 0; i < count; i++)
        {
            const RailPoint&    src = p_src[i];
            RailPoint&          dst = mRailPoint[i];

            dst.offset.x    = CD_FILE_READ_16_BE(src.offset.x);
            dst.offset.y    = CD_FILE_READ_16_BE(src.offset.y);

            CD_FILE_COPY_32_BE(&dst.speed, &src.speed);
            CD_FILE_COPY_32_BE(&dst.accel, &src.accel);

            dst.delay       = CD_FILE_READ_16_BE(src.delay);
            dst._e          = CD_FILE_READ_16_BE(src._e);
            dst._10         = src._10;
            dst._11         = src._11;
            dst._12         = src._12;
        }
    }
}

gsl::span<u8> CourseDataFile::saveFile_() const
{
    std::set<u16> used_sprites;
    for (const Sprite& sprite : mSprite)
        used_sprites.insert(sprite.id);

    const u32 scroll_data_num       = mScrollData.size();
    const u32 distant_view_data_num = mDistantViewData.size();
    const u32 next_goto_num         = mNextGoto.size();
    const u32 sprite_num            = mSprite.size();
    const u32 used_sprites_num      = used_sprites.size();
    const u32 area_data_num         = mAreaData.size();
    const u32 location_num          = mLocation.size();
    const u32 rail_num              = mRailInfo.size();
    const u32 rail_point_num        = mRailPoint.size();

    CourseDataFileHeader header;
    u32 file_size = sizeof(CourseDataFileHeader);

    header.environment.offset = file_size;
    header.environment.size = sizeof(Environment);
    file_size += header.environment.size;

    header.options.offset = file_size;
    header.options.size = sizeof(Options);
    file_size += header.options.size;

    header.scroll_data.offset = file_size;
    header.scroll_data.size = sizeof(ScrollData) * scroll_data_num;
    file_size += header.scroll_data.size;

    header._block4.offset = file_size;
    header._block4.size = 0;

    header.distant_view_data.offset = file_size;
    header.distant_view_data.size = sizeof(DistantViewData) * distant_view_data_num;
    file_size += header.distant_view_data.size;

    header._block6.offset = file_size;
    header._block6.size = 0;

    header.next_goto.offset = file_size;
    header.next_goto.size = sizeof(NextGoto) * next_goto_num;
    file_size += header.next_goto.size;

    header.sprite.offset = file_size;
    header.sprite.size = sizeof(Sprite) * sprite_num + sizeof(u32);
    file_size += header.sprite.size;

    header.sprite_load_res.offset = file_size;
    header.sprite_load_res.size = (2 * sizeof(u16)) * used_sprites_num;
    file_size += header.sprite_load_res.size;

    header.area_data.offset = file_size;
    header.area_data.size = sizeof(AreaData) * area_data_num;
    file_size += header.area_data.size;

    header.location.offset = file_size;
    header.location.size = sizeof(Location) * location_num;
    file_size += header.location.size;

    header._block12.offset = file_size;
    header._block12.size = 0;

    header._block13.offset = file_size;
    header._block13.size = 0;

    header.rail.offset = file_size;
    header.rail.size = sizeof(RailInfo) * rail_num;
    file_size += header.rail.size;

    header.rail_point.offset = file_size;
    header.rail_point.size = sizeof(RailPoint) * rail_point_num;
    file_size += header.rail_point.size;

    u8* const file = static_cast<u8*>(rio::MemUtil::alloc(file_size, 4));
    rio::MemUtil::set(file, 0, file_size);

    // Block 1
    {
        Environment* p_dst = (Environment*)(file + header.environment.offset);
      //RIO_ASSERT(header.environment.size > 0);
        {
            rio::MemUtil::copy(p_dst, &mEnvironment, sizeof(Environment));
        }
    }

    // Block 2
    {
        Options* p_dst = (Options*)(file + header.options.offset);
      //RIO_ASSERT(header.options.size > 0);
        {
            p_dst->def_events[0]                = CD_FILE_READ_32_BE(mOptions.def_events[0]);
            p_dst->def_events[1]                = CD_FILE_READ_32_BE(mOptions.def_events[1]);
            p_dst->loop                         = CD_FILE_READ_16_BE(mOptions.loop);
            p_dst->time_0                       = CD_FILE_READ_16_BE(mOptions.time_0);
            p_dst->_unused0[0]                  = mOptions._unused0[0];
            p_dst->_unused0[1]                  = mOptions._unused0[1];
            p_dst->_unused0[2]                  = mOptions._unused0[2];
            p_dst->_unused0[3]                  = mOptions._unused0[3];
            p_dst->start_next_goto              = mOptions.start_next_goto;
            p_dst->_unused1[0]                  = mOptions._unused1[0];
            p_dst->_unused1[1]                  = mOptions._unused1[1];
            p_dst->start_next_goto_coin_boost   = mOptions.start_next_goto_coin_boost;
            p_dst->time_1                       = CD_FILE_READ_16_BE(mOptions.time_1);
            p_dst->time_2                       = CD_FILE_READ_16_BE(mOptions.time_2);
        }
    }

    // Block 3
    {
        ScrollData* p_dst = (ScrollData*)(file + header.scroll_data.offset);

        for (u32 i = 0; i < scroll_data_num; i++)
        {
            const ScrollData&   src = mScrollData[i];
            ScrollData&         dst = p_dst[i];

            dst.bound[0].upper         = CD_FILE_READ_32_BE(src.bound[0].upper);
            dst.bound[0].lower         = CD_FILE_READ_32_BE(src.bound[0].lower);
            dst.bound[1].upper         = CD_FILE_READ_32_BE(src.bound[1].upper);
            dst.bound[1].lower         = CD_FILE_READ_32_BE(src.bound[1].lower);
            dst.id                     = CD_FILE_READ_16_BE(src.id);
            dst.flag                   = CD_FILE_READ_16_BE(src.flag);
            dst.mp_bound_adjust.upper  = CD_FILE_READ_16_BE(src.mp_bound_adjust.upper);
            dst.mp_bound_adjust.lower  = CD_FILE_READ_16_BE(src.mp_bound_adjust.lower);
        }
    }

    // Block 5
    {
        DistantViewData* p_dst = (DistantViewData*)(file + header.distant_view_data.offset);

        for (u32 i = 0; i < distant_view_data_num; i++)
        {
            const DistantViewData&  src = mDistantViewData[i];
            DistantViewData&        dst = p_dst[i];

            dst.id              = CD_FILE_READ_16_BE(src.id);
            dst.offset.x        = CD_FILE_READ_16_BE(src.offset.x);
            dst.offset.y        = CD_FILE_READ_16_BE(src.offset.y);
            dst.offset.z        = CD_FILE_READ_16_BE(src.offset.z);

            rio::MemUtil::copy(dst.name, src.name, CD_FILE_DV_NAME_MAX_LEN);
            dst.name[CD_FILE_DV_NAME_MAX_LEN] = '\0';

            dst.parallax_mode   = src.parallax_mode;
        }
    }

    // Block 7
    {
        NextGoto* p_dst = (NextGoto*)(file + header.next_goto.offset);

        for (u32 i = 0; i < next_goto_num; i++)
        {
            const NextGoto& src = mNextGoto[i];
            NextGoto&       dst = p_dst[i];

            dst.offset.x                = CD_FILE_READ_16_BE(src.offset.x);
            dst.offset.y                = CD_FILE_READ_16_BE(src.offset.y);
            dst.camera_offset.x         = CD_FILE_READ_16_BE(src.camera_offset.x);
            dst.camera_offset.y         = CD_FILE_READ_16_BE(src.camera_offset.y);
            dst.id                      = src.id;
            dst.destination.file        = src.destination.file;
            dst.destination.next_goto   = src.destination.next_goto;
            dst.type                    = src.type;
            dst.mp_spawn_flag           = src.mp_spawn_flag;
            dst.area                    = src.area;
            dst.mp_inner_gap            = src.mp_inner_gap;
            dst.flag                    = CD_FILE_READ_16_BE(src.flag);
            dst.chibi_yoshi_next_goto   = src.chibi_yoshi_next_goto;
            dst.coin_edit_priority      = src.coin_edit_priority;
            dst.rail.info               = src.rail.info;
            dst.rail.point              = src.rail.point;
            dst.wipe_type               = src.wipe_type;
        }
    }

    // Block 8
    {
        Sprite* p_dst = (Sprite*)(file + header.sprite.offset);
        *(u32*)(p_dst + sprite_num) = u32(-1);

        for (u32 i = 0; i < sprite_num; i++)
        {
            const Sprite&   src = mSprite[i];
            Sprite&         dst = p_dst[i];

            dst.id          = CD_FILE_READ_16_BE(src.id);
            dst.offset.x    = CD_FILE_READ_16_BE(src.offset.x);
            dst.offset.y    = CD_FILE_READ_16_BE(src.offset.y);
            dst.event_id    = CD_FILE_READ_16_BE(src.event_id);
            dst.settings[0] = CD_FILE_READ_32_BE(src.settings[0]);
            dst.settings[1] = CD_FILE_READ_32_BE(src.settings[1]);
            dst.area        = src.area;
            dst.layer       = src.layer;
            dst.movement_id = src.movement_id;
            dst.link_id     = src.link_id;
            dst.init_state  = src.init_state;
        }
    }

    // Block 9
    {
        u16* p_dst = (u16*)(file + header.sprite_load_res.offset);

        auto it = used_sprites.cbegin();
        for (u32 i = 0; i < used_sprites_num; std::advance(it, 1), i++)
            p_dst[i * 2] = CD_FILE_READ_16_BE(*it);

    }

    // Block 10
    {
        AreaData* p_dst = (AreaData*)(file + header.area_data.offset);

        for (u32 i = 0; i < area_data_num; i++)
        {
            const AreaData& src = mAreaData[i];
            AreaData&       dst = p_dst[i];

            dst.offset.x    = CD_FILE_READ_16_BE(src.offset.x);
            dst.offset.y    = CD_FILE_READ_16_BE(src.offset.y);
            dst.size.x      = CD_FILE_READ_16_BE(src.size.x);
            dst.size.y      = CD_FILE_READ_16_BE(src.size.y);
            dst.color_obj   = CD_FILE_READ_16_BE(src.color_obj);
            dst.color_bg    = CD_FILE_READ_16_BE(src.color_bg);
            dst.id          = src.id;
            dst.scroll      = src.scroll;
            dst.zoom_type   = src.zoom_type;
            dst.zoom_id     = src.zoom_id;
            dst.zoom_change = src.zoom_change;
            dst.mask        = src.mask;
            dst.bg2         = src.bg2;
            dst.bg3         = src.bg3;
            dst.direction   = src.direction;
            dst._15         = src._15;
            dst.bgm         = src.bgm;
            dst.bgm_mode    = src.bgm_mode;
            dst.dv          = src.dv;
            dst.flag        = src.flag;
        }
    }

    // Block 11
    {
        Location* p_dst = (Location*)(file + header.location.offset);

        for (u32 i = 0; i < location_num; i++)
        {
            const Location& src = mLocation[i];
            Location&       dst = p_dst[i];

            dst.offset.x    = CD_FILE_READ_16_BE(src.offset.x);
            dst.offset.y    = CD_FILE_READ_16_BE(src.offset.y);
            dst.size.x      = CD_FILE_READ_16_BE(src.size.x);
            dst.size.y      = CD_FILE_READ_16_BE(src.size.y);
            dst.id          = src.id;
        }
    }

    // Block 14
    {
        RailInfo* p_dst = (RailInfo*)(file + header.rail.offset);

        for (u32 i = 0; i < rail_num; i++)
        {
            const RailInfo& src = mRailInfo[i];
            RailInfo&       dst = p_dst[i];

            dst.id          = src.id;
            dst._1          = src._1;
            dst.point.start = CD_FILE_READ_16_BE(src.point.start);
            dst.point.num   = CD_FILE_READ_16_BE(src.point.num);
            dst.flag        = CD_FILE_READ_16_BE(src.flag);
            dst._8          = CD_FILE_READ_32_BE(src._8);
        }
    }

    // Block 15
    {
        RailPoint* p_dst = (RailPoint*)(file + header.rail_point.offset);

        for (u32 i = 0; i < rail_point_num; i++)
        {
            const RailPoint&    src = mRailPoint[i];
            RailPoint&          dst = p_dst[i];

            dst.offset.x    = CD_FILE_READ_16_BE(src.offset.x);
            dst.offset.y    = CD_FILE_READ_16_BE(src.offset.y);

            CD_FILE_COPY_32_BE(&dst.speed, &src.speed);
            CD_FILE_COPY_32_BE(&dst.accel, &src.accel);

            dst.delay       = CD_FILE_READ_16_BE(src.delay);
            dst._e          = CD_FILE_READ_16_BE(src._e);
            dst._10         = src._10;
            dst._11         = src._11;
            dst._12         = src._12;
        }
    }

    // Header
    {
        CourseDataFileHeader* p_dst = (CourseDataFileHeader*)file;

        for (s32 i = 0; i < CD_FILE_BLOCK_NUM; i++)
        {
            p_dst->blocks[i].offset = CD_FILE_READ_32_BE(header.blocks[i].offset);
            if (header.blocks[i].size > 0)
                p_dst->blocks[i].size = CD_FILE_READ_32_BE(header.blocks[i].size);
        }
    }

    return { file, file_size };
}

void CourseDataFile::loadBgDat_(u8 layer, const BgCourseData* bgdat)
{
    if (!bgdat)
        return;

    std::vector<BgCourseData>& self_bgdat = mBgData[layer];

    u32 count = 0;
    while (bgdat[count].type != 0xffff)
        count++;

    self_bgdat.resize(count);

    for (u32 i = 0; i < count; i++)
    {
        const BgCourseData& src = bgdat[i];
        BgCourseData&       dst = self_bgdat[i];

        dst.type        = CD_FILE_READ_16_BE(src.type);
        dst.offset.x    = CD_FILE_READ_16_BE(src.offset.x);
        dst.offset.y    = CD_FILE_READ_16_BE(src.offset.y);
        dst.size.x      = CD_FILE_READ_16_BE(src.size.x);
        dst.size.y      = CD_FILE_READ_16_BE(src.size.y);
        dst.flag        = src.flag;
    }
}

gsl::span<u8> CourseDataFile::saveBgDat_(u8 layer) const
{
    const std::vector<BgCourseData>& self_bgdat = mBgData[layer];
    const u32 bgdat_num = self_bgdat.size();

    if (bgdat_num == 0)
        return gsl::span<u8>();

    const size_t file_size = sizeof(BgCourseData) * bgdat_num + sizeof(BgCourseData::type);
    u8* const file = static_cast<u8*>(rio::MemUtil::alloc(file_size, 4));
    rio::MemUtil::set(file, 0, file_size);

    BgCourseData* bgdat = (BgCourseData*)file;
    bgdat[bgdat_num].type = 0xffff;

    for (u32 i = 0; i < bgdat_num; i++)
    {
        const BgCourseData& src = self_bgdat[i];
        BgCourseData&       dst = bgdat[i];

        dst.type        = CD_FILE_READ_16_BE(src.type);
        dst.offset.x    = CD_FILE_READ_16_BE(src.offset.x);
        dst.offset.y    = CD_FILE_READ_16_BE(src.offset.y);
        dst.size.x      = CD_FILE_READ_16_BE(src.size.x);
        dst.size.y      = CD_FILE_READ_16_BE(src.size.y);
        dst.flag        = src.flag;
    }

    return { file, file_size };
}

void CourseDataFile::clear()
{
    mID = -1;

    mBgData[LAYER_0].clear();
    mBgData[LAYER_1].clear();
    mBgData[LAYER_2].clear();

    mEnvironment    = { 0 };
    mOptions        = { 0 };

    mScrollData.clear();
    mDistantViewData.clear();
    mNextGoto.clear();
    mSprite.clear();
    mAreaData.clear();
    mLocation.clear();
    mRailInfo.clear();
    mRailPoint.clear();
}

void CourseDataFile::setEnvironment(u32 index, const char* name)
{
    RIO_ASSERT(index < CD_FILE_ENV_MAX_NUM);

    size_t name_len = std::min(std::strlen(name), (size_t)(CD_FILE_TS_NAME_MAX_LEN - 1));
    rio::MemUtil::copy(mEnvironment.tileset_name[index], name, name_len);
    mEnvironment.tileset_name[index][name_len] = '\0';
}
