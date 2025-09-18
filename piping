#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int run_first_program(char *program) {
	int exit_status;

	// parent waits for the child until it executes prog1
	pid_t id = fork();

	if (id == 0) {
		// child executes program
		char *args[] = {program, NULL};
		execvp(program, args);
		perror("prog1 fail");
		exit(1);
	} else if (id < 0) {
		printf("fork fail");
		return 1;
	}

	waitpid(id, &exit_status, 0);

	// parent gets the exit code of child process
	exit_status = WEXITSTATUS(exit_status); 

	return exit_status;
}

void write_in_file(char *file, int *pipe2) {
	// 0644  ~  -rw-r--r-- permission...
	int fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	
	if (fd < 0) {
		perror("open");
		exit(1);
	}

	// buf writes 256 bytes each time in file
	char buf[256];
	ssize_t n;
	while ((n = read(pipe2[0], buf, sizeof(buf))) > 0) {
		write(fd, buf, n);
	}

	close(pipe2[0]);
	close(fd);
}



int piping_and_writing_file(char *second_program, char *third_program, char *file) {
	// parent will have two child process. first will run prog2 and will pipe
	// its output to second child which runs third program
	int pipe1[2], pipe2[2];
	if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
		printf("piping fail");
		return 1;
	}

	// first child
	pid_t pid1 = fork();

	if (pid1 == 0) {
		close(pipe1[0]);             
		dup2(pipe1[1], STDOUT_FILENO); 
		close(pipe1[1]);
		
		close(pipe2[0]);
		close(pipe2[1]);
		char *args[] = {second_program, NULL};
		execvp(second_program, args);
		perror("prog2 fail");
		exit(1);
	} else if (pid1 < 0) {
		printf("fork fail");
		return 1;
	} 


	// second child
	pid_t pid2 = fork();
	if (pid2 == 0) {
		close(pipe1[1]);               
		dup2(pipe1[0], STDIN_FILENO);  
		close(pipe1[0]);

		close(pipe2[0]);               
		dup2(pipe2[1], STDOUT_FILENO); 
		close(pipe2[1]);

		char *args[] = {third_program, NULL};
		execvp(third_program, args);
		perror("prog3 fail");
		exit(1);
	} else if (pid2 < 0) {
		printf("fork fail");
		return 1;
	}


	close(pipe1[0]);
	close(pipe1[1]); 
	close(pipe2[1]);              

	write_in_file(file, pipe2);

	int second_program_status, third_program_status;

	// wait for children 
	waitpid(pid1, &second_program_status, 0);
	waitpid(pid2, &third_program_status, 0);

	// get exit codes from children processes
	second_program_status = WEXITSTATUS(second_program_status); 
	third_program_status = WEXITSTATUS(third_program_status); 

	// if one of them failed return error exit code
	if (second_program_status != 0) return second_program_status;
	if (third_program_status != 0) return third_program_status;


	return 0;
}


int main(int argc, char *argv[]) {
	// prog1 -> argv[1]. prog2 -> argv[2]. prog3 -> argv[3]. filepath argv[4]
	if (argc < 5) { 
		printf("There should be 4 arguments!\n");
		return 1;
	}

	// running first program...
	int first_program_status = run_first_program(argv[1]);

	// prog1 executed successfully if its exit code is 0
	if (first_program_status != 0) {
		return first_program_status;
	}

	// run prog2 -> write the output of prog2 as the input of prog3
	// if either of them fails -> stop
	// else write in file
	int writing_file_status = piping_and_writing_file(argv[2], argv[3], argv[4]);
	
	if (writing_file_status != 0) {
		return writing_file_status;
	}

	printf("commands successfuly worked!\n");

	return 0;
}



