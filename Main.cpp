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
#include "MainWindow.hpp"

int main(int argc, char** argv) {
  QApplication a(argc, argv);

  MainWindow w;
  w.show(); 

  return a.exec();
}