# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = D:\app\cmake_3_17_3\bin\cmake.exe

# The command to remove a file.
RM = D:\app\cmake_3_17_3\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\build-mingw

# Include any dependencies generated for this target.
include tests/CMakeFiles/gamma.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/gamma.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/gamma.dir/flags.make

tests/CMakeFiles/gamma.dir/gamma.c.obj: tests/CMakeFiles/gamma.dir/flags.make
tests/CMakeFiles/gamma.dir/gamma.c.obj: tests/CMakeFiles/gamma.dir/includes_C.rsp
tests/CMakeFiles/gamma.dir/gamma.c.obj: ../tests/gamma.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\build-mingw\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/gamma.dir/gamma.c.obj"
	cd /d D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\build-mingw\tests && D:\app\msys2\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\gamma.dir\gamma.c.obj   -c D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\tests\gamma.c

tests/CMakeFiles/gamma.dir/gamma.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gamma.dir/gamma.c.i"
	cd /d D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\build-mingw\tests && D:\app\msys2\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\tests\gamma.c > CMakeFiles\gamma.dir\gamma.c.i

tests/CMakeFiles/gamma.dir/gamma.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gamma.dir/gamma.c.s"
	cd /d D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\build-mingw\tests && D:\app\msys2\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\tests\gamma.c -o CMakeFiles\gamma.dir\gamma.c.s

tests/CMakeFiles/gamma.dir/__/deps/glad_gl.c.obj: tests/CMakeFiles/gamma.dir/flags.make
tests/CMakeFiles/gamma.dir/__/deps/glad_gl.c.obj: tests/CMakeFiles/gamma.dir/includes_C.rsp
tests/CMakeFiles/gamma.dir/__/deps/glad_gl.c.obj: ../deps/glad_gl.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\build-mingw\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object tests/CMakeFiles/gamma.dir/__/deps/glad_gl.c.obj"
	cd /d D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\build-mingw\tests && D:\app\msys2\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\gamma.dir\__\deps\glad_gl.c.obj   -c D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\deps\glad_gl.c

tests/CMakeFiles/gamma.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gamma.dir/__/deps/glad_gl.c.i"
	cd /d D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\build-mingw\tests && D:\app\msys2\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\deps\glad_gl.c > CMakeFiles\gamma.dir\__\deps\glad_gl.c.i

tests/CMakeFiles/gamma.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gamma.dir/__/deps/glad_gl.c.s"
	cd /d D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\build-mingw\tests && D:\app\msys2\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\deps\glad_gl.c -o CMakeFiles\gamma.dir\__\deps\glad_gl.c.s

# Object files for target gamma
gamma_OBJECTS = \
"CMakeFiles/gamma.dir/gamma.c.obj" \
"CMakeFiles/gamma.dir/__/deps/glad_gl.c.obj"

# External object files for target gamma
gamma_EXTERNAL_OBJECTS =

tests/gamma.exe: tests/CMakeFiles/gamma.dir/gamma.c.obj
tests/gamma.exe: tests/CMakeFiles/gamma.dir/__/deps/glad_gl.c.obj
tests/gamma.exe: tests/CMakeFiles/gamma.dir/build.make
tests/gamma.exe: src/libglfw3.a
tests/gamma.exe: tests/CMakeFiles/gamma.dir/linklibs.rsp
tests/gamma.exe: tests/CMakeFiles/gamma.dir/objects1.rsp
tests/gamma.exe: tests/CMakeFiles/gamma.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\build-mingw\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable gamma.exe"
	cd /d D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\build-mingw\tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\gamma.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/gamma.dir/build: tests/gamma.exe

.PHONY : tests/CMakeFiles/gamma.dir/build

tests/CMakeFiles/gamma.dir/clean:
	cd /d D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\build-mingw\tests && $(CMAKE_COMMAND) -P CMakeFiles\gamma.dir\cmake_clean.cmake
.PHONY : tests/CMakeFiles/gamma.dir/clean

tests/CMakeFiles/gamma.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8 D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\tests D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\build-mingw D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\build-mingw\tests D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\build-mingw\tests\CMakeFiles\gamma.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/gamma.dir/depend

