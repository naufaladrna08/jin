#include <SettingsWindow.hpp>

SettingsWindow::SettingsWindow() {
  Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create();

  try {
    builder->add_from_file("../../etc/glades/Settings.glade");
  } catch(const Glib::FileError& ex) {
    std::cerr << "FileError: " << ex.what() << std::endl;
    return;
  } catch(const Glib::MarkupError& ex) {
    std::cerr << "MarkupError: " << ex.what() << std::endl;
    return;
  } catch(const Gtk::BuilderError& ex) {
    std::cerr << "BuilderError: " << ex.what() << std::endl;
    return;
  }

  builder->get_widget("window", window);

  if (window) {
    // Gtk::Entry* entry = 0;
    // builder->get_widget("title", m_entry);
    // builder->get_widget("content", m_textview);
    // builder->get_widget("button", m_button);

    // if (m_button)
    //   m_button->signal_clicked().connect(sigc::mem_fun(*this, &SettingsWindow::OnButtonClicked), false);
  }

  window->show();
}

SettingsWindow::~SettingsWindow() {

}

void SettingsWindow::OnButtonClicked() {

  
  window->hide();
  delete window;
}
