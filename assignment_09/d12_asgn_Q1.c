#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/msg.h>

#define MQ_KEY 0x86999

typedef struct{
    long id;
    int num1;
    int num2;
    int sum;
}msg_t;

int main(){
    int ret, pid, mqid;
    
    mqid = msgget(MQ_KEY, IPC_CREAT | 0600);
    if(mqid < 0){
        perror("msgget() failed!");
        _exit(1);
    }

    pid = fork();
    if(pid == 0){
        msg_t m1;
        m1.id = 601;
        printf("Child> Enter two numbers: \n");
        printf("Child> num1 = ");
        scanf("%d",&m1.num1);
        printf("Child> num2 = ");
        scanf("%d",&m1.num2);

        ret = msgsnd(mqid, &m1, sizeof(msg_t)-sizeof(long), 0);
        if(ret < 0){
            perror("Child> msgsnd() failed");
            _exit(1);
        }
        else{
            printf("Child> numbers sent\nChild> num1 = %d\nChild> num2 = %d\n", m1.num1, m1.num2);
        }
        printf("Child> Waiting for sum...\n");

        ret = msgrcv(mqid, &m1, sizeof(msg_t)-sizeof(long), 102, 0);
        if(ret < 0){
            perror("Child> msgsrcv() failed");
            _exit(1);
        }
        else{
            printf("Child> sum received\nChild> sum = %d\n",m1.sum);
        }


    }
    else{
        msg_t m2;
        printf("Parent> Waiting for numbers to receive... \n");

        ret = msgrcv(mqid, &m2, sizeof(msg_t)-sizeof(long), 601, 0);
        if(ret < 0){
            perror("Parent> msgsrcv() failed");
            _exit(1);
        }
        else{
            printf("Parent> numbers received\nParent> num1 = %d\nParent> num2 = %d\n",m2.num1, m2.num2);
        }

        m2.sum = m2.num1 + m2.num2;
        m2.id = 102;

        ret = msgsnd(mqid, &m2, sizeof(msg_t)-sizeof(long), 0);
        if(ret < 0){
            perror("Parent> msgsnd() failed");
            _exit(1);
        }
        else{
            printf("Parent> sum sent to the child...\n");
        }

        waitpid(pid, NULL, 0);

        msgctl(mqid, IPC_RMID, NULL);
    }

    return 0;
}   