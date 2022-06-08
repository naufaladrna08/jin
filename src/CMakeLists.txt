link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS})
include_directories(../include)

add_executable(jin
  main.cxx 
  MainWindow.cxx
  Utils.cxx
)

target_link_libraries(jin ${GTKMM_LIBRARIES} -lX11)