#ifndef DEFINES_H
# define DEFINES_H

# define ALIGN_MEM(size) ((size + (sizeof(void *) - 1)) & ~(sizeof(void *) - 1))

# define TINY_BLOCK 64
# define SMALL_BLOCK 512
# define TINY_HEAP 4 * sysconf(_SC_PAGESIZE)
# define SMALL_HEAP 16 * sysconf(_SC_PAGESIZE)

# define URED "\e[4;31m"
# define BMAG "\e[1;35m"
# define YEL "\e[0;33m"
# define RESET "\e[0m"

#endif
