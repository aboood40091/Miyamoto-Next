#pragma once

#include <resource/SharcArchiveRes.h>

#include <misc/rio_MemUtil.h>

#include <string>
#include <unordered_map>

class ResMgr
{
public:
    static bool createSingleton();
    static void destroySingleton();
    static ResMgr* instance() { return sInstance; }

private:
    static ResMgr* sInstance;

    ResMgr();
    ~ResMgr();

    ResMgr(const ResMgr&);
    ResMgr& operator=(const ResMgr&);

public:
    const SharcArchiveRes* loadArchiveRes(const std::string& key, const std::string& archive_path, bool decompress);
    const SharcArchiveRes* loadArchiveRes(const std::string& key, void* archive, bool fatal_errors);
    void destroyArchiveRes(const std::string& key);

    const SharcArchiveRes* getArchiveRes(const std::string& key) const;

private:
    struct Resource
    {
        s32             ref_counter;
        void*           archive;
        SharcArchiveRes archive_res;
        bool            self_alloc;

        Resource()
            : ref_counter(0)
            , archive(nullptr)
            , self_alloc(false)
        {
        }

        ~Resource()
        {
            if (archive != nullptr)
            {
                if (self_alloc)
                    rio::MemUtil::free(archive);

                archive = nullptr;
            }
        }

        Resource(const Resource&) = delete;
        Resource& operator=(const Resource&) = delete;

        Resource(Resource&& other)
            : ref_counter(std::move(other.ref_counter))
            , archive(other.archive)
            , archive_res(std::move(other.archive_res))
            , self_alloc(std::move(other.self_alloc))
        {
            other.archive = nullptr;
        }

        Resource& operator=(Resource&& other)
        {
            if (this != &other)
            {
                if (archive != nullptr)
                    if (self_alloc)
                        rio::MemUtil::free(archive);

                ref_counter = std::move(other.ref_counter);
                archive = other.archive;
                archive_res = std::move(other.archive_res);
                self_alloc = std::move(other.self_alloc);

                other.archive = nullptr;
            }
            return *this;
        }
    };

    std::unordered_map<std::string, Resource> mResMap;
};
