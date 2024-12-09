#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <unordered_map>

int part_one();
int part_two();

int main() {
    std::string input;
    std::cout << "Part one or Part two? (1/2): ";
    std::cin >> input;
    std::cout << "You said \"" << input << "\"\n";
    if (input.compare("1") == 0) {
        int result = part_one();
        std::cout << "result: " << result << "\n";
    } else if (input.compare("2") == 0) {
        int result = part_two();
        std::cout << "result: " << result << "\n";
    }
}

int part_two() {
    std::ifstream myfile;
    myfile.open("Data/Day_1.txt");
    std::unordered_map<int, int> locations_one;
    std::unordered_map<int, int> locations_two;
    std::string temp;
    while(true) {
        myfile >> temp;
        if (myfile.eof()) break;
        std::unordered_map<int, int>::iterator loc_temp = locations_one.find(std::stoi(temp));
        if (loc_temp == locations_one.end()) {
            locations_one[std::stoi(temp)] =  0;
        }
        ++locations_one[std::stoi(temp)];
        // std:: cout << temp << " " << locations_one.at(std::stoi(temp)) << "; ";

        myfile >> temp;
        loc_temp = locations_two.find(std::stoi(temp));
        if (loc_temp == locations_two.end()) {
             locations_two[std::stoi(temp)] =  0;
        }
        ++locations_two[std::stoi(temp)];
        // std:: cout << temp << " " << locations_two.at(std::stoi(temp)) << ";" << myfile.good() << "\n";
    }
    myfile.close();
    int result = 0;
    for (std::pair<int, int> curr : locations_one) {
        std::unordered_map<int, int>::iterator loc_temp = locations_two.find(curr.first);
        if (loc_temp != locations_two.end()) {
            // std::cout << loc_temp->first << " appears " << loc_temp->second << " times in the second list and " << curr.second << " times in the first list.\n";
            result += loc_temp->first * loc_temp->second * curr.second;
        }
    }

    return result;
}

int part_one() {
    std::ifstream myfile;
    myfile.open("Data/Day_1.txt");
    std::string temp;
    std::vector<int> location_id1{};
    std::vector<int> location_id2{};
    while(myfile) {
        myfile >> temp;
        // std::cout << temp << " " << std::stoi(temp) << "; ";
        location_id1.push_back(std::stoi(temp));
        myfile >> temp;
        // std::cout << temp << " " << std::stoi(temp) << " \n";
        location_id2.push_back(std::stoi(temp));
    }
    std::sort(location_id1.begin() ,location_id1.end());
    std::sort(location_id2.begin(), location_id2.end());
    std::vector<int>::iterator iter1 = location_id1.begin();
    std::vector<int>::iterator iter2 = location_id2.begin();
    int result = 0;
    while(iter1 != location_id1.end() && iter2 != location_id2.end()) {
        result += std::abs(*iter1 - *iter2);
        iter1++; iter2++;
    }
    myfile.close();
    return result;
}
