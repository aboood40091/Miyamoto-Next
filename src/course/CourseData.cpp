#include <course/BgUnitFile.h>
#include <course/CourseData.h>
#include <resource/ResMgr.h>
#include <resource/SharcArchiveRes.h>
#include <resource/SharcWriter.h>
#include <resource/SZSCompressor.h>
#include <resource/SZSDecompressor.h>

#include <unordered_set>

namespace {

inline std::string path_basename(const std::string& path)
{
    return path.substr(path.find_last_of("/\\") + 1);
}

inline std::string remove_extension(const std::string& filename)
{
    const std::string::size_type pos = filename.find_last_of('.');
    if (pos > 0 && pos != std::string::npos)
        return filename.substr(0, pos);

    return filename;
}

}

char CourseData::sCourseDataFileName  [COURSE_DATA_FILE_NAME_LEN       + 1] = "course/courseX.bin";
char CourseData::sCourseDataFileL0Name[COURSE_DATA_FILE_LAYER_NAME_LEN + 1] = "course/courseX_bgdatL0.bin";
char CourseData::sCourseDataFileL1Name[COURSE_DATA_FILE_LAYER_NAME_LEN + 1] = "course/courseX_bgdatL1.bin";
char CourseData::sCourseDataFileL2Name[COURSE_DATA_FILE_LAYER_NAME_LEN + 1] = "course/courseX_bgdatL2.bin";

CourseData* CourseData::sInstance = nullptr;

bool CourseData::createSingleton()
{
    if (sInstance)
        return false;

    sInstance = new CourseData();
    return true;
}

void CourseData::destroySingleton()
{
    if (!sInstance)
        return;

    delete sInstance;
    sInstance = nullptr;
}

CourseData::CourseData()
{
}

CourseData::~CourseData()
{
    clearResData_();
}

bool CourseData::loadFromPack(const std::string& path)
{
    rio::FileDevice::LoadArg arg;
    arg.path = /* std::string("native://") + */ path;
    arg.alignment = 0x2000;

    u8* pack_arc_dat = SZSDecompressor::tryDecomp(arg);
    if (!pack_arc_dat)
        return false;

    SharcArchiveRes pack_arc;
    if (!pack_arc.prepareArchive(pack_arc_dat))
    {
        RIO_LOG("Could not load Sharc file...\n");
        rio::MemUtil::free(pack_arc_dat);
        return false;
    }

    std::unordered_set<std::string> read_files;

    RIO_LOG("\nLoaded %s\n", path.c_str());
    // RIO_LOG("Level data magic: %c%c%c%c\n", pack_arc_dat[0], pack_arc_dat[1], pack_arc_dat[2], pack_arc_dat[3]);

    /*
    const std::vector<SharcArchiveRes::Entry>& entries = pack_arc.readEntry();
    for (const auto& entry : entries)
        RIO_LOG("%s\n", entry.name);
    */

    SharcArchiveRes archive;

    if (pack_arc.getFile("course/course1.bin") != nullptr)
        archive = pack_arc;

    else
    {
        std::string level_name = "";

        void* level_dat = nullptr;

        u32     level_name_len = 0;
        char*   level_name_dat = static_cast<char*>(pack_arc.getFile("levelname", &level_name_len));

        if (level_name_len)
        {
            level_name = std::string(level_name_dat, level_name_len);
            level_dat = pack_arc.getFile(level_name.c_str());
        }

        if (!level_dat)
        {
            level_name = remove_extension(path_basename(path));
            level_dat = pack_arc.getFile(level_name.c_str());
        }
        else
        {
            read_files.insert(level_name);
            read_files.emplace("levelname");
        }

        if (!level_dat)
        {
            RIO_LOG("Inner level not found...\n");
            rio::MemUtil::free(pack_arc_dat);
            return false;
        }
        else
        {
            read_files.insert(level_name);
        }

        // RIO_LOG("Level name is: %s\n", level_name.c_str());

        if (!archive.prepareArchive(level_dat))
        {
            RIO_LOG("Could not load inner Sharc file...\n");
            rio::MemUtil::free(pack_arc_dat);
            return false;
        }
    }

    mBg.clear();

    for (s32 i = 0; i < CD_FILE_MAX_NUM; i++)
    {
        sCourseDataFileName  [COURSE_DATA_FILE_ID_POS] = '1' + i;
        sCourseDataFileL0Name[COURSE_DATA_FILE_ID_POS] = '1' + i;
        sCourseDataFileL1Name[COURSE_DATA_FILE_ID_POS] = '1' + i;
        sCourseDataFileL2Name[COURSE_DATA_FILE_ID_POS] = '1' + i;

        CourseDataFile& cd_file = mFile[i];

        cd_file.load(
            i,
            archive.getFile(sCourseDataFileName),
            archive.getFile(sCourseDataFileL0Name),
            archive.getFile(sCourseDataFileL1Name),
            archive.getFile(sCourseDataFileL2Name)
        );

        if (!cd_file.isValid())
            continue;

        RIO_LOG("Has area %d\n", i + 1);

        for (s32 j = 0; j < CD_FILE_ENV_MAX_NUM; j++)
        {
            std::string env_name = cd_file.getEnvironment(j);
            if (!env_name.empty())
            {
                [[maybe_unused]] bool success = mBg.loadUnit(pack_arc, env_name);
                RIO_ASSERT(success);

                read_files.emplace(env_name);
            }
        }
    }

    clearResData_();

    const std::vector<SharcArchiveRes::Entry>& entries = pack_arc.readEntry();
    for (const SharcArchiveRes::Entry& entry : entries)
    {
        const std::string& name = entry.name;

        if (read_files.find(name) != read_files.end())
            continue;

        u32 size = 0;
        u8* data = static_cast<u8*>(pack_arc.getFile(name.c_str(), &size));

        u8* new_data = static_cast<u8*>(rio::MemUtil::alloc(size, 0x2000));
        rio::MemUtil::copy(new_data, data, size);

        mResData.try_emplace(name, std::span{ new_data, size });

        ResMgr::instance()->loadArchiveRes(name, new_data, false);
    }

#if 0
    const std::span<u8> out_archive = save(level_name);
    const std::span<u8> out_szs = SZSCompressor::compress(out_archive);
    {
        rio::FileHandle handle;
#if RIO_IS_WIN
        const std::string& save_path = remove_extension(path) + "_test_win.szs";
#elif RIO_IS_CAFE
        const std::string& save_path = remove_extension(path) + "_test_cafe.szs";
#else
        const std::string& save_path = remove_extension(path) + "_test.szs";
#endif

        [[maybe_unused]] rio::FileDevice* device = rio::FileDeviceMgr::instance()->tryOpen(&handle, save_path, rio::FileDevice::FILE_OPEN_FLAG_WRITE);
        RIO_ASSERT(device != nullptr);

        [[maybe_unused]] u32 written_size = handle.write(out_szs.data(), out_szs.size());
        RIO_ASSERT(written_size == out_szs.size());
    }
    rio::MemUtil::free(out_szs.data());
    rio::MemUtil::free(out_archive.data());
#endif

    rio::MemUtil::free(pack_arc_dat);
    return true;
}

