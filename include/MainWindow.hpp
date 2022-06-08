#ifndef MAIN_WINDOWN_HPP
#define MAIN_WINDOWN_HPP

#include <gtkmm/entry.h>
#include <gtkmm/window.h>
#include <iostream>

/* Load X11 Linux */
#include <X11/Xlib.h>

class MainWindow : public Gtk::Window {
  public:
    MainWindow();
    virtual ~MainWindow();

  protected:
    Gtk::Entry m_textbox;

  private:
    int m_screenw, m_screenh;
};

#endif // MAIN_WINDOWN_HPP
