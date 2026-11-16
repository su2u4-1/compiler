#include "../time.h"

struct stat {
    // _dev_t st_dev;
    // _ino_t st_ino;
    unsigned short st_mode;
    short st_nlink;
    short st_uid;
    short st_gid;
    // _dev_t st_rdev;
    // _off_t st_size;
    time_t st_atime;
    time_t st_mtime;
    time_t st_ctime;
};
