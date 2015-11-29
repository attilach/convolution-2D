GCC=gcc -pthread -lrt -Wall -std=gnu99

main: main.o ppm.o convolution.o filtre.o
	$(GCC) $^ -o $@

main.o: main.c
	$(GCC) $< -c

ppm.o: ppm.c ppm.h
	$(GCC) $< -c

convolution.o: convolution.c convolution.h
	$(GCC) $< -c

filtre.o: filtre.c filtre.h
	$(GCC) $< -c

clean:
	rm -f *.o main
