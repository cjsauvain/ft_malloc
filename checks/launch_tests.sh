#!/bin/bash

source ${FILES_DIR}/compiling.sh
source ${FILES_DIR}/get_minor.sh
source ${FILES_DIR}/variables.sh

get_context()
{
	if [ $i -eq 0 ]; then
		context="NO MALLOC"
	elif [[ $i -ge 1 && $i -le 3 ]]; then
		context="MALLOC"
	else
		context="FREE"
	fi
}

first_part_tests()
{
	for i in {0..6}; do
		compile_test ${TEST_SRC}${i}.c "test${i}"
		get_context
		echo -e " ${UBLUE}Minor page faults :${RESET}  $context"
		get_minor_glibc_malloc ${TEST_SRC}${i}.c "test${i}"
		get_minor_libft_malloc "test${i}"
		rm -rf "test${i}"
		echo
	done
}

second_part_tests()
{
	for i in {7..9}; do
		if [ $i -eq 8 ]; then
			compile_test ${TEST_SRC}${i}.c "test${i}" "FLAGS"
		else
			compile_test ${TEST_SRC}${i}.c "test${i}"
		fi
    	echo -e " ${UBLUE}libft_malloc :${RESET} "
		${LINUX_RUN} "./test${i}"
		rm -rf "test${i}"
	done
}

launch_tests()
{
	first_part_tests
	second_part_tests $1
}
