#include "algorithms.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

void depthSearch(state start, int optimal) {
    queue<state> test = getValid_Moves(start);
    while (!test.empty()) {
        state s = test.front();
        test.pop();
        if (s.green.col == s.green_end.col && s.green.row == s.green_end.row 
        && s.orange.col == s.orange_end.col && s.orange.row == s.orange_end.row) {
            std::cout << "Found solution!\n";

            printGrid(s.grid);
            vector <turn> t = s.turns;
            for (int i = 0; i < t.size(); i++) {
                std::cout << t[i].p.color << " " << t[i].d.direc << "\n";
            }
            break;
        }
        if (s.iterations <= optimal) {
            queue<state> temp = getValid_Moves(s);
            while (!temp.empty()) {
                test.push(temp.front());
                temp.pop();
            }
        }
        else {
            std::cout << "No solution found\n";
            break;
            }
    }
}