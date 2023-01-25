#include <resource/SZSDecompressor.h>

#include <math/rio_Math.h>
#include <misc/rio_MemUtil.h>

SZSDecompressor::DecompContext::DecompContext()
{
    initialize(NULL);
}

SZSDecompressor::DecompContext::DecompContext(void* dst)
{
    initialize(dst);
}

void SZSDecompressor::DecompContext::initialize(void* dst)
{
    destp           = static_cast<u8*>(dst);
    destCount       = 0;
    forceDestCount  = 0;
    flagMask        = 0;
    flags           = 0;
    packHigh        = 0;
    step            = SZSDecompressor::STEP_NORMAL;
    lzOffset        = 0;
    headerSize      = SZSDecompressor::getHeaderSize();
}

u8* SZSDecompressor::tryDecomp(rio::FileDevice::LoadArg& arg)
{
    const u8*   src         = nullptr;
    u32         src_size    = 0;
    {
        rio::FileDevice::LoadArg load_arg;
        load_arg.path = arg.path;

        src = rio::FileDeviceMgr::instance()->tryLoad(load_arg);
        if (src)
        {
            RIO_ASSERT(load_arg.need_unload);
            src_size = load_arg.read_size;
        }
    }

    return tryDecomp_(
        src, src_size, true,
        arg.buffer, arg.buffer_size, arg.alignment,
        &arg.read_size, &arg.roundup_size, &arg.need_unload
    );
}

u8* SZSDecompressor::tryDecomp_(
        const u8* src, u32 src_size, bool src_need_delete,
        u8* dst, u32 dst_size, s32 alignment,
        u32* out_size, u32* out_buffer_size, bool* out_need_delete
)
{
    if (!src)
        return nullptr;

    if (src_size < getHeaderSize())
    {
        RIO_LOG("SZSDecompressor::tryDecomp_(): Invalid header size.\n");
        RIO_ASSERT(false);

        if (src_need_delete)
            rio::MemUtil::free(const_cast<u8*>(src));

        return nullptr;
    }

    u32 decomp_size = getDecompSize(src);
    RIO_ASSERT(decomp_size > 0);

    s32 decomp_alignment = getDecompAlignment(src);
    if (decomp_alignment && (decomp_alignment & -decomp_alignment) != rio::Mathi::abs(decomp_alignment))
    {
        RIO_LOG("SZSDecompressor::tryDecomp_(): decomp_alignment[%d] must be power of 2.\n", decomp_alignment);
        RIO_ASSERT(false);
    }

    if (dst && decomp_size > dst_size)
        decomp_size = dst_size;

    u32 buffer_size;
    {
        constexpr s32 align = 0x20;
      //buffer_size = decomp_size + (align - (decomp_size - 1) % align);
        buffer_size = ((decomp_size - 1) | (align - 1)) + 1;
    }

    bool need_delete = false;

    if (!dst)
    {
        if (alignment == 0)
        {
            alignment = decomp_alignment;
            if (alignment == 0)
                alignment = 0x20;
        }
        else
        {
            if (decomp_alignment && (alignment % decomp_alignment))
            {
                RIO_LOG("SZSDecompressor::tryDecomp_(): alignment[%d] doesn\'t meet decomp_alignment[%d].\n", alignment, decomp_alignment);
                RIO_ASSERT(false);
            }
        }

        dst = static_cast<u8*>(rio::MemUtil::alloc(buffer_size, alignment));
        if (!dst)
        {
            RIO_LOG("SZSDecompressor::tryDecomp_(): cannot alloc dst buf\n");
            RIO_ASSERT(false);

            if (src_need_delete)
                rio::MemUtil::free(const_cast<u8*>(src));

            return nullptr;
        }
        else
        {
            need_delete = true;
        }
    }
    else
    {
        if (decomp_alignment && ((uintptr_t)dst & (decomp_alignment - 1u)))
        {
#if !RIO_IS_WIN
            RIO_LOG("SZSDecompressor::tryDecomp_(): dst is not aligned with decomp_alignment[%d]\n", decomp_alignment);
            RIO_ASSERT(false);
#endif
        }
    }

#if RIO_IS_CAFE
    s32 error = decomp(dst, buffer_size, src, src_size);
#else
    DecompContext context(dst);
    context.forceDestCount = decomp_size;

    s32 error = streamDecomp(&context, src, src_size);
    if (error > 0)
    {
        // When the return is > 0, it's the expected remaining length of decompressed data (dst)
        RIO_LOG("SZSDecompressor::tryDecomp_(): Warning: incomplete src data, dst missing %d bytes.\n", error);
    }
    else
#endif // RIO_IS_CAFE
    if (error < 0)
    {
        RIO_LOG("SZSDecompressor::tryDecomp_(): decomp() returned error(%d).\n", error);
        RIO_ASSERT(false);

        if (need_delete)
            delete[] dst;

        if (src_need_delete)
            rio::MemUtil::free(const_cast<u8*>(src));

        return nullptr;
    }


    if (src_need_delete)
        rio::MemUtil::free(const_cast<u8*>(src));

    if (out_size)
        *out_size = decomp_size;

    if (out_buffer_size)
        *out_buffer_size = buffer_size;

    if (out_need_delete)
        *out_need_delete = need_delete;

    return dst;
}

