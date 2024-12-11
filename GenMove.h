#pragma once
#include <vector>
#include <cstdio>


const int INF = 1e9;

/**
 * Sets the direction index for a given direction.
 */
void set_direct_index(int16_t direct, int16_t& dx, int16_t& dy){
    switch(direct){
        case -17: dx = -2, dy = -1; break;
        case -15: dx = -2, dy =  1; break;
        case -10: dx = -1, dy = -2; break;
        case  -6: dx = -1, dy =  2; break;
        case   6: dx =  1, dy = -2; break;
        case  10: dx =  1, dy =  2; break;
        case  15: dx =  2, dy = -1; break;
        case  17: dx =  2, dy =  1; break;
        case  -9: dx = -1, dy = -1; break;
        case  -8: dx = -1, dy =  0; break;
        case  -7: dx = -1, dy =  1; break;
        case  -1: dx =  0, dy = -1; break;
        case   1: dx =  0, dy =  1; break;
        case   7: dx =  1, dy = -1; break;
        case   8: dx =  1, dy =  0; break;
        case   9: dx =  1, dy =  1; break;
    }
}

/**
 * Generates possible moves for a piece on the board.
 * @param board The current state of the chess board.
 * @param direct The directions in which the piece can move.
 * @param src_pos The source position of the piece.
 * @param max_times The maximum number of steps the piece can move in one direction.
 * @return A vector of possible move positions.
 */
template<class T, class H> 
std::vector<int16_t> piece_move(T&& board, H&& direct, int16_t src_pos, int max_times) {
    std::vector<int16_t> move_position;
    move_position.reserve(max_times == 1 ? 3 : 7);

    const int16_t src_row = src_pos >> 3;
    const int16_t src_col = src_pos & 7;
    
    for(int i = 0; i < std::size(direct); ++i){
        int16_t dx, dy;
        set_direct_index(direct[i], dx, dy);

        int16_t position = src_pos;
        int16_t cur_row  = src_row;
        int16_t cur_col  = src_col;

        position += direct[i]; 
        cur_row  += dx;
        cur_col  += dy;

        for(int cnt_times = 1; cnt_times <= max_times; ++cnt_times){
            if(!(cur_row >= 0 && cur_row <= 7 && cur_col >= 0 && cur_col <= 7))
                break;

            if(board[position] != 0){
                if((board[position] > 0 && board[src_pos] > 0) || (board[position] < 0 && board[src_pos] < 0))
                    break;
                move_position.emplace_back(position);
                break;
            }else{
                move_position.emplace_back(position);
                position += direct[i];
                cur_row  += dx;
                cur_col  += dy;
            }
        }
    }
    return move_position;
}

template<class T> 
std::vector<int16_t> king_move(T&& board, int16_t position){
    static const int16_t direct[] = {-9, -8, -7, -1, 1, 7, 8, 9};
    return piece_move(board, direct, position, 1);
}

template<class T> 
std::vector<int16_t> queen_move(T&& board, int16_t position){
    static const int16_t direct[] = {-9, -8, -7, -1, 1, 7, 8, 9};
    return piece_move(board, direct, position, INF);
}

template<class T> 
std::vector<int16_t> rook_move(T&& board, int16_t position){
    static const int16_t direct[] = {-8, -1, 1, 8};
    return piece_move(board, direct, position, INF);
}

template<class T> 
std::vector<int16_t> knight_move(T&& board, int16_t position){
    static const int16_t direct[] = {-17, -15, -10, -6, 10, 17, 15, 6};
    return piece_move(board, direct, position, 1);
}


template<class T> 
std::vector<int16_t> bishop_move(T&& board, int16_t position){
    static const int16_t direct[] = {-9, -7, 7, 9};
    return piece_move(board, direct, position, INF);
}

template<class T>
std::vector<int16_t> pawn_move(T&& board, int16_t position){  // side = 1 if white else black
    std::vector<int16_t> move_position;
    const int row = position / 8;
    const int col = position % 8;

    if(board[position] > 0){ // side is White
        if(position >= 8 && board[position - 8] == 0){
            move_position.emplace_back(position - 8);
            if(row == 6 && board[position - 16] == 0){
                move_position.emplace_back(position - 16);
            }
        }
        if(row > 0 && col > 0 && board[position - 9] < 0)
            move_position.emplace_back(position - 9);
        if(row > 0 && col < 7 && board[position - 7] < 0)
            move_position.emplace_back(position - 7);
    }else{
        if(position <= 55 && board[position + 8] == 0){
            move_position.emplace_back(position + 8);
            if(row == 1 && board[position + 16] == 0){
                move_position.emplace_back(position + 16);
            }
        }
        if(row < 7 && col > 0 && board[position + 7] > 0)
            move_position.emplace_back(position + 7);
        if(row < 7 && col < 7 && board[position + 9] > 0)
            move_position.emplace_back(position + 9);
    }
    return move_position;
}