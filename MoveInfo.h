#include <iostream>
#include <string>


struct MoveInfo{
    int16_t from, to;
    int16_t score;

    MoveInfo() = default;
    MoveInfo(int16_t from, int16_t to, int16_t score = 0): from(from), to(to), score(score) {} 

    MoveInfo& operator=(const MoveInfo& rhs){
        from  = rhs.from;
        to    = rhs.to;
        score = rhs.score; 
        return *this;
    }
    bool operator < (const MoveInfo& rhs) const{ return score < rhs.score; }
    bool operator > (const MoveInfo& rhs) const{ return score > rhs.score; }

    std::string get_command(){
        if(from == -1) return "O-O";
        if(from == -2) return "O-O-O";
        auto start_pos = encode(from);
        auto end_pos   = encode(to);
        std::string command = start_pos + " " + end_pos;
        return command;
    }

    friend std::istream& operator>>(std::istream& is, MoveInfo& move_info){
        is >> move_info.from >> move_info.to;
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const MoveInfo& move_info){
        os << move_info.from << " " << move_info.to;
        return os;
    }
};
