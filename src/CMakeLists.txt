

add_executable(game main.cpp)
target_link_libraries(game PRIVATE external)

if (MSVC)
    target_compile_options(game PRIVATE /W3 /sdl /external:anglebrackets /external:W2 /wd4068)
else ()
    target_compile_options(game PRIVATE -Wall -Wextra -Wpedantic -isystem)
endif ()