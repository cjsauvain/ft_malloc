#!/bin/bash

FILES_DIR=$(dirname "$0")

source ${FILES_DIR}/launch_tests.sh

if [ ! -e .tmp ]; then
	mkdir .tmp
fi

launch_tests $1

rm -rf .tmp
