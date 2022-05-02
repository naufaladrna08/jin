/**
 * @file Main.cpp
 * @author Naufal Adriansyah (naufaladrn90@gmail.com)
 * @brief Init app
 * @version 0.1
 * @date 2022-05-02
 * 
 * @copyright Copyright (c) 2022
 */

#include <QtWidgets/QtWidgets>
#include <QtCore/QDebug>
#include <QtGui/QClipboard>
#include "MainWindow.hpp"

int main(int argc, char** argv) {
  QApplication a(argc, argv);

  MainWindow w;
  w.show(); 

  /* Load stylesheet */
  QFile file("themes/default/theme.qss");
  file.open(QFile::ReadOnly);
  QString stylesheet = QLatin1String(file.readAll());
  a.setStyleSheet(stylesheet);

  return a.exec();
}