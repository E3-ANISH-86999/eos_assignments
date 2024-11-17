#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

typedef struct {
    int num1, num2, sum;
}num_t;

int main(){
    int ret, fd1, fd2;
    num_t n1;

    // Sending numbers to client
    ret = mkfifo("/tmp/myfifo1", 0600);
    if(ret != 0){
        perror("client: mkfifo() failed!");
        _exit(1);
    }

    fd1 = open("/tmp/myfifo1", O_WRONLY);
    if(fd1 < 0){
        perror("open() failed!\n");
        unlink("/tmp/myfifo1");
        _exit(1);
    }
    printf("Client: Enter two number: \n");
    printf("Client: num1: ");
    scanf("%d",&n1.num1);
    printf("Client: num2: ");
    scanf("%d",&n1.num2);
    
    ret = write(fd1, &n1, sizeof(n1));
    if(ret < 0){
        perror("Client: write() failed");
        _exit(1);
    }
    else{
        printf("Client: Numbers sent to server..\n");
    }           
    
    
    // Receiving the sum from server
    fd2 = open("/tmp/myfifo2", O_RDONLY);
    if(fd2 < 0){
        perror("Client: open() failed!");
        _exit(1);
    }

    ret = read(fd2, &n1, sizeof(n1));
    if(ret < 0){
        perror("Client: read() failed");
        _exit(1);
    }
    else{
        printf("Client: Sum received from server =%d\n", n1.sum);
    }    

    close(fd1);
    close(fd2);
    return 0;
}