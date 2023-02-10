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
    state end = depthSearch(start, 0);
    printGrid(end.grid);
    vector<turn> t = end.turns;
    for (int i = 0; i < t.size(); i++) {
        std::cout << t[i].p.color << " " << t[i].d.direc << "\n";
    }
    return 0;
}