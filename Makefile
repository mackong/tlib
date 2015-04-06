all: lib test

lib:
	make -C src

test:
	make -C src/tests

.PHONY: run clean

run:
	make -C src/tests run

clean:
	make -C src clean
	make -C src/tests clean
