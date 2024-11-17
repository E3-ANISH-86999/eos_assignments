#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<arpa/inet.h>
#include<string.h>

#define SERV_ADDR	"127.0.0.1"
#define SERV_PORT	2809

int main()
{
	int ret, serv_fd, cli_fd, ret1, ret2, ret3, ret4, ret5;
	struct sockaddr_in serv_addr, cli_addr;
	socklen_t socklen = sizeof(cli_addr);
	char msg[512];
	//1. create server socket
	serv_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(serv_fd < 0)
	{
		perror("socket() failed\n");
		_exit(1);
	}
	//2. bind the address
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	inet_aton(SERV_ADDR, &serv_addr.sin_addr);
	ret = bind(serv_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	if(ret < 0){
		perror("bind() failed\n");
		_exit(2);
	}
	//3.listen to server socket
	ret1 = listen(serv_fd, 5);
	if(ret1 < 0){
		perror("listen() failed\n");
		_exit(3);
	}
	//6. accept client connection
	cli_fd = accept(serv_fd, (struct sockaddr*)&cli_addr, &socklen);
	if(cli_fd < 0){
		perror("accept() failed\n");
		_exit(6);
	}
	do
	{
		//8.read data from client
		ret2 = read(cli_fd, msg, sizeof(msg));
		if(ret2 < 0){
			perror("read() failed\n");
			_exit(8);
		}
		printf("client: %s\n",msg);
		//9. send data to client
		printf("server: ");
		gets(msg);
		ret3 = write(cli_fd, msg, sizeof(msg));
		if(ret3 < 0){
			perror("write() failed\n");
			_exit(9);
		}
	}while(strcmp(msg, "bye") != 0);
	//12. close client socket
	ret4 = close(cli_fd);
	if(ret4 < 0){
		perror("close() failed\n");
		_exit(12);
	}
	//13. shutdown server socket
	ret5 = shutdown(serv_fd, SHUT_RDWR);
	if(ret5 < 0){
		perror("shutdown() failed\n");
		_exit(13);
	}
}


















