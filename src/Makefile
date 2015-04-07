CC=gcc
CFLAGS=-Wall -fPIC
LDFLAGS=-L. -ltlib -lcheck

SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
TARGET_SO=libtlib.so
DEPS=deps

.PHONY: all
all: $(TARGET_SO) $(DEPS)

$(TARGET_SO): $(OBJ)
	$(CC) -fPIC -shared -o $@ $^

$(DEPS): $(SRC)
	-rm -f $(DEPS)
	$(CC) $(CFLAGS) -MM $^ > $(DEPS)

-include $(DEPS)

.PHONY: clean
clean:
	-rm $(OBJ) $(DEPS) $(TARGET_SO)
