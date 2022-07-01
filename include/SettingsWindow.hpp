/**
 * @file SettingsWindow.hpp
 * @author Naufal Adriansyah (naufaladrn90@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef SETTINGSWINDOW_HPP
#define SETTINGSWINDOW_HPP

#include <gtkmm.h>
#include <stdio.h>
#include <Utils.h>
#include <Config.h>
#include <Common.h>

class SettingsWindow : public Gtk::Window {
  public:
    SettingsWindow();
    ~SettingsWindow();

  protected:
    void OnButtonClicked();
    Gtk::TextView* m_textview;
    Gtk::Button* m_button;
    Gtk::Entry* m_max_displayed_item;
    Gtk::Window* window = this;
};

#endif