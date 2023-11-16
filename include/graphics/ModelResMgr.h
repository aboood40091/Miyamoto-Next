#pragma once

#include <graphics/ModelResource.h>

#include <misc/rio_MemUtil.h>

#include <string>
#include <unordered_map>

class ModelResMgr
{
public:
    static bool createSingleton();
    static void destroySingleton();
    static ModelResMgr* instance() { return sInstance; }

private:
    static ModelResMgr* sInstance;

    ModelResMgr();
    ~ModelResMgr();

    ModelResMgr(const ModelResMgr&);
    ModelResMgr& operator=(const ModelResMgr&);

public:
    bool loadResFile(const std::string& key, const std::string& archive_name);
    void loadResFile(const std::string& key, const SharcArchiveRes* archive, const char* filename);
    void destroyResFile(const std::string& key);

    ModelResource* getResource(const std::string& key) const;

private:
    struct Resource
    {
        s32             ref_counter;
        ModelResource*  mdl_resource;

        Resource()
            : ref_counter(0)
            , mdl_resource(nullptr)
        {
        }

        ~Resource()
        {
            if (mdl_resource != nullptr)
            {
                delete mdl_resource;
                mdl_resource = nullptr;
            }
        }

        Resource(const Resource&) = delete;
        Resource& operator=(const Resource&) = delete;

        Resource(Resource&& other)
            : ref_counter(std::move(other.ref_counter))
            , mdl_resource(other.mdl_resource)
        {
            other.mdl_resource = nullptr;
        }

        Resource& operator=(Resource&& other)
        {
            if (this != &other)
            {
                if (mdl_resource != nullptr)
                    delete mdl_resource;

                ref_counter = std::move(other.ref_counter);
                mdl_resource = other.mdl_resource;

                other.mdl_resource = nullptr;
            }
            return *this;
        }
    };

    std::unordered_map<std::string, Resource> mResMap;
};
