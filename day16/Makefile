all: runpart1 runpart2
part1: part1.c common.c
	gcc part1.c common.c -o part1
runpart1: part1 part1Tests 
	./part1 input.txt
part1Tests: part1
	./part1 testdata.txt	
	./part1 testdata1.txt	
	./part1 testdata2.txt	
	./part1 testdata3.txt	
	./part1 testdata4.txt	
	./part1 testdata5.txt	
	./part1 testdata6.txt	
part2: part2.c common.c decoder.c
	gcc part2.c common.c decoder.c -o part2
runpart2: part2 part2Tests
	./part2 input.txt
part2Tests: part2
	./part2 testdata.txt
	./part2 part2sumtest.txt
	./part2 part2product.txt
	./part2 part2minimum.txt
	./part2 part2maximum.txt
	./part2 part2lessthan.txt
	./part2 part2greaterthan.txt
	./part2 part2equals.txt
	./part2 part2EqualsWithCalculation.txt
clean:
	rm part1 part2 
