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

  m_list = new QButtonGroup;

  /* Layout */
  m_layout = new QVBoxLayout;
  QHBoxLayout *row = new QHBoxLayout;
  QVBoxLayout *col = new QVBoxLayout;

  col->addWidget(m_textbox);
  row->addItem(col);

  m_layout->addLayout(row);

  setLayout(m_layout);

  QString search = m_textbox->text();
  QStringList lists =  read_files(search);
  qDebug() << "\n" << lists << "\n";

  QCompleter *m_completer = new QCompleter(lists, this);
  m_completer->setCaseSensitivity(Qt::CaseInsensitive);
  m_textbox->setCompleter(m_completer);

  connect(m_completer, SIGNAL(activated(QString)), this, SLOT(onCompleterActivated(QString)));
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

void MainWindow::onCompleterActivated(QString str) {
  /* 1. Load file, open. */
  QString text = open_file(str);

  /* 2. Send to clipboard */
  QClipboard* clipboard = QApplication::clipboard();
  clipboard->setText(text);

  /* 3. Close window */
  // QApplication::quit();
}