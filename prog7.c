#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
	int pipefd[2];
	if (pipe(pipefd) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid_t pid = fork();
	if (pid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0) { 
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		execlp("ls", "ls", "-l", NULL);
		perror("execlp ls");
		exit(EXIT_FAILURE);
	}
	else { 
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		execlp("wc", "wc", "-l", NULL);
		perror("execlp wc");
		exit(EXIT_FAILURE);
	}
	return 0;
}

/*

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#define FIFO_FILE "/tmp/myfifo"

int main() 
{
	char buf[256];
	int fd;
	mkfifo(FIFO_FILE, 0666);
	if (fork() != 0) {
		fd = open(FIFO_FILE, O_WRONLY);
		write(fd, "Hello from parent!", sizeof("Hello from parent!"));
		close(fd);
	}
	else {
		fd = open(FIFO_FILE, O_RDONLY);
		read(fd, buf, sizeof(buf));
		printf("Child received: %s\n", buf);
		close(fd);
	}
	return 0;
}

*/