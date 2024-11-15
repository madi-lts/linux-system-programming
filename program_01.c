// Author: Madison J. Anderson
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <getopt.h>

int main(int argc, char *argv[]) {
    int opt;
    FILE *file;
    printf("Executing %s ...\n\n", argv[0]);

    // Note: getopt()'s third argument defines the valid options and whether they require an argument or not. 
    // A colon (:) after the option indicates that the option requires an argument.
    while ((opt = getopt(argc, argv, "abc")) != -1) {
        if (opt == -1) {
            break;
        }

        switch (opt) {
            case 'a':
                printf("Option 'a' selected\n");
                break;
            case 'b':
                printf("Option 'b' selected\n");
                break;
            case 'c':
                printf("Option 'c' selected\n");
                break;
            default:
                printf("Unknown option %c\n", opt);
                break;
        }; 
    }

    for (int ii = optind; ii < argc; ii++) {
        file = fopen(argv[ii], "r");

        if (file == NULL) {
            printf("Error: File %s not found\n", argv[ii]);
        } else {
            printf("File %s opened\n", argv[ii]);

            // Get the file size:
            fseek(file, 0, SEEK_END);
            long file_size = ftell(file);
            printf("File size is %ld bytes\n", file_size);
            fseek(file, 0, SEEK_SET);

            // Allocate a buffer to store the file contents:
            char *buffer = (char *)malloc(file_size + 1);
            if (buffer == NULL) {
                perror("Error allocating memory");
                fclose(file);
                return 1;
            }

            fread(buffer, 1, file_size, file);
            buffer[file_size] = '\0';

            printf("Contents of %s:\n\n%s\n\n", argv[ii], buffer);

            free(buffer);
            fclose(file);
        }
    }
    
    return 0;
}