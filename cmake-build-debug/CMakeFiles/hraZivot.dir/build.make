# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_SOURCE_DIR = /tmp/tmp.R60RAYMiqi

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /tmp/tmp.R60RAYMiqi/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/hraZivot.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/hraZivot.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hraZivot.dir/flags.make

CMakeFiles/hraZivot.dir/main.c.o: CMakeFiles/hraZivot.dir/flags.make
CMakeFiles/hraZivot.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.R60RAYMiqi/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/hraZivot.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hraZivot.dir/main.c.o -c /tmp/tmp.R60RAYMiqi/main.c

CMakeFiles/hraZivot.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hraZivot.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /tmp/tmp.R60RAYMiqi/main.c > CMakeFiles/hraZivot.dir/main.c.i

CMakeFiles/hraZivot.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hraZivot.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /tmp/tmp.R60RAYMiqi/main.c -o CMakeFiles/hraZivot.dir/main.c.s

CMakeFiles/hraZivot.dir/server.c.o: CMakeFiles/hraZivot.dir/flags.make
CMakeFiles/hraZivot.dir/server.c.o: ../server.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.R60RAYMiqi/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/hraZivot.dir/server.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hraZivot.dir/server.c.o -c /tmp/tmp.R60RAYMiqi/server.c

CMakeFiles/hraZivot.dir/server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hraZivot.dir/server.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /tmp/tmp.R60RAYMiqi/server.c > CMakeFiles/hraZivot.dir/server.c.i

CMakeFiles/hraZivot.dir/server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hraZivot.dir/server.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /tmp/tmp.R60RAYMiqi/server.c -o CMakeFiles/hraZivot.dir/server.c.s

CMakeFiles/hraZivot.dir/klient.c.o: CMakeFiles/hraZivot.dir/flags.make
CMakeFiles/hraZivot.dir/klient.c.o: ../klient.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.R60RAYMiqi/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/hraZivot.dir/klient.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hraZivot.dir/klient.c.o -c /tmp/tmp.R60RAYMiqi/klient.c

CMakeFiles/hraZivot.dir/klient.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hraZivot.dir/klient.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /tmp/tmp.R60RAYMiqi/klient.c > CMakeFiles/hraZivot.dir/klient.c.i

CMakeFiles/hraZivot.dir/klient.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hraZivot.dir/klient.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /tmp/tmp.R60RAYMiqi/klient.c -o CMakeFiles/hraZivot.dir/klient.c.s

# Object files for target hraZivot
hraZivot_OBJECTS = \
"CMakeFiles/hraZivot.dir/main.c.o" \
"CMakeFiles/hraZivot.dir/server.c.o" \
"CMakeFiles/hraZivot.dir/klient.c.o"

# External object files for target hraZivot
hraZivot_EXTERNAL_OBJECTS =

hraZivot: CMakeFiles/hraZivot.dir/main.c.o
hraZivot: CMakeFiles/hraZivot.dir/server.c.o
hraZivot: CMakeFiles/hraZivot.dir/klient.c.o
hraZivot: CMakeFiles/hraZivot.dir/build.make
hraZivot: CMakeFiles/hraZivot.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/tmp/tmp.R60RAYMiqi/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable hraZivot"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hraZivot.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/hraZivot.dir/build: hraZivot

.PHONY : CMakeFiles/hraZivot.dir/build

CMakeFiles/hraZivot.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/hraZivot.dir/cmake_clean.cmake
.PHONY : CMakeFiles/hraZivot.dir/clean

CMakeFiles/hraZivot.dir/depend:
	cd /tmp/tmp.R60RAYMiqi/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /tmp/tmp.R60RAYMiqi /tmp/tmp.R60RAYMiqi /tmp/tmp.R60RAYMiqi/cmake-build-debug /tmp/tmp.R60RAYMiqi/cmake-build-debug /tmp/tmp.R60RAYMiqi/cmake-build-debug/CMakeFiles/hraZivot.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hraZivot.dir/depend

