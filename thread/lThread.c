#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <linux/sched.h>

#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)
#define STACK_SIZE (1024 * 1024) /* Stack size for cloned child */

static int childFunc(void *arg){ /* Start function for cloned child */
  struct utsname uts;
/* Change hostname in UTS namespace of child */
  if (sethostname(arg, strlen(arg)) == -1)
    errExit("sethostname");
/* Retrieve and display hostname */
  if (uname(&uts) == -1)
    errExit("uname");
  printf("uts.nodename in child: %s\n", uts.nodename);

  sleep(200);
  return 0; /* Child terminates now */
}

int main(int argc, char *argv[]){
  char *stack; /* Start of stack buffer */
  char *stackTop; /* End of stack buffer */
  pid_t pid;
  struct utsname uts;

  if (argc < 2) {
    fprintf(stderr, "Usage: %s <child-hostname>\n", argv[0]);
    exit(EXIT_SUCCESS);
  }

  stack = malloc(STACK_SIZE); /* Allocate stack for child */

  if (stack == NULL)
    errExit("malloc");

  stackTop = stack + STACK_SIZE;
  pid = clone(childFunc, stackTop, CLONE_NEWUTS | SIGCHLD, argv[1]);

  if (pid == -1)
    errExit("clone");
  printf("clone() returned %ld\n", (long) pid);

  /* Parent falls through to here */
  sleep(1); /* Give child time to change its hostname */

  if (uname(&uts) == -1)
    errExit("uname");
  printf("uts.nodename in parent: %s\n", uts.nodename);

  if (waitpid(pid, NULL, 0) == -1) /* Wait for child */
    errExit("waitpid");
  printf("child has terminated\n");

  exit(EXIT_SUCCESS);
}
