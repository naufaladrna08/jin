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
#include <QtCore/QDebug>

MainWindow::MainWindow(QWidget* parent)
  : QWidget(parent) {
  QScreen *screen = QGuiApplication::primaryScreen();
  QRect screenGeometry = screen->geometry();
  
  int height = screenGeometry.height();
  int width = screenGeometry.width();

  setWindowTitle(tr("Jin"));
  setFixedWidth(width / 4);
  setFixedHeight(height / 8);

  setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

  read_files("5");
  QString file = open_file("050.templ");
  qInfo() << file;
}

MainWindow::~MainWindow() {
  
}