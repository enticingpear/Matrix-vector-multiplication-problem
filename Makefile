CC = gcc
CFLAGS = -pthread

TARGET = main
SRC = main.c multiplication_student.c
REF = reference.o

all: $(TARGET)

$(TARGET): $(SRC) $(REF)
	$(CC) $(CFLAGS) $(SRC) $(REF) -o $(TARGET)

clean:
	rm -f $(TARGET)