// Author: Madison J. Anderson
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    printf("Executing %s ...\n\n", argv[0]);

    if (argc >= 2) {
        FILE *file;
        for (int ii = 1; ii < argc; ii++) {
            file = fopen(argv[ii], "r");
            if (file == NULL) {
                printf("Error: File %s not found\n", argv[ii]);
            } else {
                printf("File %s opened\n", argv[ii]);
                fseek(file, 0, SEEK_END);
                long file_size = ftell(file);
                printf("File size is %ld bytes\n\n", file_size);
                fseek(file, 0, SEEK_SET);

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
    }
    return 0;
}