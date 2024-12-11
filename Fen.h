#include "Board.h"



#define FORMAT_ERROR(condition) if(!(condition)) mes_error("format error");

class Fen {
private:
     Board board;

     std::string get_info(std::string source, size_t& ptr) {
          std::string info;
          for (; ptr < source.size() && source[ptr] != ' '; ++ptr) {
               info += source[ptr];
          }
          return info;
     }

     void set_board_value(std::string board_info) {
          size_t length = 0;
          for (int i = 0; length < 64 && i < std::size(board_info); ++i) {
               if (board_info[i] == '/') continue;
               if (isdigit(board_info[i])) {
                    auto n_empty_square = int(board_info[i] - '0');
                    length += n_empty_square;
               } else {
                    board[length] = get_piece_value_by_symbol(board_info[i]);
                    board.score += board[length] + board.get_piece_score(board[length]);
                    length += 1;
               }
          }
          FORMAT_ERROR(length == 64);
     }

     void set_player_side(std::string player_side) {
          FORMAT_ERROR(player_side == "w" || player_side == "b");
          if (player_side == "w")
               board.side = White;
          else
               board.side = Black;
     }

     void set_castle_info(std::string castle_info) {
          board.white_can_kingside_castle  = castle_info.find("K") != castle_info.npos;
          board.white_can_queenside_castle = castle_info.find("Q") != castle_info.npos;
          board.black_can_kingside_castle  = castle_info.find("k") != castle_info.npos;
          board.black_can_queenside_castle = castle_info.find("q") != castle_info.npos;
     }

     void set_en_passent(std::string en_passent_info) {
          // Implementation needed
     }

     void get_board_value(std::string& fen) {
          int n_empty_square = 0;
          for (int pos = 0; pos < 64; ++pos) {
               if (board[pos] != Empty) {
                    if (n_empty_square > 0) {
                         fen += std::to_string(n_empty_square);
                         n_empty_square = 0;
                    }
                    fen += get_piece_symbol(board[pos]);
               } else {
                    n_empty_square++;
               }
               if ((pos + 1) % 8 == 0) {
                    if (n_empty_square > 0) {
                         fen += std::to_string(n_empty_square);
                         n_empty_square = 0;
                    }
                    if (pos != 63) fen += "//";
               }
          }
          fen += ' ';
     }

     void get_player_side(std::string& fen) {
          fen += board.side == White ? "w " : "b ";
     }

     void get_castle(std::string& fen) {
          if (board.white_can_kingside_castle)
               fen += "K";
          if (board.white_can_queenside_castle)
               fen += 'Q';
          if (board.black_can_kingside_castle)
               fen += "k";
          if (board.black_can_queenside_castle)
               fen += 'q';
          if (fen.back() == ' ') fen += '-';
          fen += ' ';
     }

public:
     void load_data() {
          std::string input;
          std::getline(std::cin, input);

          size_t ptr = 0;
          set_board_value(get_info(input, ptr));
          set_player_side(get_info(input, ptr));
          set_castle_info(get_info(input, ptr));
          // set_en_passent(get_info(input, ptr));
          // set_half_move(get_info(input, ptr));
          // set_full_move(get_info(input, ptr));
     }

     auto set_board(Board& other) { board = other; }
     auto get_board() { return board; }

     auto get_fen() {
          std::string fen;
          get_board_value(fen);
          get_player_side(fen);
          get_castle(fen);
          fen += "- 0 0";
          return fen;
     }
};
