#include <FormWindow.hpp>

FormWindow::FormWindow() {
  this->set_default_size(640, 480);
  this->set_border_width(8);
  this->set_title("About");

  m_title.set_margin_bottom(16);

  m_vbox.add(m_title);
  m_vbox.add(m_textview);
  m_vbox.add(m_button);

  this->add(m_vbox);
  this->show_all_children();
}

FormWindow::~FormWindow() {

}