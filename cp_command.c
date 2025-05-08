#include<stdio.h>
#include<stdlib.h> // Needed for exit()
#include<fcntl.h> // This includes file manipulation system calls
#include<errno.h>
#include<string.h>


int main(int argc, char *argv[]){

    /*
    Check to see if the number of arguments passed to the program is 
    correct.
    */
    if (argc != 3){
        printf("Bad arguments. Use cp_command source_file destination_file\n");
        exit(EXIT_FAILURE);
    }

    else{
        
        // Declare variables
        char *source_file = argv[1];
        char *destination_file = argv[2];
        int file_descriptor_open;
        int open_flags = O_RDONLY;

        file_descriptor_open = open(source_file, open_flags);
        
        // open() failed. 
        if(file_descriptor_open == -1){
            perror(strerror(errno));
            exit(EXIT_FAILURE);
        }
        else{
            printf("If not taken, opened without errors.");

        }
        
    }
}
