// #include<vector>
// #include<cstdio>
// #include<iostream>
// #include<cstdlib>
// #include<cstdint>
#include<bits/stdc++.h>

using namespace std::chrono;
   
#define default_file() freopen("C:\\Users\\DUC ANH\\Downloads\\Gen\\default\\input.in", "r", stdin);  freopen("C:\\Users\\DUC ANH\\Downloads\\Gen\\default\\output.out", "w", stdout); 

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

struct Point{
    int x, y;
    Point(int x, int y): x(x), y(y) {}
    Point operator-(Point p){ return Point(x - p.x, y - p.y); }
    Point operator+(Point p){ return Point(x + p.x, y + p.y); }
    Point operator-=(Point p){ x -= p.x, y -= p.y; return *this; }
    Point operator+=(Point p){ x += p.x, y += p.y; return *this; }
    bool  operator==(Point p) const { return x == p.x && y == p.y; }
    bool  operator!=(Point p) const { return !(*this == p); }
    friend std::istream& operator>>(std::istream& is, Point& p){
        is >> p.x >> p.y;
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, const Point p){
        os << p.x << ' ' << p.y << "\n";
        return os;
    }
};


auto GetIdx(int x, int y){
    return (x * 8) + y; 
}
auto GetIdx(const Point& p){ return GetIdx(p.x, p.y); }


const int INF = 10000000;

std::string encode(int position){
    int x = position / 8, y = position % 8;
    x = 7 - x;
    std::string ret_str;
    ret_str += char(y + 'a');
    ret_str += char(x + 1 + '0');
    return ret_str;
}


std::vector<Point> parse(){
    std::vector<Point> record;
    std::string input;
    while(std::getline(std::cin, input)){
        if(input == "END") break;
        assert(input[2] == ' ');
        record.push_back(Point(8 - int(input[1] - '0'), int(input[0] - 'a')));
        record.push_back(Point(8 - int(input[4] - '0'), int(input[3] - 'a')));
    }
    return record;
}

enum ChessPieceValue{
    Pawn   = 100,
    Knight = 305,
    Bishop = 310, 
    Rook   = 500,
    Queen  = 900, 
    King   = 10000,
    Empty = 0
};

enum Color{
  White = 1, 
  Black = 0
};

bool is_in_board(const Point& position){
    return position.x >= 0 && position.x <= 7 && 
           position.y >= 0 && position.y <= 7; 
}

template<class T>
bool is_same_color(T&& board, Point src, Point dst){
  const auto src_value = board[GetIdx(src)];
  const auto dst_value = board[GetIdx(dst)];
  return (src_value < 0 && dst_value < 0) || 
         (src_value > 0 && dst_value > 0);
}

template<class T, class H> 
std::vector<Point> piece_move(T&& board, H&& direct, Point src_pos, int limit_times) {
    // if limit_times = INF -> unlimited moves 
    std::vector<Point> next_pos;
    for(int i = 0; i < std::size(direct); ++i) { 
      Point cur_pos = src_pos + direct[i];
      for(int cnt_times = 0; cnt_times < limit_times; ++cnt_times) {
          if(!is_in_board(cur_pos) || is_same_color(board, src_pos, cur_pos)) break;
          next_pos.push_back(cur_pos);
          if(board[GetIdx(cur_pos)] != 0) break;
          cur_pos += direct[i];
      }
    }
    return next_pos;
}

