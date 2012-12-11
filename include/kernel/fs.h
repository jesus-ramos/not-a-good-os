#ifndef _FS_H
#define _FS_H

#include <kernel/types.h>

#define MAX_FILENAME_LEN 128

struct file;

struct file_operations
{
    size_t (*read)(struct file *file, size_t offset, size_t size,
                   uint8_t *buffer);
    size_t (*write)(struct file *file, size_t offset, size_t size,
                    uint8_t *buffer);
    void (*open)(struct file *file);
    void (*close)(struct file *file);
    struct dirent *(*readdir)(struct file *file, unsigned long index);
    struct file *(*finddir)(struct file *file, char *name);
};

struct file
{
    char name[MAX_FILENAME_LEN];
    unsigned int mask;
    unsigned int uid;
    unsigned int gid;
    unsigned int flags;
    unsigned long inode;
    size_t length;
    unsigned int impl;
    struct file_operations *fops;
    struct file *file_ptr;
};

struct dirent
{
    char name[MAX_FILENAME_LEN];
    unsigned long inode_num;
};

extern struct file *root_fs;

#endif /* _FS_H */
