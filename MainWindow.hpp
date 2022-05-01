#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QtWidgets/QWidget>

class MainWindow : public QWidget {
  Q_OBJECT

  public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();
};

#endif // __MAINWINDOW_H__