u32 SZSDecompressor::getDecompAlignment(const void* header)
{
    const u32* const ptr = static_cast<const u32*>(header);
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    return __builtin_bswap32(ptr[2]);
#else
    return ptr[2];
#endif
}

u32 SZSDecompressor::getDecompSize(const void* header)
{
    const u32* const ptr = static_cast<const u32*>(header);
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    return __builtin_bswap32(ptr[1]);
#else
    return ptr[1];
#endif
}

#if RIO_IS_CAFE

namespace {

__attribute__((noinline, aligned(0x20))) s32 decodeSZSCafeAsm_(void* dst, const void* src)
{
    // Force these values to be used or code breaks by constant propagation optimization
    register void*       dst_force asm("r3") = dst;
    register const void* src_force asm("r4") = src;
    asm volatile ("" :: "r"(dst_force), "r"(src_force));

    asm volatile (
        "lwz %r5, 0x4(%r4)\n\t" \
        "li %r11, 0x20\n\t" \
        "li %r6, 0\n\t" \
        "mr %r0, %r5\n\t" \
        "addi %r4, %r4, 0xf\n\t" \
        "subi %r3, %r3, 1\n\t" \
        "cmpwi %r5, 0x132\n\t" \
        "ble _final_decloop0\n\t" \
        "subi %r5, %r5, 0x132\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n\t" \
        "nop\n" \
        "_decloop0:\n\t" \
        "rlwinm. %r6, %r6, 0x1f, 1, 0x1f\n\t" \
        "bne _decloop1\n\t" \
        "lbzu %r7, 1(%r4)\n\t" \
        "li %r6, 0x80\n" \
        "_decloop1:\n\t" \
        "and. %r8, %r6, %r7\n\t" \
        "lbzu %r8, 1(%r4)\n\t" \
        "beq _decloop2\n\t" \
        "andi. %r9, %r3, 0x1f\n\t" \
        "bne _decloop1x\n\t" \
        "dcbz %r11, %r3\n" \
        "_decloop1x:\n\t" \
        "subic. %r5, %r5, 1\n\t" \
        "stbu %r8, 1(%r3)\n\t" \
        "bne _decloop0\n\t" \
        "b _decloop8\n" \
        "_decloop2:\n\t" \
        "lbzu %r9, 1(%r4)\n\t" \
        "rlwinm. %r10, %r8, 0x1c, 4, 0x1f\n\t" \
        "bne _decloop3\n\t" \
        "lbzu %r10, 1(%r4)\n\t" \
        "addi %r10, %r10, 0x10\n" \
        "_decloop3:\n\t" \
        "addi %r10, %r10, 2\n\t" \
        "rlwimi %r9, %r8, 8, 0x14, 0x17\n\t" \
        "subf %r5, %r10, %r5\n\t" \
        "subf %r8, %r9, %r3\n\t" \
        "mtctr %r10\n\t" \
        "addi %r8, %r8, 1\n" \
        "_decloop4:\n\t" \
        "andi. %r9, %r3, 0x1f\n\t" \
        "lbz %r9, -1(%r8)\n\t" \
        "addi %r8, %r8, 1\n\t" \
        "bne _decloop5\n\t" \
        "dcbz %r11, %r3\n" \
        "_decloop5:\n\t" \
        "stbu %r9, 1(%r3)\n\t" \
        "bdnz _decloop4\n\t" \
        "cmpwi %r5, 0\n\t" \
        "bgt _decloop0\n" \
        "_decloop8:\n\t" \
        "addi %r5, %r5, 0x132\n\t" \
        "cmpwi %r5, 0\n\t" \
        "ble _final_decloop8\n" \
        "_final_decloop0:\n\t" \
        "rlwinm. %r6, %r6, 0x1f, 1, 0x1f\n\t" \
        "bne _final_decloop1\n\t" \
        "lbzu %r7, 1(%r4)\n\t" \
        "li %r6, 0x80\n" \
        "_final_decloop1:\n\t" \
        "and. %r8, %r6, %r7\n\t" \
        "lbzu %r8, 1(%r4)\n\t" \
        "beq _final_decloop2\n\t" \
        "subic. %r5, %r5, 1\n\t" \
        "stbu %r8, 1(%r3)\n\t" \
        "bne _final_decloop0\n\t" \
        "b _final_decloop8\n" \
        "_final_decloop2:\n\t" \
        "lbzu %r9, 1(%r4)\n\t" \
        "rlwinm. %r10, %r8, 0x1c, 4, 0x1f\n\t" \
        "bne _final_decloop3\n\t" \
        "lbzu %r10, 1(%r4)\n\t" \
        "addi %r10, %r10, 0x10\n" \
        "_final_decloop3:\n\t" \
        "addi %r10, %r10, 2\n\t" \
        "rlwimi %r9, %r8, 8, 0x14, 0x17\n\t" \
        "subf. %r5, %r10, %r5\n\t" \
        "blt _final_decloop8\n\t" \
        "subf %r8, %r9, %r3\n\t" \
        "mtctr %r10\n\t" \
        "addi %r8, %r8, 1\n" \
        "_final_decloop4:\n\t" \
        "lbz %r9, -1(%r8)\n\t" \
        "addi %r8, %r8, 1\n\t" \
        "stbu %r9, 1(%r3)\n\t" \
        "bdnz _final_decloop4\n\t" \
        "cmpwi %r5, 0\n\t" \
        "bgt _final_decloop0"
    );

    s32 register error asm("r3");
    asm volatile ("" : [error] "=r"(error));

    asm volatile (
        "_final_decloop8:\n\t" \
        "mr %r3, %r0\n\t" \
        "blr" // Nintendo, what?
    );

    return error;
}

}

