#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	int pidarr[3];
	int sarr[3];
	
	pidarr[0] = fork();
	if(pidarr[0] == 0){
		pidarr[1] = fork();
		if(pidarr[1] == 0){
			pidarr[2] = fork();
			if(pidarr[2] == 0){
				for(int j=1; j<=5; j++){
					printf("Child3: %d\n", j);
					sleep(1);
				}
				_exit(3);
			}
			else{
				for(int j=1; j<=5; j++){
					printf("Child2: %d\n", j);
					sleep(1);
				}
				waitpid(pidarr[2], &sarr[2], 0);
				printf("Child3 exit status: %d\n", WEXITSTATUS(sarr[2]));
				_exit(2);
			}
		}
		else{
			for(int j=1; j<=5; j++){
				printf("Child1: %d\n", j);
				sleep(1);
			}
			waitpid(pidarr[1], &sarr[1], 0); 
			printf("Child2 exit status: %d\n", WEXITSTATUS(sarr[1]));
			_exit(1);
		}
	}
	else{
		for(int j=1; j<=5; j++){
			printf("Parent: %d\n",j);
			sleep(1);
		}
		waitpid(pidarr[0], &sarr[0], 0); 
		printf("Child1 exit status: %d\n", WEXITSTATUS(sarr[0]));
	}

	return 0;
}



