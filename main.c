// Ivan Rao
// Systems HW12

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

int main(int argc, char**argv){
  DIR * d;
  char path[100];

  if (argc > 1){
	  strncpy(path, argv[1], sizeof(path)-1);
  }
  else {
		printf("Enter a directory to scan: ");
		fgets(path, sizeof(path), stdin);
  }
  int len = strlen(path);

  if (path[len-1] == '\n'){
    path[len-1] = '\0';
  }

  d =  opendir(path);
  if (!d) {
    printf("%d: %s\n", errno, strerror(errno));
    return 0;
  }

  struct dirent * entry;
  entry = readdir(d);

  printf("Statistics for directory: %s\n", path);
  unsigned int size = 0;

  while (entry){
    if (entry->d_type == DT_REG){
      struct stat file;
      stat(entry->d_name, &file);
      printf("%s", entry->d_name);
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
