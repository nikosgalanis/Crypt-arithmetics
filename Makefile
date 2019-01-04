objects=main.o functions.o

crypto.exe : $(objects)
								gcc -o crypto.exe $(objects)

main.o : main.c functions.h
								gcc -c main.c

functions.o : functions.c functions.h
								gcc -c functions.c

clean:
								rm crypto.exe $(objects)
