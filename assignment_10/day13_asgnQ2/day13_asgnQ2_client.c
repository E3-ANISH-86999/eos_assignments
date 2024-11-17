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
        msgrcv(msgid, &msg, sizeof(msg), 1, 0);

        if (strcmp(msg.fifo_name, "exit") == 0) {
            printf("Server exiting...\n");
            break;
        }

        printf("FIFO name: %s\n", msg.fifo_name);
        printf("File name: %s\n", msg.file_name);

        int fifo_fd = open(msg.fifo_name, O_RDONLY);
        char buffer[512];
        ssize_t bytes_read;

        FILE *output_file = fopen("received_file", "wb");
        if (output_file == NULL) {
            perror("File open failed");
            continue;
        }

        while ((bytes_read = read(fifo_fd, buffer, sizeof(buffer))) > 0) {
            fwrite(buffer, 1, bytes_read, output_file);
        }

        fclose(output_file);
        close(fifo_fd);
    }

    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}
