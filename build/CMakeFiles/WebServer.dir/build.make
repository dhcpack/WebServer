# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /tmp/tmp.eDsmt94mLg

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /tmp/tmp.eDsmt94mLg/build

# Include any dependencies generated for this target.
include CMakeFiles/WebServer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/WebServer.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/WebServer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/WebServer.dir/flags.make

CMakeFiles/WebServer.dir/main.cpp.o: CMakeFiles/WebServer.dir/flags.make
CMakeFiles/WebServer.dir/main.cpp.o: /tmp/tmp.eDsmt94mLg/main.cpp
CMakeFiles/WebServer.dir/main.cpp.o: CMakeFiles/WebServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.eDsmt94mLg/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/WebServer.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/WebServer.dir/main.cpp.o -MF CMakeFiles/WebServer.dir/main.cpp.o.d -o CMakeFiles/WebServer.dir/main.cpp.o -c /tmp/tmp.eDsmt94mLg/main.cpp

CMakeFiles/WebServer.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WebServer.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/tmp.eDsmt94mLg/main.cpp > CMakeFiles/WebServer.dir/main.cpp.i

CMakeFiles/WebServer.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WebServer.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/tmp.eDsmt94mLg/main.cpp -o CMakeFiles/WebServer.dir/main.cpp.s

CMakeFiles/WebServer.dir/log/log.cpp.o: CMakeFiles/WebServer.dir/flags.make
CMakeFiles/WebServer.dir/log/log.cpp.o: /tmp/tmp.eDsmt94mLg/log/log.cpp
CMakeFiles/WebServer.dir/log/log.cpp.o: CMakeFiles/WebServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.eDsmt94mLg/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/WebServer.dir/log/log.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/WebServer.dir/log/log.cpp.o -MF CMakeFiles/WebServer.dir/log/log.cpp.o.d -o CMakeFiles/WebServer.dir/log/log.cpp.o -c /tmp/tmp.eDsmt94mLg/log/log.cpp

CMakeFiles/WebServer.dir/log/log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WebServer.dir/log/log.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/tmp.eDsmt94mLg/log/log.cpp > CMakeFiles/WebServer.dir/log/log.cpp.i

CMakeFiles/WebServer.dir/log/log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WebServer.dir/log/log.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/tmp.eDsmt94mLg/log/log.cpp -o CMakeFiles/WebServer.dir/log/log.cpp.s

CMakeFiles/WebServer.dir/buffer/buffer.cpp.o: CMakeFiles/WebServer.dir/flags.make
CMakeFiles/WebServer.dir/buffer/buffer.cpp.o: /tmp/tmp.eDsmt94mLg/buffer/buffer.cpp
CMakeFiles/WebServer.dir/buffer/buffer.cpp.o: CMakeFiles/WebServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.eDsmt94mLg/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/WebServer.dir/buffer/buffer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/WebServer.dir/buffer/buffer.cpp.o -MF CMakeFiles/WebServer.dir/buffer/buffer.cpp.o.d -o CMakeFiles/WebServer.dir/buffer/buffer.cpp.o -c /tmp/tmp.eDsmt94mLg/buffer/buffer.cpp

CMakeFiles/WebServer.dir/buffer/buffer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WebServer.dir/buffer/buffer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/tmp.eDsmt94mLg/buffer/buffer.cpp > CMakeFiles/WebServer.dir/buffer/buffer.cpp.i

CMakeFiles/WebServer.dir/buffer/buffer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WebServer.dir/buffer/buffer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/tmp.eDsmt94mLg/buffer/buffer.cpp -o CMakeFiles/WebServer.dir/buffer/buffer.cpp.s

CMakeFiles/WebServer.dir/mysqlpool/mysqlpool.cpp.o: CMakeFiles/WebServer.dir/flags.make
CMakeFiles/WebServer.dir/mysqlpool/mysqlpool.cpp.o: /tmp/tmp.eDsmt94mLg/mysqlpool/mysqlpool.cpp
CMakeFiles/WebServer.dir/mysqlpool/mysqlpool.cpp.o: CMakeFiles/WebServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.eDsmt94mLg/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/WebServer.dir/mysqlpool/mysqlpool.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/WebServer.dir/mysqlpool/mysqlpool.cpp.o -MF CMakeFiles/WebServer.dir/mysqlpool/mysqlpool.cpp.o.d -o CMakeFiles/WebServer.dir/mysqlpool/mysqlpool.cpp.o -c /tmp/tmp.eDsmt94mLg/mysqlpool/mysqlpool.cpp

