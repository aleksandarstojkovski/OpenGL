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
include House/CMakeFiles/untitled.dir/depend.make

# Include the progress variables for this target.
include House/CMakeFiles/untitled.dir/progress.make

# Include the compile flags for this target's objects.
include House/CMakeFiles/untitled.dir/flags.make

House/CMakeFiles/untitled.dir/main.cpp.obj: House/CMakeFiles/untitled.dir/flags.make
House/CMakeFiles/untitled.dir/main.cpp.obj: ../House/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\aleks\CLionProjects\OpenGL\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object House/CMakeFiles/untitled.dir/main.cpp.obj"
	cd /d C:\Users\aleks\CLionProjects\OpenGL\cmake-build-debug\House && C:\MinGW\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\untitled.dir\main.cpp.obj -c C:\Users\aleks\CLionProjects\OpenGL\House\main.cpp

House/CMakeFiles/untitled.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/untitled.dir/main.cpp.i"
	cd /d C:\Users\aleks\CLionProjects\OpenGL\cmake-build-debug\House && C:\MinGW\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\aleks\CLionProjects\OpenGL\House\main.cpp > CMakeFiles\untitled.dir\main.cpp.i

House/CMakeFiles/untitled.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/untitled.dir/main.cpp.s"
	cd /d C:\Users\aleks\CLionProjects\OpenGL\cmake-build-debug\House && C:\MinGW\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\aleks\CLionProjects\OpenGL\House\main.cpp -o CMakeFiles\untitled.dir\main.cpp.s

House/CMakeFiles/untitled.dir/lib/RgbImage.cpp.obj: House/CMakeFiles/untitled.dir/flags.make
House/CMakeFiles/untitled.dir/lib/RgbImage.cpp.obj: ../House/lib/RgbImage.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\aleks\CLionProjects\OpenGL\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object House/CMakeFiles/untitled.dir/lib/RgbImage.cpp.obj"
	cd /d C:\Users\aleks\CLionProjects\OpenGL\cmake-build-debug\House && C:\MinGW\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\untitled.dir\lib\RgbImage.cpp.obj -c C:\Users\aleks\CLionProjects\OpenGL\House\lib\RgbImage.cpp

House/CMakeFiles/untitled.dir/lib/RgbImage.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/untitled.dir/lib/RgbImage.cpp.i"
	cd /d C:\Users\aleks\CLionProjects\OpenGL\cmake-build-debug\House && C:\MinGW\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\aleks\CLionProjects\OpenGL\House\lib\RgbImage.cpp > CMakeFiles\untitled.dir\lib\RgbImage.cpp.i

House/CMakeFiles/untitled.dir/lib/RgbImage.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/untitled.dir/lib/RgbImage.cpp.s"
	cd /d C:\Users\aleks\CLionProjects\OpenGL\cmake-build-debug\House && C:\MinGW\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\aleks\CLionProjects\OpenGL\House\lib\RgbImage.cpp -o CMakeFiles\untitled.dir\lib\RgbImage.cpp.s

# Object files for target untitled
untitled_OBJECTS = \
"CMakeFiles/untitled.dir/main.cpp.obj" \
"CMakeFiles/untitled.dir/lib/RgbImage.cpp.obj"

# External object files for target untitled
untitled_EXTERNAL_OBJECTS =

House/untitled.exe: House/CMakeFiles/untitled.dir/main.cpp.obj
House/untitled.exe: House/CMakeFiles/untitled.dir/lib/RgbImage.cpp.obj
House/untitled.exe: House/CMakeFiles/untitled.dir/build.make
House/untitled.exe: C:/MinGW/MinGW/lib/libfreeglut.a
House/untitled.exe: House/CMakeFiles/untitled.dir/linklibs.rsp
House/untitled.exe: House/CMakeFiles/untitled.dir/objects1.rsp
House/untitled.exe: House/CMakeFiles/untitled.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\aleks\CLionProjects\OpenGL\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable untitled.exe"
	cd /d C:\Users\aleks\CLionProjects\OpenGL\cmake-build-debug\House && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\untitled.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
House/CMakeFiles/untitled.dir/build: House/untitled.exe

.PHONY : House/CMakeFiles/untitled.dir/build

House/CMakeFiles/untitled.dir/clean:
	cd /d C:\Users\aleks\CLionProjects\OpenGL\cmake-build-debug\House && $(CMAKE_COMMAND) -P CMakeFiles\untitled.dir\cmake_clean.cmake
.PHONY : House/CMakeFiles/untitled.dir/clean

House/CMakeFiles/untitled.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\aleks\CLionProjects\OpenGL C:\Users\aleks\CLionProjects\OpenGL\House C:\Users\aleks\CLionProjects\OpenGL\cmake-build-debug C:\Users\aleks\CLionProjects\OpenGL\cmake-build-debug\House C:\Users\aleks\CLionProjects\OpenGL\cmake-build-debug\House\CMakeFiles\untitled.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : House/CMakeFiles/untitled.dir/depend

