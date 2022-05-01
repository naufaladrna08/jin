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