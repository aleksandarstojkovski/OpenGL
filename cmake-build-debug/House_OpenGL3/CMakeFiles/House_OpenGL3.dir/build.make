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
CMAKE_SOURCE_DIR = C:\Users\aleks\CLionProjects\OpenGL

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\aleks\CLionProjects\OpenGL\cmake-build-debug

# Include any dependencies generated for this target.
include House_OpenGL3/CMakeFiles/House_OpenGL3.dir/depend.make

# Include the progress variables for this target.
include House_OpenGL3/CMakeFiles/House_OpenGL3.dir/progress.make

# Include the compile flags for this target's objects.
include House_OpenGL3/CMakeFiles/House_OpenGL3.dir/flags.make

House_OpenGL3/CMakeFiles/House_OpenGL3.dir/main.cpp.obj: House_OpenGL3/CMakeFiles/House_OpenGL3.dir/flags.make
House_OpenGL3/CMakeFiles/House_OpenGL3.dir/main.cpp.obj: ../House_OpenGL3/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\aleks\CLionProjects\OpenGL\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object House_OpenGL3/CMakeFiles/House_OpenGL3.dir/main.cpp.obj"
	cd /d C:\Users\aleks\CLionProjects\OpenGL\cmake-build-debug\House_OpenGL3 && C:\MinGW\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\House_OpenGL3.dir\main.cpp.obj -c C:\Users\aleks\CLionProjects\OpenGL\House_OpenGL3\main.cpp

House_OpenGL3/CMakeFiles/House_OpenGL3.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/House_OpenGL3.dir/main.cpp.i"
	cd /d C:\Users\aleks\CLionProjects\OpenGL\cmake-build-debug\House_OpenGL3 && C:\MinGW\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\aleks\CLionProjects\OpenGL\House_OpenGL3\main.cpp > CMakeFiles\House_OpenGL3.dir\main.cpp.i

House_OpenGL3/CMakeFiles/House_OpenGL3.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/House_OpenGL3.dir/main.cpp.s"
	cd /d C:\Users\aleks\CLionProjects\OpenGL\cmake-build-debug\House_OpenGL3 && C:\MinGW\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\aleks\CLionProjects\OpenGL\House_OpenGL3\main.cpp -o CMakeFiles\House_OpenGL3.dir\main.cpp.s

House_OpenGL3/CMakeFiles/House_OpenGL3.dir/lib/RgbImage.cpp.obj: House_OpenGL3/CMakeFiles/House_OpenGL3.dir/flags.make
House_OpenGL3/CMakeFiles/House_OpenGL3.dir/lib/RgbImage.cpp.obj: ../House_OpenGL3/lib/RgbImage.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\aleks\CLionProjects\OpenGL\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object House_OpenGL3/CMakeFiles/House_OpenGL3.dir/lib/RgbImage.cpp.obj"
	cd /d C:\Users\aleks\CLionProjects\OpenGL\cmake-build-debug\House_OpenGL3 && C:\MinGW\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\House_OpenGL3.dir\lib\RgbImage.cpp.obj -c C:\Users\aleks\CLionProjects\OpenGL\House_OpenGL3\lib\RgbImage.cpp

House_OpenGL3/CMakeFiles/House_OpenGL3.dir/lib/RgbImage.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/House_OpenGL3.dir/lib/RgbImage.cpp.i"
	cd /d C:\Users\aleks\CLionProjects\OpenGL\cmake-build-debug\House_OpenGL3 && C:\MinGW\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\aleks\CLionProjects\OpenGL\House_OpenGL3\lib\RgbImage.cpp > CMakeFiles\House_OpenGL3.dir\lib\RgbImage.cpp.i

House_OpenGL3/CMakeFiles/House_OpenGL3.dir/lib/RgbImage.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/House_OpenGL3.dir/lib/RgbImage.cpp.s"
	cd /d C:\Users\aleks\CLionProjects\OpenGL\cmake-build-debug\House_OpenGL3 && C:\MinGW\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\aleks\CLionProjects\OpenGL\House_OpenGL3\lib\RgbImage.cpp -o CMakeFiles\House_OpenGL3.dir\lib\RgbImage.cpp.s

# Object files for target House_OpenGL3
House_OpenGL3_OBJECTS = \
"CMakeFiles/House_OpenGL3.dir/main.cpp.obj" \
"CMakeFiles/House_OpenGL3.dir/lib/RgbImage.cpp.obj"

# External object files for target House_OpenGL3
House_OpenGL3_EXTERNAL_OBJECTS =

House_OpenGL3/House_OpenGL3.exe: House_OpenGL3/CMakeFiles/House_OpenGL3.dir/main.cpp.obj
House_OpenGL3/House_OpenGL3.exe: House_OpenGL3/CMakeFiles/House_OpenGL3.dir/lib/RgbImage.cpp.obj
House_OpenGL3/House_OpenGL3.exe: House_OpenGL3/CMakeFiles/House_OpenGL3.dir/build.make
House_OpenGL3/House_OpenGL3.exe: C:/MinGW/MinGW/lib/libfreeglut.a
House_OpenGL3/House_OpenGL3.exe: House_OpenGL3/CMakeFiles/House_OpenGL3.dir/linklibs.rsp
House_OpenGL3/House_OpenGL3.exe: House_OpenGL3/CMakeFiles/House_OpenGL3.dir/objects1.rsp
House_OpenGL3/House_OpenGL3.exe: House_OpenGL3/CMakeFiles/House_OpenGL3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\aleks\CLionProjects\OpenGL\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable House_OpenGL3.exe"
	cd /d C:\Users\aleks\CLionProjects\OpenGL\cmake-build-debug\House_OpenGL3 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\House_OpenGL3.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
House_OpenGL3/CMakeFiles/House_OpenGL3.dir/build: House_OpenGL3/House_OpenGL3.exe

.PHONY : House_OpenGL3/CMakeFiles/House_OpenGL3.dir/build

House_OpenGL3/CMakeFiles/House_OpenGL3.dir/clean:
	cd /d C:\Users\aleks\CLionProjects\OpenGL\cmake-build-debug\House_OpenGL3 && $(CMAKE_COMMAND) -P CMakeFiles\House_OpenGL3.dir\cmake_clean.cmake
.PHONY : House_OpenGL3/CMakeFiles/House_OpenGL3.dir/clean

House_OpenGL3/CMakeFiles/House_OpenGL3.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\aleks\CLionProjects\OpenGL C:\Users\aleks\CLionProjects\OpenGL\House_OpenGL3 C:\Users\aleks\CLionProjects\OpenGL\cmake-build-debug C:\Users\aleks\CLionProjects\OpenGL\cmake-build-debug\House_OpenGL3 C:\Users\aleks\CLionProjects\OpenGL\cmake-build-debug\House_OpenGL3\CMakeFiles\House_OpenGL3.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : House_OpenGL3/CMakeFiles/House_OpenGL3.dir/depend

