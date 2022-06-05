#ifndef MAIN_WINDOWN_HPP
#define MAIN_WINDOWN_HPP

#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <iostream>

class MainWindow : public Gtk::Window {
  public:
    MainWindow();
    virtual ~MainWindow();

  protected:
    void OnButtonPressed();
    Gtk::Button m_button;
};

#endif // MAIN_WINDOWN_HPP
