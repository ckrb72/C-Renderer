
all: main

main: src/main.c
	gcc src/main.c -o main

clean:
	del main.exe
