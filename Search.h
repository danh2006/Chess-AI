#pragma once
#include "Board.h"
#include "Transposition.h"


size_t cnt_node;

auto get_depth(int depth, int possible_move){
    if(possible_move <= 16)
        depth += 2;
    return depth;
}

// auto Quiescence(Board& examine_board, int alpha, int beta, int depth){
//     int  score = examine_board.get_score();
//     bool turn  = examine_board.turn;
//     cnt_node++;

//     if(score >= beta)
//         return beta;

//     alpha = std::max(alpha, score);

//     if(depth == 0 || score >= 5000){
//         alpha = score;
//         return alpha;
//     }

//     if(examine_board.cnt_move >= 100){ // draw rule when going more than 50 steps
//         alpha = 0;
//         return 0;
//     }

//     std::vector<MoveInfo> move_list;
//     move_list.reserve(40);

//     for(int from = 0; from < 64; ++from){
//         if(examine_board.is_empty(from))
//             continue;

//         if((turn == White && examine_board.is_black(from)) || 
//            (turn == Black && examine_board.is_white(from)))
//             continue;

//         const std::vector<int16_t> move_position = examine_board.get_all_move_pos(from);

//         for(auto& to : move_position){
//             if(abs(examine_board[to]) > Pawn){
//                 move_list.emplace_back(from, to);
//             }
//         }
//     }

//     auto& attack_value_func = examine_board.get_attack_value;
//     std::sort(move_list.begin(), move_list.end(), [&attack_value_func](MoveInfo& lhs, MoveInfo& rhs){
//         return attack_value_func(lhs) > attack_value_func(rhs);
//     });
//     for(auto& [from, to, move_score] : move_list){
//         Board board = examine_board;
//         board.change_piece_position(from, to);
//         int result_score = -Quiescence(board, -beta, -alpha, depth - 1);

//         if(result_score >= beta)
//             return beta;

//         alpha = std::max(alpha, result_score);
//     }
//     // If no moves are available, return the current score
//     return alpha;
// }

TranspositionTable table;

int alpha_beta(Board& examine_board, int alpha, int beta, int depth, MoveInfo& move_info, bool extended){
    static MoveInfo killer_moves[2][64];
    auto score = examine_board.get_score();
    bool side  = examine_board.get_side();
    auto key   = examine_board.get_hash_key();
    cnt_node++;

    if(depth == 0 || score >= 5000){
        alpha = score;
        return alpha;
    }

    auto evaluate_move = [&](int from, int to) {
        Board board = examine_board;
        MoveInfo next_move_info;
        board.change_piece_position(from, to);
        int result_score = -alpha_beta(board, -beta, -alpha, depth - 1, next_move_info, extended);

        if(result_score >= beta){
            table.store(key, depth, beta, LOWER_BOUND);
            return beta;
        }

        if(result_score > alpha){
            move_info = board.last_move;
            alpha     = result_score;
        }
        return alpha;
    };

    auto table_entry = table.get_entry(key);
    if(key == table_entry.key && table_entry.depth >= depth){ 
        if(table_entry.flag == EXACT){
            return table_entry.score;
        }
        if(table_entry.flag == UPPER_BOUND && table_entry.score <= alpha){
            return alpha;
        }
        if(table_entry.flag == LOWER_BOUND && table_entry.score >= beta){
            return beta;
        }
        // auto tt_moves = examine_board.get_all_move_pos(table_entry.from);
    }

    // auto try_castling = [&](auto castling_func) {
    //     Board board = examine_board;
    //     MoveInfo next_move_info;
    //     castling_func();
    //     board.set_castled();
    //     int result_score = -alpha_beta(board, -beta, -alpha, depth - 1, next_move_info, extended);

    //     if(result_score >= beta)
    //         return beta;

    //     if(result_score > alpha){
    //         move_info = board.last_move;
    //         alpha = result_score;
    //     }
    // };

    // if(examine_board.can_kingside_castle()){
    //     try_castling([&] { return examine_board.kingside_castle(); });
    // }
    // if(examine_board.can_queenside_castle()){
    //     try_castling([&] { return examine_board.can_queenside_castle(); });
    // }

    std::vector<MoveInfo> captured_moves;
    std::vector<int16_t> moves[64];
    captured_moves.reserve(30);

    int previous_alpha = alpha;

    for(int from = 0; from < 64; ++from){
        if(examine_board.is_empty(from) || !examine_board.is_valid_move(from))
            continue;

        moves[from] = examine_board.get_all_move_pos(from);
        for(auto& to : moves[from]){
            if(examine_board[to] != 0){
                auto attack_value = examine_board.get_attack_value(from, to);
                captured_moves.emplace_back(from, to, attack_value);
            }
        }
    }

    std::sort(captured_moves.begin(), captured_moves.end(), std::greater<>());

    for(auto& [from, to, score] : captured_moves){
        alpha = evaluate_move(from, to);
        if(alpha >= beta) return beta;
    }

    // Try killer moves first
    for(int i = 0; i < 2; ++i){
        MoveInfo& killer_move = killer_moves[i][depth];
        if(!examine_board.is_valid_move(killer_move.from)) 
            continue;

        for(auto& move : moves[killer_move.from]){
            if(move == killer_move.to){
                alpha = evaluate_move(killer_move.from, killer_move.to);
                if(alpha >= beta) return beta;                                                         
            }                                                                                                                                                                           
        }                                                                                                                                                                             
    }

    for(int from = 0; from < 64; ++from){
        for(const auto& to : moves[from]){
            alpha = evaluate_move(from, to);
            if(alpha >= beta){
                killer_moves[1][depth] = killer_moves[0][depth];
                killer_moves[0][depth] = MoveInfo(from, to);
                return beta;
            }
        }
    }

    if(previous_alpha < alpha){
        table.store(key, depth, alpha, EXACT);
    }
    else{
        table.store(key, depth, alpha, UPPER_BOUND);
    }
    return alpha;
}


// upper lower
void iterative_deepening(Board& examine_board, int max_depth, MoveInfo& best_move) {
    for(auto& depth : std::vector{3, 4, 5, max_depth} ){
        alpha_beta(examine_board, -10000, 10000, depth, best_move, false);
    }
}