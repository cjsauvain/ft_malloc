#ifndef DEFINES_H
# define DEFINES_H

# define ALIGN_MEM(size) ((size + (sizeof(void *) - 1)) & ~(sizeof(void *) - 1))

# define PAGE_SIZE		sysconf(_SC_PAGESIZE)
# define TINY_BLOCK		64
# define SMALL_BLOCK	512
# define TINY_HEAP		4 * PAGE_SIZE
# define SMALL_HEAP		16 * PAGE_SIZE

# define URED "\e[4;31m"
# define BMAG "\e[1;35m"
# define YEL "\e[0;33m"
# define RESET "\e[0m"

#endif
