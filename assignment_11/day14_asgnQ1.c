#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <signal.h>

#define SEM_KEY     0x86999

union semun {
    int              val;    
    struct semid_ds *buf;    
    unsigned short  *array;  
    struct seminfo  *__buf;  
};

int semid;

void sigint_handler(){
    semctl(semid, 0, IPC_RMID);
    waitpid(-1, NULL, 0);
    _exit(1);
}

int main(){
    int ret, pid, i;
    struct sigaction sa;
    union semun su;
    unsigned short init_cnts[] = {0, 1};
    su.array = init_cnts;
    struct sembuf ops[1];

    sa.sa_handler = sigint_handler;
    ret = sigaction(SIGINT, &sa, NULL);
    if(ret < 0){
        perror("sigaction() failed!");
        _exit(0);
    }

    semid = semget(SEM_KEY, 2, IPC_CREAT | 0640);
    if(semid < 0){
        perror("semget() failed!");
        _exit(1);
    }

    
    ret = semctl(semid, 0, SETALL, su);
    if(ret < 0){
        perror("semctl() failed");
        semctl(semid, 0, IPC_RMID);
        _exit(1);
    }

    pid = fork();
    if(pid == 0){
        char *str = "SUNBEAM\n";
        while(1){
            //P(c2)
            ops[0].sem_num = 1;
            ops[0].sem_op = -1;
            ops[0].sem_flg = 0;
            ret = semop(semid, ops, 1);
            if(ret < 0){
                perror("semop() failed!");
                semctl(semid, 0, IPC_RMID);
                _exit(1);
            }
           
            for(i = 0; str[i] != '\0'; i++){
                write(1, &str[i], sizeof(str[i]));
                sleep(1);
            }
            //V(c1)        
            ops[0].sem_num = 0;
            ops[0].sem_op = +1;
            ops[0].sem_flg = 0;
            ret = semop(semid, ops, 1);
            if(ret < 0){
                perror("semop() failed!");
                semctl(semid, 0, IPC_RMID);
                _exit(1);
                    
            }
        }
    }
    else{
        while(1){
           
            //P(c1)
            ops[0].sem_num = 0;
            ops[0].sem_op = -1;
            ops[0].sem_flg = 0;
            ret = semop(semid, ops, 1);
            if(ret < 0){
                perror("semop() failed!");
                semctl(semid, 0, IPC_RMID);
                _exit(1);
            }

            char *str = "INFOTECH\n";
            for(i = 0; str[i] != '\0'; i++){
                write(1, &str[i], 1);
                sleep(1);
            }
            
            //V(c2)
            ops[0].sem_num = 1;
            ops[0].sem_op =  +1;
            ops[0].sem_flg = 0;
            ret = semop(semid, ops, 1);
            if(ret < 0){
                perror("semop() failed!");
                semctl(semid, 0, IPC_RMID);
                _exit(1);
            }
        }
    }

    return 0;
}