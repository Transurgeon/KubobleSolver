#include "template.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

void updateGrid(state &s) {
    for (int i = 0; i < s.grid.size(); i++)
    {
        for (int j = 0; j < s.grid[0].size(); j++)
        {
            if (s.green.row == i & s.green.col == j)
                s.grid[i][j] = s.green.color;
            else if (s.orange.row == i & s.orange.col == j)
                s.grid[i][j] = s.orange.color;
            else if (s.green_end.row == i & s.green_end.col == j)
                s.grid[i][j] = s.green_end.color;
            else if (s.orange_end.row == i & s.orange_end.col == j)
                s.grid[i][j] = s.orange_end.color;
            else
                s.grid[i][j] = ".";
        }
    }
}

void printGrid(vector<vector<string> > grid)
{
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[0].size(); j++)
        {   
            std::cout << grid[i][j] << "\t";
        }
        std::cout << "\n";
    }
}

vector<direction> generateDirections(state s) {

    // Define the directions that the objects can move in
    vector<direction> directions;
    direction left = {0, -1, "L"}; direction right = {0, 1, "R"};
    direction up = {-1, 0, "U"}; direction down = {1, 0, "D"};
    directions.push_back(up); directions.push_back(down);
    directions.push_back(left); directions.push_back(right);
    return directions;
}

bool isMoveRepeat(state s, point p, direction d) {
    // Check if the move is a repeat
    if (s.turns.size() == 0) {
        return false;
    }
    turn lastMove = s.turns.back();
    if (p.color == lastMove.p.color) {
        if ((d.direc == "L" && lastMove.d.direc == "R")
            || (d.direc == "R" && lastMove.d.direc == "L")
            || (d.direc == "U" && lastMove.d.direc == "D")
            || (d.direc == "D" && lastMove.d.direc == "U")) {
            return true;
        }
    }
    return false;
}

point movePoint(vector<vector<string> > grid, point p, direction d) {
    // Move the point in the direction d until it has reached
    // the edge of the grid or another object
    point &new_p = p;
    while (true) {
        new_p.row += d.d_row;
        new_p.col += d.d_col;
        if (new_p.row < 0 || new_p.row > grid.size() - 1 || 
        new_p.col < 0 || new_p.col > grid[0].size() - 1) {
            new_p.row -= d.d_row;
            new_p.col -= d.d_col;
            break;
        }
        if (grid[new_p.row][new_p.col] != "." && grid[new_p.row][new_p.col] != "a" 
        && grid[new_p.row][new_p.col] != "b") {
            new_p.row -= d.d_row;
            new_p.col -= d.d_col;
            break;
        }
    }
    return new_p;
}

queue<state> getValid_Moves(state s) {
    vector<direction> directions = generateDirections(s);
    vector < vector <string> > &grid = s.grid;
    vector < turn > &turns = s.turns;
    queue<state> valid_moves;
    // this for loop is my implementation of macros :_(
    for (int c = 0; c < 2; c++) {
        point p;
        if (c == 0) {
            p = s.green;
        }
        else {
            p = s.orange;
        }
        for (int i = 0; i < directions.size(); i++) {
            point new_p = movePoint(grid, p, directions[i]);

            if ((new_p.row != p.row || new_p.col != p.col)
                && !isMoveRepeat(s, new_p, directions[i])) {
                // update turns
                turn t = {p, directions[i]};
                vector < turn > new_turns = turns;
                new_turns.push_back(t);
                // update grid
                vector < vector <string> > new_grid = grid;
                new_grid[p.row][p.col] = ".";
                new_grid[new_p.row][new_p.col] = p.color;
                // update state
                state new_s;
                if (c == 0) {
                    new_s = (struct state){
                    new_grid,
                    new_p,
                    s.orange,
                    s.green_end,
                    s.orange_end,
                    new_turns,
                    s.iterations + 1
                    };
                }
                else {
                    new_s = (struct state){
                    new_grid,
                    s.green,
                    new_p,
                    s.green_end,
                    s.orange_end,
                    new_turns,
                    s.iterations + 1
                    };
                }
                // add new state to queue
                valid_moves.push(new_s);
            }
        }
    }
    return valid_moves;
}

state generate_init_state(string gridString) {
    // Find the green and orange objects
    point green, orange, green_end, orange_end;
    vector<vector<string> > grid;
    vector <string> rows = splitString(gridString, ';');
    for (int i = 0; i < rows.size(); i++)
    {
        vector <string> row = splitString(rows[i], ' ');
        vector <string> new_row;
        for (int j = 0; j < row.size(); j++)
        {
            for (int k = 0; k < row[j].size(); k++)
            {
                if (row[j][k] == 'A') {
                    green = (struct point){i, j, "A"};
                }
                else if (row[j][k] == 'B') {
                    orange = (struct point){i, j, "B"};
                }
                else if (row[j][k] == 'a') {
                    green_end = (struct point){i, j, "a"};
                }
                else if (row[j][k] == 'b') {
                    orange_end = (struct point){i, j, "b"};
                }
                if (!(k == 0 && row[j].size() == 2)) {
                    string s;
                    s.push_back(row[j][k]);
                    new_row.push_back(s);
                }
            }
        }
        grid.push_back(new_row);
    }
    printGrid(grid);
    // Create the initial state
    state init_state = (struct state){
        grid,
        green,
        orange,
        green_end,
        orange_end,
        {},
        0
    };
    return init_state;
}