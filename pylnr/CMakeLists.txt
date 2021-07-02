set(This pylnr)

find_package (Python3 COMPONENTS Interpreter Development)

message("python found")
message(${Python3_FOUND})
message(${Python3_INCLUDE_DIRS})

file(GLOB sources ./**.cpp )
	
set ( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
add_library(${This} SHARED ${sources} ${headers})
set_target_properties(${This} PROPERTIES LINKER_LANGUAGE CXX)
	
target_include_directories(${This} PUBLIC ${Python3_INCLUDE_DIRS})
target_link_libraries(${This} PUBLIC ${Python3_LIBRARIES})
