#include <chrono>
#include <iostream>
#include "Search.h"
#include "Board.cpp"
// #include "Fen.h"


using namespace std::chrono;


Board board;
int cnt_move;

auto run_program(){
    MoveInfo best_move;

    auto start = high_resolution_clock::now();

    int depth = 7;

    int res = alpha_beta(board,  -INF, INF, depth, best_move, false);
    // iterative_deepening(board, depth, best_move);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count(); 
    std::cout << duration << "ms" << "\n";

    std::cout << best_move.get_command() << '\n';

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
    // while(abs(result) < 10000){
    //    result = run_program();
    //    if(cnt++ >= 100) break;
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