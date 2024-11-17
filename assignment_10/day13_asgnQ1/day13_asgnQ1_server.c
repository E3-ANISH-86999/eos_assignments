#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

typedef struct {
    int num1, num2, sum;
}num_t;


int main(){
    int ret, fd1, fd2;
    num_t s1;

    // Receiving the receiving numbers from client
    fd1 = open("/tmp/myfifo1", O_RDONLY);
    if(fd1 < 0){
        perror("server: open() failed!");
        _exit(1);
    }

    ret = read(fd1, &s1, sizeof(s1));
    if(ret == -1){
        perror("Server: read() failed");
        _exit(1);
    }
    else{
        printf("Server: Numbers received from client are: n1=%d, n2=%d\n", s1.num1, s1.num2);
        s1.sum = s1.num1 + s1.num2;
    }    

    
    // Sending sum to client
    ret = mkfifo("/tmp/myfifo2", 0600);
    if(ret < 0){
        perror("Server: mkfifo() failed!");
        _exit(1);
    }

    fd2 = open("/tmp/myfifo2", O_WRONLY);
    if(fd2 < 0){
        perror("server: open() failed!");
        unlink("/tmp/myfifo2");
        _exit(1);
    }
    ret = write(fd2, &s1, sizeof(s1));
    if(ret < 0){
        perror("Server: write() failed");
        _exit(1);
    }
    else{
        printf("Server: Sum sent to client...\n");
    }           
    
    close(fd1);
    close(fd2);
    return 0;
}