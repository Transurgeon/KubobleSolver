#include "parser.h"
#include "algorithms.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

state init_state() {
    vector<vector<string> > grid(3, vector<string>(3, "||"));
    vector<turn> moves;
    // Create a new state
    state s = {
        grid,
        {0, 0, "G"},
        {0, 1, "O"}, 
        {2, 1, "g"}, 
        {2, 0, "o"}, 
        moves,
        0
        };
    
    // Update the grid
    updateGrid(s);

    return s;
}

int main() {
    
    state start = init_state();
    depthSearch(start, 5);
    return 0;
}