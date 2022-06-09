#include <MainWindow.hpp>
#include <gtkmm/main.h>
#include <Common.hpp>

MainWindow* winroot;

void shortcutHandler(const char *keystring, void *user_data) {
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
