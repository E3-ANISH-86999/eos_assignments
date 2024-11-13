#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

typedef struct sum{
    int num1, num2, sum;
}sum_t;

int main(){
    int arr1[2], arr2[2];
    int pid, err, ret;
    
    ret = pipe(arr1);
    if(ret < 0){
		perror("pipe() failed!");
		_exit(1);
	}

    ret = pipe(arr2);
    if(ret < 0){
		perror("pipe() failed!");
		_exit(1);
	}

    pid = fork();
    if(pid == 0) { // child process
        close(arr2[1]);
        close(arr1[0]);
        
        sum_t s1;
        printf("Child> Enter two numbers: \n");
        printf("Child> num1 = ");
        scanf("%d", &s1.num1); 
        printf("Child> num2 = ");
        scanf("%d", &s1.num2);
        err = write(arr1[1], &s1, sizeof(sum_t));
        if(err < 0){
            perror("Child> write() failed!");
            close(arr1[1]);
            close(arr2[0]);
            _exit(1);
        }
                
        printf("Child> Numbers sent to parent!\n");
        printf("Child> Waiting for sum...\n");

        err = read(arr2[0], &s1, sizeof(sum_t));
        if(err < 0){
            perror("Child> read() failed!");
            close(arr1[1]);
            close(arr2[0]);
            _exit(1);
        }
        printf("Child> sum recieved from parent:\nChild> sum = %d\n", s1.sum);
            
        close(arr1[1]);
        close(arr2[0]); 
        
    }
    else{ // parent process
        sum_t s2;
        close(arr1[1]);
        close(arr2[0]);
        
        printf("Parent> Waiting for numbers...\n");
        err = read(arr1[0], &s2, sizeof(sum_t));
        if(err < 0){
            perror("Parent> read() failed!");
            close(arr2[1]);
            close(arr1[0]);
            _exit(1);
        }

        printf("Parent> Numbers recieved from child are:\nParent> num1 = %d\nParent> num2 = %d\n", s2.num1, s2.num2);

        s2.sum = s2.num1 + s2.num2;

        err = write(arr2[1], &s2, sizeof(sum_t));
        if(err < 0){
            perror("Parent> write() failed!");
            close(arr1[1]);
            close(arr2[0]);
            _exit(1);
        }
                
        printf("Parent> Sum sent to child!\n");
        
        close(arr2[1]); 
        close(arr1[0]);
        
        waitpid(pid, NULL, 0); 
    }

    return 0;
}
