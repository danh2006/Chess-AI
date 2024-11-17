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
        for(int y = 1; y = 8; ++y){
            wPawn.push_back(Point(2, y));
            bPawn.push_back(Point(7, y));
        }
        wKing(1, ); bKing(8, );
        wQueen.push_back(1, ); bKing(8, );
        wRook(1, 1); wRook(1, 8);
        bRook(8, 1); bRook(8, 8);
        wBishop(1, 2); wBishop(1, 7);
        bBishop(8, 2); bBishop(8, 7);
        wKnight(1, 3); wKnight(1, 6);
        bKnight(8, 3); bKnight(8, 6);
    }

    // cuu chua kieu gi day
    auto& select(int piece_value){
        switch(piece_value):
            case Queen:  return turn ? &wQueen  : &bQueen;
            case Rook:   return turn ? &wRook   : &bRook;
            case Bishop: return turn ? &wBishop : &bBishop;
            case Knight: return turn ? &wKnight : &bKnight;
            case Pawn:   return turn ? &wPawn   : &bPawn;
            // case King      
    }

    void simulation(std::vector<Point>& command){
        for(int i = 0; i < command.size(); i += 2){
            auto& src = turn ;
            auto& dst = ;
            assert(src != EMPTY && dst == EMPTY);
            src = dst;
            dst = EMPTY;
            turn ^= 1;
        }
    }
    
    auto check_move(int piece_value, std::vector<Point>& point){
        auto& pieces = select(piece_value);
        // piece we need to check
        auto piece = *find(pieces.begin(), pieces.end(), point); 
        return piece.move == false; 
    }
    auto can_kingside_castle(auto&& board, auto& row){ // kiem tra xem co the nhap thanh gan khong
        for(int i = 1; i <= 2; ++i){
            if(WhiteBoard[GetIdx(row, 7 - i)] || BlackBoard[GetIdx(row, 7 - i)])
                return false;
        }
        // kiem tra xem cac quan co nay da di chuyen chua
        return board[GetIdx(row, 7)] == Rook && board[GetIdx(row, 4)] == King &&
               (*std::ranges::find(Rook, Point(row, 7))).move == false &&
               (*std::ranges::find(King, Point(row, 4))).move == false;
    }
    auto can_queenside_castle(auto&& board, auto& row){ // kiem tra xem co the nhap thanh xa khong
        for(int i = 1; i <= 3; ++i){
            if(WhiteBoard[GetIdx(row, i)] || BlackBoard[GetIdx(row, i)])
                return false;
        }
        // kiem tra xem cac quan co nay da di chuyen chua
        return board[GetIdx(row, 0)] == Rook && board[GetIdx(row, 4)] == King &&
               (*std::ranges::find(Rook, Point(row, 0))).move == false &&
               (*std::ranges::find(King, Point(row, 4))).move == false;
    }

    std::vector<Point> castle(){
        auto& board = turn ? WhiteBoard : BlackBoard;
        auto  row   = turn ? 8 : 1;  
        if(can_kingside_castle(board, row))

        if(can_queenside_castle(board, row))

    }

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
