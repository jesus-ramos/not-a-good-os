/**
 * @file
 *
 * Basic doubly linked list implementation
 */

#ifndef _LIST_H
#define _LIST_H

#include <kernel/stddef.h>

/**
 * @brief Structure that maintains the pointers in a linked list. Embed this
 * into whatever structure you want to maintain in a linked list.
 */
struct list_head
{
    struct list_head *prev;
    struct list_head *next;
};

/**
 * @brief Internal function called by list_add(), call it instead of this one
 */
static inline void _list_add(struct list_head *new,
                             struct list_head *prev,
                             struct list_head *next)
{
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}

/**
 * @brief Add an item to the end of the list
 *
 * @param[out] new new item to append to the list
 * @param[out] head head of the list you want to append to
 */
static inline void list_add_tail(struct list_head *new, struct list_head *head)
{
    _list_add(new, head->prev, head);
}

/**
 * @brief Deletes an item from a linked list. Does not free the item.
 *
 * @param[out] entry the entry to remove from the list
 */
static inline void list_del(struct list_head *entry)
{
    struct list_head *prev;
    struct list_head *next;

    prev = entry->prev;
    next = entry->next;

    next->prev = prev;
    prev->next = next;
}

/**
 * @brief Initializes a list head structure to an empty list
 *
 * @param[out] list pointer to the struct list_head you want to initialize
 */
static inline void init_list_head(struct list_head *list)
{
    list->next = list;
    list->prev = list;
}

/**
 * @brief Checks if a list is empty
 *
 * @param[in] head the head of the list to check
 *
 * @return 1 if the list is empty, 0 otherwise
 */
static inline int list_empty(struct list_head *head)
{
    return head->next == head;
}

/**
 * @brief Gets the structure that the struct list_head is embedded inside
 * provided you know the type
 *
 * @param[in] ptr pointer to the struct list_head
 * @param type the type of structure that the struct list_head is embedded in
 * @param member the name of the struct list_head variable inside struct type
 *
 * @return Pointer to the struct which has the struct list_head inside
 */
#define list_entry(ptr, type, member)           \
    container_of(ptr, type, member)

/**
 * @brief For each loop that iterates through a linked list. The list ordering
 * cannot be modified while using this loop.
 *
 * @param[out] pos a struct list_head * to use as an iterator
 * @param[in] head pointer to the head of the list
 * @param member the name of the struct list_head variable in the structure you
 * want to retrieve
 */
#define list_for_each_entry(pos, head, member)                          \
    for (pos = list_entry((head)->next, typeof(*pos), member);          \
         &pos->member != (head);                                        \
         pos = list_entry(pos->member.next, typeof(*pos), member))

/**
 * @brief For each loop that iterates through a linked list. List modification
 * is allowed in this loop.
 *
 * @param[out] pos a struct list_head * to use as an iterator
 * @param[out] n backup pointer in case the list is modified
 * @param[in] head the head of the list to iterate
 * @param member the name of the struct list_head variable in the structure you
 * want to retrieve
 */
#define list_for_each_entry_safe(pos, n, head, member)                  \
    for (pos = list_entry((head)->next, typeof(*pos), member),          \
             n = list_entry(pos->member.next, typeof(*pos), member);    \
         &pos->member != (head);                                        \
         pos = n, n = list_entry(n->member.next, typeof(*n), member))

#endif /* _LIST_H */
