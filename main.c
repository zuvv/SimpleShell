//Ted Protasiewicz
//Simple Shell

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_LIMIT 1024

int main(void) { 


//Input
char str[MAX_LIMIT]; 

while(1){

  //input
  printf("\nEnter a command or type quit to exit: ");
  fgets(str, MAX_LIMIT, stdin); 
  printf("%s", str); 

  if(strcmp(str,"quit\n")==0){
    exit(0);
  }



  /* Remove trailing newline, if there. FGETS creates trailling new line */
  if ((strlen(str) > 0) && (str[strlen (str) - 1] == '\n'))
     str[strlen (str) - 1] = '\0';


  //String token part
  char * pch;
  pch = strtok (str," ");
  //array of string pointers, which point to strings
  char *strs[100];
  int stringCount = 0;

  while (pch != NULL)
  {
    strs[stringCount] = pch;
    pch = strtok (NULL, " ");
    stringCount += 1;
  }

  //last value must be NULL for executing
  strs[stringCount] = NULL;

  //gets current working directory
  char cwd[500];
  getcwd(cwd, sizeof(cwd));
  printf("\nCurrent working directory is: %s\n", cwd);

  //this is for change directory
  if(strcmp(strs[0], "cd") == 0){

    char* path = (char*)malloc(strlen(strs[0]) + 2);
    strcat(path, "./");
    strcat(path, strs[1]);

    if(chdir(path) != 0){
      printf("no directory path\n");
    }else{
      getcwd(cwd, sizeof(cwd));
      printf("%s: ", cwd);
    }
  }else{
  //execute with child process
  pid_t pid = fork();
    int status;     
    if ( pid >= 0 ) {
      if(pid == 0){
        int error = execvp(strs[0],strs);
        if (error<0){
          printf("not a valid command\n");
          if(strcmp(str,"quit")){
            exit(0);
          }
        }
      }else if(pid > 0){
        wait(&status);
      }
    }else{
      printf("Bad fork");
      exit(1);
    }
  }
}
  return 0;
}


