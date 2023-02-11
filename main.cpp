#include "parser.h"
#include "algorithms.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

state init_state() {
    vector<vector<string> > grid(3, vector<string>(4, "||"));
    vector<turn> moves;
    // Create a new state
    state s = {
        grid,
        {0, 3, "G"},
        {0, 2, "O"}, 
        {1, 1, "g"}, 
        {0, 2, "o"}, 
        moves,
        0
        };
    
    // Update the grid
    updateGrid(s);
    s.grid[0][0] = "X";
    s.grid[1][3] = "X";
    printGrid(s.grid);
    return s;
}

int main() {
    
    state start = init_state();
    depthSearch(start, 10);
    return 0;
}