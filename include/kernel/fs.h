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

/**
 * @brief Structure that defines basic file operations for a file
 */
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

/**
 * @brief Structure that contains all the information about a file and what
 * operations can be performed on it
 */
struct file
{
    char name[MAX_FILENAME_LEN]; /**< File name string */
    unsigned int mask; /**< Permission mask */
    unsigned int uid; /**< UID of the file */
    unsigned int gid; /**< GID of the file */
    unsigned int flags; /**< File flags */
    unsigned long inode; /**< inode number */
    size_t length; /**< File length */
    unsigned int impl;
    struct file_operations *fops; /**< File operations function pointer */
    struct file *file_ptr;
};

/**
 * @brief Directory entity structure for filesystems that support directories
 */
struct dirent
{
    char name[MAX_FILENAME_LEN]; /**< Directory name */
    unsigned long inode_num; /**< Directory inode number */
};

extern struct file *root_fs;

void open_fs(struct file *file);
void close_fs(struct file *file);
size_t read_fs(struct file *file, size_t offset, size_t size, char *buffer);
size_t write_fs(struct file *file, size_t offset, size_t size, char *buffer);
struct dirent *readdir_fs(struct file *file, unsigned long index);
struct file *finddir_fs(struct file *file, char *name);

#endif /* _FS_H */
