#include <cstdio>
#include <iostream>
#include <cassert>
#include <cstdint>
#include <vector>

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

