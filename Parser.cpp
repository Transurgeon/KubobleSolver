#include "parser.h"
#include "template.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<string> getNextLineAndSplit(istream& str)
{
    vector<string> result;
    string line;
    getline(str,line);

    stringstream lineStream(line);
    string cell;

    while(getline(lineStream,cell, ','))
    {
        result.push_back(cell);
    }
    // This checks for a trailing comma with no data after it.
    if (!lineStream && cell.empty())
    {
        // If there was a trailing comma then add an empty element.
        result.push_back("");
    }
    return result;
}

vector < vector <string> > parseGrid(string gridString) {
    vector < vector <string> > grid;
    vector <string> row;
    for (int i = 0; i < gridString.size(); i++) {
        if (gridString[i] == '.') {
            row.push_back("||");
        }
        else if (gridString[i] == 'X') {
            row.push_back("X");
        }
        else if (gridString[i] == 'A') {
            row.push_back("G");
        }
        else if (gridString[i] == 'B') {
            row.push_back("O");
        }
        else if (gridString[i] == 'a') {
            row.push_back("g");
        }
        else if (gridString[i] == 'b') {
            row.push_back("o");
        }
        else if (gridString[i] == ';') {
            grid.push_back(row);
            row.clear();
        }
        else {
            continue;
        }
    }
    grid.push_back(row);
    return grid;
}

