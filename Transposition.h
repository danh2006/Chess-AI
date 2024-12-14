#include <vector>
#include <cstdint>

const int MAX_SIZE = 1 << 23;

enum Flag{
    LOWER_BOUND = 0,
    UPPER_BOUND = 2,
    EXACT = 1
};

struct Entry{
    int8_t depth;
    int16_t score;
    int8_t flag;
    uint64_t key;
    int8_t from;
    int8_t to;
};

int rewrite_times;

struct TranspositionTable{
    Entry table[MAX_SIZE];
  
    Entry get_entry(uint64_t key){
        return table[key % MAX_SIZE];
    }
    void store(uint64_t key, int8_t depth, int16_t score, int8_t flag, int8_t from, int8_t to){
        rewrite_times++;
        if(depth >= table[key % MAX_SIZE].depth)
            table[key % MAX_SIZE] = {depth, score, flag, key, from, to};
    }   
};

