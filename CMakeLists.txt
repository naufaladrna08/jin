cmake_minimum_required(VERSION 3.0.0)
project(Jin VERSION 0.1.0)

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)
pkg_check_modules(KEYBINDER keybinder-3.0)
add_subdirectory(src) 

file(GLOB EXTRA_FILES
  "./etc/assets/default.css"
  "./etc/config/jin.conf"
)

file(COPY ${EXTRA_FILES} DESTINATION ${CMAKE_BINARY_DIR}/src/extra)