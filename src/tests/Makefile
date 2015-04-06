CC=gcc
CFLAGS=-Wall
LDFLAGS=-L.. -ltlib -lcheck

SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
TARGET=test
DEPS=deps

.PHONY: all run clean
all: $(TARGET) $(DEPS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $(LDFLAGS) $^

$(DEPS): $(SRC)
	-rm -f $(DEPS)
	@echo $^
	$(CC) $(CFLAGS) -MM $^ > $(DEPS)

-include $(DEPS)

run: $(TARGET)
	LD_LIBRARY_PATH=.. ./$(TARGET)

clean:
	-rm $(OBJ) $(DEPS) $(TARGET)
