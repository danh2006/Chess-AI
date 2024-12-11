#include<cstdio>
#include<chrono>
#include<iostream>
#include<random>


std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());


uint64_t piece_values[2][6][64];
uint64_t castling_values[2][2]; 
uint64_t side_to_move_values[2];
uint64_t en_passant_values[17]; 

struct Zobrist {
    Zobrist() {
        std::uniform_int_distribution<uint64_t> distrib(1, uint64_t(1e18));
        for(int side = 0; side < 2; ++side) {
            for(int piece = 0; piece < 6; ++piece) {
                for(int pos = 0; pos < 64; ++pos) {
                    piece_values[side][piece][pos] = distrib(rng);
                }
            }
        }
        for(int side = 0; side < 2; ++side) {
            for(int i = 0; i < 2; ++i) {
                castling_values[side][i] = distrib(rng);
            }
        }
        for(int i = 0; i < 2; ++i) {
            side_to_move_values[i] = distrib(rng);
        }
        for(int i = 0; i < 17; ++i) {
            en_passant_values[i] = distrib(rng);
        }
    }
};

Zobrist zobrist; 