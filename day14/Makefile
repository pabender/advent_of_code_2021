all: runpart1 runpart2-2
part1: part1.c common.c
	gcc part1.c common.c -o part1
runpart1: part1
	./part1 testdata.txt	
	./part1 input.txt
part2: part2.c common.c
	gcc part2.c common.c -o part2
runpart2: part2
	./part2 testdata.txt	
	./part2 input.txt
part2-2: part2-2.c common.c
	gcc part2-2.c common.c -o part2-2
runpart2-2: part2-2
	./part2-2 testdata.txt	
	./part2-2 input.txt
clean:
	rm part1 part2 part2-2 
