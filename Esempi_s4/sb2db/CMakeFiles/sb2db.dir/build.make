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
include serie4/sb2db/CMakeFiles/sb2db.dir/depend.make

# Include the progress variables for this target.
include serie4/sb2db/CMakeFiles/sb2db.dir/progress.make

# Include the compile flags for this target's objects.
include serie4/sb2db/CMakeFiles/sb2db.dir/flags.make

serie4/sb2db/CMakeFiles/sb2db.dir/sb2db.c.o: serie4/sb2db/CMakeFiles/sb2db.dir/flags.make
serie4/sb2db/CMakeFiles/sb2db.dir/sb2db.c.o: serie4/sb2db/sb2db.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mazzar/Data/Work_SUPSI/Didattica/Corsi_di_base/Grafica_computerizzata/17_18/GL_Esempi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object serie4/sb2db/CMakeFiles/sb2db.dir/sb2db.c.o"
	cd /Users/mazzar/Data/Work_SUPSI/Didattica/Corsi_di_base/Grafica_computerizzata/17_18/GL_Esempi/serie4/sb2db && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/sb2db.dir/sb2db.c.o   -c /Users/mazzar/Data/Work_SUPSI/Didattica/Corsi_di_base/Grafica_computerizzata/17_18/GL_Esempi/serie4/sb2db/sb2db.c

serie4/sb2db/CMakeFiles/sb2db.dir/sb2db.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sb2db.dir/sb2db.c.i"
	cd /Users/mazzar/Data/Work_SUPSI/Didattica/Corsi_di_base/Grafica_computerizzata/17_18/GL_Esempi/serie4/sb2db && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/mazzar/Data/Work_SUPSI/Didattica/Corsi_di_base/Grafica_computerizzata/17_18/GL_Esempi/serie4/sb2db/sb2db.c > CMakeFiles/sb2db.dir/sb2db.c.i

serie4/sb2db/CMakeFiles/sb2db.dir/sb2db.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sb2db.dir/sb2db.c.s"
	cd /Users/mazzar/Data/Work_SUPSI/Didattica/Corsi_di_base/Grafica_computerizzata/17_18/GL_Esempi/serie4/sb2db && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/mazzar/Data/Work_SUPSI/Didattica/Corsi_di_base/Grafica_computerizzata/17_18/GL_Esempi/serie4/sb2db/sb2db.c -o CMakeFiles/sb2db.dir/sb2db.c.s

serie4/sb2db/CMakeFiles/sb2db.dir/sb2db.c.o.requires:

.PHONY : serie4/sb2db/CMakeFiles/sb2db.dir/sb2db.c.o.requires

serie4/sb2db/CMakeFiles/sb2db.dir/sb2db.c.o.provides: serie4/sb2db/CMakeFiles/sb2db.dir/sb2db.c.o.requires
	$(MAKE) -f serie4/sb2db/CMakeFiles/sb2db.dir/build.make serie4/sb2db/CMakeFiles/sb2db.dir/sb2db.c.o.provides.build
.PHONY : serie4/sb2db/CMakeFiles/sb2db.dir/sb2db.c.o.provides

serie4/sb2db/CMakeFiles/sb2db.dir/sb2db.c.o.provides.build: serie4/sb2db/CMakeFiles/sb2db.dir/sb2db.c.o


# Object files for target sb2db
sb2db_OBJECTS = \
"CMakeFiles/sb2db.dir/sb2db.c.o"

# External object files for target sb2db
sb2db_EXTERNAL_OBJECTS =

serie4/sb2db/sb2db: serie4/sb2db/CMakeFiles/sb2db.dir/sb2db.c.o
serie4/sb2db/sb2db: serie4/sb2db/CMakeFiles/sb2db.dir/build.make
serie4/sb2db/sb2db: /usr/local/lib/libGLEW.dylib
serie4/sb2db/sb2db: serie4/sb2db/CMakeFiles/sb2db.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/mazzar/Data/Work_SUPSI/Didattica/Corsi_di_base/Grafica_computerizzata/17_18/GL_Esempi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable sb2db"
	cd /Users/mazzar/Data/Work_SUPSI/Didattica/Corsi_di_base/Grafica_computerizzata/17_18/GL_Esempi/serie4/sb2db && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sb2db.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
serie4/sb2db/CMakeFiles/sb2db.dir/build: serie4/sb2db/sb2db

.PHONY : serie4/sb2db/CMakeFiles/sb2db.dir/build

serie4/sb2db/CMakeFiles/sb2db.dir/requires: serie4/sb2db/CMakeFiles/sb2db.dir/sb2db.c.o.requires

.PHONY : serie4/sb2db/CMakeFiles/sb2db.dir/requires

serie4/sb2db/CMakeFiles/sb2db.dir/clean:
	cd /Users/mazzar/Data/Work_SUPSI/Didattica/Corsi_di_base/Grafica_computerizzata/17_18/GL_Esempi/serie4/sb2db && $(CMAKE_COMMAND) -P CMakeFiles/sb2db.dir/cmake_clean.cmake
.PHONY : serie4/sb2db/CMakeFiles/sb2db.dir/clean

serie4/sb2db/CMakeFiles/sb2db.dir/depend:
	cd /Users/mazzar/Data/Work_SUPSI/Didattica/Corsi_di_base/Grafica_computerizzata/17_18/GL_Esempi && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/mazzar/Data/Work_SUPSI/Didattica/Corsi_di_base/Grafica_computerizzata/17_18/GL_Esempi /Users/mazzar/Data/Work_SUPSI/Didattica/Corsi_di_base/Grafica_computerizzata/17_18/GL_Esempi/serie4/sb2db /Users/mazzar/Data/Work_SUPSI/Didattica/Corsi_di_base/Grafica_computerizzata/17_18/GL_Esempi /Users/mazzar/Data/Work_SUPSI/Didattica/Corsi_di_base/Grafica_computerizzata/17_18/GL_Esempi/serie4/sb2db /Users/mazzar/Data/Work_SUPSI/Didattica/Corsi_di_base/Grafica_computerizzata/17_18/GL_Esempi/serie4/sb2db/CMakeFiles/sb2db.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : serie4/sb2db/CMakeFiles/sb2db.dir/depend

