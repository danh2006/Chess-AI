#include <cstdint>
#include <string>
#include <cmath>
#include <stdexcept>


enum ChessPieceValue{
    Pawn   = 100,
    Knight = 320,
    Bishop = 325, 
    Rook   = 500,
    Queen  = 950, 
    King   = 10000,
    Empty  = 0
};

int16_t get_piece_index(int piece_value) {
     int absolute_piece_value = std::abs(piece_value);
     switch (absolute_piece_value) {
          case King:   return 0;
          case Queen:  return 1;
          case Rook:   return 2;
          case Bishop: return 3;
          case Knight: return 4;
          case Pawn:   return 5;
     }
     return 0;
}

std::string get_piece_unicode_symbol(int16_t piece_value) {
     int absolute_piece_value = std::abs(piece_value);
     switch (absolute_piece_value) {
          case King:   return "♚";
          case Queen:  return "♛";
          case Rook:   return "♜";
          case Knight: return "♞";
          case Bishop: return "♝";
          case Pawn:   return "♟";
          case Empty:  return "♢ ";
          default:     
               throw std::invalid_argument("Unsupported piece value");
     }
}

std::string get_piece_symbol(int piece_value) {
     switch (piece_value) {
          case Pawn:   return "P";
          case -Pawn:  return "p";
          case Knight: return "N";
          case -Knight:return "n";
          case Bishop: return "B";
          case -Bishop:return "b";
          case Rook:   return "R";
          case -Rook:  return "r";
          case Queen:  return "Q";
          case -Queen: return "q";
          case King:   return "K";
          case -King:  return "k";
          default:     
               throw std::invalid_argument("Unsupported piece value");
     }
}

int16_t get_piece_value_by_symbol(char piece_symbol) {
     switch (piece_symbol) {
          case 'P': return Pawn;
          case 'p': return -Pawn;
          case 'N': return Knight;
          case 'n': return -Knight;
          case 'B': return Bishop;
          case 'b': return -Bishop;
          case 'R': return Rook;
          case 'r': return -Rook;
          case 'Q': return Queen;
          case 'q': return -Queen;
          case 'K': return King;
          case 'k': return -King;
          default:  
               throw std::invalid_argument("Unsupported piece symbol");
     }
}
