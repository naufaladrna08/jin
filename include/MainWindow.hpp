#ifndef MAIN_WINDOWN_HPP
#define MAIN_WINDOWN_HPP

#include <gtkmm.h>
#include <iostream>
#include <Utils.h>
#include <Common.hpp>

/* Load X11 Linux */
#include <X11/Xlib.h>
#include <keybinder-3.0/keybinder.h>

extern tfile_t root;

enum {
  COL_NAME = 0,
  COL_PATH,
  NUM_COLS
};

class MainWindow : public Gtk::Window {
  public:
    MainWindow();
    virtual ~MainWindow();

  protected:
    Gtk::Entry m_textbox;
    GtkListStore *store;
    GtkTreeModel* populateCompletion();

    bool onKeyPress(GdkEventKey* event);
    void shortcutHandler(const char *keystring, void *user_data);

  private:
    int m_screenw, m_screenh;
};

#endif // MAIN_WINDOWN_HPP
