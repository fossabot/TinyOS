#ifndef __FS_FS_H
#define __FS_FS_H
#include "ide.h"
#include "stdint.h"

#define MAX_FILES_PER_PART 4096 // maximum file number of each partition
#define BITS_PER_SECTOR 4096    // BITS_PER_SECTOR
#define SECTOR_SIZE 512         // sector size
#define BLOCK_SIZE SECTOR_SIZE  // block size

#define FS_MAGIC 0x19590318
// file type
typedef enum _FILE_TYPES {
  FT_UNKNOWN,  // unknown file type
  FT_REGULAR,  // ordinary file
  FT_DIRECTORY // directory
} file_types,
    FILE_TYPES;
void filesys_init(void);
#endif // !__FS_FS_H