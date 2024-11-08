TARGET=q1
CC=gcc

$(TARGET).out: $(TARGET).o
	$(CC) $(TARGET).o -o $(TARGET).out

$(TARGET).o: $(TARGET).c
	$(CC) -c $(TARGET).c

run:
	./$(TARGET).out

clean:
	rm *.o *out | ls

open:
	vim $(TARGET).c

phony: run clean open


