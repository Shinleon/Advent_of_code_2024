CC=g++

all: Day1 Day2

Day1: 
	$(CC) -o Day_1.a Day_1.cpp -std=c++11
	
Day2: 
	$(CC) -o Day_2.a Day_2.cpp -std=c++11 -g


