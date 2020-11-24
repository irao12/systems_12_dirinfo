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
  char *path;

  if (argc > 1){
	path = argv[1];
  }
  else {
	int found = 1;
	char buffer[100];
	while (found){
		printf("Enter a directory to scan: ");
		fgets(buffer, sizeof(buffer), stdin);
		path = buffer;
		d = opendir(path);
		if (!d) found = 0;
  	}
  }

  d =  opendir(path);
  if (!d) {
    printf("%s", strerror(errno));
    return 0;
  }
  
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
