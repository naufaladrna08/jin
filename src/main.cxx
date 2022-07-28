#include <MainWindow.hpp>
// #include <gtkmm/main.h>
#include <gtkmm-3.0/gtkmm.h>
#include <Common.h>

MainWindow* winroot;

void shortcutHandler(const char *keystring, void *user_data) {
  winroot->resetCompletion();
  winroot->set_keep_above(true);
  winroot->show();
  winroot->set_focus_visible(true);
}

int main(int argc, char *argv[]) {
  Gtk::Main kit(argc, argv);

  winroot = new MainWindow();
  auto app = Gtk::Application::create(GTK_ID);
  app->hold();

  keybinder_init();
  keybinder_bind(KEY_SHORTCUT, shortcutHandler, NULL);

  return app->run(*winroot);
}
