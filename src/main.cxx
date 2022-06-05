#include <MainWindow.hpp>

int main(int argc, char** argv) {
  auto app = Gtk::Application::create(argc, argv, "org.kincirangin.jin");

  MainWindow w;
  
  return app->run(w);
}
