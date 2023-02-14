#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

struct point {
    int row;
    int col;
    string color;
};

struct direction {
    int d_row;
    int d_col;
    string direc;
};

struct turn {
    struct point p;
    struct direction d;
};

struct state {
    vector<vector<string> > grid;
    struct point green;
    struct point orange;
    struct point green_end;
    struct point orange_end;
    vector<struct turn> turns;
    int iterations;
};

void updateGrid(state &s);

void printGrid(vector<vector<string> > grid);

vector<direction> generateDirections(state s);

point movePoint(vector<vector<string> > grid, point p, direction d);

queue<state> getValid_Moves(state s);