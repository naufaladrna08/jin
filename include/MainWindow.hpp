#ifndef MAIN_WINDOWN_HPP
#define MAIN_WINDOWN_HPP

#include <gtkmm.h>
#include <stdio.h>
#include <Utils.h>
#include <Common.h>
#include <FormWindow.hpp>
#include <SettingsWindow.hpp>
#include <Config.h>
#include <iostream>
#include <vector>

/* Load X11 Linux */
#include <X11/Xlib.h>
#include <keybinder-3.0/keybinder.h>

extern tfile_t root;
extern tfile_t result;

enum {
  COL_ICON = 0,
  COL_NAME,
  COL_NUM
};

class MainWindow : public Gtk::Window {
  public:
    MainWindow();
    virtual ~MainWindow();

    void setVisual(Glib::RefPtr<Gdk::Visual> visual);
    void resetCompletion();

  protected:
    Gtk::Entry m_textbox;
    GtkListStore* store;
    GtkEntryCompletion* completion;
    GtkTreeModel* completion_model;
    GtkTreeModel* populateCompletion(std::string key);

    Glib::RefPtr<Gtk::EntryCompletion> m_completion;
    Glib::RefPtr<Gtk::TreeModel> m_model;
    // void set_match_func(const Gtk::EntryCompletion::SlotMatch &slot)
    bool onKeyPress(GdkEventKey* event);
    void onEntryChanged();
    void ActivateCompletion(std::string key);
    bool on_match(const Glib::ustring& key, const Gtk::TreeModel::const_iterator& iter);
    
    void shortcutHandler(const char *keystring, void *user_data);
    virtual bool onDraw(const Cairo::RefPtr<Cairo::Context>& ctx);
    void onScreenChanged(const Glib::RefPtr<Gdk::Screen>& previous_screen);
    FormWindow* m_formwindow;
    SettingsWindow* m_settingswindow;

    bool _SUPPORTS_ALPHA = false;
    
  private:
    int m_screenw, m_screenh;

    void LoadStylesheet();
};

#endif // MAIN_WINDOWN_HPP
