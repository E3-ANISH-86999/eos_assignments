#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
	int pidarr[5];
	int s;

	for(int i=0; i<5; i++){
		pidarr[i] = fork();
		if(pidarr[i] == 0){
			for(int j=1; j<=5; j++){
				printf("Child%d: %d\tPid: %d\n",i+1, j, getpid());
				sleep(1);
			}
			_exit(0);
		}	
	}

	while(waitpid(-1, &s, 0) > 0){
		printf("Child exit status: %d\n", WEXITSTATUS(s));
	}
	
	return 0;
}



