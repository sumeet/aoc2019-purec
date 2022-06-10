day1: day1.c
	mkdir -p build
	gcc -o build/day1 day1.c
	./build/day1

day2: day2.c
	mkdir -p build
	gcc -g -o build/day2 day2.c
	./build/day2

day3: day3.c
	mkdir -p build
	gcc -g -o build/day3 day3.c
	./build/day3

day4: day4.c
	mkdir -p build
	gcc -g -o build/day4 day4.c
	./build/day4

day5: day5.c
	mkdir -p build
	gcc -g -o build/day5 day5.c
	./build/day5

day6: day6.c
	mkdir -p build
	gcc -g -o build/day6 day6.c
	./build/day6

current: day6

clean:
	rm -rf build/*
