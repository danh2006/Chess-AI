#include<cstdio>
#include"Piece.h"


class Board{
private:
    std::vector<Pawn>   wPawn,   bPawn;
    std::vector<Bishop> wBishop, bBishop;
    std::vector<Knight> wKnight, bKnight;
    std::vector<Rook>   wRook,   bRook;
    std::vector<Queen>  wQueen,  bQueen;
    King                wKing,   bKing;

    bool turn;


public:
    void init(){
        wKing(Point(7, 4)); bKing({0, 4});
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

    // auto& select(int piece_value){
    //     switch(piece_value):
    //         case Queen:  return turn ? &wQueen  : &bQueen;
    //         case Rook:   return turn ? &wRook   : &bRook;
    //         case Bishop: return turn ? &wBishop : &bBishop;
    //         case Knight: return turn ? &wKnight : &bKnight;
    //         case Pawn:   return turn ? &wPawn   : &bPawn;
    //         // case King      
    // }

    void simulation(std::vector<Point>& command){
        for(int i = 0; i < command.size(); i += 2){
            auto& src = ;
            auto& dst = ;
            assert(src != EMPTY && dst == EMPTY);
            src = dst;
            dst = EMPTY;
            turn ^= 1;
        }
    }
    
    template<class T>
    auto check_move(T&& pieces, Point& position){
        // piece we need to check
        auto piece = *find_if(pieces.begin(), pieces.end(), [&](auto& p){
            return p.position == position;
        }); 
        return piece.move == false; 
    }

    auto can_kingside_castle(auto&& board, auto& row){ // kiem tra xem co the nhap thanh gan khong
        for(int i = 1; i <= 2; ++i){
            if(WhiteBoard[GetIdx(row, 7 - i)] || BlackBoard[GetIdx(row, 7 - i)])
                return false;
        }
        // kiem tra xem cac quan co nay da di chuyen chua
        return board[GetIdx(row, 7)] == Rook && board[GetIdx(row, 4)] == King &&
               checkMove(turn ? wRook : bRook, Point(row, 7)) && 
               checkMove(turn ? wKing : bKing, Point(row, 4));
    }

    auto can_queenside_castle(auto&& board, auto& row){ // kiem tra xem co the nhap thanh xa khong
        for(int i = 1; i <= 3; ++i){
            if(WhiteBoard[GetIdx(row, i)] || BlackBoard[GetIdx(row, i)])
                return false;
        }
        // kiem tra xem cac quan co nay da di chuyen chua
        return board[GetIdx(row, 0)] == Rook && board[GetIdx(row, 4)] == King &&
               checkMove(turn ? wRook : bRook, Point(row, 0)) && 
               checkMove(turn ? wKing : bKing, Point(row, 4));
    }

    std::vector<Point> castle(){
        auto& board = turn ? WhiteBoard : BlackBoard;
        auto  row   = turn ? 8 : 1;  
        if(can_kingside_castle(board, row))

        if(can_queenside_castle(board, row))

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
