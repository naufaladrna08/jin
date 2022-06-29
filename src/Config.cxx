#include <Config.h>

/**
 * @brief Initialize config
 * 
 * we'll put this on main.c, when the program is started.
 * basically it will check if config file is available or
 * not. if yes, then yes. if no, then copy config to jin
 * directory.  
 */
void init_config() {
  char ch; 
  FILE *src, *dst;

  string dst_path = (string) malloc(strlen(get_home_directory()) + 1024); 
  strncpy(dst_path, get_home_directory(), strlen(get_home_directory()) + 1);
  strcat(dst_path, "/");
  strcat(dst_path, CONFIG_NAME);
  dst = fopen(dst_path, "r");

  if (dst == NULL) {
    /* Copy file */
    string src_path = "extra/jin.conf";
    src = fopen(src_path, "r");

    if (src != NULL) {
      /* Copy src content to dst_path */
      dst = fopen(dst_path, "w");

      while ((ch = fgetc(src)) != EOF)
        fputc(ch, dst);
      
      printf("Config file has been created.\n");
      
      fclose(src);
      fclose(dst);
    }
  } else {
    printf("Configuration is found: %s\n", dst_path);
    fclose(dst);
  }

  free(dst_path);
}

string get_config_string(string config_name) {
  // string path = (string) get_home_directory
  string path = (string) malloc(strlen(get_home_directory()) + 1024); 
  strncpy(path, get_home_directory(), strlen(get_home_directory()) + 1);
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
  free(path);
  return result;
}

int get_config_int(string config_name) { 
  return atoi(get_config_string(config_name));
}