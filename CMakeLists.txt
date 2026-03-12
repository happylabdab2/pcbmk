cmake_minimum_required(VERSION 3.14)

project(PCBMK)
# Add an executable or library
add_executable(PCBMK main.cpp)

include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Specify installation rules
install(TARGETS MyApp
   RUNTIME DESTINATION bin # For executables
   LIBRARY DESTINATION lib # For shared libraries
   ARCHIVE DESTINATION lib/static # For static libraries
)