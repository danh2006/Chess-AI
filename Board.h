#pragma once
#include <algorithm>
#include "PGN.h"
#include "Error.h"
#include "Piece.h"
#include "GenMove.h"
#include "Evaluate.h"
#include "MoveInfo.h"
#include "Hash.h"


enum Color {
     White = 1,
     Black = 0
};

enum Castle{
     Kingside = 0,
     Queenside = 1
};

class Board {
public:
     int16_t board[64];
     MoveInfo last_move;
     int16_t score;
     int16_t cnt_move;
     bool white_can_kingside_castle;
     bool white_can_queenside_castle;
     bool black_can_kingside_castle;
     bool black_can_queenside_castle;
     bool side;
     uint64_t hash_value;

     void hash_board();
     void init();
     Board operator=(Board& rhs);
     bool is_empty(int16_t position);
     bool is_white(int16_t position);
     bool is_black(int16_t position);
     bool can_promotion(int16_t from, int16_t to);
     bool is_valid_move(int16_t position);
     bool can_kingside_castle();
     bool can_queenside_castle();
     void kingside_castle();
     void queenside_castle();
     void change_castle_info(int16_t from);
     void set_castled();
     int16_t  get_score();
     uint64_t get_hash_key();
     bool     get_side();
     int16_t& operator[](int16_t idx);
     const int16_t& operator[](int16_t idx) const;
     template<class H> auto get_piece_score(H&& evaluate_board, int16_t position);
     std::vector<int16_t> get_all_move_pos(int16_t position);
     auto& get_evaluate_board(int16_t position);
     int16_t evaluate_score(int16_t from, int16_t to);
     int16_t get_attack_value(int16_t from, int16_t to);
     void update_move_info();
     void change_piece_position(int16_t from, int16_t to);
     void simulation(std::vector<int16_t>& command);
     void display();
};

