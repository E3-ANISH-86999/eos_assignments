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
    int ret, serv_fd, cli_fd;
    struct sockaddr_un serv_addr, cli_addr;
    socklen_t socklen = sizeof(cli_addr);
    num_t n2;
    //1. create server socket
    serv_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(serv_fd < 0){
        perror("server: socket() failed");
        _exit(1);
    }
    //2. bind the address
    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, SOCK_FILE);
    ret = bind(serv_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if(ret < 0){
        perror("server: bind() failed");
        _exit(1);
    }
    
    //3. listen to server socket
    listen(serv_fd, 5);
    //6. accept client connection
    cli_fd = accept(serv_fd, (struct sockaddr*)&cli_addr, &socklen);
    if(cli_fd < 0){
        perror("server: accept() failed");
        _exit(1);
    }else{
        printf("server: waiting for numbers from client..\n");
    }

    ret = read(cli_fd, &n2, sizeof(num_t));
    if(ret < 0){
        perror("server: read() failed");
        _exit(1);
    }
    printf("server: numbers received from client\nserver: num1=%d, num2=%d\n", n2.num1, n2.num2);
    //9. send data to client
    n2.sum = n2.num1 + n2.num2;
    printf("server: sum sent to client...\n ");
    
    ret = write(cli_fd, &n2, sizeof(num_t));
    if(ret < 0){
        perror("server: write() failed");
        _exit(1);
    }

    //12. close client socket
    close(cli_fd);
    //13. shutdown server socket
    shutdown(serv_fd, SHUT_RDWR);
    //14. delete the socket file
    unlink(SOCK_FILE);
    return 0;
}
