cmake_minimum_required(VERSION 3.0.0)
project(prism LANGUAGES C)

add_subdirectory(./GLFW)
add_subdirectory(./cglm)

include_directories(
    "include"
	"src"
)
    
file(GLOB SRC
	"src/*.c"
	"src/*.h"
)
    
add_executable(prism ${SRC})
target_link_libraries(prism glfw cglm)
