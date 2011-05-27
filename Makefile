# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lmborba/bppc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lmborba/bppc

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running interactive CMake command-line interface..."
	/usr/bin/cmake -i .
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/lmborba/bppc/CMakeFiles /home/lmborba/bppc/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/lmborba/bppc/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named bppc

# Build rule for target.
bppc: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 bppc
.PHONY : bppc

# fast build rule for target.
bppc/fast:
	$(MAKE) -f CMakeFiles/bppc.dir/build.make CMakeFiles/bppc.dir/build
.PHONY : bppc/fast

bpp.o: bpp.cpp.o
.PHONY : bpp.o

# target to build an object file
bpp.cpp.o:
	$(MAKE) -f CMakeFiles/bppc.dir/build.make CMakeFiles/bppc.dir/bpp.cpp.o
.PHONY : bpp.cpp.o

bpp.i: bpp.cpp.i
.PHONY : bpp.i

# target to preprocess a source file
bpp.cpp.i:
	$(MAKE) -f CMakeFiles/bppc.dir/build.make CMakeFiles/bppc.dir/bpp.cpp.i
.PHONY : bpp.cpp.i

bpp.s: bpp.cpp.s
.PHONY : bpp.s

# target to generate assembly for a file
bpp.cpp.s:
	$(MAKE) -f CMakeFiles/bppc.dir/build.make CMakeFiles/bppc.dir/bpp.cpp.s
.PHONY : bpp.cpp.s

bppc.o: bppc.cpp.o
.PHONY : bppc.o

# target to build an object file
bppc.cpp.o:
	$(MAKE) -f CMakeFiles/bppc.dir/build.make CMakeFiles/bppc.dir/bppc.cpp.o
.PHONY : bppc.cpp.o

bppc.i: bppc.cpp.i
.PHONY : bppc.i

# target to preprocess a source file
bppc.cpp.i:
	$(MAKE) -f CMakeFiles/bppc.dir/build.make CMakeFiles/bppc.dir/bppc.cpp.i
.PHONY : bppc.cpp.i

bppc.s: bppc.cpp.s
.PHONY : bppc.s

# target to generate assembly for a file
bppc.cpp.s:
	$(MAKE) -f CMakeFiles/bppc.dir/build.make CMakeFiles/bppc.dir/bppc.cpp.s
.PHONY : bppc.cpp.s

graph.o: graph.cpp.o
.PHONY : graph.o

# target to build an object file
graph.cpp.o:
	$(MAKE) -f CMakeFiles/bppc.dir/build.make CMakeFiles/bppc.dir/graph.cpp.o
.PHONY : graph.cpp.o

graph.i: graph.cpp.i
.PHONY : graph.i

# target to preprocess a source file
graph.cpp.i:
	$(MAKE) -f CMakeFiles/bppc.dir/build.make CMakeFiles/bppc.dir/graph.cpp.i
.PHONY : graph.cpp.i

graph.s: graph.cpp.s
.PHONY : graph.s

# target to generate assembly for a file
graph.cpp.s:
	$(MAKE) -f CMakeFiles/bppc.dir/build.make CMakeFiles/bppc.dir/graph.cpp.s
.PHONY : graph.cpp.s

incidence.o: incidence.cpp.o
.PHONY : incidence.o

# target to build an object file
incidence.cpp.o:
	$(MAKE) -f CMakeFiles/bppc.dir/build.make CMakeFiles/bppc.dir/incidence.cpp.o
.PHONY : incidence.cpp.o

incidence.i: incidence.cpp.i
.PHONY : incidence.i

# target to preprocess a source file
incidence.cpp.i:
	$(MAKE) -f CMakeFiles/bppc.dir/build.make CMakeFiles/bppc.dir/incidence.cpp.i
.PHONY : incidence.cpp.i

incidence.s: incidence.cpp.s
.PHONY : incidence.s

# target to generate assembly for a file
incidence.cpp.s:
	$(MAKE) -f CMakeFiles/bppc.dir/build.make CMakeFiles/bppc.dir/incidence.cpp.s
.PHONY : incidence.cpp.s

main.o: main.cpp.o
.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) -f CMakeFiles/bppc.dir/build.make CMakeFiles/bppc.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i
.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) -f CMakeFiles/bppc.dir/build.make CMakeFiles/bppc.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s
.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) -f CMakeFiles/bppc.dir/build.make CMakeFiles/bppc.dir/main.cpp.s
.PHONY : main.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... bppc"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... bpp.o"
	@echo "... bpp.i"
	@echo "... bpp.s"
	@echo "... bppc.o"
	@echo "... bppc.i"
	@echo "... bppc.s"
	@echo "... graph.o"
	@echo "... graph.i"
	@echo "... graph.s"
	@echo "... incidence.o"
	@echo "... incidence.i"
	@echo "... incidence.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

