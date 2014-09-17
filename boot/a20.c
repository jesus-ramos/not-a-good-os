#include <asm/boot.h>

#define A20_ENABLE_ATTEMPTS 255
#define A20_ADDR (0x480)
#define A20_TEST_FAST_ATTEMPTS (1 << 5)
#define A20_TEST_SLOW_ATTEMPTS (1 << 21)

/**
 * @brief Test to see if A20 is enabled
 *
 * @param attempts number of times to test if A20 is enabled, use more for
 * "slower" methods of enabling
 *
 * @return 1 if the test passed, 0 if a20 is not enabled (as far as we know)
 */
static int a20_enabled_test(int attempts)
{
    int set = 0;
    int prev; /* Store the old value to set once we're done testing */
    int counter;

    prev = read_fs32(A20_ADDR);
    counter = prev;

    set_fs(0x0000); /* It's just zero but just to make the code align nicely */
    set_gs(0xFFFF);

    /* Better try this multiple times, good old A20... */
    while (attempts--)
    {
        set_fs32(++counter, A20_ADDR); /* Let's write something */
        io_delay(); /* Wait for hardware to catch up */
        /* See if something actually changed */
        set = read_gs32(A20_ADDR + 0x10) ^ counter;
        if (set) /* Phew... something changed */
            break;
        /* Keep trying I guess... */
    }

    set_fs32(prev, A20_ADDR); /* Tidy things up just in case */

    return set;
}

/**
 * @brief Do a "quick" test to see if A20 is enabled
 *
 * @return 1 if a20 is enabled, 0 if it's not enabled
 */
static inline int a20_test_fast()
{
    return a20_enabled_test(A20_TEST_FAST_ATTEMPTS);
}

/**
 * @brief Do a slow test to see if A20 is enabled
 *
 * @return 1 if a20 is enabled, 0 if it's not enabled
 */
static inline int a20_test_slow()
{
    return a20_enabled_test(A20_TEST_SLOW_ATTEMPTS);
}

/**
 * @brief Enable the A20 line on the CPU to prepare for entering protected mode
 *
 * Enabling A20 is a bit of a complicated matter, ranging from simple
 * enable/checks to using the keyboard for some legacy reason...
 *
 * @return 0 if the A20 line was enabled, -1 if we failed after multiple
 * attempts
 */
int enable_a20_line()
{
    int attempts = A20_ENABLE_ATTEMPTS;

    while (attempts--)
    {
        if (a20_test_fast()) /* Maybe we'll get lucky and it's already enabled */
            return 0;


    }

    return -1;
}
