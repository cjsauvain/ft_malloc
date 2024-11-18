#ifndef DEFINES_BONUS_H
# define DEFINES_BONUS_H

# define ALIGN_MEM(size) ((size + (sizeof(void *) - 1)) & ~(sizeof(void *) - 1))

# define TINY_BLOCK 64
# define SMALL_BLOCK 512
# define TINY_HEAP 4 * sysconf(_SC_PAGESIZE)
# define SMALL_HEAP 16 * sysconf(_SC_PAGESIZE)

# define YEL "\e[0;33m"
# define MAG "\e[0;35m"
# define BCYN "\e[1;36m"
# define BRED "\e[1;31m"
# define RESET "\e[0m"

#endif
