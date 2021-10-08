set(This LNR)

file(GLOB sources ./**.cpp )
file(GLOB headers ./**.h )
	
set ( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
add_library(${This} ${sources} ${headers})
set_target_properties(${This} PROPERTIES LINKER_LANGUAGE CXX)

message("bin directory" ${BIN_DIRECTORY})

install(TARGETS ${This} 
		RUNTIME DESTINATION ${BIN_DIRECTORY}
		LIBRARY DESTINATION ${LIB_DIRECTORY}
		PUBLIC_HEADER DESTINATION ${INCLUDE_DIRECTORY}
	)
	