CMakeFiles/WebServer.dir/mysqlpool/mysqlpool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WebServer.dir/mysqlpool/mysqlpool.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/tmp.eDsmt94mLg/mysqlpool/mysqlpool.cpp > CMakeFiles/WebServer.dir/mysqlpool/mysqlpool.cpp.i

CMakeFiles/WebServer.dir/mysqlpool/mysqlpool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WebServer.dir/mysqlpool/mysqlpool.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/tmp.eDsmt94mLg/mysqlpool/mysqlpool.cpp -o CMakeFiles/WebServer.dir/mysqlpool/mysqlpool.cpp.s

CMakeFiles/WebServer.dir/timer/heaptimer.cpp.o: CMakeFiles/WebServer.dir/flags.make
CMakeFiles/WebServer.dir/timer/heaptimer.cpp.o: /tmp/tmp.eDsmt94mLg/timer/heaptimer.cpp
CMakeFiles/WebServer.dir/timer/heaptimer.cpp.o: CMakeFiles/WebServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.eDsmt94mLg/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/WebServer.dir/timer/heaptimer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/WebServer.dir/timer/heaptimer.cpp.o -MF CMakeFiles/WebServer.dir/timer/heaptimer.cpp.o.d -o CMakeFiles/WebServer.dir/timer/heaptimer.cpp.o -c /tmp/tmp.eDsmt94mLg/timer/heaptimer.cpp

CMakeFiles/WebServer.dir/timer/heaptimer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WebServer.dir/timer/heaptimer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/tmp.eDsmt94mLg/timer/heaptimer.cpp > CMakeFiles/WebServer.dir/timer/heaptimer.cpp.i

CMakeFiles/WebServer.dir/timer/heaptimer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WebServer.dir/timer/heaptimer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/tmp.eDsmt94mLg/timer/heaptimer.cpp -o CMakeFiles/WebServer.dir/timer/heaptimer.cpp.s

CMakeFiles/WebServer.dir/http/httprequest.cpp.o: CMakeFiles/WebServer.dir/flags.make
CMakeFiles/WebServer.dir/http/httprequest.cpp.o: /tmp/tmp.eDsmt94mLg/http/httprequest.cpp
CMakeFiles/WebServer.dir/http/httprequest.cpp.o: CMakeFiles/WebServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.eDsmt94mLg/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/WebServer.dir/http/httprequest.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/WebServer.dir/http/httprequest.cpp.o -MF CMakeFiles/WebServer.dir/http/httprequest.cpp.o.d -o CMakeFiles/WebServer.dir/http/httprequest.cpp.o -c /tmp/tmp.eDsmt94mLg/http/httprequest.cpp

CMakeFiles/WebServer.dir/http/httprequest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WebServer.dir/http/httprequest.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/tmp.eDsmt94mLg/http/httprequest.cpp > CMakeFiles/WebServer.dir/http/httprequest.cpp.i

CMakeFiles/WebServer.dir/http/httprequest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WebServer.dir/http/httprequest.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/tmp.eDsmt94mLg/http/httprequest.cpp -o CMakeFiles/WebServer.dir/http/httprequest.cpp.s

CMakeFiles/WebServer.dir/http/userfunctions.cpp.o: CMakeFiles/WebServer.dir/flags.make
CMakeFiles/WebServer.dir/http/userfunctions.cpp.o: /tmp/tmp.eDsmt94mLg/http/userfunctions.cpp
CMakeFiles/WebServer.dir/http/userfunctions.cpp.o: CMakeFiles/WebServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.eDsmt94mLg/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/WebServer.dir/http/userfunctions.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/WebServer.dir/http/userfunctions.cpp.o -MF CMakeFiles/WebServer.dir/http/userfunctions.cpp.o.d -o CMakeFiles/WebServer.dir/http/userfunctions.cpp.o -c /tmp/tmp.eDsmt94mLg/http/userfunctions.cpp

