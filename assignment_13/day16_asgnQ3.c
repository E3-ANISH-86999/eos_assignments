#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>

pthread_mutex_t m;
pthread_cond_t c;
int sun_flag = 0;


void siginit_handler(int sig){

    printf("Signal caught! %d\n", sig);

    pthread_mutex_destroy(&m);
    pthread_cond_destroy(&c);
    _exit(0);

}

void* sun_fn(void *param){
    char *str = "SUNBEAM\n";
    while(1){
        pthread_mutex_lock(&m);
        while(sun_flag)
            pthread_cond_wait(&c, &m);
        for(int i=0; str[i] != '\0'; i++){
            write(1, &str[i], 1);
            sleep(1);

        }
        sun_flag = 1;
        pthread_cond_signal(&c);

        pthread_mutex_unlock(&m);
        
    }
    return NULL;
}

void* info_fn(void *param){
    char *str = "INFOTECH\n";
    while(1){
        pthread_mutex_lock(&m);
        while(!sun_flag)
            pthread_cond_wait(&c, &m);

        for(int i=0; str[i] != '\0'; i++){
            
            write(1, &str[i], 1);
            sleep(1);

        }
        sun_flag = 0;
        
        pthread_cond_signal(&c);
        pthread_mutex_unlock(&m);
        
    }
    return NULL;
}


int main(){
    int ret;
    pthread_t th1, th2;
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = siginit_handler;
    
    ret = sigaction(SIGINT, &sa, NULL);
    if(ret != 0){
        perror("Main> sigaction failed");
        _exit(1);
    }
    ret = pthread_mutex_init(&m, NULL);
    if(ret < 0){
        perror("Main> pthread_mutex_init() failed!");
        _exit(1);
    }
     
    ret = pthread_cond_init(&c, NULL);
    if(ret < 0){
        perror("Main> pthread_cond_init() failed!");
        pthread_mutex_destroy(&m);
        _exit(1);
    }
    ret = pthread_create(&th1, NULL, sun_fn, NULL);
    if(ret != 0){
        perror("Main> pthread_create() failed");
        pthread_mutex_destroy(&m);
        pthread_cond_destroy(&c);
        _exit(1);
    }

    ret = pthread_create(&th2, NULL, info_fn, NULL);
    if(ret != 0){
        perror("Main> pthread_create() failed");
        pthread_mutex_destroy(&m);
        pthread_cond_destroy(&c);
        _exit(1);
    }
    
    printf("Press enter to exit from process..\n");
    getchar();
    pthread_kill(th1, SIGINT);

    return 0;
}