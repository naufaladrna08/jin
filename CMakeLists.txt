cmake_minimum_required(VERSION 3.0.0)
project(Jin VERSION 0.1.0)

# Enable Testing
enable_testing()

# Find GTK4 Library
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

# Include path
include(CTest)
include_directories(include)
include_directories(${GTK4_INCLUDE_DIRS})

link_directories(${GTK4_LIBRARY_DIRS})
add_definitions(${GTK4_CFLAGS_OTHER})

add_executable(Jin 
  src/main.c
)

target_link_libraries(Jin ${GTK4_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