CMakeFiles/WebServer.dir/http/userfunctions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WebServer.dir/http/userfunctions.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/tmp.eDsmt94mLg/http/userfunctions.cpp > CMakeFiles/WebServer.dir/http/userfunctions.cpp.i

CMakeFiles/WebServer.dir/http/userfunctions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WebServer.dir/http/userfunctions.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/tmp.eDsmt94mLg/http/userfunctions.cpp -o CMakeFiles/WebServer.dir/http/userfunctions.cpp.s

CMakeFiles/WebServer.dir/http/httpresponse.cpp.o: CMakeFiles/WebServer.dir/flags.make
CMakeFiles/WebServer.dir/http/httpresponse.cpp.o: /tmp/tmp.eDsmt94mLg/http/httpresponse.cpp
CMakeFiles/WebServer.dir/http/httpresponse.cpp.o: CMakeFiles/WebServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.eDsmt94mLg/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/WebServer.dir/http/httpresponse.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/WebServer.dir/http/httpresponse.cpp.o -MF CMakeFiles/WebServer.dir/http/httpresponse.cpp.o.d -o CMakeFiles/WebServer.dir/http/httpresponse.cpp.o -c /tmp/tmp.eDsmt94mLg/http/httpresponse.cpp

CMakeFiles/WebServer.dir/http/httpresponse.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WebServer.dir/http/httpresponse.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/tmp.eDsmt94mLg/http/httpresponse.cpp > CMakeFiles/WebServer.dir/http/httpresponse.cpp.i

CMakeFiles/WebServer.dir/http/httpresponse.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WebServer.dir/http/httpresponse.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/tmp.eDsmt94mLg/http/httpresponse.cpp -o CMakeFiles/WebServer.dir/http/httpresponse.cpp.s

CMakeFiles/WebServer.dir/http/httpconnect.cpp.o: CMakeFiles/WebServer.dir/flags.make
CMakeFiles/WebServer.dir/http/httpconnect.cpp.o: /tmp/tmp.eDsmt94mLg/http/httpconnect.cpp
CMakeFiles/WebServer.dir/http/httpconnect.cpp.o: CMakeFiles/WebServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.eDsmt94mLg/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/WebServer.dir/http/httpconnect.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/WebServer.dir/http/httpconnect.cpp.o -MF CMakeFiles/WebServer.dir/http/httpconnect.cpp.o.d -o CMakeFiles/WebServer.dir/http/httpconnect.cpp.o -c /tmp/tmp.eDsmt94mLg/http/httpconnect.cpp

CMakeFiles/WebServer.dir/http/httpconnect.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WebServer.dir/http/httpconnect.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/tmp.eDsmt94mLg/http/httpconnect.cpp > CMakeFiles/WebServer.dir/http/httpconnect.cpp.i

CMakeFiles/WebServer.dir/http/httpconnect.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WebServer.dir/http/httpconnect.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/tmp.eDsmt94mLg/http/httpconnect.cpp -o CMakeFiles/WebServer.dir/http/httpconnect.cpp.s

CMakeFiles/WebServer.dir/server/webserver.cpp.o: CMakeFiles/WebServer.dir/flags.make
CMakeFiles/WebServer.dir/server/webserver.cpp.o: /tmp/tmp.eDsmt94mLg/server/webserver.cpp
CMakeFiles/WebServer.dir/server/webserver.cpp.o: CMakeFiles/WebServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.eDsmt94mLg/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/WebServer.dir/server/webserver.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/WebServer.dir/server/webserver.cpp.o -MF CMakeFiles/WebServer.dir/server/webserver.cpp.o.d -o CMakeFiles/WebServer.dir/server/webserver.cpp.o -c /tmp/tmp.eDsmt94mLg/server/webserver.cpp

CMakeFiles/WebServer.dir/server/webserver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WebServer.dir/server/webserver.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/tmp.eDsmt94mLg/server/webserver.cpp > CMakeFiles/WebServer.dir/server/webserver.cpp.i

