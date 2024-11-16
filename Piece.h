#include"Parse.h"

const int INF = 10000000;

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

bool WhiteBoard[] = 
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

bool BlackBoard[] = 
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


bool InBoard(Point position){
    return position.x >= 1 && position.x <= 8 && 
           position.y >= 1 && position.y <= 8; 
}

template<class T> 
std::vector<Point> MovePiece(T&& direct_move, Point position, int limit_times){
    // if limit_times = INF -> unlimited moves 
    std::vector<Point> next_position;
    int count_times = 0;
    for(int i = 0; i < direct_move.size(); ++i){ 
        Point cur_pos = position;
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
        Point position;
    public:
        King(Point pos): position(pos) {}
        Point getPosition() const { return position; }
        
        std::vector<Point> move(){
            const Point direct_move[] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, 
                                            {0, 1}, {1, -1}, {1, 0}, {1, 1}};
            return MovePiece(direct_move, pos, 1);
        }
}
class Queen{
    private:
        Point position;
    public:
        Queen(Point pos): position(pos) {}
        Point getPosition() const { return position; }

        std::vector<Point> move(){
            const Point direct_move[] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, 
                                        {0, 1}, {1, -1}, {1, 0}, {1, 1}};
            return MovePiece(direct_move, pos, INF);
        }
}
class Rook{
    private:
        Point position;
    public:
        Queen(Point pos): position(pos) {}
        Point getPosition() const { return position; }

        std::vector<Point> move(){
            const Point direct_move[] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
            return MovePiece(direct_move, pos, INF);
        }
}
class Knight{
    private:
        Point position;
    public:
    Knight(Point pos): position(pos) {}
    Point getPosition() const { return position; }

    std::vector<Point> move(){
        const Point direct_move[] = {{-2, -1}, {-1, -2}, {-2, 1}, {-1, 2}
                                      {2, -1}, {1, -2}, {2, 1}, {1, 2}};
        return MovePiece(direct_move, pos, 1);
    } 
}
class Bishop{
    Point position;
    Bishop(Point pos): position(pos) {}
    Point getPosition() const { return position; }

    std::vector<Point> move(){
        const Point direct_move[] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
        return MovePiece(direct_move, position, INF);
    } 
}

class Pawn{
    private:
        Point position;
    public:
        Bishop(Point pos): position(pos) {}
        Point getPosition() const { return position; }

        std::vector<Point> move(bool side){  // side = 1 if white else black
            std::vector<Point> next_position;
            
            auto nxt_pos = position + Point(side == White ? 1 : -1, 0);
            if(InBoard(nxt_pos))
                next_position.push_back(nxt_pos);

            auto [x, y] = position;
            if(side == White){
                if(x - 1 >= 1 && y - 1 >= 1 && BlackBoard[x-1][y-1] != 0)
                    next_position.push_back(Point(x-1, y-1));
                if(x + 1 <= 8 && y - 1 >= 1 && BlackBoard[x+1][y-1] != 0)
                    next_position.push_back(Point(x+1, y-1));
            }
            else{
                if(x - 1 >= 1 && y + 1 <= 8 && WhiteBoard[x-1][y+1] != 0)
                    next_position.push_back(Point(x-1, y+1));
                if(x + 1 <= 8 && y + 1 <= 8 && WhiteBoard[x+1][y+1] != 0)
                    next_position.push_back(Point(x+1, y+1));     
            }  

            return next_position;
        } 
}