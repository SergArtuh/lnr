cmake_minimum_required(VERSION 3.11)
project(LNR)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(src)

if(LNR_BUILD_TESTING)
	enable_testing()
	add_subdirectory(tests)
endif(LNR_BUILD_TESTING)
