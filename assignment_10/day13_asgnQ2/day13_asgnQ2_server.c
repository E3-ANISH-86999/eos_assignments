#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define MSG_QUEUE_KEY 1234

struct message {
    long msg_type;
    char fifo_name[100];
    char file_name[100];
};

int main() {
    int msgid = msgget(MSG_QUEUE_KEY, 0666 | IPC_CREAT);
    struct message msg;

    while (1) {
        printf("Enter FIFO name : ");
        scanf("%s", msg.fifo_name);
        if (strcmp(msg.fifo_name, "exit") == 0) {
            break;
        }

        printf("Enter file name : ");
        scanf("%s", msg.file_name);
        if (strcmp(msg.file_name, "exit") == 0) {
            break;
        }

        msg.msg_type = 1;

        msgsnd(msgid, &msg, sizeof(msg), 0);

        mkfifo(msg.fifo_name, 0666);

        int fd = open(msg.file_name, O_RDONLY);
        if (fd < 0) {
            perror("File open failed");
            continue;
        }

        int fifo_fd = open(msg.fifo_name, O_WRONLY);
        char buffer[512];
        ssize_t bytes_read;

        while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
            write(fifo_fd, buffer, bytes_read);
        }

        close(fd);
        close(fifo_fd);
    }

    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}
