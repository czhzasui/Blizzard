# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /opt/clion-2018.2.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion-2018.2.4/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /work/Blizzard

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /work/Blizzard/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/bootanimation.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/bootanimation.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bootanimation.dir/flags.make

CMakeFiles/bootanimation.dir/blizzard/lib/glad/glad.c.o: CMakeFiles/bootanimation.dir/flags.make
CMakeFiles/bootanimation.dir/blizzard/lib/glad/glad.c.o: ../blizzard/lib/glad/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/work/Blizzard/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/bootanimation.dir/blizzard/lib/glad/glad.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/bootanimation.dir/blizzard/lib/glad/glad.c.o   -c /work/Blizzard/blizzard/lib/glad/glad.c

CMakeFiles/bootanimation.dir/blizzard/lib/glad/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/bootanimation.dir/blizzard/lib/glad/glad.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /work/Blizzard/blizzard/lib/glad/glad.c > CMakeFiles/bootanimation.dir/blizzard/lib/glad/glad.c.i

CMakeFiles/bootanimation.dir/blizzard/lib/glad/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/bootanimation.dir/blizzard/lib/glad/glad.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /work/Blizzard/blizzard/lib/glad/glad.c -o CMakeFiles/bootanimation.dir/blizzard/lib/glad/glad.c.s

CMakeFiles/bootanimation.dir/blizzard/lib/stb_image/stb_image.cpp.o: CMakeFiles/bootanimation.dir/flags.make
CMakeFiles/bootanimation.dir/blizzard/lib/stb_image/stb_image.cpp.o: ../blizzard/lib/stb_image/stb_image.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/work/Blizzard/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/bootanimation.dir/blizzard/lib/stb_image/stb_image.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bootanimation.dir/blizzard/lib/stb_image/stb_image.cpp.o -c /work/Blizzard/blizzard/lib/stb_image/stb_image.cpp

CMakeFiles/bootanimation.dir/blizzard/lib/stb_image/stb_image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bootanimation.dir/blizzard/lib/stb_image/stb_image.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /work/Blizzard/blizzard/lib/stb_image/stb_image.cpp > CMakeFiles/bootanimation.dir/blizzard/lib/stb_image/stb_image.cpp.i

CMakeFiles/bootanimation.dir/blizzard/lib/stb_image/stb_image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bootanimation.dir/blizzard/lib/stb_image/stb_image.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /work/Blizzard/blizzard/lib/stb_image/stb_image.cpp -o CMakeFiles/bootanimation.dir/blizzard/lib/stb_image/stb_image.cpp.s

CMakeFiles/bootanimation.dir/blizzard/src/game.cpp.o: CMakeFiles/bootanimation.dir/flags.make
CMakeFiles/bootanimation.dir/blizzard/src/game.cpp.o: ../blizzard/src/game.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/work/Blizzard/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/bootanimation.dir/blizzard/src/game.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bootanimation.dir/blizzard/src/game.cpp.o -c /work/Blizzard/blizzard/src/game.cpp

CMakeFiles/bootanimation.dir/blizzard/src/game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bootanimation.dir/blizzard/src/game.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /work/Blizzard/blizzard/src/game.cpp > CMakeFiles/bootanimation.dir/blizzard/src/game.cpp.i

CMakeFiles/bootanimation.dir/blizzard/src/game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bootanimation.dir/blizzard/src/game.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /work/Blizzard/blizzard/src/game.cpp -o CMakeFiles/bootanimation.dir/blizzard/src/game.cpp.s

CMakeFiles/bootanimation.dir/blizzard/src/game_object.cpp.o: CMakeFiles/bootanimation.dir/flags.make
CMakeFiles/bootanimation.dir/blizzard/src/game_object.cpp.o: ../blizzard/src/game_object.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/work/Blizzard/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/bootanimation.dir/blizzard/src/game_object.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bootanimation.dir/blizzard/src/game_object.cpp.o -c /work/Blizzard/blizzard/src/game_object.cpp

CMakeFiles/bootanimation.dir/blizzard/src/game_object.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bootanimation.dir/blizzard/src/game_object.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /work/Blizzard/blizzard/src/game_object.cpp > CMakeFiles/bootanimation.dir/blizzard/src/game_object.cpp.i

CMakeFiles/bootanimation.dir/blizzard/src/game_object.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bootanimation.dir/blizzard/src/game_object.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /work/Blizzard/blizzard/src/game_object.cpp -o CMakeFiles/bootanimation.dir/blizzard/src/game_object.cpp.s

