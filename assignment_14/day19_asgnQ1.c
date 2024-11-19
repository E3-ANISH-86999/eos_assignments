#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>


int main(int argc, char *argv[]) {
    int fs, fd, ret;
    void *ptr, *ptr2;
    struct stat st1;
    fs = open(argv[1], O_RDONLY);
    if(fs < 0) {
        perror("open() failed");
        _exit(1);
    }

    ret = fstat(fs, &st1);
    if(ret < 0) {
        perror("fstat() failed");
        close(fs);
        _exit(1);
    }

    ptr = mmap(NULL, st1.st_size, PROT_READ, MAP_PRIVATE, fs, 0);
    if(ptr == (void*)-1) {
        perror("mmap() failed");
        close(fs);
        _exit(1);
    }

    fd = open(argv[2], O_CREAT | O_RDWR | O_TRUNC, 0666);
    if(fd < 0) {
        perror("open() failed");
        close(fs);
        _exit(1);
    }

    ret = ftruncate(fd, st1.st_size);
    if(ret < 0) {
        perror("ftruncate() failed");
        close(fs);
        close(fd);
        _exit(1);
    }

    ptr2 = mmap(NULL, st1.st_size, PROT_WRITE, MAP_SHARED, fd, 0);
    if(ptr2 == (void*)-1) {
        perror("mmap() failed");
        close(fs);
        close(fd);

        _exit(1);
    }
 
    memcpy(ptr2, ptr, st1.st_size);
    printf("File copied successfully!\n");

    close(fs);
    close(fd);
 
    return 0;
}