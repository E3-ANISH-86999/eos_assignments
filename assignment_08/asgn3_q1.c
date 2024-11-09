/*
Question1:
Improve your shell program so that it should not be terminated due to SIGINT (ctrl+C).
*/


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>


// this handler will be executed when ctrl+c is pressed
void signal_handler(){
	printf("Ctrl+C no allowed!!\nUse cmd:exit to terminate.\n");
}

int main(){
	char cmd[512], *ptr, *args[32];
	int ret, err, s;
	
	signal(SIGINT, signal_handler);


	printf("Welcome to Ash shell!!\n");
	
	while(1){
		printf("cmd>");
		gets(cmd);  // getting string 
		
		int i = 0;
		ptr = strtok(cmd, " "); // breaking string in each word(token creation)
		args[i] = ptr;
		i++;
	
		do{
			ptr = strtok(NULL, " ");
			args[i] = ptr;
			i++;
		}while(ptr != NULL);  //creating tokens until null (end of string)
		
		if(strcmp(args[0], "exit") == 0) // internal cmd: exit
			_exit(0);
		else if(strcmp(args[0], "cd") == 0) // internal cmd: cd
			chdir(args[1]);
		else{
			ret = fork();  //external cmd execution
			if(ret == 0){
				err = execvp(args[0], args);
				if(err < 0){
					perror("exec() failed!");
					_exit(1);
				}
			}
			else{
				waitpid(ret, &s, 0);  // waiting for execution of child to complete(synchronous excn)
			}
		}
	}
	return 0;
}


