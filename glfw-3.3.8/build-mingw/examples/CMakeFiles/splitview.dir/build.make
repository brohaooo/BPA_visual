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
include examples/CMakeFiles/splitview.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/splitview.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/splitview.dir/flags.make

examples/CMakeFiles/splitview.dir/splitview.c.obj: examples/CMakeFiles/splitview.dir/flags.make
examples/CMakeFiles/splitview.dir/splitview.c.obj: examples/CMakeFiles/splitview.dir/includes_C.rsp
examples/CMakeFiles/splitview.dir/splitview.c.obj: ../examples/splitview.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\build-mingw\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object examples/CMakeFiles/splitview.dir/splitview.c.obj"
	cd /d D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\build-mingw\examples && D:\app\msys2\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\splitview.dir\splitview.c.obj   -c D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\examples\splitview.c

examples/CMakeFiles/splitview.dir/splitview.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/splitview.dir/splitview.c.i"
	cd /d D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\build-mingw\examples && D:\app\msys2\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\examples\splitview.c > CMakeFiles\splitview.dir\splitview.c.i

examples/CMakeFiles/splitview.dir/splitview.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/splitview.dir/splitview.c.s"
	cd /d D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\build-mingw\examples && D:\app\msys2\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\examples\splitview.c -o CMakeFiles\splitview.dir\splitview.c.s

examples/CMakeFiles/splitview.dir/glfw.rc.obj: examples/CMakeFiles/splitview.dir/flags.make
examples/CMakeFiles/splitview.dir/glfw.rc.obj: ../examples/glfw.rc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\build-mingw\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building RC object examples/CMakeFiles/splitview.dir/glfw.rc.obj"
	cd /d D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\build-mingw\examples && D:\app\msys2\mingw64\bin\windres.exe -O coff $(RC_DEFINES) $(RC_INCLUDES) $(RC_FLAGS) D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\examples\glfw.rc CMakeFiles\splitview.dir\glfw.rc.obj

examples/CMakeFiles/splitview.dir/__/deps/glad_gl.c.obj: examples/CMakeFiles/splitview.dir/flags.make
examples/CMakeFiles/splitview.dir/__/deps/glad_gl.c.obj: examples/CMakeFiles/splitview.dir/includes_C.rsp
examples/CMakeFiles/splitview.dir/__/deps/glad_gl.c.obj: ../deps/glad_gl.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\build-mingw\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object examples/CMakeFiles/splitview.dir/__/deps/glad_gl.c.obj"
	cd /d D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\build-mingw\examples && D:\app\msys2\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\splitview.dir\__\deps\glad_gl.c.obj   -c D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\deps\glad_gl.c

examples/CMakeFiles/splitview.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/splitview.dir/__/deps/glad_gl.c.i"
	cd /d D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\build-mingw\examples && D:\app\msys2\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\deps\glad_gl.c > CMakeFiles\splitview.dir\__\deps\glad_gl.c.i

examples/CMakeFiles/splitview.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/splitview.dir/__/deps/glad_gl.c.s"
	cd /d D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\build-mingw\examples && D:\app\msys2\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\deps\glad_gl.c -o CMakeFiles\splitview.dir\__\deps\glad_gl.c.s

# Object files for target splitview
splitview_OBJECTS = \
"CMakeFiles/splitview.dir/splitview.c.obj" \
"CMakeFiles/splitview.dir/glfw.rc.obj" \
"CMakeFiles/splitview.dir/__/deps/glad_gl.c.obj"

# External object files for target splitview
splitview_EXTERNAL_OBJECTS =

examples/splitview.exe: examples/CMakeFiles/splitview.dir/splitview.c.obj
examples/splitview.exe: examples/CMakeFiles/splitview.dir/glfw.rc.obj
examples/splitview.exe: examples/CMakeFiles/splitview.dir/__/deps/glad_gl.c.obj
examples/splitview.exe: examples/CMakeFiles/splitview.dir/build.make
examples/splitview.exe: src/libglfw3.a
examples/splitview.exe: examples/CMakeFiles/splitview.dir/linklibs.rsp
examples/splitview.exe: examples/CMakeFiles/splitview.dir/objects1.rsp
examples/splitview.exe: examples/CMakeFiles/splitview.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\build-mingw\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable splitview.exe"
	cd /d D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\build-mingw\examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\splitview.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/splitview.dir/build: examples/splitview.exe

.PHONY : examples/CMakeFiles/splitview.dir/build

examples/CMakeFiles/splitview.dir/clean:
	cd /d D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\build-mingw\examples && $(CMAKE_COMMAND) -P CMakeFiles\splitview.dir\cmake_clean.cmake
.PHONY : examples/CMakeFiles/splitview.dir/clean

examples/CMakeFiles/splitview.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8 D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\examples D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\build-mingw D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\build-mingw\examples D:\code\code\test_fish\c_related\BPA_visual\glfw-3.3.8\build-mingw\examples\CMakeFiles\splitview.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/splitview.dir/depend

