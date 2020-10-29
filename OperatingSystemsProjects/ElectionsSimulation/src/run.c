/****** run.c ******/
#include "run.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printError() { // write once the usage error message
  fprintf(stderr,
          "Usage:\n./runelection -i inputfile -o outfile (-n numofupdates)\n");
}

CmdParams run(int argc, char **argv) {
  CmdParams args;
  for (int i = 0; i < 3; i++)
    args.params[i] = NULL;

  if (argc != 7 &&
      argc != 5) { // 3 flags with their 6 parameters plus the programme name
                   // (maybe the numofupdates is missing)
    printError();
    args.rightUsage = 0;
    return args; // returns False for wrong use
  } else {       // checks whether there are all needed parameters on program
           // execution
    char *validParams[] = {"-i", "-o", "-n"};
    int flag = 0;
    int foundParams = 0;
    for (int i = 1; i < argc;
         i += 2) { // by incrementing by 2, I ensure that there are arguments
                   // after the options required
      for (int j = 0; j < 3; j++) {
        if (!(strcmp(argv[i], validParams[j]))) {
          foundParams++;
          if (!(strcmp(argv[i], "-i"))) {
            args.params[0] = malloc(sizeof(char) * (1 + strlen(argv[i + 1])));
            strcpy(args.params[0], argv[i + 1]);
          } else if (!(strcmp(argv[i], "-o"))) {
            args.params[1] = malloc(sizeof(char) * (1 + strlen(argv[i + 1])));
            strcpy(args.params[1], argv[i + 1]);
          } else if (!(strcmp(argv[i], "-n"))) {
            args.params[2] = malloc(sizeof(char) * (1 + strlen(argv[i + 1])));
            strcpy(args.params[2], argv[i + 1]);
          }
          flag = 1;
          break;
        }
      }
      if (flag == 0) { // argument found is invalid
        printError();
        args.rightUsage = 0;
        freeCmdParams(&args);
        return args;
      } else // check next argument
        flag = 0;
    }
    if (foundParams != 3 && foundParams != 2) { // fewer arguments than required
      printError();
      args.rightUsage = 0;
      freeCmdParams(&args);
      return args;
    } else if (foundParams == 2 && args.params[2] == NULL) {
      args.params[2] = malloc(sizeof(char) * 2);
      strcpy(args.params[2], "5");
    } else if (foundParams == 2 && args.params[2] != NULL) {
      printError();
      args.rightUsage = 0;
      freeCmdParams(&args);
      return args;
    }

    args.rightUsage = 1;
    return args; // no errors found
  }
}

void freeCmdParams(CmdParams *arguments) { // free any allocated memory
  for (int i = 0; i < 3; i++)
    free(arguments->params[i]);
}