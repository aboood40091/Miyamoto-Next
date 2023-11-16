#include <resource/ResMgr.h>
#include <resource/SZSDecompressor.h>

#include <filedevice/rio_FileDeviceMgr.h>

ResMgr* ResMgr::sInstance = nullptr;

bool ResMgr::createSingleton()
{
    if (sInstance)
        return false;

    sInstance = new ResMgr();
    return true;
}

void ResMgr::destroySingleton()
{
    if (!sInstance)
        return;

    delete sInstance;
    sInstance = nullptr;
}

ResMgr::ResMgr()
{
}

ResMgr::~ResMgr()
{
    // Ideally, everything should be freed manually
    RIO_ASSERT(mResMap.empty());
}

const SharcArchiveRes* ResMgr::loadArchiveRes(const std::string& key, const std::string& archive_path, bool decompress)
{
    {
        const auto& it = mResMap.find(key);
        if (it != mResMap.end())
        {
            it->second.ref_counter++;
            return &it->second.archive_res;
        }
    }

    rio::FileDevice::LoadArg arg;
    arg.path = archive_path;
    arg.alignment = 0x2000;

    u8* data =
        decompress
            ? SZSDecompressor::tryDecomp(arg)
            : rio::FileDeviceMgr::instance()->tryLoad(arg);

    if (!data)
        return nullptr;

    Resource res;
    res.ref_counter = 1;
    res.archive = data;
    res.self_alloc = true;
    if (!res.archive_res.prepareArchive(res.archive))
        return nullptr;

    const auto& it = mResMap.try_emplace(key, std::move(res));
    RIO_ASSERT(it.second);
    return &it.first->second.archive_res;
}

const SharcArchiveRes* ResMgr::loadArchiveRes(const std::string& key, void* archive, bool fatal_errors)
{
    {
        const auto& it = mResMap.find(key);
        if (it != mResMap.end())
        {
            it->second.ref_counter++;
            return &it->second.archive_res;
        }
    }

    Resource res;
    res.ref_counter = 1;
    res.archive = archive;
    res.self_alloc = false;
    if (!res.archive_res.prepareArchive(res.archive, fatal_errors))
        return nullptr;

    const auto& it = mResMap.try_emplace(key, std::move(res));
    RIO_ASSERT(it.second);
    return &it.first->second.archive_res;
}

void ResMgr::destroyArchiveRes(const std::string& key)
{
    const auto& it = mResMap.find(key);
    if (it == mResMap.end())
        return;

    if (--it->second.ref_counter <= 0)
        mResMap.erase(it);
}

const SharcArchiveRes* ResMgr::getArchiveRes(const std::string& key) const
{
    const auto& it = mResMap.find(key);
    if (it == mResMap.end())
        return nullptr;

    return &it->second.archive_res;
}
