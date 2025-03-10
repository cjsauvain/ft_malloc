#ifndef DEFINES_H
# define DEFINES_H

# define ALIGN_MEM(size) ((size + 2 * sizeof(void *) - 1) & ~(2 * sizeof(void *) - 1))

# define PAGE_SIZE		sysconf(_SC_PAGESIZE)
# define TINY_BLOCK		128
# define SMALL_BLOCK	1024
# define TINY_HEAP		4 * PAGE_SIZE
# define SMALL_HEAP		26 * PAGE_SIZE

# define YEL "\e[0;33m"
# define BCYN "\e[1;36m"
# define BMAG "\e[1;35m"
# define MAG "\e[0;35m"
# define BRED "\e[1;31m"
# define URED "\e[4;31m"
# define RESET "\e[0m"

#endif
