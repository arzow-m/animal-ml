maksumArzowA1: maksumArzowA1.o maksumArzowA1Main.o 
	gcc maksumArzowA1.o maksumArzowA1Main.o -o maksumArzowA1 -lm

maksumArzowA1.o: maksumArzowA1.c givenA1.h
	gcc -Wall -std=c99 -c maksumArzowA1.c

maksumArzowA1Main.o: maksumArzowA1Main.c givenA1.h
	gcc -Wall -std=c99 -c maksumArzowA1Main.c

clean:
	rm *.o maksumArzowA1