s32 SZSDecompressor::decomp(void* dst, u32 dst_size, const void* src, u32 src_size)
{
    RIO_ASSERT(src_size >= getHeaderSize());
    RIO_ASSERT(dst);
    RIO_ASSERT(src);

    if ((uintptr_t)dst % 0x20)
    {
        RIO_LOG("SZSDecompressor::decomp(): dst[0x%x] must be aligned to 32.\n", (uintptr_t)dst);
        RIO_ASSERT(false);
    }

    if (dst_size % 0x20)
    {
        RIO_LOG("SZSDecompressor::decomp(): dst_size[%u] must be multiple of 32.\n", dst_size);
        RIO_ASSERT(false);
    }

    u32 magic = *static_cast<const u32*>(src);
    if (magic != 0x59617A30) // Yaz0
        return -1;

    u32 decomp_size = getDecompSize(src);
    if (dst_size < decomp_size)
        return -2;

    return decodeSZSCafeAsm_(dst, src);
}

#endif // RIO_IS_CAFE

s32 SZSDecompressor::readHeader_(DecompContext* context, const u8* srcp, u32 src_size)
{
    s32 header_size = 0;

    while (context->headerSize > 0)
    {
        context->headerSize--;

        if (context->headerSize == 0xF)
        {
            if (*srcp != 'Y')
                return -1;
        }
        else if (context->headerSize == 0xE)
        {
            if (*srcp != 'a')
                return -1;
        }
        else if (context->headerSize == 0xD)
        {
            if (*srcp != 'z')
                return -1;
        }
        else if (context->headerSize == 0xC)
        {
            if (*srcp != '0')
                return -1;
        }

        else if (context->headerSize >= 8)
            context->destCount |= static_cast<u32>(*srcp) << ((static_cast<u32>(context->headerSize) - 8) << 3);

        srcp++; header_size++; src_size--;
        if (src_size == 0 && context->headerSize > 0)
            return header_size;
    }

    if (context->forceDestCount > 0 && context->forceDestCount < context->destCount)
        context->destCount = context->forceDestCount;

    return header_size;
}

