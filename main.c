#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<stdlib.h>
#include"list.h"
#include <errno.h>


int give_extenstion(char *name, int filename_size, char **extenstion);

int main(){
    DIR * direcotory;
    struct dirent * entry;
    int count = 0;
    node *head = NULL;
    direcotory = opendir("/home/kethankrk/Downloads");

    if(direcotory == NULL){
        perror("Unable to open direcotry!\n");
        exit(EXIT_FAILURE);
    }

    printf("Files in the direcotry: \n\n");

    while((entry = readdir(direcotory)) != NULL){
        if(entry->d_name[0] != '.'){
            int filename_size = strlen(entry->d_name);
            char *extenstion;
            count++;
            if(!give_extenstion(entry->d_name, filename_size, &extenstion)) continue;
            int status = mkdir(extenstion, 0777);
            if(status || errno != EEXIST){
                printf("Failed to create directory.\n");
                perror("mkdir");
                return EXIT_FAILURE;
            }
            
        }
    }
    printf("\nFound a total of %d files\n", count);
    closedir(direcotory);
    return 0;
}

int give_extenstion(char *name, int filename_size, char **extenstion){

    int index_of_dot = 0, extenstion_size = 0;

    for(int i = 0; i < filename_size; i++){
        if(name[i] == '.'){
            index_of_dot = i + 1;
        }
    }

    extenstion_size = index_of_dot != 0 ? (filename_size - 1) - index_of_dot : 0;
    if(!extenstion_size) return 0;

    *extenstion = (char *)malloc(extenstion_size * sizeof(char) + 1);

    char * start = name + index_of_dot;
    memcpy(*extenstion, start, extenstion_size + 1);
    return 1;
}