#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {

  int orcInput[2];
  int orcOutput[2];
  pid_t pid;

  /*
   *  Basically  I am creating two pipes. This array stores id to identify the
   * pipe 1 index is alwaays the write end of the pipe and 0 index is always the
   * read end.*/
  if (pipe(orcInput) == -1 || pipe(orcOutput) == -1) {
    perror("Pipe failed");
    return 1;
  }

  pid = fork();

  if (pid == 0) {
    // dup2 is the in built redirect function, Using it to redirect the streams,
    // Rest is self explanatory I think.
    dup2(orcInput[0], STDIN_FILENO);
    dup2(orcOutput[1], STDOUT_FILENO);
    execlp("./murces-orchestrator", "./murces-orchestrator", NULL);
  } else {
    //
    //  //Closing the ends you wont use.
    close(orcInput[0]);
    close(orcOutput[1]);

    /*Your code here, close the ends after using them k?*/
  }

  return 0;
}
