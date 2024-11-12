#include <stdio.h>
#include <unistd.h>


int main(){
	int ret, arr[2], count = 0;
	char ch = 'a';
	
	ret = pipe(arr);
	if(ret < 0){
		perror("pipe() failed!");
		_exit(1);
	}
	
	while(1){
		count = count + write(arr[1], &ch, sizeof(ch));	
		printf("count = %d\n", count);
	}
	return 0;
}

