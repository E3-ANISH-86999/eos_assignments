#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	int ret,s, count = 0;
	
	while(1){
		ret = fork();
		if(ret == -1){
			printf("fork() failed!\n");
			break;
		}
		else if(ret == 0){
			sleep(5);
			_exit(0);
		}
		else{
			count++;
			printf("Child count: %d\n", count);
		}

	}

	while(waitpid(-1, &s, 0) > 0){
		count--;
		printf("Child remaining to teminate: %d\n", count);
	}
	return 0;
}


