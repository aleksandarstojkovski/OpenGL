# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/mazzar/Data/Work_SUPSI/Didattica/Corsi_di_base/Grafica_computerizzata/17_18/GL_Esempi

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/mazzar/Data/Work_SUPSI/Didattica/Corsi_di_base/Grafica_computerizzata/17_18/GL_Esempi

# Include any dependencies generated for this target.
include serie4/text/CMakeFiles/text.dir/depend.make

# Include the progress variables for this target.
include serie4/text/CMakeFiles/text.dir/progress.make

# Include the compile flags for this target's objects.
include serie4/text/CMakeFiles/text.dir/flags.make

serie4/text/CMakeFiles/text.dir/text.c.o: serie4/text/CMakeFiles/text.dir/flags.make
serie4/text/CMakeFiles/text.dir/text.c.o: serie4/text/text.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mazzar/Data/Work_SUPSI/Didattica/Corsi_di_base/Grafica_computerizzata/17_18/GL_Esempi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object serie4/text/CMakeFiles/text.dir/text.c.o"
	cd /Users/mazzar/Data/Work_SUPSI/Didattica/Corsi_di_base/Grafica_computerizzata/17_18/GL_Esempi/serie4/text && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/text.dir/text.c.o   -c /Users/mazzar/Data/Work_SUPSI/Didattica/Corsi_di_base/Grafica_computerizzata/17_18/GL_Esempi/serie4/text/text.c

serie4/text/CMakeFiles/text.dir/text.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/text.dir/text.c.i"
	cd /Users/mazzar/Data/Work_SUPSI/Didattica/Corsi_di_base/Grafica_computerizzata/17_18/GL_Esempi/serie4/text && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/mazzar/Data/Work_SUPSI/Didattica/Corsi_di_base/Grafica_computerizzata/17_18/GL_Esempi/serie4/text/text.c > CMakeFiles/text.dir/text.c.i

serie4/text/CMakeFiles/text.dir/text.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/text.dir/text.c.s"
	cd /Users/mazzar/Data/Work_SUPSI/Didattica/Corsi_di_base/Grafica_computerizzata/17_18/GL_Esempi/serie4/text && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/mazzar/Data/Work_SUPSI/Didattica/Corsi_di_base/Grafica_computerizzata/17_18/GL_Esempi/serie4/text/text.c -o CMakeFiles/text.dir/text.c.s

serie4/text/CMakeFiles/text.dir/text.c.o.requires:

.PHONY : serie4/text/CMakeFiles/text.dir/text.c.o.requires

serie4/text/CMakeFiles/text.dir/text.c.o.provides: serie4/text/CMakeFiles/text.dir/text.c.o.requires
	$(MAKE) -f serie4/text/CMakeFiles/text.dir/build.make serie4/text/CMakeFiles/text.dir/text.c.o.provides.build
.PHONY : serie4/text/CMakeFiles/text.dir/text.c.o.provides

serie4/text/CMakeFiles/text.dir/text.c.o.provides.build: serie4/text/CMakeFiles/text.dir/text.c.o


# Object files for target text
text_OBJECTS = \
"CMakeFiles/text.dir/text.c.o"

# External object files for target text
text_EXTERNAL_OBJECTS =

serie4/text/text: serie4/text/CMakeFiles/text.dir/text.c.o
serie4/text/text: serie4/text/CMakeFiles/text.dir/build.make
serie4/text/text: /usr/local/lib/libGLEW.dylib
serie4/text/text: serie4/text/CMakeFiles/text.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/mazzar/Data/Work_SUPSI/Didattica/Corsi_di_base/Grafica_computerizzata/17_18/GL_Esempi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable text"
	cd /Users/mazzar/Data/Work_SUPSI/Didattica/Corsi_di_base/Grafica_computerizzata/17_18/GL_Esempi/serie4/text && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/text.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
serie4/text/CMakeFiles/text.dir/build: serie4/text/text

.PHONY : serie4/text/CMakeFiles/text.dir/build

serie4/text/CMakeFiles/text.dir/requires: serie4/text/CMakeFiles/text.dir/text.c.o.requires

.PHONY : serie4/text/CMakeFiles/text.dir/requires

serie4/text/CMakeFiles/text.dir/clean:
	cd /Users/mazzar/Data/Work_SUPSI/Didattica/Corsi_di_base/Grafica_computerizzata/17_18/GL_Esempi/serie4/text && $(CMAKE_COMMAND) -P CMakeFiles/text.dir/cmake_clean.cmake
.PHONY : serie4/text/CMakeFiles/text.dir/clean

serie4/text/CMakeFiles/text.dir/depend:
	cd /Users/mazzar/Data/Work_SUPSI/Didattica/Corsi_di_base/Grafica_computerizzata/17_18/GL_Esempi && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/mazzar/Data/Work_SUPSI/Didattica/Corsi_di_base/Grafica_computerizzata/17_18/GL_Esempi /Users/mazzar/Data/Work_SUPSI/Didattica/Corsi_di_base/Grafica_computerizzata/17_18/GL_Esempi/serie4/text /Users/mazzar/Data/Work_SUPSI/Didattica/Corsi_di_base/Grafica_computerizzata/17_18/GL_Esempi /Users/mazzar/Data/Work_SUPSI/Didattica/Corsi_di_base/Grafica_computerizzata/17_18/GL_Esempi/serie4/text /Users/mazzar/Data/Work_SUPSI/Didattica/Corsi_di_base/Grafica_computerizzata/17_18/GL_Esempi/serie4/text/CMakeFiles/text.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : serie4/text/CMakeFiles/text.dir/depend
