#include "parser.h"
#include "template.h"
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

    stack<state> tests = getValid_Moves(s);
    while (!tests.empty()) {
        state b = tests.top();
        printGrid(b.grid);
        std::cout << "------------------" << "\n";
        tests.pop();
        vector<turn> t = b.turns;
        for (int i = 0; i < t.size(); i++) {
            std::cout << t[i].p.color << " " << t[i].d.direc << "\n";
        }
    }

    return s;
}

int main() {
    
    state start = init_state();
    return 0;
}