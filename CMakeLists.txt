cmake_minimum_required(VERSION 3.26)
project(Project)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 17)
# Remove the "-O2" flag if you have problems with the debugger.
set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Werror -O2")
set(CMAKE_EXE_LINKER_FLAGS -pthread)

# Set include dir
include_directories(./given_utility ./gtest/include)

# Set Library dir
link_directories(./gtest/lib)

# Set source files for RELEASE target
# Only add cpp files, no h files!
# Only add files with functionality here, no test files!
set(RELEASE_SOURCE_FILES
        src/main.cpp
        src/QueueNode.cpp
        src/Job.cpp
        src/Device.cpp
        src/PrintingSystem.cpp
        src/Queue.cpp
        src/Output.cpp
        src/XMLprocessor.cpp
        given_utility/tinystr.cpp
        given_utility/tinyxml.cpp
        given_utility/tinyxmlerror.cpp
        given_utility/tinyxmlparser.cpp
        src/Scanner.cpp
        src/Scanner.h
        src/Colorprinter.cpp
        src/Colorprinter.h
        src/BWprinter.cpp
        src/BWprinter.h
        src/Logger.cpp
        src/Logger.h
)

# Set source files for DEBUG target
# Only add cpp files, no h files!
set(DEBUG_SOURCE_FILES
        src/Output.cpp
        src/tests.cpp
        src/QueueNode.cpp
        src/Job.cpp
        src/Device.cpp
        src/PrintingSystem.cpp
        src/Queue.cpp
        src/XMLprocessor.cpp
        given_utility/tinystr.cpp
        given_utility/tinyxml.cpp
        given_utility/tinyxmlerror.cpp
        given_utility/tinyxmlparser.cpp
        src/Scanner.cpp
        src/Scanner.h
        src/Colorprinter.cpp
        src/Colorprinter.h
        src/BWprinter.cpp
        src/BWprinter.h
        src/Logger.cpp
)

# Create RELEASE target
add_executable(release_target ${RELEASE_SOURCE_FILES})

# Create DEBUG target
add_executable(debug_target ${DEBUG_SOURCE_FILES})

# Link library
target_link_libraries(debug_target gtest)
