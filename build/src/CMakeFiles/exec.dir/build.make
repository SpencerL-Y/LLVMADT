# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/clexma/Desktop/Disk_D/gitRepos/LLVMADT

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/clexma/Desktop/Disk_D/gitRepos/LLVMADT/build

# Include any dependencies generated for this target.
include src/CMakeFiles/exec.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/exec.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/exec.dir/flags.make

src/CMakeFiles/exec.dir/Main.cpp.o: src/CMakeFiles/exec.dir/flags.make
src/CMakeFiles/exec.dir/Main.cpp.o: ../src/Main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/clexma/Desktop/Disk_D/gitRepos/LLVMADT/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/exec.dir/Main.cpp.o"
	cd /home/clexma/Desktop/Disk_D/gitRepos/LLVMADT/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/exec.dir/Main.cpp.o -c /home/clexma/Desktop/Disk_D/gitRepos/LLVMADT/src/Main.cpp

src/CMakeFiles/exec.dir/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exec.dir/Main.cpp.i"
	cd /home/clexma/Desktop/Disk_D/gitRepos/LLVMADT/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/clexma/Desktop/Disk_D/gitRepos/LLVMADT/src/Main.cpp > CMakeFiles/exec.dir/Main.cpp.i

src/CMakeFiles/exec.dir/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exec.dir/Main.cpp.s"
	cd /home/clexma/Desktop/Disk_D/gitRepos/LLVMADT/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/clexma/Desktop/Disk_D/gitRepos/LLVMADT/src/Main.cpp -o CMakeFiles/exec.dir/Main.cpp.s

# Object files for target exec
exec_OBJECTS = \
"CMakeFiles/exec.dir/Main.cpp.o"

# External object files for target exec
exec_EXTERNAL_OBJECTS =

bin/exec: src/CMakeFiles/exec.dir/Main.cpp.o
bin/exec: src/CMakeFiles/exec.dir/build.make
bin/exec: src/cfa/libcfa.a
bin/exec: src/converter/libconverter.a
bin/exec: src/automata/libautomata.a
bin/exec: src/CMakeFiles/exec.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/clexma/Desktop/Disk_D/gitRepos/LLVMADT/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/exec"
	cd /home/clexma/Desktop/Disk_D/gitRepos/LLVMADT/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/exec.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/exec.dir/build: bin/exec

.PHONY : src/CMakeFiles/exec.dir/build

src/CMakeFiles/exec.dir/clean:
	cd /home/clexma/Desktop/Disk_D/gitRepos/LLVMADT/build/src && $(CMAKE_COMMAND) -P CMakeFiles/exec.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/exec.dir/clean

src/CMakeFiles/exec.dir/depend:
	cd /home/clexma/Desktop/Disk_D/gitRepos/LLVMADT/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/clexma/Desktop/Disk_D/gitRepos/LLVMADT /home/clexma/Desktop/Disk_D/gitRepos/LLVMADT/src /home/clexma/Desktop/Disk_D/gitRepos/LLVMADT/build /home/clexma/Desktop/Disk_D/gitRepos/LLVMADT/build/src /home/clexma/Desktop/Disk_D/gitRepos/LLVMADT/build/src/CMakeFiles/exec.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/exec.dir/depend

