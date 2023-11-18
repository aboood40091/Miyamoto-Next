#include <graphics/ModelResMgr.h>
#include <resource/ResMgr.h>

ModelResMgr* ModelResMgr::sInstance = nullptr;

bool ModelResMgr::createSingleton()
{
    if (sInstance)
        return false;

    sInstance = new ModelResMgr();
    return true;
}

void ModelResMgr::destroySingleton()
{
    if (!sInstance)
        return;

    delete sInstance;
    sInstance = nullptr;
}

ModelResMgr::ModelResMgr()
{
}

ModelResMgr::~ModelResMgr()
{
    // Ideally, everything should be freed manually
    RIO_ASSERT(mResMap.empty());
}

ModelResource* ModelResMgr::loadResFile(const std::string& key, const std::string& archive_name)
{
    {
        const auto& it = mResMap.find(key);
        if (it != mResMap.end())
        {
            it->second.ref_counter++;
            return it->second.mdl_resource;
        }
    }

    const SharcArchiveRes* archive = ResMgr::instance()->getArchiveRes(archive_name);
    if (archive == nullptr)
        return nullptr;

    ModelResource* mdl_resource = new ModelResource;
    mdl_resource->load(archive, archive_name.c_str(), true);

    Resource res;
    res.ref_counter = 1;
    res.mdl_resource = mdl_resource;

    const auto& it = mResMap.try_emplace(key, std::move(res));
    RIO_ASSERT(it.second);
    return it.first->second.mdl_resource;
}

ModelResource* ModelResMgr::loadResFile(const std::string& key, const SharcArchiveRes* archive, const char* filename)
{
    {
        const auto& it = mResMap.find(key);
        if (it != mResMap.end())
        {
            it->second.ref_counter++;
            return it->second.mdl_resource;
        }
    }

    ModelResource* mdl_resource = new ModelResource;
    mdl_resource->load(archive, filename, true);

    Resource res;
    res.ref_counter = 1;
    res.mdl_resource = mdl_resource;

    const auto& it = mResMap.try_emplace(key, std::move(res));
    RIO_ASSERT(it.second);
    return it.first->second.mdl_resource;
}

void ModelResMgr::destroyResFile(const std::string& key)
{
    const auto& it = mResMap.find(key);
    if (it == mResMap.end())
        return;

    if (--it->second.ref_counter <= 0)
        mResMap.erase(it);
}

ModelResource* ModelResMgr::getResource(const std::string& key) const
{
    const auto& it = mResMap.find(key);
    if (it == mResMap.end())
        return nullptr;

    return it->second.mdl_resource;
}
