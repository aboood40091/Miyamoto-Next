#pragma once

#include <course/CourseDataFile.h>

#include <span>
#include <string>
#include <unordered_map>

class CourseData
{
public:
    static bool createSingleton();
    static void destroySingleton();
    static CourseData* instance() { return sInstance; }

private:
    static CourseData* sInstance;

    CourseData();
    ~CourseData();

    CourseData(const CourseData&);
    CourseData& operator=(const CourseData&);

public:
    void createNew();
    bool loadFromPack(const std::string& path);
    std::span<u8> save() const;

    CourseDataFile& getCourseDataFile(u32 index)
    {
        RIO_ASSERT(index < CD_FILE_MAX_NUM);
        return mFile[index];
    }

    const CourseDataFile& getCourseDataFile(u32 index) const
    {
        RIO_ASSERT(index < CD_FILE_MAX_NUM);
        return mFile[index];
    }

private:
    void clearResData_();

private:
    std::array<CourseDataFile, CD_FILE_MAX_NUM> mFile;

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
