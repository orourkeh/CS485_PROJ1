COMPILER=gcc -std=c99
SOURCES=main.c
EXEC=program

all: clean build run

build:
	$(COMPILER) $(SOURCES) -o $(EXEC)

clean:
	rm -f program
run:
	./$(EXEC)

