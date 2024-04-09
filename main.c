#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<stdlib.h>
#include <errno.h>
#include <sys/stat.h>


int give_extenstion(char *name, int filename_size, char **extenstion);
char *concat_strings(const char *str1, const char *str2);

int main(){
    DIR * direcotory;
    struct dirent * entry;
    int count = 0;
    const char * dir = "/home/kethankrk/Downloads/";
    char *extenstion, *dir_with_extension, *final_full_path, *file_full_path;
    direcotory = opendir(dir);

    if(direcotory == NULL){
        perror("Unable to open direcotry!\n");
        exit(EXIT_FAILURE);
    }

    printf("Files in the direcotry: \n\n");

    while((entry = readdir(direcotory)) != NULL){
        if(entry->d_name[0] != '.'){
            int filename_size = strlen(entry->d_name);
            count++;
            if(!give_extenstion(entry->d_name, filename_size, &extenstion)) continue;
            dir_with_extension = concat_strings(dir, extenstion);
            int status = mkdir(dir_with_extension, 0777);
            if(status && errno != EEXIST){
                printf("Failed to create dir: %s\n", extenstion);
                perror("mkdir");
                continue;
            }
            final_full_path = concat_strings(dir_with_extension, entry->d_name);
            file_full_path = concat_strings(dir, entry->d_name);
            rename(file_full_path, final_full_path);
            printf("Successfuly moved the file: %s to dir: %s\n\n\n", file_full_path, final_full_path);
        }
    }
    free(extenstion);
    free(dir_with_extension);
    free(final_full_path);
    free(file_full_path);
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

    *extenstion = (char *)malloc(extenstion_size * sizeof(char) + 2);

    char * start = name + index_of_dot;
    memcpy(*extenstion, start, extenstion_size + 1);
    *extenstion = concat_strings(*extenstion, "/");
    return 1;
}




#include <stdlib.h>
#include <string.h>

char *concat_strings(const char *str1, const char *str2) {

    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    char *result = (char *)malloc(len1 + len2 + 1); 
    if (result == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    strcpy(result, str1);
    strcat(result, str2);
    return result;
}