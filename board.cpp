#include<cstdio>

const int INF = 10000000;


int WhiteBoard[] = 
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1
}; 

int BlackBoard[] = 
{
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
}; 

enum ChessPieceValue{
    Pawn = 1,
    Bishop = 3, 
    Knight = 3,
    Rook = 5,
    Queen = 9, 
    King = 10000
};

enum Color{
    White = 1, Black = 0
};

bool InBoard(int position){
    return position >= 0 && position <= 63;
}

template<class Status, class T> // Status = 1 if white else black 
std::vector<int> MovePiece(T&& direct_move, int position, int limit_times){
    // if limit_times = INF, it is I don limit time move
    std::vector<int> next_position;
    int count_times = 0;
    for(int i = 0; i < direct_move.size(); ++i){ 
        int cur_pos = position;
        cur_pos += direct_move[i];
        while(InBoard(cur_pos) && count_times < limit_times){
            next_position.push_back(cur_pos);
            cur_pos += direct_move[i];
            count_times++;
            if(WhiteBoard(cur_pos) != 0 || BlackBoard(cur_pos) != 0)
                break;
        }
    }
    return next_position;
}

class King{
    private:
        int position;
    public:
        King(int pos): position(pos) {}
        int getPosition() const { return position; }
        std::vector<int> move(){
            const int direct_move[] = {-9, -8, -7, -1, 1, 7, 8, 9};
            return MovePiece(direct_move, pos, 1);
        }
}
class Queen{
    int position;
    Queen(int pos): position(pos) {}
    int getPosition() const { return position; }
    std::vector<int> move(){
        const int direct_move[] = {-9, -8, -7, -1, 1, 7, 8, 9};
        std::vector<int> next_position;
        return MovePiece(direct_move, pos, INF);
    }
}
class Rook{
    int position;
    Queen(int pos): position(pos) {}
    int getPosition() const { return position; }

    std::vector<int> move(){
        const int direct_move[] = {-8, -1, 1, 8};
        return MovePiece(direct_move, pos, INF);
    }
}
class Knight{
    int position;
    Knight(int pos): position(pos) {}
    int getPosition() const { return position; }

    std::vector<int> move(){
        const int direct_move[] = {-9, -8, -7, -1, 1, 7, 8, 9};
        std::vector<int> next_position;

        for(auto& cur_direct : direct_move){
            int cur_pos = position;
            cur_pos += cur_direct;
            while(InBoard(cur_pos)){
                next_position.push_back(cur_pos);
                cur_pos += cur_direct;
                if(WhiteBoard(cur_pos) != 0 || BlackBoard(cur_pos) != 0)
                    break;
            }
        }
    } 
}
class Bishop{
    int position;
    Bishop(int pos): position(pos) {}
    int getPosition() const { return position; }

    std::vector<int> move(){
        const int direct_move[] = {-9, -7, 7, 9};
        return MovePiece(direct_move, position, INF);
    } 
}

class Bishop{
    int position;
    bool status; // status = 1 if white else black
    
    Bishop(int pos, bool status): position(pos), status(status) {}
    int getPosition() const { return position; }

    std::vector<int> move(){

    } 
}

class Board{
private:
    std::vector<Pawn>   wPawn,   bPawn;
    std::vector<Bishop> wBishop, bBishop;
    std::vector<Knight> wKnight, bKnight;
    std::vector<Rook>   wRook,   bRook;
    std::vector<Queen>  wQueen,  bQueen;
    King                wKing,   bKing;

public:
    void init(){
        
    }
};