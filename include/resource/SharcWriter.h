#pragma once

#include <misc/rio_Types.h>

#include <map>
#include <string>

#include <gsl/span>

template <u32 hash_key>
class SharcWriter
{
public:
    SharcWriter();
    ~SharcWriter();

    void addFile(const std::string& name, const gsl::span<u8>& data);
    void addFile(u32 name_hash, const gsl::span<u8>& data);

    gsl::span<u8> save(bool is_be = true) const;

private:
    std::multimap< u32, std::pair< std::string, gsl::span<u8> > > mFiles;
};

#include "SharcWriter.hpp"
