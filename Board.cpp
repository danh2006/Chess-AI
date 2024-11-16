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

    void simulation()
    
    void display(){
        std::vector<std::string> printWindow(64, "♢ ");
        
        auto GetIdx = [&] (Point p){
            return p.x * 8 + y;
        };

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