#ifndef __JIN_H__
#define __JIN_H__

#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include <fstream>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

QStringList read_files(QString search);

#endif // __JIN_H__