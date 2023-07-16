#pragma once

#include <misc/rio_Types.h>

#include <map>
#include <span>
#include <string>

template <u32 hash_key>
class SharcWriter
{
public:
    SharcWriter();
    ~SharcWriter();

    void addFile(const std::string& name, std::span<const u8> data);
    void addFile(u32 name_hash, std::span<const u8> data);

    std::span<u8> save(bool is_be = true) const;

private:
    std::multimap< u32, std::pair< std::string, std::span<const u8> > > mFiles;
};

#include "SharcWriter.hpp"
