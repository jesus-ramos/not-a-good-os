#include <kernel/lock.h>
#include <kernel/screen.h>
#include <kernel/stdio.h>
#include <kernel/timer.h>

#include <asm/asm_common.h>
#include <asm/atomic_ops.h>
#include <asm/desc_tables.h>

int kinit()
{
    fb_clear();
    init_descriptor_tables();
    enable_interrupts();
    
    return 0;
}

int kmain(void *mbd, unsigned int magic)
{
    int test;
    int other_test;
    spinlock_t lock;
    
    if (magic != 0x2BADB002)
    {
        fb_put_str("BAD MAGIC VALUE FROM LOADER!!! PANIC!!!");
        return 0xDEADBEEF;
    }

    kinit();
    
    //init_timer(50);

    printk("This %d string is awesome %s\n", 123, "testing string");

    test = 5;

    atomic_incrememt(&test);

    printk("Increment: %d\n", test);

    atomic_decrement(&test);

    printk("Decrement: %d\n", test);

    test = 5;
    other_test = 400;

    other_test = atomic_xchg(&test, other_test);

    printk("TEST: %d, OTHER_TEST: %d\n", test, other_test);

    init_spinlock(&lock);

    spin_lock(&lock);

    printk("Locking this thing\n");

    spin_lock(&lock);

    printk("SHOULD NEVER GET HERE!!!\n");

    while (1);
    
    return 0;
}
