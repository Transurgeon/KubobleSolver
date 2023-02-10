#include "template.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void updateGrid(state &s) {
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
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
                s.grid[i][j] = "||";
        }
    }
}

void printGrid(vector<vector<string> > grid)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
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

point movePoint(vector<vector<string> > grid, point p, direction d) {
    // move p in direction d
    int new_x = p.row + d.d_row;
    int new_y = p.col + d.d_col;
    if (new_x <= 2 && new_x >= 0 && new_y <= 2 && new_y >= 0 && grid[new_x][new_y] != "G" && grid[new_x][new_y] != "O") {
        
        while (new_x <= 2 && new_x >= 0 && new_y <= 2 && new_y >= 0 && grid[new_x][new_y] != "G" && grid[new_x][new_y] != "O") {
            p.row += d.d_row;
            p.col += d.d_col;
            new_x = p.row;
            new_y = p.col;
        }
        if (new_x > 2) {
            new_x = 2;
        }
        else if (new_x < 0) {
            new_x = 0;
        }
        if (new_y > 2) {
            new_y = 2;
        }
        else if (new_y < 0) {
            new_y = 0;
        }
        point new_p = {new_x, new_y, p.color};
        return new_p;
    }
    else {
        return p;
    }
}

stack<state> getValid_Moves(state s) {
    vector<direction> directions = generateDirections(s);
    vector < vector <string> > &grid = s.grid;
    vector < turn > &turns = s.turns;
    stack<state> valid_moves;
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

            if (new_p.row != p.row || new_p.col != p.col) {
                // update turns
                turn t = {p, directions[i]};
                vector < turn > new_turns = turns;
                new_turns.push_back(t);
                // update grid
                vector < vector <string> > new_grid = grid;
                new_grid[p.row][p.col] = "||";
                new_grid[new_p.row][new_p.col] = p.color;
                // update state
                state new_s;
                if (c == 0) {
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
                else {
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
                // add new state to stack
                valid_moves.push(new_s);
            }
        }
    }
    return valid_moves;
}