template<class T> 
std::vector<Point> king_move(T&& board, Point position){
    const Point direct[] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, 
                             {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    return piece_move(board, direct, position, 1);
}

template<class T> 
std::vector<Point> queen_move(T&& board, Point position){
    const Point direct[] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, 
                            {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    return piece_move(board, direct, position, INF);
}

template<class T> 
std::vector<Point> rook_move(T&& board, Point position){
    const Point direct[] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
    return piece_move(board, direct, position, INF);
}

template<class T> 
std::vector<Point> knight_move(T&& board, Point position){
    const Point direct[] = {{-2, -1}, {-1, -2}, {-2, 1}, {-1, 2},
                            {2, -1}, {1, -2}, {2, 1}, {1, 2}};
    return piece_move(board, direct, position, 1);
}


template<class T> 
std::vector<Point> bishop_move(T&& board, Point position){
    const Point direct[] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    return piece_move(board, direct, position, INF);
}

template<class T>
std::vector<Point> pawn_move(T&& board, Point position){  // side = 1 if white else black
    std::vector<Point> next_pos;
    bool side    = board[GetIdx(position)] > 0 ? White : Black;
    auto nxt_pos = position + Point(side == White ? -1 : 1, 0);

    if(is_in_board(nxt_pos) && board[GetIdx(nxt_pos)] == 0){
        next_pos.push_back(nxt_pos);

        if(position.x == (side == White ? 6 : 1) &&
            is_in_board(nxt_pos + Point(side == White ? -1 : 1, 0)) && board[GetIdx(nxt_pos + Point(side == White ? -1 : 1, 0))] == 0)
            next_pos.push_back(nxt_pos + Point(side == White ? -1 : 1, 0));
    }

    auto [x, y] = position;
    if(side == White){
        if(x > 0 && y > 0 && board[GetIdx(x - 1, y - 1)] < 0)
            next_pos.push_back(Point(x - 1, y - 1));
        if(x > 0 && y < 7 && board[GetIdx(x - 1, y + 1)] < 0)
            next_pos.push_back(Point(x - 1, y + 1));
    }
    else{
        if(x < 7 && y > 0 && board[GetIdx(x + 1, y - 1)] > 0)
            next_pos.push_back(Point(x - 1, y + 1));
        if(x < 7 && y < 7 && board[GetIdx(x + 1, y + 1)] > 0)
            next_pos.push_back(Point(x + 1, y + 1));     
    }  

    return next_pos;
}


namespace Evaluate{ // Evaluate by position
    const int pawn[] = {
        0,  0,  0,  0,  0,  0,  0,  0,
        50, 50, 50, 50, 50, 50, 50, 50,
        10, 10, 20, 30, 30, 20, 10, 10,
        5,  5, 10, 25, 25, 10,  5,  5,
        0,  0,  0, 20, 20,  0,  0,  0,
        5, -5,-10,  0,  0,-10, -5,  5,
        5, 10, 10,-20,-20, 10, 10,  5,
        0,  0,  0,  0,  0,  0,  0,  0
    };

    const int knight[] = {
        -50,-40,-30,-30,-30,-30,-40,-50,
        -40,-20,  0,  0,  0,  0,-20,-40,
        -30,  0, 10, 15, 15, 10,  0,-30,
        -30,  5, 15, 20, 20, 15,  5,-30,
        -30,  0, 15, 20, 20, 15,  0,-30,
        -30,  5, 10, 15, 15, 10,  5,-30,
        -40,-20,  0,  5,  5,  0,-20,-40,
        -50,-40,-30,-30,-30,-30,-40,-50
    };

    const int bishop[] = {
        -20,-10,-10,-10,-10,-10,-10,-20,
        -10,  0,  0,  0,  0,  0,  0,-10,
        -10,  0,  5, 10, 10,  5,  0,-10,
        -10,  5,  5, 10, 10,  5,  5,-10,
        -10,  0, 10, 10, 10, 10,  0,-10,
        -10, 10, 10, 10, 10, 10, 10,-10,
        -10,  5,  0,  0,  0,  0,  5,-10,
        -20,-10,-10,-10,-10,-10,-10,-20
    };

    const int rook[] = {
        0,  0,  0,  0,  0,  0,  0,  0,
        5, 10, 10, 10, 10, 10, 10,  5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        0,  0,  0,  5,  5,  0,  0,  0
    };

    const int queen[] = {
        -20,-10,-10, -5, -5,-10,-10,-20,
        -10,  0,  0,  0,  0,  0,  0,-10,
        -10,  0,  5,  5,  5,  5,  0,-10,
        -5,  0,  5,  5,  5,  5,  0, -5,
        0,  0,  5,  5,  5,  5,  0, -5,
        -10,  5,  5,  5,  5,  5,  0,-10,
        -10,  0,  5,  0,  0,  0,  0,-10,
        -20,-10,-10, -5, -5,-10,-10,-20
    };

    const int king[] = {
        -30,-40,-40,-50,-50,-40,-40,-30,
        -30,-40,-40,-50,-50,-40,-40,-30,
        -30,-40,-40,-50,-50,-40,-40,-30,
        -30,-40,-40,-50,-50,-40,-40,-30,
        -20,-30,-30,-40,-40,-30,-30,-20,
        -10,-20,-20,-20,-20,-20,-20,-10,
        20, 20,  0,  0,  0,  0, 20, 20,
        20, 30, 10,  0,  0, 10, 30, 20
    };
    const int empty[64] = {0};
}



struct MoveInfo{
    int from, to;
    MoveInfo(int from = 0, int to = 0): from(from), to(to) {} 

    MoveInfo operator=( MoveInfo rhs){
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
  int      score;
//   int      attack_score;
  bool     turn;

    void init(){
        const int16_t default_value[64] = {
            -500, -305, -310, -900, -10000, -310, -305, -500,
            -100, -100, -100, -100, -100, -100, -100, -100,
                0,   0,     0,   0,    0,    0,    0,    0,
                0,   0,     0,   0,    0,    0,    0,    0,
                0,   0,     0,   0,    0,    0,    0,    0,
                0,   0,     0,   0,    0,    0,    0,    0,
            100,  100,  100,  100,  100,  100,  100,  100,
            500,  305,  310,  900,  10000, 310,  305,  500
        }; 
        memcpy(board, default_value, sizeof(board));
        can_castle   = true;
        score        = 0;
        // attack_score = 0;
        turn         = White;
    }

    bool is_empty(int position) { return board[position] == Empty; }
    bool is_white(int position) { return board[position] > 0; }
    bool is_black(int position) { return board[position] < 0; }

    auto get_score(){
        return turn == White ? score : -score;   
    }

    Board operator = (Board rhs){
        memcpy(rhs.board, board, sizeof(board));
        last_move  = rhs.last_move;
        can_castle = rhs.can_castle;
        score      = rhs.score;
        turn       = rhs.turn;
        return *this;
    }

    auto& operator[](int idx){
        return board[idx];
    }
    const auto& operator[](int idx) const{
        return board[idx];
    }

    template<class H> auto get_piece_score(H&& evaluate_board, int position){
        // if turn = black, we need to reverse board to evaluate
        if(is_black(position)){ 
            position = 63 - position;
        }
        return evaluate_board[position];
    }


    std::vector<Point> get_all_move_pos(int position){
        const int absolute_piece_value = abs(board[position]);
        const int row = position / 8 , col = position % 8;
        const Point point(row, col);
        
        switch(absolute_piece_value){
            case King:   return king_move(board, point);
            case Queen:  return queen_move(board, point);
            case Rook:   return rook_move(board, point);
            case Knight: return knight_move(board, point);
            case Bishop: return bishop_move(board, point);
            case Pawn:   return pawn_move(board, point);
            default:
                mes_error("There are no pieces in this position.");
        }
        return std::vector<Point>{};
    }

    auto& get_evaluate_board(int position){
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

    auto change_piece_position(int from, int to){
        auto&& evaluate_board_from_pos = get_evaluate_board(from);
        auto&& evaluate_board_to_pos   = get_evaluate_board(to);
        int   base = is_white(from) ? 1 : -1;
        /*
            We imagine white and black have opposite points, 
            so if white is plus then black will be minus, and vice versa.
        */
        score += base * (get_piece_score(evaluate_board_from_pos, to) - 
                         get_piece_score(evaluate_board_from_pos, from));
        

        if(!is_empty(to)){
            score -= board[to] + base * get_piece_score(evaluate_board_to_pos, to);
        }

        // attack_score    = get_attack_value();
        board[to]       = board[from];
        board[from]     = 0;
        last_move       = MoveInfo(from, to);
        turn ^= 1;
    } 


    void simulation(std::vector<Point>& command) {
        for(int i = 0; i < command.size(); i += 2){
            auto from  = GetIdx(command[i]);
            auto to    = GetIdx(command[i + 1]);

            if((turn == White && is_black(from)) || (turn == Black && is_white(from)))
                mes_error("Invalid move");

            change_piece_position(from, to);
        }
    }


    auto promotion(int piece_value, int position){
        int side = board[position] > 0 ? 1 : -1;
        board[piece_value] = side * piece_value;
        return board;
    }


    std::string piece_symbol(int position){
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

using Group = std::vector<int>;

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


auto get_attack_index(int piece_value){
    auto absolute_piece_value = abs(piece_value);
    switch(absolute_piece_value){
        case King:   return 0;
        case Queen:  return 1;
        case Rook:   return 2;
        case Bishop: return 3;
        case Knight: return 4;
        case Pawn:   return 5;
        default:   
            return 0;
    }
}

int get_attack_value(Board& board, MoveInfo& move_info){
    int captured_piece_value = board[move_info.from];
    int attack_piece_value   = board[move_info.to];

    int captured_piece_index = get_attack_index(captured_piece_value);
    int attack_piece_index   = get_attack_index(attack_piece_value);

    return Attack::attacked[captured_piece_value][attack_piece_value];
}


size_t cnt_node;

auto get_depth(int depth, int possible_move){
    if(possible_move <= 16)
        depth += 2;
    return depth;
}

auto alpha_beta(Board& examine_board, int alpha, int beta, int depth, MoveInfo& move_info){
    int score = examine_board.get_score();
    int turn  = examine_board.turn;
    cnt_node++;

    if(depth == 0 || examine_board.score >= 10000){
        alpha = examine_board.score;
        return alpha;
    }
  
    std::vector<MoveInfo> move_list;

    for(int from = 0; from < 64; ++from){
        if(examine_board.is_empty(from))
            continue;

        if((turn == White && examine_board.is_black(from)) || 
           (turn == Black && examine_board.is_white(from)))
            continue;

        std::vector<Point> next_pos = examine_board.get_all_move_pos(from);

        for(auto& next : next_pos){
          int to = GetIdx(next);
          move_list.push_back(MoveInfo(from, to));
        }
    }

    std::sort(move_list.begin(), move_list.end(), [&](MoveInfo& lhs, MoveInfo& rhs){
        return get_attack_value(examine_board, lhs) > get_attack_value(examine_board, rhs);
    });

    MoveInfo next_move_info;
    for(auto& [from, to] : move_list){
        Board board = examine_board;
        board.change_piece_position(from, to);
        int result_score = -alpha_beta(board, -beta, -alpha, depth - 1, next_move_info);

        if(result_score >= beta)
            return beta;

        if(result_score > alpha){
            move_info = board.last_move;
            alpha = result_score;
        }
    }
    return alpha;
}


void print_board(){
    for(int i = 0; i < 64; ++i){
        std::cout << i << ' ';
        if((i + 1) % 8 == 0)
            std::cout << "\n";
    }
}

Board board;
int cnt_move;

auto run_program(){
    MoveInfo best_move;

    auto start = high_resolution_clock::now();

    int depth;
    if(cnt_move % 2 == 0) depth = 4;
    else depth = 3;

    // if(cnt_move >= 110) depth += 2; 
    int res = alpha_beta(board, -INF, INF, depth, best_move);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count(); 
    std::cout << duration << "ms" << "\n";

    // dbg(best_move.get_command());
    std::cout << best_move.get_command() << '\n';

    board.change_piece_position(best_move.from, best_move.to);
    // board.display();

    // dbg(board.score);
    dbg(cnt_node);

    cnt_node = 0;
    cnt_move++;
    // dbg(cnt_move,depth);

    return board.score;
}

signed main(){
    // default_file();
    auto record = parse();
    board.init();
    board.simulation(record);
    cnt_move += record.size() / 2;
    board.display();

    // int result = 0;
    // int cnt = 0;
    // while(abs(result) < 10000){
    //    run_program();
    //    if(cnt++ >= 6) break;
    // }

    // if(result <= -10000)
    //     std::cout << "Black win";
    // if(result >= 10000)
    //     std::cout << "White win";
    // else 
    //     std::cout << "Error";
    run_program();
    // auto x = get_attack_index(King);
    // auto y = get_attack_index(0);
    // dbg(Attack::attacked[x][y]);
    // dbg(get_attack_index(-500));
    // dbg(get_attack_index(0));
    return 0;
}

