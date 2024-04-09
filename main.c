#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<stdlib.h>
#include <errno.h>
#include <sys/stat.h>


int give_extenstion(char *name, int filename_size, char **extenstion);
char *concat_strings(const char *str1, const char *str2);

int main(int argc, char *argv[]){
    if(argc < 2){
        printf("Usage:\n\teg: organize /home/username/Downloads/\n\n!! Dont forget to add the / at the end !!\n");
        return 1;
    }
    else if(!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")){
        printf("Usage:\n\teg: organize /home/username/Downloads/\n\n!! Dont forget to add the / at the end !!\n");
        return 1;
    }
    DIR * direcotory;
    struct dirent * entry;
    int count = 0, organize_count = 0;
    char * dir = argv[1];
    char *extenstion, *dir_with_extension, *final_full_path, *file_full_path;
    // const char * dir = "/home/kethankrk/Downloads/";

    
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
            organize_count++;
        }
    }
    free(extenstion);
    free(dir_with_extension);
    free(final_full_path);
    free(file_full_path);
    printf("\nFound a total of %d files\n", count);

    if(organize_count == 0){
        printf("Folder already organized\n");
    }
    else{
        printf("Folder organized successfuly\n");
    }
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