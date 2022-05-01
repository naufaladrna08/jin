#include <QtWidgets/QtWidgets>
#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget* parent)
  : QWidget(parent) {
  setWindowTitle(tr("Jib"));
  setFixedWidth(640);
}

MainWindow::~MainWindow() {
  
}