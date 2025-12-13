#include <stdint.h>
#include <stdbool.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wimplicit-fallthrough"

/*
 * Give hints to the compiler for branch prediction optimization.
 */
#if defined(__clang__) || (defined(__GNUC__) && (__GNUC__ > 2))
#define FASTLZ_LIKELY(c) (__builtin_expect(!!(c), 1))
#define FASTLZ_UNLIKELY(c) (__builtin_expect(!!(c), 0))
#else
#define FASTLZ_LIKELY(c) (c)
#define FASTLZ_UNLIKELY(c) (c)
#endif

/*
 * Specialize custom 64-bit implementation for speed improvements.
 */
#if defined(__x86_64__) || defined(_M_X64) || defined(__aarch64__)
#define FLZ_ARCH64
#endif

/*
 * Workaround for DJGPP to find uint8_t, uint16_t, etc.
 */
#if defined(__MSDOS__) && defined(__GNUC__)
#include <stdint-gcc.h>
#endif

#if defined(FASTLZ_USE_MEMMOVE) && (FASTLZ_USE_MEMMOVE == 0)

static void fastlz_memmove(uint8_t *dest, const uint8_t *src, uint32_t count)
{
    do
    {
        *dest++ = *src++;
    } while (--count);
}

static void fastlz_memcpy(uint8_t *dest, const uint8_t *src, uint32_t count)
{
    return fastlz_memmove(dest, src, count);
}

#else

#include <string.h>

static void fastlz_memmove(uint8_t *dest, const uint8_t *src, uint32_t count)
{
    if ((count > 4) && (dest >= src + count))
    {
        memmove(dest, src, count);
    }
    else
    {
        switch (count)
        {
        default:
            do
            {
                *dest++ = *src++;
            } while (--count);
            break;
        case 3:
            *dest++ = *src++;
        case 2:
            *dest++ = *src++;
        case 1:
            *dest++ = *src++;
        case 0:
            break;
        }
    }
}

static void fastlz_memcpy(uint8_t *dest, const uint8_t *src, uint32_t count) { memcpy(dest, src, count); }

#endif

#if defined(FLZ_ARCH64)

static uint32_t flz_readu32(const void *ptr) { return *(const uint32_t *)ptr; }

static uint32_t flz_cmp(const uint8_t *p, const uint8_t *q, const uint8_t *r)
{
    const uint8_t *start = p;

    if (flz_readu32(p) == flz_readu32(q))
    {
        p += 4;
        q += 4;
    }
    while (q < r && *p == *q)
    {
        ++p;
        ++q;
    }
    return (uint32_t)(p - start);
}

#else

static uint32_t flz_readu32(const void *ptr)
{
    const uint8_t *p = (const uint8_t *)ptr;
    return (p[3] << 24) | (p[2] << 16) | (p[1] << 8) | p[0];
}

static uint32_t flz_cmp(const uint8_t *p, const uint8_t *q, const uint8_t *r)
{
    const uint8_t *start = p;
    while (q < r && *p == *q)
    {
        ++p;
        ++q;
    }
    return (uint32_t)(p - start);
}

#endif

#define MAX_COPY 8
#define MAX_LEN 273
#define MAX_MATCH_DISTANCE 4096

#define HASH_LOG 13
#define HASH_SIZE (1 << HASH_LOG)
#define HASH_MASK (HASH_SIZE - 1)

static uint16_t flz_hash(uint32_t v)
{
    uint32_t h = (v * 2654435769LL) >> (32 - HASH_LOG);
    return h & HASH_MASK;
}

/* special case of memcpy: at most MAX_COPY bytes */
static void flz_smallcopy(uint8_t *dest, const uint8_t *src, uint32_t count)
{
#if defined(FLZ_ARCH64)
    if (count >= 4)
    {
        const uint32_t *p = (const uint32_t *)src;
        uint32_t *q = (uint32_t *)dest;
        while (count > 4)
        {
            *q++ = *p++;
            count -= 4;
            dest += 4;
            src += 4;
        }
    }
#endif
    fastlz_memcpy(dest, src, count);
}

/* special case of memcpy: exactly MAX_COPY bytes */
static void yaz0w_maxcopy(void *dest, const void *src)
{
#if defined(FLZ_ARCH64)
    const uint32_t *p = (const uint32_t *)src;
    uint32_t *q = (uint32_t *)dest;
    *q++ = *p++;
    *q++ = *p++;
#else
    fastlz_memcpy((uint8_t *)dest, (const uint8_t *)src, MAX_COPY);
#endif
}

typedef struct
{
    uint8_t *op;    /* current write position                              */
    uint8_t *flagp; /* pointer to current flag byte                        */
    uint8_t mask;   /* current mask bit (starts at 0x80, shifts right)     */
} yaz0w_t;

/* start a new flag byte */
static inline void yaz0w_newgroup(yaz0w_t *w)
{
    w->flagp = w->op;
    *w->op++ = 0;
    w->mask = 0x80;
}

