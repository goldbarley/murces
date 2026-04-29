#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **getMods() {
  struct dirent *file;
  DIR *mods = opendir("./mods");
  if (mods == NULL) {
    perror("Mods folder not found:");
    return NULL;
  }

  char **files = malloc(256 * sizeof(char *));
  if (!files)
    return NULL;
  int multi = 1;
  int total = 1;
  while ((file = readdir(mods))) {

    if (total > multi * 256)
      files = realloc(files, 256 * (multi++) * sizeof(char *));
    if (!files)
      return NULL;

    files[(total++ - 1)] = strdup(file->d_name);
  }

  return files;
}
