#include <Utils.h>

cstring get_template_directory() {
  /* Getting home directory */
  struct passwd* pw = getpwuid(getuid());;
  char* HOME = pw->pw_dir;

  /* Concat HOME with templates folder */
  strcat(HOME, "/.jin-templates/");

  return (cstring) HOME;
}

std::vector<cstring> ls_home() {
  std::vector<cstring> vec;

  cstring HOME = get_template_directory();

  /* Read! */
  DIR* d;
  struct dirent* dir;
  d = opendir(HOME);

  if (d) {
    while ((dir = readdir(d)) != NULL) {
      vec.push_back(dir->d_name);
    }

    closedir(d);
  }

  return vec;
}

cstring open(char* name) {
  char* HOME = (char*) get_template_directory();
  strcat(HOME, name);

  FILE    *textfile;
  char    *text;
  long    numbytes;
    
  textfile = fopen(HOME, "r");
  if(textfile == NULL)
    exit(1);
    
  fseek(textfile, 0L, SEEK_END);
  numbytes = ftell(textfile);
  fseek(textfile, 0L, SEEK_SET);  

  text = (char*) calloc(numbytes, sizeof(char));   
  
  if (text == NULL)
    exit(1);

  fread(text, sizeof(char), numbytes, textfile);
  fclose(textfile);

  return text;
}