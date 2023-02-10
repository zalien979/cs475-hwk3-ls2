#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "stack.h"
#include "ls2.h"
#include <errno.h>
#include <sys/types.h>



// TODO: function definitions here for ls2
void mode1(char *argv, stack_t* st, int indent){

    DIR *dir;
    struct dirent* entry;
    char test[1000];
    struct stat info;
    char indentStr[10]="";
    //create indent
    for (int i = 0; i < indent; i++){
      strcat(indentStr, "  ");
    }
    //check if directory is openable while opening it
    if ((dir = opendir(argv)) == NULL)
      perror("opendir() error");
    else {
      //check if entry exits
      while ((entry = readdir(dir)) != NULL){
        //make sure entry does not recurse
        if(strcmp(entry->d_name, ".") !=0 && strcmp(entry->d_name, "..") != 0){
          char bufstr[300];
          lstat(entry->d_name, &info);
          //check if entry is directory 
          if(entry->d_type  == DT_DIR) {
            sprintf(bufstr, "%s%s/ (Directory)", indentStr, entry->d_name);
            sprintf(test, "%s/%s", argv, entry->d_name);
            char *tmp = (char*) malloc(sizeof(bufstr));
            strcpy(tmp, strdup(bufstr));
            push(st,tmp);
           mode1(test, st, indent+1);
         }
         //check if entry is file
         else if(S_ISREG(info.st_mode)){
           sprintf(bufstr, "%s%s/ (%ld bytes)", indentStr, entry->d_name, info.st_size);
           char *tmp = (char*) malloc(sizeof(bufstr));
           strcpy(tmp, strdup(bufstr));
           push(st,tmp);
          }
        
        }
    }
    closedir(dir);
  }
}

