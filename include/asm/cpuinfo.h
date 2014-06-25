#ifndef _CPU_INFO_H
#define _CPU_INFO_H

#include <kernel/types.h>

#include <asm/cpufeature.h>

/* XXX: Stubbed for now, should be autoconfig'd */
#define X86_L1_CACHE_SHIFT (6)
#define L1_CACHE_SHIFT (X86_L1_CACHE_SHIFT)
#define L1_CACHE_BYTES (1 << L1_CACHE_SHIFT)

/**
 * @brief X86 Cpu info
 */
struct cpuinfo_x86
{
    uint8_t family; /**< CPU family */
    uint8_t vendor; /**< CPU vendor */
    uint8_t model; /**< CPU model */
    uint8_t mask;
#ifndef __X86_64__
    char wp_works_ok;
    char hard_math;
    char rfu;
    char pad0;
#else
    int tlbsize;
#endif /* __X86_64__ */
    uint8_t virtual_bits;
    uint8_t physical_bits;
    uint8_t coreid_bits;
    uint32_t extended_cpuid_level;
    int cpuid_level;
    uint32_t capability[NUM_INFO_WORDS + NUM_BUG_FLAGS];
    char vendor_id[16];
    char model_id[64];
    int cache_size; /**< Cache size in kb */
    int cache_alignment; /**< Cache alignment in bytes */
    int power;
    unsigned long loops_per_jiffy;
    uint16_t max_cores;
    uint16_t apicid;
    uint16_t initial_apicid;
    uint16_t clflush_size;
    uint16_t booted_cores;
    uint16_t proc_id;
    uint16_t core_id;
    uint8_t compute_unit_id;
    uint16_t cpu_index;
    uint32_t microcode;
} __attribute__((__aligned__(SMP_CACHE_BYTES)));

#endif /* _CPU_INFO_H */
