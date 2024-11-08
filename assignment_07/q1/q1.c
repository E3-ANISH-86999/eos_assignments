/*
Input signal number and a process id from user. Send given signal to the given process using kill() syscall.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

int main(int argc, char *argv[]){
	int ret;
	
	int pid = atoi(argv[1]);
	int sig = atoi(argv[2]);

	ret = kill(pid,sig); 
	if(ret == 0){
		printf("Kill cmd successfully executed!\n");
	}
	else{
		printf("Unsuccessful to execute kill\n");
	}



	return 0;
}

