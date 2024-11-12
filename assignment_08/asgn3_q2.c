/*
Question2:
Implement asynchronous execution in your shell i.e. if command suﬃxed with &, then shell should not wait for the child process. Ensure that process isn't
left zombie.
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

//This handler will be called when ctrl+c is pressed
void sigint_handler(){
	printf("--:Ctrl+C no allowed!!\nUse cmd:exit --to terminate.\n");
}

//handler will be called when any child completes its execution and sends SIGCHLD signal
void sigchld_handler(){  
	int s;
	waitpid(-1, &s, 0);
}


int main(){
	char cmd[512], *ptr, *args[32];
	int ret, err, s, i, async;
	
	signal(SIGINT, sigint_handler);
	signal(SIGCHLD, sigchld_handler);

	printf("Welcome to Ash shell!!\n");
	
	while(1){
		async = 0;
		printf("cmd> ");
		gets(cmd);   // get cmd as a string
		
		i = 0;   //get first argument
		ptr = strtok(cmd, " ");
		args[i] = ptr;
		i++;
	
		do{
			ptr = strtok(NULL, " ");
			args[i] = ptr;
			i++;
		}while(ptr != NULL); //do until end of string
	//	printf("i = %d\n", i);

		if(args[0] == NULL)
			continue;

		if(strcmp(args[0], "exit") == 0){  //internal command: exit
			_exit(0);
		}
		else if(strcmp(args[0], "cd") == 0){ //internal command: cd
			chdir(args[1]);
		}
		else{
			if( i>1 && strcmp(args[i-2], "&") == 0){ //asynchronous execution
				args[i-2] = NULL;
				async = 1;
			}

			ret = fork();
			if(ret == 0){
			//	printf("synchronous execution\n");
				err = execvp(args[0], args);  //synchronous execution
				if(err < 0){
					perror("exec() failed!");
					_exit(1);
				}
			}
			else{
				if(!async) {
					pause();
				}
			}
		}
	}
	return 0;
}

