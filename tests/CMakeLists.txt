set(This tests)

add_executable(${This} LinearTests.cpp catch_amalgamated.hpp catch_amalgamated.cpp)

add_custom_command(TARGET ${This}
                   POST_BUILD
                   COMMAND tests)