CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -O2
LIBS = -lpcap

SRC = src/ids/main.c src/ids/utils.c src/ids/parser.c src/ids/filter.c \
      src/ids/logger.c src/ids/capture.c
OBJ = $(SRC:.c=.o)
TARGET = build/ids

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean