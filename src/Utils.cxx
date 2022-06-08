#include <Utils.h>

void test() {
  std::cout << "test" << std::endl;
}

std::vector<cstring> ls_home() {
  std::vector<cstring> vec;

  /* Getting home directory */
  struct passwd* pw = getpwuid(getuid());;
  char* HOME = pw->pw_dir;

  /* Concat HOME with templates folder */
  strcat(HOME, "/.jin-templates");

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

cstring open(const char* name) {
  cstring tmp;
  
  return tmp;
}