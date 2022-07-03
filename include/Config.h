#ifndef CONFIG_H
#define CONFIG_H
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <Common.h>
#include <Utils.h>

void init_config_and_css();
std::string get_config_string(std::string config_name);
int get_config_int(std::string config_name);

#endif