// This file is included by SharcWriter.h
//#include "SharcWriter.h"

#include <resource/SharcArchiveRes.h>
#include <resource/SharcHasher.h>

#include <misc/rio_MemUtil.h>

namespace {

inline void Write(bool is_be, u16& dst, u16 src)
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    if (is_be)
#else
    if (!is_be)
#endif
        dst = __builtin_bswap16(src);
    else
        dst = src;
}

inline void Write(bool is_be, u32& dst, u32 src)
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    if (is_be)
#else
    if (!is_be)
#endif
        dst = __builtin_bswap32(src);
    else
        dst = src;
}

}

template <u32 hash_key>
SharcWriter<hash_key>::SharcWriter()
{
}

template <u32 hash_key>
SharcWriter<hash_key>::~SharcWriter()
{
}

template <u32 hash_key>
void SharcWriter<hash_key>::addFile(const std::string& name, std::span<const u8> data)
{
    RIO_ASSERT(!name.empty());
    RIO_ASSERT(data.data() != nullptr);
    RIO_ASSERT(data.size() != 0);
    RIO_ASSERT(mFiles.size() < SharcArchiveRes::cArchiveEntryMax);

    mFiles.emplace(sharcCalcHash32(name.c_str(), hash_key), std::pair{ name, data });
}

template <u32 hash_key>
void SharcWriter<hash_key>::addFile(u32 name_hash, std::span<const u8> data)
{
    RIO_ASSERT(name_hash != 0);
    RIO_ASSERT(data.data() != nullptr);
    RIO_ASSERT(data.size() != 0);
    RIO_ASSERT(mFiles.size() < SharcArchiveRes::cArchiveEntryMax);

    mFiles.emplace(name_hash, std::pair{ "", data });
}

