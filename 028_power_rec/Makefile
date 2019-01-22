test-power: power.o test-power.o
	gcc -o test-power test-power.o power.o
power.o:power.c
	gcc -c --std=gnu99 -Wall -Werror -pedantic power.c
test-power.o:test-power.c 
	gcc -c --std=gnu99 -Wall -Werror -pedantic test-power.c
clean:
	rm *.o
