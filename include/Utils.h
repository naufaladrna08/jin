/**
 * @file Utils.hpp
 * @author Naufal Adriansyah (naufaladrn90@gmail.com)
 * @brief Jin Utilities.
 * @version 0.1
 * @date 2022-06-08
 * 
 * File ini berisi fungsi-fungsi bahasa C untuk mencari file,
 * membuka file dan lain-lain. 
 * 
 * NOTE AND TODO:
 * Untuk saat ini, Jin hanya membaca file-file dalam sistem
 * operasi berbasis Linux. Kedepannya, diharapkan Jin dapat
 * membaca untuk sistem operasi lain, tepatnya Windows :|
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef UTILS_H
#define UTILS_H

#include <dirent.h>
#include <vector>

#include <iostream>
#include <fstream>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <TFile.h>

#include <gtk/gtk.h>

typedef const char* cstring;

cstring get_template_directory();
void ls_home();
cstring open(char* name);
void create_template(string title, string content);
string get_text_of_textview(GtkTextView* text_view);

#endif