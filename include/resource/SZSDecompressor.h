#pragma once

#include <filedevice/rio_FileDeviceMgr.h>

class SZSDecompressor
{
public:
    enum Step
    {
        STEP_NORMAL = 0,
        STEP_SHORT,
        STEP_LONG,
    };

public:
    struct DecompContext
    {
        DecompContext();
        DecompContext(void* dst);

        void initialize(void* dst);

        u8*     destp;
        s32     destCount;
        s32     forceDestCount;
        u8      flagMask;
        u8      flags;
        u8      packHigh;
        Step    step;
        u16     lzOffset;
        u8      headerSize;
    };

public:
    static u8* tryDecomp(rio::FileDevice::LoadArg& arg);

    static inline u8* tryDecomp(
        const u8* src, u32 src_size,
        u8* dst = nullptr, u32 dst_size = 0, s32 alignment = 0,
        u32* out_size = nullptr, u32* out_buffer_size = nullptr, bool* out_need_delete = nullptr
    )
    {
        return tryDecomp_(
            src, src_size, false,
            dst, dst_size, alignment,
            out_size, out_buffer_size, out_need_delete
        );
    }

private:
    static u8* tryDecomp_(
        const u8* src, u32 src_size, bool src_need_delete,
        u8* dst, u32 dst_size, s32 alignment,
        u32* out_size, u32* out_buffer_size, bool* out_need_delete
    );

public:
    static inline u32 getHeaderSize()
    {
        return 0x10;
    }

    static u32 getDecompAlignment(const void* header);
    static u32 getDecompSize(const void* header);

#if RIO_IS_CAFE
    static s32 decomp(void* dst, u32 dst_size, const void* src, u32 src_size);
#endif // RIO_IS_CAFE
    static s32 streamDecomp(DecompContext* context, const void* src, u32 len);

private:
    static s32 readHeader_(DecompContext* context, const u8* srcp, u32 src_size);
};
