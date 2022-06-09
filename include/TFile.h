/**
 * @file File.h
 * @author Naufal Adriansyah (naufaladrn90@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-09
 * 
 * since FILE struct has been used by standard I/O and i seems to use that 
 * struct, i'll name this as TFILE (Template File). TFILE is used to store 
 * file name in linked list. Why don't i put it on vector instead? Because 
 * i don't want to use C++ for basic stuff. Why dont use array?  don't ask
 * me why, i don't know why.
 * 
 * To use this, we have to declare head first. 
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef TFILE_H
#define TFILE_H
#include <stdlib.h>
#include <stdio.h>
#define nullptr NULL

typedef char* string;
typedef const char* cstring;

struct TFILE {
  string data;
  struct TFILE* next;
};

typedef struct TFILE* tfile_t;

void tfile_append(tfile_t* head, string data);
void tfile_print(tfile_t* head);

#endif