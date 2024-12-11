#include <vector>
#include <cstdint>

const int MAX_SIZE = 1 << 22;

enum Flag{
    LOWER_BOUND = 0,
    UPPER_BOUND = 2,
    EXACT = 1
};

struct Entry{
    int16_t depth;
    int16_t score;
    int16_t flag;
    uint64_t key;
};

struct TranspositionTable{
    Entry table[MAX_SIZE];

    Entry get_entry(uint64_t key){
        return table[key % MAX_SIZE];
    }
    void store(uint64_t key, int16_t depth, int16_t score, int16_t flag) {
        if(depth >= table[key % MAX_SIZE].depth)
            table[key % MAX_SIZE] = {depth, score, flag, key};
    }
};

