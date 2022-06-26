#ifndef CONFIG_H
#define CONFIG_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <Common.h>
#include <Utils.h>

typedef char* string;
typedef const char* cstring;

void init_config();
string get_config_string(string config_name);
int get_config_int(string config_name);

#endif