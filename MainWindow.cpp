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
  
  int textboxHeight = 32 + 8;
  int width = screenGeometry.width() / 3;
  int height = (screenGeometry.height() / 8) / 2 + 8;

  setFixedWidth(width);
  setFixedHeight(height);
  setGeometry(
    screenGeometry.width() / 2 - width / 2,
    screenGeometry.height() / 2 - 100,
    width,
    height
  );

  setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
  setAttribute(Qt::WA_TranslucentBackground);

  m_clipboard = QApplication::clipboard();
  m_textbox = new QLineEdit;
  m_textbox->setFixedHeight(textboxHeight);

  /* Layout */
  QVBoxLayout *row = new QVBoxLayout;
  row->addWidget(m_textbox);
  row->addStretch(1);

  setLayout(row);
}

MainWindow::~MainWindow() {
  
}

void MainWindow::paintEvent(QPaintEvent* e) {
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.setPen(Qt::transparent);
  painter.setBrush(Qt::white);

  QRect rect = this->rect();
  rect.setWidth(rect.width() - 1);
  rect.setHeight(rect.height() - 1);
  painter.drawRoundedRect(rect, 15, 15);

  QWidget::paintEvent(e);
}