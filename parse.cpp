#include<iostream>
#include<vector>
#include<cstdint>


int GetIdx(char x, char y){
    return int(x - 'a') * 8 + int(y - '0');
}

int en_code(){
    
}

std::vector<int> parse(){
    std::vector<int> record;
    std::string input;
    while(std::getline(std::cin, input)){
        if(input == "END") break;
        record.push_back(GetIdx(input[0], input[1]));
        record.push_back(GetIdx(input[3], input[4]));
    }
    return record;
}
signed main(){
    // default_file();
    std::vector<int> record = parse();
    return 0;
}