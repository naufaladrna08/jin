/**
 * @file FormWindow.hpp
 * @author Naufal Adriansyah (naufaladrn90@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef FORMWINDOW_HPP
#define FORMWINDOW_HPP

#include <gtkmm.h>
#include <stdio.h>
#include <Utils.h>
#include <Common.h>

class FormWindow : public Gtk::Window {
  public:
    FormWindow();
    ~FormWindow();

  protected:
    Gtk::VBox m_vbox;
    Gtk::Entry m_title;
    Gtk::TextView m_textview;
    Gtk::Button m_button;
};

#endif