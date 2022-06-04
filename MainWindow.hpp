/**
 * @file MainWindow.cpp
 * @author Naufal Adriansyah (naufaladrn90@gmail.com)
 * @brief Main window
 * @version 0.1
 * @date 2022-05-02
 * 
 * We'll have two application, first the main app which is Jin,
 * and last is Jin Settings.
 * 
 * @copyright Copyright (c) 2022
 */

#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QtWidgets/QWidget>
#include <vector>
#include "Jin.h"

class QLineEdit;
class QVBoxLayout;
class QButtonGroup;
class QClipboard;

class MainWindow : public QWidget {
  Q_OBJECT

  public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

  private slots:
    void onCompleterActivated(QString str);

  private:
    QClipboard* m_clipboard;
    QLineEdit* m_textbox;
    QVBoxLayout *m_layout;
    QButtonGroup* m_list;

    void paintEvent(QPaintEvent* e);
};

#endif // __MAINWINDOW_H__