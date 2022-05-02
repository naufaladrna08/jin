/**
 * @file MainWindow.cpp
 * @author Naufal Adriansyah (naufaladrn90@gmail.com)
 * @brief Implementation of Main window
 * @version 0.1
 * @date 2022-05-02
 * 
 * 
 * @copyright Copyright (c) 2022
 */

#include <QtWidgets/QtWidgets>
#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget* parent)
  : QWidget(parent) {
  /* Get screen size and set window size */
  QScreen *screen = QGuiApplication::primaryScreen();
  QRect screenGeometry = screen->geometry();
  
  int width = screenGeometry.width() / 4;
  int height = (screenGeometry.height() / 8) / 2;

  setFixedWidth(width);
  setFixedHeight(height);
  setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

  m_clipboard = QApplication::clipboard();
  m_textbox = new QLineEdit;

  /* Layout */
  QHBoxLayout *row = new QHBoxLayout;
  row->addWidget(m_textbox);
  row->addStretch(1);

  setLayout(row);
}

MainWindow::~MainWindow() {
  
}