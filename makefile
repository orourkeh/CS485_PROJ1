COMPILER=gcc -std=c99
SOURCES=main.c
EXEC=SVM

all: clean build run

build:
	$(COMPILER) $(SOURCES) -o $(EXEC)

clean:
	rm -f program
run:
	./$(EXEC)

