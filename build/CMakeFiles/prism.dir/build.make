# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dev/Desktop/prism

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dev/Desktop/prism/build

# Include any dependencies generated for this target.
include CMakeFiles/prism.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/prism.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/prism.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/prism.dir/flags.make

CMakeFiles/prism.dir/src/glad.c.o: CMakeFiles/prism.dir/flags.make
CMakeFiles/prism.dir/src/glad.c.o: ../src/glad.c
CMakeFiles/prism.dir/src/glad.c.o: CMakeFiles/prism.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dev/Desktop/prism/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/prism.dir/src/glad.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/prism.dir/src/glad.c.o -MF CMakeFiles/prism.dir/src/glad.c.o.d -o CMakeFiles/prism.dir/src/glad.c.o -c /home/dev/Desktop/prism/src/glad.c

CMakeFiles/prism.dir/src/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/prism.dir/src/glad.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dev/Desktop/prism/src/glad.c > CMakeFiles/prism.dir/src/glad.c.i

CMakeFiles/prism.dir/src/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/prism.dir/src/glad.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dev/Desktop/prism/src/glad.c -o CMakeFiles/prism.dir/src/glad.c.s

CMakeFiles/prism.dir/src/main.c.o: CMakeFiles/prism.dir/flags.make
CMakeFiles/prism.dir/src/main.c.o: ../src/main.c
CMakeFiles/prism.dir/src/main.c.o: CMakeFiles/prism.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dev/Desktop/prism/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/prism.dir/src/main.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/prism.dir/src/main.c.o -MF CMakeFiles/prism.dir/src/main.c.o.d -o CMakeFiles/prism.dir/src/main.c.o -c /home/dev/Desktop/prism/src/main.c

CMakeFiles/prism.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/prism.dir/src/main.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dev/Desktop/prism/src/main.c > CMakeFiles/prism.dir/src/main.c.i

CMakeFiles/prism.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/prism.dir/src/main.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dev/Desktop/prism/src/main.c -o CMakeFiles/prism.dir/src/main.c.s

CMakeFiles/prism.dir/src/shader.c.o: CMakeFiles/prism.dir/flags.make
CMakeFiles/prism.dir/src/shader.c.o: ../src/shader.c
CMakeFiles/prism.dir/src/shader.c.o: CMakeFiles/prism.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dev/Desktop/prism/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/prism.dir/src/shader.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/prism.dir/src/shader.c.o -MF CMakeFiles/prism.dir/src/shader.c.o.d -o CMakeFiles/prism.dir/src/shader.c.o -c /home/dev/Desktop/prism/src/shader.c

CMakeFiles/prism.dir/src/shader.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/prism.dir/src/shader.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dev/Desktop/prism/src/shader.c > CMakeFiles/prism.dir/src/shader.c.i

CMakeFiles/prism.dir/src/shader.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/prism.dir/src/shader.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dev/Desktop/prism/src/shader.c -o CMakeFiles/prism.dir/src/shader.c.s

# Object files for target prism
prism_OBJECTS = \
"CMakeFiles/prism.dir/src/glad.c.o" \
"CMakeFiles/prism.dir/src/main.c.o" \
"CMakeFiles/prism.dir/src/shader.c.o"

# External object files for target prism
prism_EXTERNAL_OBJECTS =

prism: CMakeFiles/prism.dir/src/glad.c.o
prism: CMakeFiles/prism.dir/src/main.c.o
prism: CMakeFiles/prism.dir/src/shader.c.o
prism: CMakeFiles/prism.dir/build.make
prism: GLFW/src/libglfw3.a
prism: /usr/lib/x86_64-linux-gnu/librt.a
prism: /usr/lib/x86_64-linux-gnu/libm.so
prism: CMakeFiles/prism.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dev/Desktop/prism/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable prism"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/prism.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/prism.dir/build: prism
.PHONY : CMakeFiles/prism.dir/build

CMakeFiles/prism.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/prism.dir/cmake_clean.cmake
.PHONY : CMakeFiles/prism.dir/clean

CMakeFiles/prism.dir/depend:
	cd /home/dev/Desktop/prism/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dev/Desktop/prism /home/dev/Desktop/prism /home/dev/Desktop/prism/build /home/dev/Desktop/prism/build /home/dev/Desktop/prism/build/CMakeFiles/prism.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/prism.dir/depend