CMakeFiles/bootanimation.dir/blizzard/src/resource_manager.cpp.o: CMakeFiles/bootanimation.dir/flags.make
CMakeFiles/bootanimation.dir/blizzard/src/resource_manager.cpp.o: ../blizzard/src/resource_manager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/work/Blizzard/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/bootanimation.dir/blizzard/src/resource_manager.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bootanimation.dir/blizzard/src/resource_manager.cpp.o -c /work/Blizzard/blizzard/src/resource_manager.cpp

CMakeFiles/bootanimation.dir/blizzard/src/resource_manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bootanimation.dir/blizzard/src/resource_manager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /work/Blizzard/blizzard/src/resource_manager.cpp > CMakeFiles/bootanimation.dir/blizzard/src/resource_manager.cpp.i

CMakeFiles/bootanimation.dir/blizzard/src/resource_manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bootanimation.dir/blizzard/src/resource_manager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /work/Blizzard/blizzard/src/resource_manager.cpp -o CMakeFiles/bootanimation.dir/blizzard/src/resource_manager.cpp.s

CMakeFiles/bootanimation.dir/blizzard/src/shader.cpp.o: CMakeFiles/bootanimation.dir/flags.make
CMakeFiles/bootanimation.dir/blizzard/src/shader.cpp.o: ../blizzard/src/shader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/work/Blizzard/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/bootanimation.dir/blizzard/src/shader.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bootanimation.dir/blizzard/src/shader.cpp.o -c /work/Blizzard/blizzard/src/shader.cpp

CMakeFiles/bootanimation.dir/blizzard/src/shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bootanimation.dir/blizzard/src/shader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /work/Blizzard/blizzard/src/shader.cpp > CMakeFiles/bootanimation.dir/blizzard/src/shader.cpp.i

CMakeFiles/bootanimation.dir/blizzard/src/shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bootanimation.dir/blizzard/src/shader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /work/Blizzard/blizzard/src/shader.cpp -o CMakeFiles/bootanimation.dir/blizzard/src/shader.cpp.s

CMakeFiles/bootanimation.dir/blizzard/src/sprite_renderer.cpp.o: CMakeFiles/bootanimation.dir/flags.make
CMakeFiles/bootanimation.dir/blizzard/src/sprite_renderer.cpp.o: ../blizzard/src/sprite_renderer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/work/Blizzard/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/bootanimation.dir/blizzard/src/sprite_renderer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bootanimation.dir/blizzard/src/sprite_renderer.cpp.o -c /work/Blizzard/blizzard/src/sprite_renderer.cpp

CMakeFiles/bootanimation.dir/blizzard/src/sprite_renderer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bootanimation.dir/blizzard/src/sprite_renderer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /work/Blizzard/blizzard/src/sprite_renderer.cpp > CMakeFiles/bootanimation.dir/blizzard/src/sprite_renderer.cpp.i

CMakeFiles/bootanimation.dir/blizzard/src/sprite_renderer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bootanimation.dir/blizzard/src/sprite_renderer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /work/Blizzard/blizzard/src/sprite_renderer.cpp -o CMakeFiles/bootanimation.dir/blizzard/src/sprite_renderer.cpp.s

CMakeFiles/bootanimation.dir/blizzard/src/texture.cpp.o: CMakeFiles/bootanimation.dir/flags.make
CMakeFiles/bootanimation.dir/blizzard/src/texture.cpp.o: ../blizzard/src/texture.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/work/Blizzard/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/bootanimation.dir/blizzard/src/texture.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bootanimation.dir/blizzard/src/texture.cpp.o -c /work/Blizzard/blizzard/src/texture.cpp

CMakeFiles/bootanimation.dir/blizzard/src/texture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bootanimation.dir/blizzard/src/texture.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /work/Blizzard/blizzard/src/texture.cpp > CMakeFiles/bootanimation.dir/blizzard/src/texture.cpp.i

CMakeFiles/bootanimation.dir/blizzard/src/texture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bootanimation.dir/blizzard/src/texture.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /work/Blizzard/blizzard/src/texture.cpp -o CMakeFiles/bootanimation.dir/blizzard/src/texture.cpp.s

CMakeFiles/bootanimation.dir/blizzard/src/texture_vision.cpp.o: CMakeFiles/bootanimation.dir/flags.make
CMakeFiles/bootanimation.dir/blizzard/src/texture_vision.cpp.o: ../blizzard/src/texture_vision.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/work/Blizzard/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/bootanimation.dir/blizzard/src/texture_vision.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bootanimation.dir/blizzard/src/texture_vision.cpp.o -c /work/Blizzard/blizzard/src/texture_vision.cpp

