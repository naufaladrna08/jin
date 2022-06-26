#include <Config.h>

string get_config_string(string config_name) {
  string path = get_home_directory();
  string result = "\0";
  FILE* fptr;

  strcat(path, "/");
  strcat(path, CONFIG_NAME);

  fptr = fopen(path, "r");

  if (fptr == NULL) {
    printf("Configuration file is not found\n");
    exit(1);
  }
  char buffer[1024];

  while (fgets(buffer, sizeof(buffer), fptr)) {
    string key = strtok(buffer, " = ");

    if (strcmp(key, config_name) == 0) {
      while (key != NULL) {
        result = key;
        key = strtok(NULL, " = ");
      }
    }
  }

  fclose(fptr);
  return result;
}

int get_config_int(string config_name) { 
  return atoi(get_config_string(config_name));
}