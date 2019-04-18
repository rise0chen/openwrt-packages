#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char** argv) {
  int ret, i, status;
  char* child_argv[8] = {0};
  pid_t pid;

  if (argc < 2) {
    fprintf(stderr, "Usage: %s <exe_path> <args...>\n", argv[0]);
    return -1;
  }
  for (i = 1; i < argc; ++i) {
    int argLen = strlen(argv[i]);
    child_argv[i - 1] = (char*)malloc(argLen + 1);
    strncpy(child_argv[i - 1], argv[i], argLen);
    child_argv[i - 1][argLen] = '\0';
  }
  while (1) {
    pid = fork();
    if (pid == -1) {
      perror("fork.");
      break;
    }
    if (pid == 0) {
      ret = execv(child_argv[0], (char**)child_argv);
      if (ret < 0) {
        perror("execv.");
        continue;
      }

      fprintf(stdout, "normal exit.");
      exit(0);
    }

    if (pid > 0) {
      pid = wait(&status);
      fprintf(stdout, "wait return.");
    }
  }

  return 0;
}