CMakeFiles/bootanimation.dir/blizzard/src/texture_vision.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bootanimation.dir/blizzard/src/texture_vision.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /work/Blizzard/blizzard/src/texture_vision.cpp > CMakeFiles/bootanimation.dir/blizzard/src/texture_vision.cpp.i

CMakeFiles/bootanimation.dir/blizzard/src/texture_vision.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bootanimation.dir/blizzard/src/texture_vision.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /work/Blizzard/blizzard/src/texture_vision.cpp -o CMakeFiles/bootanimation.dir/blizzard/src/texture_vision.cpp.s

CMakeFiles/bootanimation.dir/module/persioncv/vision/vision.cpp.o: CMakeFiles/bootanimation.dir/flags.make
CMakeFiles/bootanimation.dir/module/persioncv/vision/vision.cpp.o: ../module/persioncv/vision/vision.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/work/Blizzard/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/bootanimation.dir/module/persioncv/vision/vision.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bootanimation.dir/module/persioncv/vision/vision.cpp.o -c /work/Blizzard/module/persioncv/vision/vision.cpp

CMakeFiles/bootanimation.dir/module/persioncv/vision/vision.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bootanimation.dir/module/persioncv/vision/vision.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /work/Blizzard/module/persioncv/vision/vision.cpp > CMakeFiles/bootanimation.dir/module/persioncv/vision/vision.cpp.i

CMakeFiles/bootanimation.dir/module/persioncv/vision/vision.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bootanimation.dir/module/persioncv/vision/vision.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /work/Blizzard/module/persioncv/vision/vision.cpp -o CMakeFiles/bootanimation.dir/module/persioncv/vision/vision.cpp.s

CMakeFiles/bootanimation.dir/samples/animation/animation.cpp.o: CMakeFiles/bootanimation.dir/flags.make
CMakeFiles/bootanimation.dir/samples/animation/animation.cpp.o: ../samples/animation/animation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/work/Blizzard/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/bootanimation.dir/samples/animation/animation.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bootanimation.dir/samples/animation/animation.cpp.o -c /work/Blizzard/samples/animation/animation.cpp

CMakeFiles/bootanimation.dir/samples/animation/animation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bootanimation.dir/samples/animation/animation.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /work/Blizzard/samples/animation/animation.cpp > CMakeFiles/bootanimation.dir/samples/animation/animation.cpp.i

CMakeFiles/bootanimation.dir/samples/animation/animation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bootanimation.dir/samples/animation/animation.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /work/Blizzard/samples/animation/animation.cpp -o CMakeFiles/bootanimation.dir/samples/animation/animation.cpp.s

CMakeFiles/bootanimation.dir/samples/animation/main.cpp.o: CMakeFiles/bootanimation.dir/flags.make
CMakeFiles/bootanimation.dir/samples/animation/main.cpp.o: ../samples/animation/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/work/Blizzard/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/bootanimation.dir/samples/animation/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bootanimation.dir/samples/animation/main.cpp.o -c /work/Blizzard/samples/animation/main.cpp

CMakeFiles/bootanimation.dir/samples/animation/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bootanimation.dir/samples/animation/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /work/Blizzard/samples/animation/main.cpp > CMakeFiles/bootanimation.dir/samples/animation/main.cpp.i

CMakeFiles/bootanimation.dir/samples/animation/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bootanimation.dir/samples/animation/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /work/Blizzard/samples/animation/main.cpp -o CMakeFiles/bootanimation.dir/samples/animation/main.cpp.s

# Object files for target bootanimation
bootanimation_OBJECTS = \
"CMakeFiles/bootanimation.dir/blizzard/lib/glad/glad.c.o" \
"CMakeFiles/bootanimation.dir/blizzard/lib/stb_image/stb_image.cpp.o" \
"CMakeFiles/bootanimation.dir/blizzard/src/game.cpp.o" \
"CMakeFiles/bootanimation.dir/blizzard/src/game_object.cpp.o" \
"CMakeFiles/bootanimation.dir/blizzard/src/resource_manager.cpp.o" \
"CMakeFiles/bootanimation.dir/blizzard/src/shader.cpp.o" \
"CMakeFiles/bootanimation.dir/blizzard/src/sprite_renderer.cpp.o" \
"CMakeFiles/bootanimation.dir/blizzard/src/texture.cpp.o" \
"CMakeFiles/bootanimation.dir/blizzard/src/texture_vision.cpp.o" \
"CMakeFiles/bootanimation.dir/module/persioncv/vision/vision.cpp.o" \
"CMakeFiles/bootanimation.dir/samples/animation/animation.cpp.o" \
"CMakeFiles/bootanimation.dir/samples/animation/main.cpp.o"

