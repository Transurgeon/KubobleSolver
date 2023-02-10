#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct point {
    int row;
    int col;
    string color;
};

struct direction {
    int d_row;
    int d_col;
};

struct state {
    vector<vector<string> > grid;
    struct point green;
    struct point orange;
    struct point green_end;
    struct point orange_end;
    int iterations;
};

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

vector<direction> generateDirections() {

    // Define the directions that the objects can move in
    vector<direction> directions;
    direction left = {0, -1}; direction right = {0, 1};
    direction up = {-1, 0}; direction down = {1, 0};
    directions.push_back(up); directions.push_back(down);
    directions.push_back(left); directions.push_back(right);
    return directions;
}

state init_state() {
    vector<vector<string> > grid(3, vector<string>(3, "||"));
    // Create a new state
    state s = {
        grid,
        {0, 0, "G"},
        {0, 1, "O"}, 
        {2, 1, "g"}, 
        {2, 0, "o"}, 
        0
        };

    // Update the grid
    updateGrid(s);

    // Print the grid
    printGrid(s.grid);
    
    return s;
}

point movePoint(vector<vector<string> > grid, point p, direction d) {
    // move p in direction d
    int new_x = p.row + d.d_row;
    int new_y = p.col + d.d_col;
    if (new_x < 2 & new_x >= 0 & new_y < 2 & new_y >= 0 & grid[new_x][new_y] == "||") {
        
        grid[p.row][p.col] = "||";
        while (new_x < 2 & new_x >= 0 & new_y < 2 & new_y >= 0 & grid[new_x][new_y] == "||") {
            p.row += d.d_row;
            p.col += d.d_col;
            new_x = p.row;
            new_y = p.col;
        }
        point new_p = {new_x, new_y, p.color};
        
        grid[new_p.row][new_p.col] = p.color;
        return new_p;
    }
    else {
        return p;
    }
}

stack<point> getValid_Moves(vector<vector<string> > grid, point p) {
    vector<direction> directions = generateDirections();
    stack<point> valid_moves;
    for (int i = 0; i < directions.size(); i++) {
        point new_p = movePoint(grid, p, directions[i]);
        if (new_p.row != p.row || new_p.col != p.col) {
            valid_moves.push(new_p);
        }
    }
    return valid_moves;
}

void depthSearch(state s) {
    stack<state> states;
    states.push(s);
    
}

int main() {
    
    state start = init_state();
    return 0;
}