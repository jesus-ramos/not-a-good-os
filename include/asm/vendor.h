#ifndef _ASM_VENDOR_H
#define _ASM_VENDOR_H

enum x86_cpu_vendor
{
    INTEL = 0,
    CYRIX,
    AMD,
    UMC,
    CENTAUR,
    TRANSMETA,
    NSC,
    NUM,
    UNKNOWN = 0xFF
};

#endif /* _ASM_VENDOR_H */
