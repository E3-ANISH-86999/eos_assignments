/*
Write a program that compiles above multi-ﬁle project. It runs commands "gcc -c circle.c", "gcc -c square.c", "gcc -c rectangle.c", "gcc -c main.c"
concurrently.
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	int pidarr[6]; // pid array
	int esarr[6]; //exit status array
	int err;

	// child 1
	pidarr[0] = fork();
	if(pidarr[0] == 0){ 
		err = execlp("gcc","gcc", "-c", "circle.c", NULL);
		if(err < 0){
			perror("Child1 exec() failed");
			_exit(1);
		}
		else
			_exit(0);
	}

	// child 2
	pidarr[1] = fork();
	if(pidarr[1] == 0){  
		err = execlp("gcc","gcc", "-c", "square.c", NULL);
		if(err < 0){
			perror("Child2 exec() failed");
			_exit(1);
		}
		else
			_exit(0);
	}
	
	// child 3
	pidarr[2] = fork();
	if(pidarr[2] == 0){  
		err = execlp("gcc","gcc", "-c", "rectangle.c", NULL);
		if(err < 0){
			perror("Child3 exec() failed");
			_exit(1);
		}
		else
			_exit(0);
	}

	//child 4
	pidarr[3] = fork();
	if(pidarr[3] == 0){ 
		err = execlp("gcc","gcc", "-c", "main.c", NULL);
		if(err < 0){
			perror("Child4 exec() failed");
			_exit(1);
		}
		else
			_exit(0);
	}
	
	//checking exit status of 4 children
	for(int i=0; i<4; i++)
		waitpid(pidarr[i], &esarr[i], 0);

	// check whether all the child executed successfully 
	if((WEXITSTATUS(esarr[0]) && 
		WEXITSTATUS(esarr[1]) && 
		WEXITSTATUS(esarr[2]) && 
		WEXITSTATUS(esarr[3])) == 0){
		
		pidarr[4] = fork(); //child 5
		if(pidarr[4] == 0){
			err = execlp("gcc","gcc", "-o", "program.out", "circle.o", "square.o", "rectangle.o", "main.o", NULL);
			if(err < 0){
				perror("Child5 exec() failed");
				_exit(1);
			}
			else
				_exit(0);
		}
	}
	else{
		perror("Cannot link files");
		_exit(1);
	}
	
	//waiting for child5
	waitpid(pidarr[4], &esarr[4], 0);

	if((WEXITSTATUS(esarr[4])) == 0){

		pidarr[5] = fork();   //child 6
		if(pidarr[5] == 0){
			err = execlp("./program.out","./program.out", NULL);
			if(err < 0){
				perror("Child6 exec() failed");
				_exit(1);
			}
			else
				_exit(0);
		}
	}
	else{
		perror("Cannot run program");
		_exit(1);
	}
	
	//waiting for child6
	waitpid(pidarr[5], &esarr[5], 0);
	printf("Child6 exit status: %d\n", WEXITSTATUS(esarr[5]));


	return 0;
}