s32 SZSDecompressor::streamDecomp(DecompContext* context, const void* src, u32 len)
{
    RIO_ASSERT(context);
    RIO_ASSERT(src);

    const u8* srcp = static_cast<const u8*>(src);

    if (context->headerSize > 0)
    {
        s32 header_size = readHeader_(context, srcp, len);
        if (header_size < 0)
            return header_size;

        srcp += header_size; len -= header_size;
        if (len == 0)
        {
            if (context->headerSize == 0)
                return context->destCount;

            return -1;
        }
    }

    while (context->destCount > 0)
    {
        if (context->step == STEP_LONG)
        {
            u32 n = (*srcp++) + 0x12; len--;
            if (s32(n) > context->destCount)
            {
                if (context->forceDestCount == 0)
                    return -2;

                n = static_cast<u16>(context->destCount);
            }

            context->destCount -= n;

            do
            {
                *context->destp = *(context->destp - context->lzOffset);
                context->destp++;
            }
            while (--n != 0);

            context->step = STEP_NORMAL;
        }
        else if (context->step == STEP_SHORT)
        {
            u32 offsetLen = static_cast<u32>(context->packHigh) << 8 | *srcp++; len--;
            context->lzOffset = (offsetLen & 0xFFFu) + 1;

            u32 n = offsetLen >> 12;
            if (n == 0)
                context->step = STEP_LONG;

            else
            {
                n  += 2;
                if (s32(n) > context->destCount)
                {
                    if (context->forceDestCount == 0)
                        return -2;

                    n = static_cast<u16>(context->destCount);
                }

                context->destCount -= n;

                do
                {
                    *context->destp = *(context->destp - context->lzOffset);
                    context->destp++;
                }
                while (--n != 0);

                context->step = STEP_NORMAL;
            }
        }
        else
        {
            if (context->flagMask == 0)
            {
                context->flags = *srcp++; len--;
                context->flagMask = 0x80;
                if (len == 0)
                    break;
            }

            if ((context->flags & context->flagMask) != 0)
            {
                *context->destp++ = *srcp++;
                context->destCount--;
            }
            else
            {
                context->packHigh = *srcp++;
                context->step = STEP_SHORT;
            }

            len--;
            context->flagMask >>= 1;
        }

        if (len == 0)
            break;
    }

    if (context->destCount == 0 && context->forceDestCount == 0 && len > 0x20)
        return -1;

    return context->destCount;
}
