# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.1.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.1.1\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\aleks\CLionProjects\OpenGL\Other\s3_es1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\aleks\CLionProjects\OpenGL\Other\s3_es1\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/s3_es1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/s3_es1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/s3_es1.dir/flags.make

CMakeFiles/s3_es1.dir/main.c.obj: CMakeFiles/s3_es1.dir/flags.make
CMakeFiles/s3_es1.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\aleks\CLionProjects\OpenGL\Other\s3_es1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/s3_es1.dir/main.c.obj"
	C:\MinGW\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\s3_es1.dir\main.c.obj   -c C:\Users\aleks\CLionProjects\OpenGL\Other\s3_es1\main.c

CMakeFiles/s3_es1.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/s3_es1.dir/main.c.i"
	C:\MinGW\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\aleks\CLionProjects\OpenGL\Other\s3_es1\main.c > CMakeFiles\s3_es1.dir\main.c.i

CMakeFiles/s3_es1.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/s3_es1.dir/main.c.s"
	C:\MinGW\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\aleks\CLionProjects\OpenGL\Other\s3_es1\main.c -o CMakeFiles\s3_es1.dir\main.c.s

# Object files for target s3_es1
s3_es1_OBJECTS = \
"CMakeFiles/s3_es1.dir/main.c.obj"

# External object files for target s3_es1
s3_es1_EXTERNAL_OBJECTS =

s3_es1.exe: CMakeFiles/s3_es1.dir/main.c.obj
s3_es1.exe: CMakeFiles/s3_es1.dir/build.make
s3_es1.exe: CMakeFiles/s3_es1.dir/linklibs.rsp
s3_es1.exe: CMakeFiles/s3_es1.dir/objects1.rsp
s3_es1.exe: CMakeFiles/s3_es1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\aleks\CLionProjects\OpenGL\Other\s3_es1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable s3_es1.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\s3_es1.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/s3_es1.dir/build: s3_es1.exe

.PHONY : CMakeFiles/s3_es1.dir/build

CMakeFiles/s3_es1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\s3_es1.dir\cmake_clean.cmake
.PHONY : CMakeFiles/s3_es1.dir/clean

CMakeFiles/s3_es1.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\aleks\CLionProjects\OpenGL\Other\s3_es1 C:\Users\aleks\CLionProjects\OpenGL\Other\s3_es1 C:\Users\aleks\CLionProjects\OpenGL\Other\s3_es1\cmake-build-debug C:\Users\aleks\CLionProjects\OpenGL\Other\s3_es1\cmake-build-debug C:\Users\aleks\CLionProjects\OpenGL\Other\s3_es1\cmake-build-debug\CMakeFiles\s3_es1.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/s3_es1.dir/depend
