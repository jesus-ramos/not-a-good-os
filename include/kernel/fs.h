#ifndef _FS_H
#define _FS_H

#include <kernel/types.h>

#define MAX_FILENAME_LEN 128

#define FS_FILE        0x01
#define FS_DIRECTORY   0x02
#define FS_CHARDEVICE  0x03
#define FS_BLOCKDEVICE 0x04
#define FS_PIPE        0x05
#define FS_SYMLINK     0x06
#define FS_MOUNTPOINT  0x08

struct file;

struct file_operations
{
    size_t (*read)(struct file *file, size_t offset, size_t size,
                   char *buffer);
    size_t (*write)(struct file *file, size_t offset, size_t size,
                    char *buffer);
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

void open_fs(struct file *file);
void close_fs(struct file *file);
size_t read_fs(struct file *file, size_t offset, size_t size, char *buffer);
size_t write_fs(struct file *file, size_t offset, size_t size, char *buffer);
struct dirent *readdir_fs(struct file *file, unsigned long index);
struct file *finddir_fs(struct file *file, char *name);

#endif /* _FS_H */
