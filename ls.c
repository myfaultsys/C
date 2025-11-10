#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char** argv) {
    // open directory stream
    DIR* mydir;
    // entry in drectory
    struct dirent* myfile;
    // stat structure size, permission, timestamps
    struct stat mystat;
    // buffer to store complete path
    char buff[512];
    mydir = opendir(argv[1]);
    if (!mydir) {
        perror(argv[1]);
        return 1;
    }
    while ((myfile = readdir(mydir)) != NULL) {
        // write complete path to buffer
        sprintf(buff, "%s/%s", argv[1], myfile->d_name);
        // store whats in buffer to a stat struct
        stat(buff, &mystat);
        printf("%-5zu  %s\n ", mystat.st_size, myfile->d_name);
    }
    closedir(mydir);
}
