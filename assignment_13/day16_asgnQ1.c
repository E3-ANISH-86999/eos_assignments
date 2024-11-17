#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define SIZE 6
#define SWAP(a,b) int temp = a; a=b; b=temp;

int arr1[SIZE];

void display(int arr[SIZE])
{
    for(int i =0; i< SIZE; i++)
    {
        printf("%4d",arr[i]);
    }
    printf("\n");
  
}

void* thsort_fn(void *param){

    int *arr2 = (int *)param;    
    int sel_pos = 0,pos = 0;

    for(sel_pos = 0;sel_pos < SIZE-1; sel_pos++)
    {
        for(pos = sel_pos+1; pos < SIZE; pos++)
        {
            if(arr2[sel_pos] > arr2[pos])
            {
                SWAP(arr2[sel_pos],arr2[pos])
            }
        }
    }
        
    return NULL;
}

int main(){
    int ret;
    pthread_t th;
    int arr1[SIZE] = {44, 77, 11, 99, 22, 88};

    printf("Main> Array before swap: ");
    display(arr1);

    ret = pthread_create(&th, NULL, thsort_fn, arr1);        
    if(ret != 0){
        perror("Main> pthread_create() failed!");
        _exit(0);
    }

    pthread_join(th, NULL);

    printf("Main> Array after swap: ");
    display(arr1);
    

    return 0;
}
