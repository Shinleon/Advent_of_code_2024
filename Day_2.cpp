#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <string>

enum Ordering {
    ASCENDING,
    DESCENDING,
    UNKNOWN,
};

enum ValidStep {
    BY_ONE = 1,
    BY_TWO = 2,
    BOTH = 3,
    NEITHER = 0,
};

void part2();

int main() {
    part2();
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
        std::cout << "\"" << line_store << "\" " << (line_safe ? "good" : "bad") << std::endl;
    }
    std::cout << "total: " << counter << std::endl;
}

std::tuple<ValidStep, Ordering, Ordering> lookahead(int index, Ordering order, std::vector<int> levels, bool fault_used) {
    ValidStep result = NEITHER;
    Ordering return_order_by_one = Ordering::UNKNOWN;
    Ordering return_order_by_two = Ordering::UNKNOWN;
    if(index < levels.size() -1) {
        if (std::abs(levels.at(index) - levels.at(index+1)) <= 3 && levels.at(index) != levels.at(index+1)) {
            if((order == Ordering::UNKNOWN) || (levels.at(index) < levels.at(index+1) ? order == Ordering::ASCENDING : order == Ordering::DESCENDING)) {
                result = ValidStep::BY_ONE;
                return_order_by_one = levels.at(index) < levels.at(index+1) ? Ordering::ASCENDING : Ordering::DESCENDING;
            }
        }
    }
    if(fault_used != true) { // we can look ahead by two
        if(index < levels.size()-2) {
            if (std::abs(levels.at(index) - levels.at(index+2)) <= 3 && levels.at(index) != levels.at(index+2)) {
                if((order == UNKNOWN) || (levels.at(index) < levels.at(index+2) ? order == Ordering::ASCENDING : order == Ordering::DESCENDING)) {
                    result = result == ValidStep::BY_ONE ? BOTH : BY_TWO;
                    return_order_by_two = levels.at(index) < levels.at(index+2) ? Ordering::ASCENDING : Ordering::DESCENDING;
                }
            }
        } else {
            result = result == ValidStep::BY_ONE ? BOTH : BY_TWO;
            return_order_by_two = order;
        }
    }
    return {result, return_order_by_one, return_order_by_two};
}

bool part2helper(int index, Ordering order, std::vector<int> levels, bool fault_used) {
    if(index == -1) {
        return part2helper(0, order, levels, false) || part2helper(1, order, levels, true);
    } else if (index >= levels.size() - 1) { // we've reached the end
        return true;
    } else {
        std::tuple<ValidStep, Ordering, Ordering> info = lookahead(index, order, levels, fault_used);
        bool result = false;
        result = result || ((std::get<0>(info) == BOTH || std::get<0>(info) == ValidStep::BY_ONE) ? part2helper(index+1, std::get<1>(info), levels, fault_used): false);
        result = result || ((std::get<0>(info) == BOTH || std::get<0>(info) == BY_TWO) ? part2helper(index+2, std::get<2>(info), levels, true): false);
        return result;
    }
}

void part2() {
    std::ifstream file_reader;
    std::string line_store;
    file_reader.open("Data/Day_2.txt");
    int counter = 0;
    while (std::getline(file_reader, line_store)) {
        std::istringstream iss(line_store);
        std::string temp;
        std::vector<int> levels;
        while(std::getline(iss, temp, ' ')) {
            levels.push_back(std::stoi(temp));
        }
        if(part2helper(-1, Ordering::UNKNOWN, levels, false)){
            counter++;
        }
    }
    std::cout << "result: " << counter << std::endl;
}
