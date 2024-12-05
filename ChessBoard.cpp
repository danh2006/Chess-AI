// #include<vector>
// #include<cstdio>
// #include<iostream>
// #include<cstdlib>
// #include<cstdint>
#include<bits/stdc++.h>

using namespace std::chrono;
   
#define default_file() freopen("C:\\Users\\DUC ANH\\Downloads\\Gen\\default\\input.in", "r", stdin);  freopen("C:\\Users\\DUC ANH\\Downloads\\Gen\\default\\output.out ", "w", stdout); 

template<class... T> void debug(T&&... t){ 
    int x = sizeof...(t); 
    ((std::cout << t << (--x ? ", " : "]\n")), ...); 
}
bool debug_flag = false;
bool error_flag = true;
                                                


#define dbg(...) std::cout << "LINE(" << __LINE__ << ") : [" << #__VA_ARGS__ << "] = [", debug(__VA_ARGS__)
#define ifdbg if(debug_flag) 

template<class T>
void mes_error(T&& t){
    if(!error_flag) 
        return;
    std::cout << "Not satisfy the condition: " << t;
    assert(false);
}



const int INF = 10000000;

std::string encode(int16_t position){
    int x = position / 8, y = position % 8;
    x = 7 - x;
    std::string ret_str;
    ret_str += char(y + 'a');
    ret_str += char(x + 1 + '0');
    return ret_str;
}


std::vector<int16_t> parse(){
    std::vector<int16_t> record;
    std::string input;
    while(std::getline(std::cin, input)){
        if(input == "END") break;
        assert(input[2] == ' ');
        auto from = (8 - int(input[1] - '0')) * 8 +  int(input[0] - 'a');
        auto to   = (8 - int(input[4] - '0')) * 8 +  int(input[3] - 'a');
        record.emplace_back(from);
        record.emplace_back(to);
    }
    return record;
}

enum ChessPieceValue{
    Pawn   = 100,
    Knight = 320,
    Bishop = 325, 
    Rook   = 500,
    Queen  = 950, 
    King   = 10000,
    Empty = 0
};

