cmake_minimum_required(VERSION 3.14)

project(PCBMK)
# Add an executable or library
add_executable(PCBMK main.cpp)

target_include_directories(PCBMK
    PRIVATE
        ${CMAKE_SOURCE_DIR}/lib/fmt/include   # Only for this target
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Specify installation rules
install(TARGETS PCBMK
   RUNTIME DESTINATION bin # For executables
   LIBRARY DESTINATION lib # For shared libraries
   ARCHIVE DESTINATION lib/static # For static libraries
)