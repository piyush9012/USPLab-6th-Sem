#include <stdio.h>
#include <unistd.h>
#include <limits.h>
int main() {
    // (i) No. of clock ticks
    printf("Maximum number of clock ticks per second: %ld\n", sysconf(_SC_CLK_TCK));

    // (ii) Max. no. of child processes
    printf("Maximum number of child processes: %ld\n", sysconf(_SC_CHILD_MAX));

    // (iii) Max. path length
    printf("Maximum path length: %ld\n", pathconf("/", _PC_PATH_MAX));

    // (iv) Max. no. of characters in a file name
    printf("Maximum number of characters in a file name: %ld\n", pathconf("/", _PC_NAME_MAX));

    // (v) Max. no. of open files per process
    printf("Maximum number of open files per process: %ld\n", sysconf(_SC_OPEN_MAX));

    // Retrieve system's page size
    printf("System's page size: %ld bytes\n", sysconf(_SC_PAGESIZE));

    // Retrieve system's hostname
    char hostname[HOST_NAME_MAX];
    if (gethostname(hostname, HOST_NAME_MAX) == 0) {
        printf("System hostname: %s\n", hostname);
    }
    else {
        perror("gethostname");
    }

    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working directory: %s\n", cwd);
    }
    else {
        perror("getcwd");
    }
    return 0;
}