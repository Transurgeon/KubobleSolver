#include "algorithms.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

state depthSearch(state start, int optimal) {
    stack<state> states = getValid_Moves(start);
    while (!states.empty()) {
        state s = states.top();
        states.pop();
        if (s.green.row == s.green_end.row && s.green.col == s.green_end.col 
        && s.orange.row == s.orange_end.row && s.orange.col == s.orange_end.col) {
            return s;
        }
        printGrid(s.grid);
        std::cout << "------------------" << "\n";

        stack<state> newStates = getValid_Moves(s);
        while (!newStates.empty()) {
            states.push(newStates.top());
            newStates.pop();
        }
    }
    return start;
}