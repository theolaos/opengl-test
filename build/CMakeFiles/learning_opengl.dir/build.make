# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_SOURCE_DIR = /home/theolaos/Documents/omilos/learning_opengl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/theolaos/Documents/omilos/learning_opengl/build

# Include any dependencies generated for this target.
include CMakeFiles/learning_opengl.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/learning_opengl.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/learning_opengl.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/learning_opengl.dir/flags.make

CMakeFiles/learning_opengl.dir/main.cpp.o: CMakeFiles/learning_opengl.dir/flags.make
CMakeFiles/learning_opengl.dir/main.cpp.o: /home/theolaos/Documents/omilos/learning_opengl/main.cpp
CMakeFiles/learning_opengl.dir/main.cpp.o: CMakeFiles/learning_opengl.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/theolaos/Documents/omilos/learning_opengl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/learning_opengl.dir/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/learning_opengl.dir/main.cpp.o -MF CMakeFiles/learning_opengl.dir/main.cpp.o.d -o CMakeFiles/learning_opengl.dir/main.cpp.o -c /home/theolaos/Documents/omilos/learning_opengl/main.cpp

CMakeFiles/learning_opengl.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/learning_opengl.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/theolaos/Documents/omilos/learning_opengl/main.cpp > CMakeFiles/learning_opengl.dir/main.cpp.i

CMakeFiles/learning_opengl.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/learning_opengl.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/theolaos/Documents/omilos/learning_opengl/main.cpp -o CMakeFiles/learning_opengl.dir/main.cpp.s

# Object files for target learning_opengl
learning_opengl_OBJECTS = \
"CMakeFiles/learning_opengl.dir/main.cpp.o"

# External object files for target learning_opengl
learning_opengl_EXTERNAL_OBJECTS =

learning_opengl: CMakeFiles/learning_opengl.dir/main.cpp.o
learning_opengl: CMakeFiles/learning_opengl.dir/build.make
learning_opengl: CMakeFiles/learning_opengl.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/theolaos/Documents/omilos/learning_opengl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable learning_opengl"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/learning_opengl.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/learning_opengl.dir/build: learning_opengl
.PHONY : CMakeFiles/learning_opengl.dir/build

CMakeFiles/learning_opengl.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/learning_opengl.dir/cmake_clean.cmake
.PHONY : CMakeFiles/learning_opengl.dir/clean

CMakeFiles/learning_opengl.dir/depend:
	cd /home/theolaos/Documents/omilos/learning_opengl/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/theolaos/Documents/omilos/learning_opengl /home/theolaos/Documents/omilos/learning_opengl /home/theolaos/Documents/omilos/learning_opengl/build /home/theolaos/Documents/omilos/learning_opengl/build /home/theolaos/Documents/omilos/learning_opengl/build/CMakeFiles/learning_opengl.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/learning_opengl.dir/depend