template <u32 hash_key>
std::span<u8> SharcWriter<hash_key>::save(bool is_be) const
{
    if (mFiles.empty())
        return std::span<u8>();

    u32 file_num = mFiles.size();

    // Calculate name and data start offsets
    std::vector<u32> name_offsets; name_offsets.reserve(file_num);
    std::vector<u32> data_start_offsets; data_start_offsets.reserve(file_num);
    u32 name_table_size;
    u32 data_block_size;
    {
        constexpr s32 name_align = SharcArchiveRes::cFileNameTableAlign;
        constexpr s32 data_align = 0x2000;  // Value used by NSMBU

        u32 name_offset = 0;
        u32 data_offset = 0;

        for (const auto& it : mFiles)
        {
            const auto& file = it.second;
            const std::string& name = file.first;
            const std::span<const u8> data = file.second;

            // Name
            {
                if (name.empty())
                    name_offsets.push_back(0);

                else
                {
                    name_offsets.push_back(name_offset);
                    name_offset += name.length() + 1;

                  //name_offset += name_align - (name_offset - 1) % name_align;
                    name_offset = ((name_offset - 1) | (name_align - 1)) + 1;
                }
            }
            // Data
            {
              //data_offset += data_align - (data_offset - 1) % data_align;
                data_offset = ((data_offset - 1) | (data_align - 1)) + 1;

                data_start_offsets.push_back(data_offset);
                data_offset += data.size();
            }
        }

        RIO_ASSERT(name_offsets.size() == file_num);
        RIO_ASSERT(data_start_offsets.size() == file_num);

        name_table_size = name_offset;
        data_block_size = data_offset;
    }

  //RIO_LOG("File name table length: 0x%08X\n", name_table_size);
  //RIO_LOG("File data block length: 0x%08X\n", data_block_size);

    constexpr   size_t address_table_header_offset  =                               sizeof(SharcArchiveRes::ArchiveBlockHeader);
    constexpr   size_t address_table_offset         = address_table_header_offset + sizeof(SharcArchiveRes::FATBlockHeader);
    const       size_t name_table_header_offset     = address_table_offset        + sizeof(SharcArchiveRes::FATEntry) * file_num;
    const       size_t name_table_offset            = name_table_header_offset    + sizeof(SharcArchiveRes::FNTBlockHeader);

    size_t data_block_offset = name_table_offset + name_table_size;

    // Align
  //data_block_offset += 0x2000 - (data_block_offset - 1) % 0x2000;
    data_block_offset = ((data_block_offset - 1) | (0x2000 - 1)) + 1;

    const size_t file_size = data_block_offset + data_block_size;
    void* const archive = rio::MemUtil::alloc(file_size, 0x2000);
    rio::MemUtil::set(archive, 0, file_size);

    u8* const archive8 = reinterpret_cast<u8*>(archive);

    // ArchiveBlockHeader
    {
        SharcArchiveRes::ArchiveBlockHeader* const archive_header = reinterpret_cast<SharcArchiveRes::ArchiveBlockHeader*>(archive8);
        rio::MemUtil::copy(archive_header->signature, "SARC", 4);
        Write(is_be, archive_header->header_size, sizeof(SharcArchiveRes::ArchiveBlockHeader));
        Write(is_be, archive_header->byte_order, 0xFEFF);
        Write(is_be, archive_header->file_size, file_size);
        Write(is_be, archive_header->data_block_offset, data_block_offset);
        Write(is_be, archive_header->version, SharcArchiveRes::cArchiveVersion);
    }
    // FNTBlockHeader
    {
        SharcArchiveRes::FNTBlockHeader* const name_table_header = reinterpret_cast<SharcArchiveRes::FNTBlockHeader*>(archive8 + name_table_header_offset);
        rio::MemUtil::copy(name_table_header->signature, "SFNT", 4);
        Write(is_be, name_table_header->header_size, sizeof(SharcArchiveRes::FNTBlockHeader));
    }
    // FATBlockHeader
    {
        SharcArchiveRes::FATBlockHeader* const address_table_header = reinterpret_cast<SharcArchiveRes::FATBlockHeader*>(archive8 + address_table_header_offset);
        rio::MemUtil::copy(address_table_header->signature, "SFAT", 4);
        Write(is_be, address_table_header->header_size, sizeof(SharcArchiveRes::FATBlockHeader));
        Write(is_be, address_table_header->file_num, file_num);
        Write(is_be, address_table_header->hash_key, hash_key);
    }
    // Address Table Block (FATEntry[]) + Name Table Block + Data Block
    {
        SharcArchiveRes::FATEntry* const address_table = reinterpret_cast<SharcArchiveRes::FATEntry*>(archive8 + address_table_offset);
        char* const name_table = reinterpret_cast<char*>(archive8 + name_table_offset);
        u8* const data_block = archive8 + data_block_offset;

        std::map<u32, u8> collision;

        for (const auto& it : mFiles)
        {
            u32 hash = it.first;
            const auto& file = it.second;
            const std::string& name = file.first;

            collision.insert({ hash, 0 });
            if (!name.empty())
                collision[hash]++;
        }

        auto it = mFiles.cbegin();
        for (u32 i = 0; i < file_num; std::advance(it, 1), i++)
        {
            u32 hash = it->first;
            const auto& file = it->second;
            const std::string& name = file.first;
            const std::span<const u8> data = file.second;

            u32 name_offset = name_offsets[i];
            u32 data_start_offset = data_start_offsets[i];
            u32 data_end_offset = data_start_offset + data.size();

            SharcArchiveRes::FATEntry* const entry = &(address_table[i]);
            Write(is_be, entry->hash, hash);
            Write(is_be, entry->name_offset, (name_offset / SharcArchiveRes::cFileNameTableAlign) | (collision[hash] << 24));
            Write(is_be, entry->data_start_offset, data_start_offset);
            Write(is_be, entry->data_end_offset, data_end_offset);

            if (!name.empty())
                rio::MemUtil::copy(name_table + name_offset, name.c_str(), name.length());

            rio::MemUtil::copy(data_block + data_start_offset, data.data(), data.size());
        }
    }

    return { archive8, file_size };
}
