#include <stdio.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    DIR *d;
    struct dirent *f;
    for (int ii = 0; ii < argc; ii++) {
        d = opendir(argv[ii]);
        if (d) {
            while ((f = readdir(d)) != NULL) {
                if (f->d_type == DT_DIR) {
                    printf("%s\n", f->d_name);
                }
            }
            rewinddir(d);
            while ((f = readdir(d)) != NULL) {
                if (f->d_type == DT_REG) {
                    printf("%s\n", f->d_name);
                }
            }
            closedir(d);
        }
    }
    return 0;
}