# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

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
CMAKE_SOURCE_DIR = /home/crylia/Dokumente/git/CryliaPlayer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/crylia/Dokumente/git/CryliaPlayer/debug

# Utility rule file for CryliaPlayer_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/CryliaPlayer_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/CryliaPlayer_autogen.dir/progress.make

CMakeFiles/CryliaPlayer_autogen: CryliaPlayer_autogen/timestamp

CryliaPlayer_autogen/timestamp: /usr/lib/qt6/moc
CryliaPlayer_autogen/timestamp: /usr/lib/qt6/uic
CryliaPlayer_autogen/timestamp: CMakeFiles/CryliaPlayer_autogen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/crylia/Dokumente/git/CryliaPlayer/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target CryliaPlayer"
	/usr/bin/cmake -E cmake_autogen /home/crylia/Dokumente/git/CryliaPlayer/debug/CMakeFiles/CryliaPlayer_autogen.dir/AutogenInfo.json Debug
	/usr/bin/cmake -E touch /home/crylia/Dokumente/git/CryliaPlayer/debug/CryliaPlayer_autogen/timestamp

CryliaPlayer_autogen: CMakeFiles/CryliaPlayer_autogen
CryliaPlayer_autogen: CryliaPlayer_autogen/timestamp
CryliaPlayer_autogen: CMakeFiles/CryliaPlayer_autogen.dir/build.make
.PHONY : CryliaPlayer_autogen

# Rule to build all files generated by this target.
CMakeFiles/CryliaPlayer_autogen.dir/build: CryliaPlayer_autogen
.PHONY : CMakeFiles/CryliaPlayer_autogen.dir/build

CMakeFiles/CryliaPlayer_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CryliaPlayer_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CryliaPlayer_autogen.dir/clean

CMakeFiles/CryliaPlayer_autogen.dir/depend:
	cd /home/crylia/Dokumente/git/CryliaPlayer/debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/crylia/Dokumente/git/CryliaPlayer /home/crylia/Dokumente/git/CryliaPlayer /home/crylia/Dokumente/git/CryliaPlayer/debug /home/crylia/Dokumente/git/CryliaPlayer/debug /home/crylia/Dokumente/git/CryliaPlayer/debug/CMakeFiles/CryliaPlayer_autogen.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/CryliaPlayer_autogen.dir/depend

