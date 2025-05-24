.PHONY: all build run test clean

all: build

build:
	./build.sh

run:
	./run.sh

test:
	./test.sh

clean:
	./clean.sh

format:
	./format.sh

install:
	cd build && sudo make install
