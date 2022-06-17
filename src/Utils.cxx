#include <Utils.h>

/*
 * i dont know how to this properly, but it seems to work.
 * root is meant to be root of all files and result is all
 * files to be displayed in the completion.
 */
tfile_t root = nullptr;
tfile_t result = nullptr;

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