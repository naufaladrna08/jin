#include <FormWindow.hpp>

FormWindow::FormWindow() {
  Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create();

  try {
    builder->add_from_file("../../etc/glades/Popup.glade");
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
    Gtk::Entry* entry = 0;
    builder->get_widget("title", m_entry);
    builder->get_widget("content", m_textview);
    builder->get_widget("button", m_button);

    if (m_button)
      m_button->signal_clicked().connect(sigc::mem_fun(*this, &FormWindow::OnButtonClicked), false);
  }

  window->show();
}

FormWindow::~FormWindow() {

}

void FormWindow::OnButtonClicked() {
  if (m_entry->get_text_length() > 3) {
    create_template(
      (string) m_entry->get_text().c_str(),       // Title 
      get_text_of_textview(m_textview->gobj())    // Content
    );
  }
  
  window->hide();
  delete window;
}
