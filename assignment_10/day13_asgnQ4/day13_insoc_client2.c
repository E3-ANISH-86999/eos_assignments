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
	int ret, cli_fd, ret1, ret2, ret3;
	struct sockaddr_in serv_addr;
    num_t n1;
	//4. create client socket
	cli_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(cli_fd < 0){
		perror("client: socket() failed\n");
		_exit(1);
	}

	//5. connect to server socket
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	inet_aton(SERV_ADDR, &serv_addr.sin_addr);
	ret = connect(cli_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	if(ret < 0){
		perror("client: connect() failed\n");
		_exit(1);
	}
	//7. send data to server
	    printf("client: Enter two numbers seperated by space: ");
	    scanf("%d %d",&n1.num1, &n1.num2);
	    ret = write(cli_fd, &n1, sizeof(num_t));
		if(ret1 < 0){
			perror("client: write() failed\n");
			_exit(1);
		}
		//10. read data from server
	    ret = read(cli_fd, &n1, sizeof(num_t));
		if(ret2 < 0){
			perror("client: read() failed\n");
			_exit(1);
		}
	    printf("client: sum received from server = %d\n", n1.sum);
	//11. close client socket
	ret3 = close(cli_fd);
	if(ret3 < 0){
		perror("close() failed\n");
		_exit(11);
	}
	return 0;
}