std::span<u8> CourseData::save(const std::string& level_name) const
{
    SharcWriter<0x65> pack_writer;
    for (const auto& file : mResData)
        pack_writer.addFile(file.first, file.second);

    pack_writer.addFile("levelname", { (u8*)level_name.c_str(), level_name.length() });
    for (const auto& file : mBg.getUnitFileMap())
    {
        [[maybe_unused]] bool success = file.second->save();
        RIO_ASSERT(success);
        pack_writer.addFile(file.first, file.second->getData());
    }

    SharcWriter<0x65> level_arc_writer;
    for (s32 i = 0; i < CD_FILE_MAX_NUM; i++)
    {
        const CourseDataFile& cd_file = mFile[i];
        if (!cd_file.isValid())
            continue;

        sCourseDataFileName  [COURSE_DATA_FILE_ID_POS] = '1' + i;
        sCourseDataFileL0Name[COURSE_DATA_FILE_ID_POS] = '1' + i;
        sCourseDataFileL1Name[COURSE_DATA_FILE_ID_POS] = '1' + i;
        sCourseDataFileL2Name[COURSE_DATA_FILE_ID_POS] = '1' + i;

        const auto& cd_file_data = cd_file.save();

        level_arc_writer.addFile(sCourseDataFileName, cd_file_data[0]);
        if (cd_file_data[1].data()) level_arc_writer.addFile(sCourseDataFileL0Name, cd_file_data[1]);
        if (cd_file_data[2].data()) level_arc_writer.addFile(sCourseDataFileL1Name, cd_file_data[2]);
        if (cd_file_data[3].data()) level_arc_writer.addFile(sCourseDataFileL2Name, cd_file_data[3]);
    }

    const std::span<u8> out_level_archive = level_arc_writer.save();
    pack_writer.addFile(level_name, out_level_archive);

    const std::span<u8> out_archive = pack_writer.save(true);
    rio::MemUtil::free(out_level_archive.data());

    return out_archive;
}

void CourseData::clearResData_()
{
    for (const auto& file : mResData)
    {
        ResMgr::instance()->destroyArchiveRes(file.first);
        rio::MemUtil::free(file.second.data());
    }

    mResData.clear();
}