enum Color{
  White = 1, 
  Black = 0
};



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
    bool side = board[position] > 0 ? White : Black;
    const int row = position / 8;
    const int col = position % 8;

    if(side == White){
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
    }
    else{ 
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

namespace Evaluate{ // Evaluate by position
    const int16_t pawn[64] = {
        0,  0,  0,  0,  0,  0,  0,  0,
        50, 50, 50, 50, 50, 50, 50, 50,
        10, 10, 20, 30, 30, 20, 10, 10,
        5,  5, 10, 25, 25, 10,  5,  5,
        0,  0,  0, 20, 20,  0,  0,  0,
        5, -5,-10,  0,  0,-10, -5,  5,
        5, 10, 10,-20,-20, 10, 10,  5,
        0,  0,  0,  0,  0,  0,  0,  0
    };

    const int16_t knight[64] = {
        -50,-40,-30,-30,-30,-30,-40,-50,
        -40,-20,  0,  0,  0,  0,-20,-40,
        -30,  0, 10, 15, 15, 10,  0,-30,
        -30,  5, 15, 20, 20, 15,  5,-30,
        -30,  0, 15, 20, 20, 15,  0,-30,
        -30,  5, 10, 15, 15, 10,  5,-30,
        -40,-20,  0,  5,  5,  0,-20,-40,
        -50,-40,-30,-30,-30,-30,-40,-50
    };

    const int16_t bishop[64] = {
        -20,-10,-10,-10,-10,-10,-10,-20,
        -10,  0,  0,  0,  0,  0,  0,-10,
        -10,  0,  5, 10, 10,  5,  0,-10,
        -10,  5,  5, 10, 10,  5,  5,-10,
        -10,  0, 10, 10, 10, 10,  0,-10,
        -10, 10, 10, 10, 10, 10, 10,-10,
        -10,  5,  0,  0,  0,  0,  5,-10,
        -20,-10,-10,-10,-10,-10,-10,-20
    };

    const int16_t rook[64] = {
        0,  0,  0,  0,  0,  0,  0,  0,
        5, 10, 10, 10, 10, 10, 10,  5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        0,  0,  0,  5,  5,  0,  0,  0
    };

    const int16_t queen[64] = {
        -20,-10,-10, -5, -5,-10,-10,-20,
        -10,  0,  0,  0,  0,  0,  0,-10,
        -10,  0,  5,  5,  5,  5,  0,-10,
        -5,  0,  5,  5,  5,  5,  0, -5,
        0,  0,  5,  5,  5,  5,  0, -5,
        -10,  5,  5,  5,  5,  5,  0,-10,
        -10,  0,  5,  0,  0,  0,  0,-10,
        -20,-10,-10, -5, -5,-10,-10,-20
    };

    const int16_t king[64] = {
        -30,-40,-40,-50,-50,-40,-40,-30,
        -30,-40,-40,-50,-50,-40,-40,-30,
        -30,-40,-40,-50,-50,-40,-40,-30,
        -30,-40,-40,-50,-50,-40,-40,-30,
        -20,-30,-30,-40,-40,-30,-30,-20,
        -10,-20,-20,-20,-20,-20,-20,-10,
        20, 20,  0,  0,  0,  0, 20, 20,
        20, 30, 10,  0,  0, 10, 30, 20
    };

    const int16_t king_end_game[64] = {
        -50,-40,-30,-20,-20,-30,-40,-50,
        -30,-20,-10,  0,  0,-10,-20,-30,
        -30,-10, 20, 30, 30, 20,-10,-30,
        -30,-10, 30, 40, 40, 30,-10,-30,
        -30,-10, 30, 40, 40, 30,-10,-30,
        -30,-10, 20, 30, 30, 20,-10,-30,
        -30,-30,  0,  0,  0,  0,-30,-30,
        -50,-30,-30,-30,-30,-30,-30,-50
    };

    const int16_t flip[64] =  {
        56, 57, 58, 59, 60, 61, 62, 63,
        48, 49, 50, 51, 52, 53, 54, 55,
        40, 41, 42, 43, 44, 45, 46, 47,
        32, 33, 34, 35, 36, 37, 38, 39,
        24, 25, 26, 27, 28, 29, 30, 31,
        16, 17, 18, 19, 20, 21, 22, 23,
        8,  9, 10, 11, 12, 13, 14, 15,
        0,  1,  2,  3,  4,  5,  6,  7,
    };

    const int16_t empty[64] = {0};
}


using Group = std::vector<int16_t>;

// https://rustic-chess.org/search/ordering/mvv_lva.html
namespace Attack{
    const Group pawn     = {10, 11, 12, 13, 14, 15, 0};
    const Group knight   = {20, 21, 22, 23, 24, 25, 0};
    const Group bishop   = {30, 31, 32, 33, 34, 35, 0};
    const Group rook     = {40, 41, 42, 43, 44, 45, 0};
    const Group queen    = {50, 51, 52, 53, 54, 55, 0};
    const Group king     = { 0,  0,  0,  0,  0,  0, 0};

    const std::vector attacked = {king, queen, rook, bishop, knight, pawn};
}




struct MoveInfo{
    int16_t from, to;
    MoveInfo() = default;
    MoveInfo(int16_t from, int16_t to): from(from), to(to) {} 

    MoveInfo& operator=(const MoveInfo& rhs){
        from = rhs.from;
        to   = rhs.to;
        return *this;
    }

    std::string get_command(){
        auto start_pos = encode(from);
        auto end_pos   = encode(to);
        std::string command = start_pos + " " + end_pos;
        return command;
    }

    friend std::istream& operator>>(std::istream& is, MoveInfo& move_info){
        is >> move_info.from >> move_info.to;
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const MoveInfo& move_info){
        os << move_info.from << " " << move_info.to;
        return os;
    }
};

class Board{
// private:
public:
  int16_t  board[64];
  MoveInfo last_move;
  bool     can_castle;
//   int16_t  n_pieces[2];  // 0 is white, 1 is black
  int16_t  score;
  bool     turn;

    void init(){
        const int16_t default_value[64] = {
            -500, -320, -325, -950, -10000, -325, -320, -500,
            -100, -100, -100, -100, -100, -100, -100, -100,
                0,   0,     0,   0,    0,    0,    0,    0,
                0,   0,     0,   0,    0,    0,    0,    0,
                0,   0,     0,   0,    0,    0,    0,    0,
                0,   0,     0,   0,    0,    0,    0,    0,
            100,  100,  100,  100,  100,  100,  100,  100,
            500,  320,  325,  950,  10000, 325,  320,  500
        }; 
        memcpy(board, default_value, sizeof(board));
        // n_pieces[0]  = 16;
        // n_pieces[1]  = 16;
        can_castle   = true;
        score        = 0;
        turn         = White;
    }

    bool is_empty(int16_t position) { return board[position] == Empty; }
    bool is_white(int16_t position) { return board[position] > 0; }
    bool is_black(int16_t position) { return board[position] < 0; }

    auto get_score(){
        return turn == White ? score : -score;   
    }

    Board operator = (Board& rhs){
        // memcpy(rhs.n_pieces, n_pieces, sizeof(n_pieces));
        memcpy(rhs.board, board, sizeof(board));

        last_move  = rhs.last_move;
        can_castle = rhs.can_castle;
        score      = rhs.score;
        turn       = rhs.turn;

        return *this;
    }

    auto& operator[](int16_t idx){
        return board[idx];
    }
    const auto& operator[](int16_t idx) const{
        return board[idx];
    }

    template<class H> auto get_piece_score(H&& evaluate_board, int16_t position){
        // if turn = white, we need to reverse board to evaluate
        if(is_black(position)){ 
            position = Evaluate::flip[position];
        }
        return evaluate_board[position];
    }


    std::vector<int16_t> get_all_move_pos(int16_t position){
        const int16_t absolute_piece_value = abs(board[position]);
        switch(absolute_piece_value){
            case King:   return king_move(board, position);
            case Queen:  return queen_move(board, position);
            case Rook:   return rook_move(board, position);
            case Knight: return knight_move(board, position);
            case Bishop: return bishop_move(board, position);
            case Pawn:   return pawn_move(board, position);
            default:
                mes_error("There are no pieces in this position.");
        }
        return std::vector<int16_t>{};
    }

    auto& get_evaluate_board(int16_t position){
        auto absolute_piece_value = abs(board[position]);
        switch(absolute_piece_value){
            case King:   return Evaluate::king;
            case Queen:  return Evaluate::queen;
            case Rook:   return Evaluate::rook;
            case Bishop: return Evaluate::bishop;
            case Knight: return Evaluate::knight;
            case Pawn:   return Evaluate::pawn;
            default: 
                return Evaluate::empty;
        }
    }

    int16_t evaluate_score(int16_t from, int16_t to){
        auto&& evaluate_board_from_pos = get_evaluate_board(from);
        auto&& evaluate_board_to_pos   = get_evaluate_board(to);
        int   base = is_white(from) ? 1 : -1;
        int16_t evaluate = 0;
        /*
            We imagine white and black have opposite points, 
            so if white is plus then black will be minus, and vice versa.
        */
        evaluate += base * (get_piece_score(evaluate_board_from_pos, to) - 
                           get_piece_score(evaluate_board_from_pos, from));
        
        if(!is_empty(to)){
            evaluate -= board[to] + base * get_piece_score(evaluate_board_to_pos, to);
            // auto& n_piece = is_white(to) ? n_pieces[0] : n_pieces[1];  
            // n_piece -= 1;
        }
        return evaluate;
    }

    auto get_attack_index(int piece_value){
        const auto absolute_piece_value = abs(piece_value);
        switch(absolute_piece_value){
            case King:   return 0;
            case Queen:  return 1;
            case Rook:   return 2;
            case Bishop: return 3;
            case Knight: return 4;
            case Pawn:   return 5;
        }
        return 0;
    }

    auto get_attack_value(const MoveInfo& move_info){
        auto captured_piece_value = board[move_info.to];
        auto attack_piece_value   = board[move_info.from];

        return Attack::attacked[get_attack_index(captured_piece_value)][get_attack_index(attack_piece_value)];
    }

    auto change_piece_position(int16_t from, int16_t to){
        score += evaluate_score(from, to);

        board[to]       = board[from];
        board[from]     = 0;
        last_move       = MoveInfo(from, to);
        turn ^= 1;
    } 

    void simulation(std::vector<int16_t>& command) {
        for(int i = 0; i < command.size(); i += 2){
            auto from  = command[i];
            auto to    = command[i + 1];

            if((turn == White && is_black(from)) || (turn == Black && is_white(from)))
                mes_error("Invalid move");

            change_piece_position(from, to);
        }
    }


    auto promotion(int piece_value, int16_t position){
        int16_t side = board[position] > 0 ? 1 : -1;
        board[piece_value] = side * piece_value;
        return board;
    }


    std::string piece_symbol(int16_t position){
        auto absolute_piece_value = abs(board[position]);
        switch(absolute_piece_value){
          case King:   return "♚";
          case Queen:  return "♛";
          case Rook:   return "♜";
          case Knight: return "♞";
          case Bishop: return "♝";
          case Pawn:   return "♟";
          case Empty:  return "♢ ";
          default: 
            mes_error("don't support this piece");
        }
    }

    void display(){
      for(int i = 0; i < 64; ++i){
        if(i % 8 == 0)
            std::cout << 8 - i / 8 << ' '; 

        std::cout << piece_symbol(i);

        if((i + 1) % 8 == 0)
          std::cout << "\n";
      }
      std::cout << ' ';
      for(int i = 0; i < 8; ++i) 
        std::cout << " " << char('a' + i);
      std::cout << "\n";
    }
};


size_t cnt_node;

auto get_depth(int depth, int possible_move){
    if(possible_move <= 16)
        depth += 2;
    return depth;
}


auto Quiescence(Board& examine_board, int alpha, int beta, int depth){
    int  score = examine_board.score;
    bool turn  = examine_board.turn;
    cnt_node++;

    if(score >= beta)
        return beta;

    alpha = std::max(alpha, score);

    if(depth == 0){
        return score;
    }

    std::vector<MoveInfo> move_list;
    move_list.reserve(40);

    for(int from = 0; from < 64; ++from){
        if(examine_board.is_empty(from))
            continue;

            if((turn == White && examine_board.is_black(from)) || 
            (turn == Black && examine_board.is_white(from)))
                continue;

            const std::vector<int16_t> move_position = examine_board.get_all_move_pos(from);

            for(auto& to : move_position){
                if(examine_board[to] != 0){
                    move_list.emplace_back(from, to);
                }
            }
    }

    std::sort(move_list.begin(), move_list.end(), [&](MoveInfo& lhs, MoveInfo& rhs){
        return examine_board.get_attack_value(lhs) > examine_board.get_attack_value(rhs);
    });

    for(auto& [from, to] : move_list){
        Board board = examine_board;
        board.change_piece_position(from, to);
        int result_score = -Quiescence(board, -beta, -alpha, depth - 1);

        if(result_score >= beta)
            return beta;

        alpha = std::max(alpha, result_score);
    }
    if(move_list.empty()){
        return score;
    }
    return alpha;
}


auto alpha_beta(Board& examine_board, int alpha, int beta, int depth, MoveInfo& move_info, bool extended){
    bool turn  = examine_board.turn;
    cnt_node++;

    // if(depth == 0){
    //     if(!extended)
    //         extended = true,
    //         depth   += 1;
    //     else
    //         return Quiescence(examine_board, alpha, beta, 2);
    // }

    if(depth == 0 || examine_board.score >= 5000){
        alpha = examine_board.score;
        return alpha;
    }

    std::vector<MoveInfo> move_list;
    std::vector<int16_t> move_pos_list[64]; 
    move_list.reserve(30);

    MoveInfo next_move_info;
    for(int from = 0; from < 64; ++from){
        if(examine_board.is_empty(from))
            continue;

        if((turn == White && examine_board.is_black(from)) || 
           (turn == Black && examine_board.is_white(from)))
            continue;

        move_pos_list[from] = examine_board.get_all_move_pos(from);

        for(auto& to : move_pos_list[from]){
            if(examine_board[to] != 0)
                move_list.emplace_back(from, to);
        }
    }

    std::sort(move_list.begin(), move_list.end(), [&](MoveInfo& lhs, MoveInfo& rhs){
        return examine_board.get_attack_value(lhs) > examine_board.get_attack_value(rhs);
    });

    for(auto& [from, to] : move_list){
        Board board = examine_board;
        board.change_piece_position(from, to);
        int result_score = -alpha_beta(board, -beta, -alpha, depth - 1, next_move_info, extended);

        if(result_score >= beta)
            return beta;

        if(result_score > alpha){
            move_info = board.last_move;
            alpha = result_score;
        }
    }

    for(int from = 0; from < 64; ++from){
        for(auto& to : move_pos_list[from]){
            if(examine_board[to] != 0) continue;
            Board board = examine_board;
            board.change_piece_position(from, to);
            int result_score = -alpha_beta(board, -beta, -alpha, depth - 1, next_move_info, extended);

            if(result_score >= beta)
                return beta;

            if(result_score > alpha){
                move_info = board.last_move;
                alpha = result_score;
            }
        }
    }
    return alpha;
}


Board board;
int cnt_move;

auto run_program(){
    MoveInfo best_move;

    auto start = high_resolution_clock::now();

    int depth;
    if(cnt_move % 2 == 0) depth = 6;
    else depth = 7;


    int res = alpha_beta(board, -INF, INF, depth, best_move, false);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count(); 

    std::cout << (cnt_move % 2 == 0 ? "White" : "Black") << "\n";
    std::cout << duration << "ms" << "\n";


    std::cout << best_move.get_command() << "\n";

    board.change_piece_position(best_move.from, best_move.to);
    board.display();

    // dbg(cnt_node);

    cnt_node = 0;
    cnt_move++;
    // dbg(board.score);

    return board.score;
}

signed main(){
    // default_file();
    auto record = parse();
    board.init();
    board.simulation(record);
    cnt_move += record.size() / 2;
    // board.display();

    // int result = 0;
    // int cnt = 0;
    // while(abs(result) < 5000){
    //    result = run_program();
    //    if(cnt++ >= 20) break;
    // }

    // if(result <= -10000){
    //     std::cout << "Black win";
    //     return 0;
    // }
    // if(result >= 10000)
    //     std::cout << "White win";
    // else 
    //     std::cout << "Error";
    run_program();

    return 0;
}

