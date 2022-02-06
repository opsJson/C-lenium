CC = "C:\mingw64\bin\gcc.exe"
LIBS =
INCLUDE =
FLAGS = -O3 -m64 -Wall -std=c99

main: main.c
	$(CC) main.c -o main $(INCLUDE) $(LIBS) $(FLAGS)
