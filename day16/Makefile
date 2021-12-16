all: runpart1 runpart2
part1: part1.c common.c
	gcc part1.c common.c -o part1
runpart1: part1
	./part1 testdata.txt	
	./part1 testdata1.txt	
	./part1 testdata2.txt	
	./part1 testdata3.txt	
	./part1 testdata4.txt	
	./part1 testdata5.txt	
	./part1 testdata6.txt	
	./part1 input.txt
part2: part2.c common.c
	gcc part2.c common.c -o part2
runpart2: part2
	./part2 testdata.txt	
	./part2 input.txt
clean:
	rm part1 part2 
