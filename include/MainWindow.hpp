#ifndef MAIN_WINDOWN_HPP
#define MAIN_WINDOWN_HPP

#include <gtkmm.h>
#include <stdio.h>
#include <Utils.h>
#include <Common.h>

/* Load X11 Linux */
#include <X11/Xlib.h>
#include <keybinder-3.0/keybinder.h>

extern tfile_t root;

enum {
  COL_NAME = 0,
  NUM_COLS
};

class MainWindow : public Gtk::Window {
  public:
    MainWindow();
    virtual ~MainWindow();
    void setVisual(Glib::RefPtr<Gdk::Visual> visual);

  protected:
    Gtk::Entry m_textbox;
    GtkListStore *store;
    GtkEntryCompletion *completion;
    GtkTreeModel *completion_model;
    GtkTreeModel* populateCompletion();

    bool onKeyPress(GdkEventKey* event);
    void shortcutHandler(const char *keystring, void *user_data);
    virtual bool onDraw(const Cairo::RefPtr<Cairo::Context>& ctx);
    void onScreenChanged(const Glib::RefPtr<Gdk::Screen>& previous_screen);

    bool _SUPPORTS_ALPHA = false;
    
  private:
    int m_screenw, m_screenh;

    void LoadStylesheet();
};

#endif // MAIN_WINDOWN_HPP
