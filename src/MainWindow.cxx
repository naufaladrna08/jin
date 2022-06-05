#include <MainWindow.hpp>

MainWindow::MainWindow()
: m_button("Hello World") {
  set_border_width(10);
  m_button.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::OnButtonPressed));

  add(m_button);
  m_button.show();;
}

MainWindow::~MainWindow() {

}

void MainWindow::OnButtonPressed() {
  std::cout << "Jello World" << std::endl;
}