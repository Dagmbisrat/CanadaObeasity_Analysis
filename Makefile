# Makefile

# Default target
run: Main.o
	gcc -o run Main.o

# Rule to compile Main.c into Main.o
Main.o: Main.c
	gcc -c Main.c

# Clean rule to remove the generated files
clean:
	rm -f run Main.o
