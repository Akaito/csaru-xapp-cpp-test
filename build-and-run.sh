#!/bin/bash

# run from base repo dir

make
if [ $? -eq 0 ]; then
	./csaru-xapp-cpp-test
fi

