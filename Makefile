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

current: day3

clean:
	rm -rf build/*
