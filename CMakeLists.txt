cmake_minimum_required(VERSION 3.0.0)
project(prism LANGUAGES C CXX)

add_subdirectory(./GLFW)
add_subdirectory(./glm)
add_subdirectory(./assimp)

include_directories(
	"include"
	"src"
)

file(GLOB SRC
	"src/*.c"
	"src/*.cpp"
	"src/*.h"
	"src/**/*.cpp"
	"src/**/*.h"
)
    
add_executable(prism ${SRC})
target_link_libraries(prism glfw ${CMAKE_SOURCE_DIR}/lib/lua.a)