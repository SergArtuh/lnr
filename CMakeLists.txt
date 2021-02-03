cmake_minimum_required(VERSION 3.11)
project(LNR)

add_subdirectory(src)

if(LNR_BUILD_TESTING)
	enable_testing()
	add_subdirectory(tests)
endif(LNR_BUILD_TESTING)
