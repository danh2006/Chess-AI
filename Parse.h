#include<vector>
#include"Point.h"

// int en_code(){
    
// }

std::vector<Point> parse(){
    std::vector<Point> record;
    std::string input;
    while(std::getline(std::cin, input)){
        if(input == "END") break;
        record.push_back(Point(int(input[0] - 'a') + 1, int(input[1] - '0')));
        record.push_back(Point(int(input[3] - 'a') + 1, int(input[4] - '0')));
    }
    return record;
}
signed main(){
    // default_file();
    std::vector<Point> record = parse();
    // for(auto& p : record)
    //     std::cout << p;
    return 0;
}