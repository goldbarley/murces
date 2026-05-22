#ifndef COMMUNICATE_H
#define COMMUNICATE_H

#include <sys/types.h>

// Starts the orchestrator and returns an array of 3 integers:
// [0] = write_fd
// [1] = read_fd
// [2] = orchestrator_pid
// Returns NULL on failure.
int *init_orchestrator(int mode);

// Searches for mods and returns a null-terminated array of strings.
// The caller must free each string and the array itself.
char **search(const char *modBrowser, const char *query, const char *version,
              const char *modLoader);

// Returns a list of modloaders based on availability.
char **modLoader(const char *version);

// Shuts down the orchestrator and cleans up.
void cleanup_orchestrator();

extern int IOP[3];

#endif // COMMUNICATE_H
