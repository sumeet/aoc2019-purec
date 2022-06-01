day1: day1.c
	gcc -o build/day1 day1.c
	./build/day1

clean:
	rm -rf build/*
