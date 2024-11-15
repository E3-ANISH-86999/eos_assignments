#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int arr2[2];

void* addition_fn(void *param){
    int *ip = (int *)param;
    int i;
    if(ip[0]> ip[1]){
        printf("Thread> Starting range is greater than ending range.\n");
        arr2[0] = 1;
        pthread_exit(NULL);
    }

    for(i = ip[0]; i<=ip[1]; i++){
        arr2[1] = arr2[1] + i;
        printf("%d\n", arr2[1]);
    }
    return NULL;
}

int main(){
    int ret;
    pthread_t th1;
    int arr1[2];
    printf("Main> Enter starting of range: ");
    scanf("%d", &arr1[0]);
    printf("Main> Enter ending of range: ");
    scanf("%d", &arr1[1]);

    ret = pthread_create(&th1, NULL, addition_fn, arr1);
    if(ret != 0){
        perror("Main> pthread_create() failed!");
        _exit(1);
    }

    pthread_join(th1, NULL);
    if(arr2[0] == 0){
        printf("Main> Sum: %d\n", arr2[1]);
    }
    else
        printf("Main> Starting range is greater than ending range.\n");
       
    return 0;
}