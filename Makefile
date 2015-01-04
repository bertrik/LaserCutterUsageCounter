CFLAGS = -W -Wall -O3

all: build

build: main_test

test: main_test
	./main_test

main_test: main_test.c usagecounter/buffer.c usagecounter/storage.c

clean:
	rm main_test

