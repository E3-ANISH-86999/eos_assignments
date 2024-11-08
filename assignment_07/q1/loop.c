#include<stdio.h>
#include <unistd.h>

int main(){
	int count = 0;
	while(1){
		printf("Counting: %d\tpid:%d\n", count++, getpid());
		sleep(1);
	}

	return 0;
}


