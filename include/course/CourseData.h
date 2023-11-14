#pragma once

#include <course/Bg.h>
#include <course/CourseDataFile.h>

#include <span>

class CourseData
{
public:
    CourseData();
    ~CourseData();

    bool loadFromPack(const std::string& path);
    std::span<u8> save(const std::string& level_name) const;

    CourseDataFile* getFile(u32 index)
    {
        RIO_ASSERT(index < CD_FILE_MAX_NUM);

        CourseDataFile& cd_file = mFile[index];
        if (cd_file.isValid())
            return &cd_file;

        return nullptr;
    }

    const CourseDataFile* getFile(u32 index) const
    {
        RIO_ASSERT(index < CD_FILE_MAX_NUM);

        const CourseDataFile& cd_file = mFile[index];
        if (cd_file.isValid())
            return &cd_file;

        return nullptr;
    }

    Bg& getBg()
    {
        return mBg;
    }

    const Bg& getBg() const
    {
        return mBg;
    }

    std::span<u8> getRes(const std::string& name) const;

private:
    void clearResData_();

private:
    std::array<CourseDataFile, CD_FILE_MAX_NUM> mFile;
    Bg                                          mBg;

    // Unused res data to be included at saving
    std::unordered_map< std::string, std::span<u8> > mResData;

    enum
    {
        COURSE_DATA_FILE_NAME_LEN       = 18,
        COURSE_DATA_FILE_LAYER_NAME_LEN = 26,
        COURSE_DATA_FILE_ID_POS         = 13,
    };

    static char sCourseDataFileName  [COURSE_DATA_FILE_NAME_LEN       + 1];
    static char sCourseDataFileL0Name[COURSE_DATA_FILE_LAYER_NAME_LEN + 1];
    static char sCourseDataFileL1Name[COURSE_DATA_FILE_LAYER_NAME_LEN + 1];
    static char sCourseDataFileL2Name[COURSE_DATA_FILE_LAYER_NAME_LEN + 1];
};
