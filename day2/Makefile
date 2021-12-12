all: position positionWithAim

position: position.c positionMethods.c
	gcc position.c positionMethods.c -o position
	./position testInput
	./position adventofcode-day2-input.txt 

positionWithAim: position.c positionMethodsWithAim.c
	gcc position.c positionMethodsWithAim.c -o positionWithAim
	./positionWithAim testInput
	./positionWithAim adventofcode-day2-input.txt 

clean:
	rm position positionWithAim
