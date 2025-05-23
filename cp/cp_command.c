#include<stdio.h>
#include<stdlib.h>  // Needed for exit().
#include<fcntl.h>   // This includes file manipulation system calls.
#include<errno.h>   // Includes errno which is used in error handling.
#include<string.h>
#include<sys/types.h>   // Include standard data types. 
#include<unistd.h>  // read() is declared here.
#include<sys/stat.h>    // Defines mode_t permission constants


// Declare function prototype
void copy_file(int, int);


int main(int argc, char *argv[]){

    /*
    Check to see if the number of arguments passed to the program is 
    correct.
    */
    if (argc != 3){
        printf("Bad arguments. Use cp_command source_file destination_file.\n");
        exit(EXIT_FAILURE);
    }
        

    // Declare variables for the open() call to read
    char *source_file = argv[1];
    int file_descriptor_read;
    int open_r_flags = O_RDONLY;
    
    // variables required for the open() call to write
    char *destination_file = argv[2];
    int open_w_flags = O_WRONLY | O_TRUNC | O_APPEND | O_CREAT;
    mode_t w_permissions = S_IRWXU | S_IRWXG;
    int file_descriptor_write;


    // Open the file specified by the input to read from.
    file_descriptor_read = open(source_file, open_r_flags);

    // open() failed. 
    if(file_descriptor_read == -1){
        printf("DEBUG: Open to read Failed.\n");
        perror(strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Open the file specified by the input to write to. 
    file_descriptor_write = open(destination_file, open_w_flags, 
                                    w_permissions);

    // Second open() failed.
    if (file_descriptor_write == -1){
        printf("DEBUG: Open to write Failed.\n");
        perror(strerror(errno));
        exit(EXIT_FAILURE);
    }

    
    // Copy content of source to destination
    copy_file(file_descriptor_read, file_descriptor_write);
    

    return 0;
}


void copy_file(int fd_source, int fd_destination){
    
    // variables required for the read() call
    size_t count = 1024;
    void *data_read = malloc(count + 1);
    ssize_t bytes_read = 0;    
    ssize_t bytes_wrote = 0;
    
    do {
        bytes_read = read(fd_source, data_read, count);
        
        // Error checking for read()
        if (bytes_read == -1){
            printf("DEBUG: read() failed in copy_file().\n");
            perror(strerror(errno));
            exit(EXIT_FAILURE);
        }

        bytes_wrote = write(fd_destination, data_read, bytes_read);

        // Error checking for write()
        if (bytes_wrote == -1){
            printf("DEBUG: write() failed in copy_file().\n");
            perror(strerror(errno));
            exit(EXIT_FAILURE);
        }

    } while (bytes_read > 0);

    
    free(data_read);
}