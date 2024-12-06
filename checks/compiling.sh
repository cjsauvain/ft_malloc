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
		INC_LIBFT="-I ../libft"
		INC_LIBFT_MALLOC="-I ../libft_malloc/mandatory/include"
		LIBFLAGS="-L.. -lft_malloc"
	fi
    gcc ${FILE_SRC} ${INC_LIBFT} ${INC_LIBFT_MALLOC} ${LIBFLAGS} -o ${FILE_EXEC}
}
