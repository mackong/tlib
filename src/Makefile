CC=gcc
CFLAGS=-Wall
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
	@echo $^
	$(CC) $(CFLAGS) -MM $^ > $(DEPS)

-include $(DEPS)

.PHONY: clean
clean:
	-rm $(OBJ) $(DEPS) $(TARGET_SO)
