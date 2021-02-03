set(This LNR)

file(GLOB sources ./**.cpp )
file(GLOB headers ./**.h )
	
set ( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
add_library(${This} ${sources} ${headers})
set_target_properties(${This} PROPERTIES LINKER_LANGUAGE CXX)
	
