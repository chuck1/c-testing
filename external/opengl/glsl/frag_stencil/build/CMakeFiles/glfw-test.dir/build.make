# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/chuck/git/c-testing/external/opengl/glsl/frag_stencil

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/chuck/git/c-testing/external/opengl/glsl/frag_stencil/build

# Include any dependencies generated for this target.
include CMakeFiles/glfw-test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/glfw-test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/glfw-test.dir/flags.make

CMakeFiles/glfw-test.dir/main.cpp.o: CMakeFiles/glfw-test.dir/flags.make
CMakeFiles/glfw-test.dir/main.cpp.o: ../main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/chuck/git/c-testing/external/opengl/glsl/frag_stencil/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/glfw-test.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/glfw-test.dir/main.cpp.o -c /home/chuck/git/c-testing/external/opengl/glsl/frag_stencil/main.cpp

CMakeFiles/glfw-test.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/glfw-test.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/chuck/git/c-testing/external/opengl/glsl/frag_stencil/main.cpp > CMakeFiles/glfw-test.dir/main.cpp.i

CMakeFiles/glfw-test.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/glfw-test.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/chuck/git/c-testing/external/opengl/glsl/frag_stencil/main.cpp -o CMakeFiles/glfw-test.dir/main.cpp.s

CMakeFiles/glfw-test.dir/main.cpp.o.requires:
.PHONY : CMakeFiles/glfw-test.dir/main.cpp.o.requires

CMakeFiles/glfw-test.dir/main.cpp.o.provides: CMakeFiles/glfw-test.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/glfw-test.dir/build.make CMakeFiles/glfw-test.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/glfw-test.dir/main.cpp.o.provides

CMakeFiles/glfw-test.dir/main.cpp.o.provides.build: CMakeFiles/glfw-test.dir/main.cpp.o

# Object files for target glfw-test
glfw__test_OBJECTS = \
"CMakeFiles/glfw-test.dir/main.cpp.o"

# External object files for target glfw-test
glfw__test_EXTERNAL_OBJECTS =

glfw-test: CMakeFiles/glfw-test.dir/main.cpp.o
glfw-test: CMakeFiles/glfw-test.dir/build.make
glfw-test: CMakeFiles/glfw-test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable glfw-test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/glfw-test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/glfw-test.dir/build: glfw-test
.PHONY : CMakeFiles/glfw-test.dir/build

CMakeFiles/glfw-test.dir/requires: CMakeFiles/glfw-test.dir/main.cpp.o.requires
.PHONY : CMakeFiles/glfw-test.dir/requires

CMakeFiles/glfw-test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/glfw-test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/glfw-test.dir/clean

CMakeFiles/glfw-test.dir/depend:
	cd /home/chuck/git/c-testing/external/opengl/glsl/frag_stencil/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chuck/git/c-testing/external/opengl/glsl/frag_stencil /home/chuck/git/c-testing/external/opengl/glsl/frag_stencil /home/chuck/git/c-testing/external/opengl/glsl/frag_stencil/build /home/chuck/git/c-testing/external/opengl/glsl/frag_stencil/build /home/chuck/git/c-testing/external/opengl/glsl/frag_stencil/build/CMakeFiles/glfw-test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/glfw-test.dir/depend