# External object files for target bootanimation
bootanimation_EXTERNAL_OBJECTS =

bootanimation: CMakeFiles/bootanimation.dir/blizzard/lib/glad/glad.c.o
bootanimation: CMakeFiles/bootanimation.dir/blizzard/lib/stb_image/stb_image.cpp.o
bootanimation: CMakeFiles/bootanimation.dir/blizzard/src/game.cpp.o
bootanimation: CMakeFiles/bootanimation.dir/blizzard/src/game_object.cpp.o
bootanimation: CMakeFiles/bootanimation.dir/blizzard/src/resource_manager.cpp.o
bootanimation: CMakeFiles/bootanimation.dir/blizzard/src/shader.cpp.o
bootanimation: CMakeFiles/bootanimation.dir/blizzard/src/sprite_renderer.cpp.o
bootanimation: CMakeFiles/bootanimation.dir/blizzard/src/texture.cpp.o
bootanimation: CMakeFiles/bootanimation.dir/blizzard/src/texture_vision.cpp.o
bootanimation: CMakeFiles/bootanimation.dir/module/persioncv/vision/vision.cpp.o
bootanimation: CMakeFiles/bootanimation.dir/samples/animation/animation.cpp.o
bootanimation: CMakeFiles/bootanimation.dir/samples/animation/main.cpp.o
bootanimation: CMakeFiles/bootanimation.dir/build.make
bootanimation: /usr/local/lib/libglfw3.a
bootanimation: /usr/local/lib/libglfw3.a
bootanimation: /usr/local/lib/libopencv_superres.so.3.4.3
bootanimation: /usr/local/lib/libopencv_videostab.so.3.4.3
bootanimation: /usr/local/lib/libopencv_photo.so.3.4.3
bootanimation: /usr/local/lib/libopencv_objdetect.so.3.4.3
bootanimation: /usr/local/lib/libopencv_stitching.so.3.4.3
bootanimation: /usr/local/lib/libopencv_ml.so.3.4.3
bootanimation: /usr/local/lib/libopencv_dnn.so.3.4.3
bootanimation: /usr/local/lib/libopencv_shape.so.3.4.3
bootanimation: /usr/local/lib/libopencv_calib3d.so.3.4.3
bootanimation: /usr/lib/x86_64-linux-gnu/librt.so
bootanimation: /usr/lib/x86_64-linux-gnu/libm.so
bootanimation: /usr/lib/x86_64-linux-gnu/libX11.so
bootanimation: /usr/lib/x86_64-linux-gnu/libXrandr.so
bootanimation: /usr/lib/x86_64-linux-gnu/libXinerama.so
bootanimation: /usr/lib/x86_64-linux-gnu/libXxf86vm.so
bootanimation: /usr/lib/x86_64-linux-gnu/libXcursor.so
bootanimation: /usr/local/lib/libopencv_features2d.so.3.4.3
bootanimation: /usr/local/lib/libopencv_highgui.so.3.4.3
bootanimation: /usr/local/lib/libopencv_flann.so.3.4.3
bootanimation: /usr/local/lib/libopencv_videoio.so.3.4.3
bootanimation: /usr/local/lib/libopencv_imgcodecs.so.3.4.3
bootanimation: /usr/local/lib/libopencv_video.so.3.4.3
bootanimation: /usr/local/lib/libopencv_imgproc.so.3.4.3
bootanimation: /usr/local/lib/libopencv_core.so.3.4.3
bootanimation: CMakeFiles/bootanimation.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/work/Blizzard/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Linking CXX executable bootanimation"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bootanimation.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bootanimation.dir/build: bootanimation

.PHONY : CMakeFiles/bootanimation.dir/build

CMakeFiles/bootanimation.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bootanimation.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bootanimation.dir/clean

CMakeFiles/bootanimation.dir/depend:
	cd /work/Blizzard/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /work/Blizzard /work/Blizzard /work/Blizzard/cmake-build-debug /work/Blizzard/cmake-build-debug /work/Blizzard/cmake-build-debug/CMakeFiles/bootanimation.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bootanimation.dir/depend
