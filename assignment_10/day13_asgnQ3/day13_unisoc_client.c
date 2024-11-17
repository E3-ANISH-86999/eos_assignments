#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>

#define SOCK_FILE   "/tmp/mysock"

typedef struct {
    int num1, 
        num2,
        sum;    
}num_t;

int main() {
    int ret, cli_fd;
    struct sockaddr_un serv_addr;
    num_t n1;
    //4. create client socket
    cli_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(cli_fd < 0){
        perror("client: socket() failed");
        _exit(1);
    }
    //5. connect to server socket
    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, SOCK_FILE);
    ret = connect(cli_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if(ret < 0){
        perror("client: connect() failed");
        _exit(1);
    }
    //7. send data to server
    printf("client: Enter two numbers seperated by space: ");
    scanf("%d %d",&n1.num1, &n1.num2);
    ret = write(cli_fd, &n1, sizeof(num_t));
    if(ret < 0){
        perror("client: write() failed");
        _exit(1);
    }
    //10. read data from server
    ret = read(cli_fd, &n1, sizeof(num_t));
    if(ret < 0){
        perror("client: read() failed");
        _exit(1);
    }
    printf("client: sum received from server = %d\n", n1.sum);
    
    //11. close client socket
    close(cli_fd);
    return 0;
}
