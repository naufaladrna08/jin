#include "Jin.h"

/**
 * @brief Reading files
 * 
 * This function is to read all template files inside ./jin-templates 
 * on $HOME directory. We'll be using the data an show it while 
 * we search something on the textbox window.
 * 
 * @return int 
 */
QStringList read_files(QString search) {
  QStringList lists;

  /* Getting home directory */
  struct passwd* pw = getpwuid(getuid());
  char* HOME = pw->pw_dir;

  /* Concat $HOME with templates folder */
  strcat(HOME, "/.jin-templates");

  /* Read. */
  QDir dir(HOME);
  QStringList templates = dir.entryList(QStringList() << "*.templ" ,QDir::Files);
  
  if (search.length() > 0) {
    QDirIterator it(dir, QDirIterator::Subdirectories);

    while (it.hasNext()) {
      QString filename = it.next();
      QFileInfo file(filename);

      if (file.fileName().contains(search, Qt::CaseInsensitive)) {
        lists.append(file.fileName());
      }
    }
  } else {
    foreach (QString filename, templates) {
      lists.append(filename);
    }
  }

  return lists;
}

QString open_file(QString name) {
  QString content;

  /* Getting home directory */
  struct passwd* pw = getpwuid(getuid());
  char* HOME = pw->pw_dir;
  strcat(HOME, "/.jin-templates/");

  QString path = QString::fromLocal8Bit(HOME);
  path.append(name);

  /* Read. */
  QFile file(path);
  file.open(QIODevice::ReadOnly);

  if (file.exists()) {
    QTextStream in(&file);

    QString line;
    while (!in.atEnd()) {
      line = in.readLine();
      content.append(line);
    }
  } else {
    return QString("File not found");
  } 

  file.close();
  return content;
}