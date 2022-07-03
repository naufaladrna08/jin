#include <Config.h>

/**
 * @brief Initialize config
 * 
 * we'll put this on main.c, when the program is started.
 * basically it will check if config file is available or
 * not. if yes, then yes. if no, then copy config to jin
 * directory.  
 */
void init_config_and_css() {
  char ch; 
  FILE *src, *dst;

  /* Copy configurations */ 
  std::string dst_path = get_home_directory();
  dst_path += "/";
  dst_path += CONFIG_NAME;

  std::cout << dst_path << std::endl;
  dst = fopen(dst_path.c_str(), "r");

  if (dst == NULL) {
    /* Copy file */
    std::string src_path = "extra/jin.conf";
    src = fopen(src_path.c_str(), "r");

    if (src != NULL) {
      /* Copy src content to dst_path */
      dst = fopen(dst_path.c_str(), "w");

      while ((ch = fgetc(src)) != EOF)
        fputc(ch, dst);
      
      printf("Config file has been created.\n");
      
      fclose(src);
      fclose(dst);
    }
  } else {
    printf("Configuration is found: %s\n", dst_path.c_str());
    fclose(dst);
  }

  /* Copy stylesheet */
  dst_path.clear();
  dst_path = get_home_directory();
  dst_path += "/";
  dst_path += CONFIG_PATH;
  dst_path += DEFAULT_CSS;
  dst = fopen(dst_path.c_str(), "r");
  
  if (dst == NULL) {
    /* Copy file */
    std::string src_path = "extra/default.css";
    src = fopen(src_path.c_str(), "r");

    if (src != NULL) {
      /* Copy src content to dst_path */
      dst = fopen(dst_path.c_str(), "w");

      while ((ch = fgetc(src)) != EOF)
        fputc(ch, dst);
      
      printf("CSS file has been created.\n");
      
      fclose(src);
      fclose(dst);
    }
  } else {
    printf("CSS file is found: %s\n", dst_path.c_str());
    fclose(dst);
  }
}

std::string get_config_string(std::string config_name) {
  std::string result;
  std::string path = get_home_directory();
  
  FILE* fptr;

  path += "/";
  path += CONFIG_NAME;

  fptr = fopen(path.c_str(), "r");

  if (fptr == NULL) {
    printf("Configuration file is not found\n");
    exit(1);
  }
  char buffer[1024];

  while (fgets(buffer, sizeof(buffer), fptr)) {
    string key = strtok(buffer, " = ");

    if (config_name.compare(key) == 0) {
      while (key != NULL) {
        result = key;
        key = strtok(NULL, " = ");
      }
    }
  }

  fclose(fptr);
  return result;
}

int get_config_int(std::string config_name) { 
  return stoi(get_config_string(config_name));
}