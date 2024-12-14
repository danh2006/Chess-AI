
#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <cstdint>


std::string encode(int16_t position){
    int x = position / 8, y = position % 8;
    x = 7 - x;
    std::string ret_str;
    ret_str += char(y + 'a');
    ret_str += char(x + 1 + '0');
    return ret_str;
}


std::vector<int16_t> parse(){
    std::vector<int16_t> record;
    std::string input;
    while(std::getline(std::cin, input)){
        if(input == "END") break;
        // assert(input[2] == ' ');
        if(input == "O-O"){
            record.emplace_back(-1);
            record.emplace_back(-1);
            continue;
        }
        if(input == "O-O-O"){
            record.emplace_back(-2);
            record.emplace_back(-2);
            continue;
        }
        auto from = (8 - int(input[1] - '0')) * 8 +  int(input[0] - 'a');
        auto to   = (8 - int(input[4] - '0')) * 8 +  int(input[3] - 'a');
        record.emplace_back(from);
        record.emplace_back(to);
    }
    return record;
}
