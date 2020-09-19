build:
	g++ -o run main.cpp

test:
	g++ -o test tests.cpp
	./test
	rm ./test

all:
	make build
	./run
