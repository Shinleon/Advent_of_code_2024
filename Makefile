CC=g++

.PHONY
all: Day_1.a Day_2.a

Day_1.a: Day_1.cpp
	$(CC) -o Day_1.a Day_1.cpp -std=c++11
	
Day_2.a: Day_2.cpp
	$(CC) -o Day_2.a Day_2.cpp -std=c++11 -g


