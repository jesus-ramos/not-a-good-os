#include "screen.h"

void kmain(void *mbd, unsigned int magic)
{
    if (magic != 0x2BADB002)
        prints("BAD MULTIBOOT ABORT!!!", 0x07);

    prints("For now I'm completely useless", 0x07);
}
