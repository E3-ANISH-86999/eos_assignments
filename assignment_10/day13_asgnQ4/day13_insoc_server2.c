#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<arpa/inet.h>
#include<string.h>

#define SERV_ADDR	"127.0.0.1"
#define SERV_PORT	2809

typedef struct {
    int num1, 
        num2,
        sum;
}num_t;


int main()
{
	int ret, serv_fd, cli_fd, ret1, ret2, ret3, ret4, ret5;
	struct sockaddr_in serv_addr, cli_addr;
	socklen_t socklen = sizeof(cli_addr);
    num_t n2;
	//1. create server socket
	serv_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(serv_fd < 0){
        perror("server: socket() failed");
		_exit(1);
	}
	//2. bind the address
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	inet_aton(SERV_ADDR, &serv_addr.sin_addr);
	ret = bind(serv_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	if(ret < 0){
        perror("server: bind() failed");
		_exit(2);
	}
	//3.listen to server socket
	ret1 = listen(serv_fd, 5);
	if(ret1 < 0){
        perror("server: accept() failed");
		_exit(3);
	}
	//6. accept client connection
	cli_fd = accept(serv_fd, (struct sockaddr*)&cli_addr, &socklen);
	if(cli_fd < 0){
        perror("server: accept() failed");
		_exit(6);
	}else{
        printf("server: waiting for numbers from client..\n");
    }
		//8.read data from client
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
	ret4 = close(cli_fd);
	if(ret4 < 0){
		perror("server: close() failed\n");
		_exit(12);
	}
	//13. shutdown server socket
	ret5 = shutdown(serv_fd, SHUT_RDWR);
	if(ret5 < 0){
		perror("server: shutdown() failed\n");
		_exit(13);
	}
}


















