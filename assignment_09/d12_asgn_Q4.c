#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    int arr[2];
    int pid1, pid2, err1, err2, s1, s2, ret;
    ret = pipe(arr);
    if(ret < 0){
		perror("pipe() failed!");
		_exit(1);
	}

    pid1 = fork();
    if(pid1 == 0) { // writer process
        close(arr[0]);
        // output redirection
        dup2(arr[1], 1); // stdout
        close(arr[1]);
        err1 = execlp("who", "who", NULL);
        if(err1 < 0){
            perror("execlp() failed!");
        }
    }

    pid2 = fork();
    if(pid2 == 0) { // reader process
        close(arr[1]);
        // input redirection
        dup2(arr[0], 0); // stdin
        close(arr[0]);
        err2 = execlp("wc", "wc", NULL);
        if(err2 < 0){
            perror("execlp() failed!");
        }
    }

    close(arr[1]); // parent neither writing to pipe
    close(arr[0]); // nor reading from pipe
    waitpid(pid1, &s1, 0);
    waitpid(pid2, &s2, 0);

    return 0;
}
