#!/bin/bash

get_minor_glibc_malloc()
{
    FILE_SRC=$1
    FILE_EXEC=$2

    /usr/bin/time -v ./${FILE_EXEC} 2>.tmp/${FILE_EXEC}_out
    MALLOC_PAGE=$(cat .tmp/${FILE_EXEC}_out | grep Minor | rev | cut -d ' ' -f 1  | rev)
    echo -e -n "   ${YELLOW}glibc_malloc:${RESET} "
    echo -e "${RED}${MALLOC_PAGE}${RESET}"
}

get_minor_libft_malloc()
{
    FILE_EXEC=$1
    ${LINUX_RUN} /usr/bin/time -v ./${FILE_EXEC} 2>.tmp/${FILE_EXEC}_out
    MALLOC_PAGE=$(cat .tmp/${FILE_EXEC}_out | grep Minor | rev | cut -d ' ' -f 1  | rev)
    echo -e -n "   ${YELLOW}libft_malloc:${RESET} "
    echo -e "${RED}${MALLOC_PAGE}${RESET}"
}