CMakeFiles/WebServer.dir/server/webserver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WebServer.dir/server/webserver.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/tmp.eDsmt94mLg/server/webserver.cpp -o CMakeFiles/WebServer.dir/server/webserver.cpp.s

CMakeFiles/WebServer.dir/server/epoller.cpp.o: CMakeFiles/WebServer.dir/flags.make
CMakeFiles/WebServer.dir/server/epoller.cpp.o: /tmp/tmp.eDsmt94mLg/server/epoller.cpp
CMakeFiles/WebServer.dir/server/epoller.cpp.o: CMakeFiles/WebServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.eDsmt94mLg/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/WebServer.dir/server/epoller.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/WebServer.dir/server/epoller.cpp.o -MF CMakeFiles/WebServer.dir/server/epoller.cpp.o.d -o CMakeFiles/WebServer.dir/server/epoller.cpp.o -c /tmp/tmp.eDsmt94mLg/server/epoller.cpp

CMakeFiles/WebServer.dir/server/epoller.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WebServer.dir/server/epoller.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/tmp.eDsmt94mLg/server/epoller.cpp > CMakeFiles/WebServer.dir/server/epoller.cpp.i

CMakeFiles/WebServer.dir/server/epoller.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WebServer.dir/server/epoller.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/tmp.eDsmt94mLg/server/epoller.cpp -o CMakeFiles/WebServer.dir/server/epoller.cpp.s

# Object files for target WebServer
WebServer_OBJECTS = \
"CMakeFiles/WebServer.dir/main.cpp.o" \
"CMakeFiles/WebServer.dir/log/log.cpp.o" \
"CMakeFiles/WebServer.dir/buffer/buffer.cpp.o" \
"CMakeFiles/WebServer.dir/mysqlpool/mysqlpool.cpp.o" \
"CMakeFiles/WebServer.dir/timer/heaptimer.cpp.o" \
"CMakeFiles/WebServer.dir/http/httprequest.cpp.o" \
"CMakeFiles/WebServer.dir/http/userfunctions.cpp.o" \
"CMakeFiles/WebServer.dir/http/httpresponse.cpp.o" \
"CMakeFiles/WebServer.dir/http/httpconnect.cpp.o" \
"CMakeFiles/WebServer.dir/server/webserver.cpp.o" \
"CMakeFiles/WebServer.dir/server/epoller.cpp.o"

# External object files for target WebServer
WebServer_EXTERNAL_OBJECTS =

WebServer: CMakeFiles/WebServer.dir/main.cpp.o
WebServer: CMakeFiles/WebServer.dir/log/log.cpp.o
WebServer: CMakeFiles/WebServer.dir/buffer/buffer.cpp.o
WebServer: CMakeFiles/WebServer.dir/mysqlpool/mysqlpool.cpp.o
WebServer: CMakeFiles/WebServer.dir/timer/heaptimer.cpp.o
WebServer: CMakeFiles/WebServer.dir/http/httprequest.cpp.o
WebServer: CMakeFiles/WebServer.dir/http/userfunctions.cpp.o
WebServer: CMakeFiles/WebServer.dir/http/httpresponse.cpp.o
WebServer: CMakeFiles/WebServer.dir/http/httpconnect.cpp.o
WebServer: CMakeFiles/WebServer.dir/server/webserver.cpp.o
WebServer: CMakeFiles/WebServer.dir/server/epoller.cpp.o
WebServer: CMakeFiles/WebServer.dir/build.make
WebServer: CMakeFiles/WebServer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/tmp/tmp.eDsmt94mLg/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking CXX executable WebServer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/WebServer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/WebServer.dir/build: WebServer
.PHONY : CMakeFiles/WebServer.dir/build

CMakeFiles/WebServer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/WebServer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/WebServer.dir/clean

CMakeFiles/WebServer.dir/depend:
	cd /tmp/tmp.eDsmt94mLg/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /tmp/tmp.eDsmt94mLg /tmp/tmp.eDsmt94mLg /tmp/tmp.eDsmt94mLg/build /tmp/tmp.eDsmt94mLg/build /tmp/tmp.eDsmt94mLg/build/CMakeFiles/WebServer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/WebServer.dir/depend

