#include <kernel/fs.h>

struct file *root_fs;

size_t read_fs(struct file *file, size_t offset, size_t size, char *buffer)
{
    return (file->fops->read) ? file->fops->read(file, offset, size, buffer)
        : -1;
}

size_t write_fs(struct file *file, size_t offset, size_t size, char *buffer)
{
    return (file->fops->write) ? file->fops->write(file, offset, size, buffer)
        : - 1;
}

struct dirent *readdir_fs(struct file *file, unsigned long index)
{
    return ((file->flags & 0x07) == FS_DIRECTORY &&
            file->fops->readdir) ?
        file->fops->readdir(file, index) : NULL;
}

struct file *finddir_fs(struct file *file, char *name)
{
    return ((file->flags & 0x07) == FS_DIRECTORY &&
            file->fops->finddir) ?
        file->fops->finddir(file, name) : NULL;
}
