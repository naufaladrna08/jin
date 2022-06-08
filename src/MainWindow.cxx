#include <MainWindow.hpp>

MainWindow::MainWindow() {
  set_border_width(1);

  /* Get screen resolution in Linux, X11. */
  Display* display = XOpenDisplay(NULL);
  Screen* screen = DefaultScreenOfDisplay(display);

  m_screenw = screen->width;
  m_screenh = screen->height;

  /* Disable window's frame */
  Gtk::Window::set_decorated(false);

  /* Set window's size */
  Gtk::Window::set_size_request(m_screenw / 3, 32);
  Gtk::Window::move((m_screenw / 2) - (m_screenw / 3) / 2, m_screenh / 2 - 64);
  add(m_textbox);
  m_textbox.show();

  // m_button.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::OnButtonPressed));
}

MainWindow::~MainWindow() {

}