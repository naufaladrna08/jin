#include <Utils.h>
tfile_t root = nullptr;

cstring get_template_directory() {
  /* Getting home directory */
  struct passwd* pw = getpwuid(getuid());;
  char* HOME = pw->pw_dir;

  /* Concat HOME with templates folder */
  strcat(HOME, "/.jin-templates/");

  return (cstring) HOME;
}

void ls_home() {
  cstring HOME = get_template_directory();

  /* Read! */
  DIR* d;
  struct dirent* dir;
  d = opendir(HOME);

  if (d) {
    while ((dir = readdir(d)) != NULL) {
      tfile_append(&root, dir->d_name);
    }

    closedir(d);
  }
}

cstring open(char* name) {
  char* HOME = (char*) get_template_directory();
  strcat(HOME, name);
  strcat(HOME, ".tmpl");

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

void create_template(string title, string content) {
  string PATH = (string) get_template_directory();
  strcat(PATH, title);
  
  FILE *fptr;
  fptr = fopen(PATH, "w");
  fputs(content, fptr);

  fclose(fptr);
}