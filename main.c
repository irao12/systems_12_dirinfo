// Ivan Rao
// Systems HW12

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>

int main(){
  DIR * d;
  d = opendir("./");
  struct dirent * entry;
  entry = readdir(d);

  printf("Statistics for directory: %s\n", entry->d_name);
  unsigned int size = 0;

  while (entry){
    if (entry->d_type == DT_REG){
      struct stat file;
      stat(entry->d_name, &file);
      size += file.st_size;
    }
    entry = readdir(d);
  }
  printf("Total directory size: %u bytes\n", size);

  rewinddir(d);
  entry = readdir(d);
  printf("Directories:\n");
  while (entry) {
    if (entry->d_type == DT_DIR){
      printf("\t%s\n", entry->d_name);
    }
    entry = readdir(d);
  }

  rewinddir(d);
  entry = readdir(d);
  printf("Regular Files:\n");
  while (entry){
    if (entry->d_type == DT_REG){
      printf("\t%s\n", entry->d_name);
    }
    entry = readdir(d);
  }

  closedir(d);
  return 0;
}
