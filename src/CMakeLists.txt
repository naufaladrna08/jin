link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS})
include_directories(../include)

set(GCC_COVERAGE_COMPILE_FLAGS "-Wno-write-strings")

add_executable(jin
  main.cxx 
  MainWindow.cxx
  Utils.cxx
  TFile.cxx
)

target_link_libraries(jin ${GTKMM_LIBRARIES} -lX11)