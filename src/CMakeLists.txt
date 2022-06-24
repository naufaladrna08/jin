link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS})
include_directories(../include)

set(GCC_COMPILE_FLAGS "-Wno-write-strings")
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

add_executable(jin
  main.cxx 
  MainWindow.cxx
  Utils.cxx
  TFile.cxx
  FormWindow.cxx
  Config.cxx
)

target_link_libraries(jin ${GTKMM_LIBRARIES} ${KEYBINDER_LIBRARIES} -lX11)