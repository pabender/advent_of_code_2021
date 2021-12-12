all: day1-part1 day1-part2
day1-part1: increase.c intmethods.c
	gcc increase.c intmethods.c -o increase
	./increase adventofcode-day1-input.txt
day1-part2: slidingwindowincrease.c intmethods.c
	gcc slidingwindowincrease.c intmethods.c -o slidingwindowincrease 
	./slidingwindowincrease adventofcode-day1-input.txt
clean:
	rm increase slidingwindowincrease
