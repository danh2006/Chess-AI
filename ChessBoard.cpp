#include<cstdio>
#include"ChessPiece.h"


class Board{
private:
    std::vector<Pawn>   wPawn,   bPawn;
    std::vector<Bishop> wBishop, bBishop;
    std::vector<Knight> wKnight, bKnight;
    std::vector<Rook>   wRook,   bRook;
    std::vector<Queen>  wQueen,  bQueen;
    King                wKing,   bKing;

    bool    turn;
    int     alpha;
    int     beta;
    short   depth;
    times_t times; 

public:
    void init(){
        wKing({7, 4}); bKing({0, 4});
        for(int y = 0; y < 8; ++y){
            wPawn.push_back(Point(6, y));
            bPawn.push_back(Point(1, y));
        }
        wQueen  = {{7, 3}}; bQueen = {{0, 3}};
        wRook   = {{7, 0}, {7, 7}};
        bRook   = {{0, 0}, {0, 7}};
        wKnight = {{7, 1}, {7, 6}};
        bKnight = {{0, 1}, {0, 6}};
        wBishop = {{7, 2}, {7, 5}};
        bBishop = {{0, 2}, {0, 5}};
    }

    template<class T> auto& choose(T&& param_one, T&& param_two){
        return turn == White ? param_one : param_two;
    }
    template<class Func, class Ranges, class T> 
    auto make(Func&& func, Ranges&& range, T&& paramType){
        return func(range.begin(), range.end(), paramType);
    }
    template<class Func, class T> 
    auto select(Func&& func, int piece_value, bool side, T&& paramType){
        // [&](){ 
            switch(piece_value) { 
                case Queen:  
                    return make(func, side ? wQueen  : bQueen,  paramType); 
                case Rook:   
                    return make(func, side ? wRook   : bRook,   paramType); 
                case Bishop:  
                    return make(func, side ? wBishop : bBishop, paramType); 
                case Knight: 
                    return make(func, side ? wKnight : bKnight, paramType); 
                case Pawn:   
                    return make(func, side ? wPawn   : bPawn,   paramType); 
                default:     
                    assert(false); 
            } 
        // }() 
    }

    template<class T> 
    void change_position_piece(T&& src, T&& dst, Point& srcPosition, Point& dstPosition){
        
        auto& pieceMovePosInList = select(find, src, turn, srcPosition);
             *pieceMovePosInList = dstPosition; 

        if(dst != Empty){
            auto& pieceCapturePosInList = select(find, dst, !turn, dstPosition);
            *pieceCapturePosInList = Point(Empty, Empty);
        }

        src = dst;
    }

    void simulation(std::vector<Point>& command){
        for(int i = 0; i < command.size() && turn ^= 1; i += 2){
            auto& board = choose(WhiteBoard, BlackBoard);
            auto& src   = board[GetIdx(comand[i])];
            auto& dst   = board[GetIdx(command[i + 1])];
            change_position_piece(&src, &dst, command[i], command[i+1]);
        }
    }

    template<class T>
    auto check_move(T&& pieces, Point& position){
        // piece we need to check
        auto piece = *find_if(pieces.begin(), pieces.end(), [&](auto& p){
            return p.position == position;
        }); 
        return piece.moved == false; 
    }

    auto can_kingside_castle(auto&& board, auto& row){ // kiem tra xem co the nhap thanh gan khong
        for(int i = 1; i <= 2; ++i){
            if(WhiteBoard[GetIdx(row, 7 - i)] || BlackBoard[GetIdx(row, 7 - i)])
                return false;
        }
        // kiem tra xem cac quan co nay da di chuyen chua
        return board[GetIdx(row, 7)] == Rook && board[GetIdx(row, 4)] == King &&
               check_move(turn ? wRook : bRook, Point(row, 7)) && 
               check_move(turn ? wKing : bKing, Point(row, 4));
    }

    auto can_queenside_castle(auto&& board, auto& row){ // kiem tra xem co the nhap thanh xa khong
        for(int i = 1; i <= 3; ++i){
            if(WhiteBoard[GetIdx(row, i)] || BlackBoard[GetIdx(row, i)])
                return false;
        }
        // kiem tra xem cac quan co nay da di chuyen chua
        return board[GetIdx(row, 0)] == Rook && board[GetIdx(row, 4)] == King &&
               check_move(turn ? wRook : bRook, Point(row, 0)) && 
               check_move(turn ? wKing : bKing, Point(row, 4));
    }

    std::vector<Point> castle(){
        auto& board = turn ? WhiteBoard : BlackBoard;
        auto  row   = turn ? 7 : 0;  
        if(can_kingside_castle(board, row))

        if(can_queenside_castle(board, row))

    }

    auto set_depth(int16_t _depth){
        depth = _depth;
    } 
    
    auto set_times(time_t max_times){
        times = max_times;
    }

    auto minimax(){
        
    }

    void best_next_move(){
        auto command = minimax();
        cout << en_code(command) << endl;
    }
/*
    std::vector<Point> get_all_next_pos_enemy(){

    }
    bool is_end_game(){

    }
*/
    void display(){
        std::vector<std::string> printWindow(64, "♢ ");
        
        // King
        printWindow[GetIdx(wKing)] = printWindow[GetIdx(bKing)] = "♚";
        
        // Queen
        for(auto& queen : wQueen)
            printWindow(GetIdx(q)) = "♛";
        for(auto& queen : wQueen)
            printWindow(GetIdx(q)) = "♛";

        // Rook
        for(auto& rook : wRook)
            printWindow(GetIdx(rook)) = "♜";
        for(auto& rook : bRook)
            printWindow(GetIdx(rook)) = "♜";
        
        // Bishop
        for(auto& bishop : wBishop)
            printWindow(GetIdx(bishop)) = "♝";
        for(auto& bishop : bBishop)
            printWindow(GetIdx(bishop)) = "♝";
        
        // Knight
        for(auto& knight : wKnight)
            printWindow(GetIdx(knight)) = "♞";
        for(auto& knight : bKnight)
            printWindow(GetIdx(knight)) = "♞";
           
        // Pawn
        for(auto& pawn : wPawn)
            printWindow(GetIdx(pawn)) = "♟";
        for(auto& pawn : bPawn)
            printWindow(GetIdx(pawn)) = "♟";

        for(int i = 0; i < 63; ++i){
            cout << printWindow[i];
            if(i % 8 == 0) cout << "\n";
        }
    }
};

int main(){

    auto record = parse();
    Board board; 
    board.init();
    board.simulation(record);
    board.minimax();
    board.best_next_move();
    board.display();
}
