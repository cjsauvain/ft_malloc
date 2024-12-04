#!/bin/bash

display_compiling_banner()
{
	echo -e "${MAG}*********************************"
    echo -e "*${BHRED}   Compiling ${FILE_SRC}...${RESET}   ${MAG}*"
	echo -e "*********************************${RESET}"
}

compile_test()
{
    FILE_SRC=$1
    FILE_EXEC=$2

	display_compiling_banner
	if [[ $3 = "FLAGS" ]]; then
		INC_LIBFT="-I $(find ~ -type f -name "libft.h" 2>/dev/null -exec dirname {} +)"
		INC_LIBFT_MALLOC="-I $(find ~ -type f -name "libft_malloc.h" 2>/dev/null -exec dirname {} +)"
		LIBFLAGS="-L.. -lft_malloc"
	fi
    gcc ${FILE_SRC} ${INC_LIBFT} ${INC_LIBFT_MALLOC} ${LIBFLAGS} -o ${FILE_EXEC}
}
