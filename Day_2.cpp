#include <iostream>
#include <fstream>
#include <sstream>

int main() {

}

void part1() {
    std::ifstream file_reader;
    std::string line_store;
    file_reader.open("Data/Day_2.txt");
    int counter = 0;
    while(!file_reader.eof()){
        std::getline(file_reader, line_store);
        if (file_reader.eof()) break;
        std::istringstream iss(line_store);
        std::string temp;
        int* prev = nullptr;
        bool* ascending = nullptr;
        ;
        bool line_safe = true;
        while(std::getline(iss, temp, ' ') && line_safe) {
            int curr = std::stoi(temp);
            if (prev == nullptr) {
                prev = new int(curr);
            } else {
                if(ascending == nullptr) {
                    ascending = new bool(curr > *prev);
                } else {
                    if ((*ascending ^ (curr > *prev))) {
                        
                        line_safe = false;
                    }
                }
                if (*prev == curr || std::abs(*prev - curr) > 3) {
                    line_safe = false;
                }
                *prev = curr;
            }
        }
        if (line_safe) counter++;
        std::cout << "\"" << line_store << "\"" << (line_safe ? "true" : "false") << std::endl;
    }
    std::cout << "total: " << counter << std::endl;
}
