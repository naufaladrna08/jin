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

    Glib::RefPtr<Gtk::ListStore> refCompletionModel;
    Glib::RefPtr<Gtk::EntryCompletion> m_completion;
    Gtk::TreeModel::Row row;

    bool onKeyPress(GdkEventKey* event);
    void onEntryChanged();
    void CreateModel();
    void ActivateCompletion();
    bool on_match(const Glib::ustring& key, const Gtk::TreeModel::const_iterator& iter);
    
    void shortcutHandler(const char *keystring, void *user_data);
    virtual bool onDraw(const Cairo::RefPtr<Cairo::Context>& ctx);
    void onScreenChanged(const Glib::RefPtr<Gdk::Screen>& previous_screen);
    FormWindow* m_formwindow;
    SettingsWindow* m_settingswindow;

    bool _SUPPORTS_ALPHA = false;

    class ModelColumns : public Gtk::TreeModel::ColumnRecord {
      public:

        ModelColumns() { 
          add(m_col_id); 
          add(m_col_name); 
          add(m_col_icon); 
        }

        Gtk::TreeModelColumn<unsigned int> m_col_id;
        Gtk::TreeModelColumn<Glib::ustring> m_col_name;
        Gtk::TreeModelColumn<Glib::ustring> m_col_icon;
    };

    ModelColumns m_column;
    typedef std::map<int, Glib::ustring> type_actions_map;
    type_actions_map m_CompletionActions;
    
  private:
    int m_screenw, m_screenh;

    void LoadStylesheet();
};

#endif // MAIN_WINDOWN_HPP
