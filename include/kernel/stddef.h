#ifndef _STDDEF_H
#define _STDDEF_H

/**
 * @brief Gets the offset of a member (in bytes) inside of structure
 *
 * @param type the type of the structure that member is inside
 * @param member the name of the member that you want to get an offset for
 *
 * @return offset in bytes of member inside type
 */
#define offsetof(type, member) ((size_t)&((type *)0)->member)

/**
 * @brief Gets a pointer to the structure that a member is embedded in (C style
 * OOP)
 *
 * @param[in] ptr pointer to the embedded member
 * @param type the type of the structure that holds member
 * @param member the name of the member inside the structure you want
 *
 * @return the structure that contains member
 */
#define container_of(ptr, type, member)                         \
    ({                                                          \
        const typeof(((type *)0)->member) *__mptr = (ptr);      \
        (type *)((char *)__mptr - offsetof(type, member));      \
    })

#endif /* _STDDEF_H */
