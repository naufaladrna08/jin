#include <Utils.h>

/*
 * i dont know how to this properly, but it seems to work.
 * root is meant to be root of all files and result is all
 * files to be displayed in the completion.
 */
tfile_t root = nullptr;
tfile_t result = nullptr;

cstring get_home_directory() {
  cstring homedir = (string) malloc(256);

  if ((homedir = getenv("HOME")) == NULL) {
    homedir = getpwuid(getuid())->pw_dir;
  }

  return homedir;
}

cstring get_template_directory() {
  /* Getting home directory */
  string PATH = (string) malloc(strlen(get_home_directory()) + 1024); 
  strncpy(PATH, get_home_directory(), strlen(get_home_directory()) + 1);

  /* Concat HOME with templates folder */
  strcat(PATH, "/.jin-templates/");

  return (cstring) PATH;
}

std::vector<std::string> ls_home() {
  cstring PATH = get_template_directory();
  std::vector<std::string> files;

  /* Read! */
  DIR* d;
  struct dirent* dir;
  d = opendir(PATH);

  if (d) {
    while ((dir = readdir(d)) != NULL) {
      if (dir->d_name[0] != '.')
        files.push_back(dir->d_name);
    }

    closedir(d);
  } else {
    printf("Failed to load templates: %s\n", PATH);
    exit(1);
  }

  return files;
}

cstring open(std::string name) {
  std::string PATH = get_template_directory();
  PATH += name;
  PATH += ".tmpl";

  FILE    *textfile;
  char    *text;
  long    numbytes;
    
  textfile = fopen(PATH.c_str(), "r");

  if (textfile == NULL) {
    printf("File not found\n");
    return NULL;
  }

  fseek(textfile, 0L, SEEK_END);
  numbytes = ftell(textfile);
  fseek(textfile, 0L, SEEK_SET);  

  text = (char*) calloc(numbytes, sizeof(char));   
  
  if (text == NULL) {
    printf("Empty template selected\n");
    return NULL;
  }

  fread(text, sizeof(char), numbytes, textfile);
  fclose(textfile);

  return text;
}

void create_template(string title, string content) {
  string PATH = (string) get_template_directory();
  strcat(PATH, title);
  strcat(PATH, ".tmpl");

  FILE *fptr;
  fptr = fopen(PATH, "w+");
  fprintf(fptr, "%s\n", content);

  fclose(fptr);
}

string get_text_of_textview(GtkTextView* text_view) {
  GtkTextIter start, end;
  GtkTextBuffer *buffer = gtk_text_view_get_buffer((GtkTextView*) text_view);
  gchar *text;
  gtk_text_buffer_get_bounds(buffer, &start, &end);
  text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);

  return text;
}