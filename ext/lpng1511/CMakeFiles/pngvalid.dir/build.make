# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/joylinen/Voltrox/ext/lpng1511

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/joylinen/Voltrox/ext/lpng1511

# Include any dependencies generated for this target.
include CMakeFiles/pngvalid.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/pngvalid.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pngvalid.dir/flags.make

CMakeFiles/pngvalid.dir/contrib/libtests/pngvalid.o: CMakeFiles/pngvalid.dir/flags.make
CMakeFiles/pngvalid.dir/contrib/libtests/pngvalid.o: contrib/libtests/pngvalid.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/joylinen/Voltrox/ext/lpng1511/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/pngvalid.dir/contrib/libtests/pngvalid.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/pngvalid.dir/contrib/libtests/pngvalid.o   -c /home/joylinen/Voltrox/ext/lpng1511/contrib/libtests/pngvalid.c

CMakeFiles/pngvalid.dir/contrib/libtests/pngvalid.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/pngvalid.dir/contrib/libtests/pngvalid.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/joylinen/Voltrox/ext/lpng1511/contrib/libtests/pngvalid.c > CMakeFiles/pngvalid.dir/contrib/libtests/pngvalid.i

CMakeFiles/pngvalid.dir/contrib/libtests/pngvalid.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/pngvalid.dir/contrib/libtests/pngvalid.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/joylinen/Voltrox/ext/lpng1511/contrib/libtests/pngvalid.c -o CMakeFiles/pngvalid.dir/contrib/libtests/pngvalid.s

CMakeFiles/pngvalid.dir/contrib/libtests/pngvalid.o.requires:
.PHONY : CMakeFiles/pngvalid.dir/contrib/libtests/pngvalid.o.requires

CMakeFiles/pngvalid.dir/contrib/libtests/pngvalid.o.provides: CMakeFiles/pngvalid.dir/contrib/libtests/pngvalid.o.requires
	$(MAKE) -f CMakeFiles/pngvalid.dir/build.make CMakeFiles/pngvalid.dir/contrib/libtests/pngvalid.o.provides.build
.PHONY : CMakeFiles/pngvalid.dir/contrib/libtests/pngvalid.o.provides

CMakeFiles/pngvalid.dir/contrib/libtests/pngvalid.o.provides.build: CMakeFiles/pngvalid.dir/contrib/libtests/pngvalid.o
.PHONY : CMakeFiles/pngvalid.dir/contrib/libtests/pngvalid.o.provides.build

# Object files for target pngvalid
pngvalid_OBJECTS = \
"CMakeFiles/pngvalid.dir/contrib/libtests/pngvalid.o"

# External object files for target pngvalid
pngvalid_EXTERNAL_OBJECTS =

pngvalid: CMakeFiles/pngvalid.dir/contrib/libtests/pngvalid.o
pngvalid: libpng15.so.15.11.0
pngvalid: /usr/lib/libz.so
pngvalid: /usr/lib/libm.so
pngvalid: CMakeFiles/pngvalid.dir/build.make
pngvalid: CMakeFiles/pngvalid.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable pngvalid"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pngvalid.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pngvalid.dir/build: pngvalid
.PHONY : CMakeFiles/pngvalid.dir/build

CMakeFiles/pngvalid.dir/requires: CMakeFiles/pngvalid.dir/contrib/libtests/pngvalid.o.requires
.PHONY : CMakeFiles/pngvalid.dir/requires

CMakeFiles/pngvalid.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pngvalid.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pngvalid.dir/clean

CMakeFiles/pngvalid.dir/depend:
	cd /home/joylinen/Voltrox/ext/lpng1511 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/joylinen/Voltrox/ext/lpng1511 /home/joylinen/Voltrox/ext/lpng1511 /home/joylinen/Voltrox/ext/lpng1511 /home/joylinen/Voltrox/ext/lpng1511 /home/joylinen/Voltrox/ext/lpng1511/CMakeFiles/pngvalid.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/pngvalid.dir/depend