/* emit N literal bytes  */
static inline void yaz0w_literals(yaz0w_t *w, uint32_t runs, const uint8_t *src)
{
    if (FASTLZ_UNLIKELY(runs == 0))
        return;

    if (w->mask != 0x80)
    {
        uint32_t room = (uint32_t)__builtin_ctz(w->mask) + 1;
        const bool less_than_room = runs < room;
        uint32_t n = less_than_room ? runs : room;

        for (uint32_t i = 0; i < n; ++i)
        {
            *w->flagp |= w->mask;
            w->mask >>= 1;
        }

        flz_smallcopy(w->op, src, n);
        w->op += n;
        src += n;
        runs -= n;

        if (/* runs == 0 */ less_than_room)
            return;
        else
            yaz0w_newgroup(w);
    }

    while (runs >= MAX_COPY)
    {
        *w->flagp = 0xFF;
        yaz0w_maxcopy(w->op, src);
        w->op += MAX_COPY;
        src += MAX_COPY;
        runs -= MAX_COPY;
        yaz0w_newgroup(w);
    }

    if (runs)
    {
        *w->flagp |= 0xFFu << (8 - runs);
        w->mask = 0x80u >> runs;

        flz_smallcopy(w->op, src, runs);
        w->op += runs;
    }
}

/* emit one LZ match (flag-bit = 0, distance 1-4096, len 3-273) */
static inline void yaz0w_match(yaz0w_t *w, uint32_t len, uint32_t distance)
{
    distance--;
    if (FASTLZ_UNLIKELY(len > MAX_LEN))
        while (len > MAX_LEN)
        {
            /* If a full 273-byte chunk would leave a tail of only 1-2 bytes,
               emit 271 bytes instead so the tail will be ≥3 bytes. */
            uint32_t chunk = FASTLZ_UNLIKELY(len - MAX_LEN < 3) ? (MAX_LEN - 2) : MAX_LEN;

            /* -------- long 3-byte form --------------- */
            uint8_t packHigh = (distance >> 8) & 0x0F;
            *w->op++ = packHigh;
            *w->op++ = distance & 0xFF;
            *w->op++ = (uint8_t)(chunk - 0x12);

            /* one flag consumed                                             */
            w->mask >>= 1;
            if (FASTLZ_UNLIKELY(w->mask == 0))
                yaz0w_newgroup(w);

            len -= chunk;
        }

    /* -------- single final chunk, 3…273 bytes --------------------- */
    if (len <= 17) /* short 2-byte form     */
    {
        uint16_t code = ((len - 2) << 12) | distance;
        *w->op++ = code >> 8;
        *w->op++ = code & 0xFF;
    }
    else /* long 3-byte form      */
    {
        uint8_t packHigh = (distance >> 8) & 0x0F; /* len nibble = 0        */
        *w->op++ = packHigh;
        *w->op++ = distance & 0xFF;
        *w->op++ = (uint8_t)(len - 0x12);
    }

    /* consume the flag bit for that final token                       */
    w->mask >>= 1;
    if (FASTLZ_UNLIKELY(w->mask == 0))
        yaz0w_newgroup(w);
}

int yaz0_compress(const void *input, int length, void *output)
{
    const uint8_t *ip = (const uint8_t *)input;
    const uint8_t *ip_start = ip;
    const uint8_t *ip_bound = ip + length - 4; /* because readU32 */
    const uint8_t *ip_limit = ip + length - 12 - 1;
    uint8_t *op = (uint8_t *)output;

    op[0] = 'Y';
    op[1] = 'a';
    op[2] = 'z';
    op[3] = '0';
    op[4] = (length >> 24) & 0xFF;
    op[5] = (length >> 16) & 0xFF;
    op[6] = (length >> 8) & 0xFF;
    op[7] = (length) & 0xFF;
    /* alignment and reserved fields -> zero */
    for (int i = 8; i < 16; ++i)
        op[i] = 0;

    /* writer starts after 16-byte header */
    yaz0w_t w;
    w.op = op + 16;
    yaz0w_newgroup(&w);

    uint32_t htab[HASH_SIZE] = {0};

    /* we start with literal copy */
    const uint8_t *anchor = ip;
    ip += 2;

    /* main loop */
    while (FASTLZ_LIKELY(ip < ip_limit))
    {
        const uint8_t *ref;
        uint32_t distance, cmp, seq, hash;

        /* find potential match */
        do
        {
            seq = flz_readu32(ip) & 0xffffff;
            hash = flz_hash(seq);
            ref = ip_start + htab[hash];
            htab[hash] = ip - ip_start;
            distance = ip - ref;
            cmp = FASTLZ_LIKELY(distance < MAX_MATCH_DISTANCE) ? flz_readu32(ref) & 0xffffff : 0x1000000;
            if (FASTLZ_UNLIKELY(ip >= ip_limit))
                break;
            ++ip;
        } while (seq != cmp);

        if (FASTLZ_UNLIKELY(ip >= ip_limit))
            break;
        --ip;

        if (FASTLZ_LIKELY(anchor < ip))
        {
            yaz0w_literals(&w, (uint32_t)(ip - anchor), anchor);
        }

        uint32_t len = flz_cmp(ref + 3, ip + 3, ip_bound) + 3;
        yaz0w_match(&w, len, distance);

        /* update the hash at match boundary */
        ip += len;
        anchor = ip;

        seq = flz_readu32(ip);
        hash = flz_hash(seq & 0xFFFFFF);
        htab[hash] = ip++ - ip_start;
        seq >>= 8;
        hash = flz_hash(seq);
        htab[hash] = ip++ - ip_start;
    }

    uint32_t copy = ip_start + length - anchor;
    yaz0w_literals(&w, copy, anchor);

    return (int)(w.op - (uint8_t *)output);
}

#pragma GCC diagnostic pop