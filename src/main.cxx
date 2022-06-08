#include <MainWindow.hpp>
#include <gtkmm/main.h>

int main(int argc, char *argv[]) {
  Gtk::Main kit(argc, argv);

  MainWindow root;
  Gtk::Main::run(root);

  return 0;
}
