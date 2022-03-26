#include <iostream>
#include "stack.h"
#include <vector>
#include <fstream>
#include <string>

using namespace std;

struct Cell{
    int x, y;
    bool up, down, left, right;
    bool isVisited;

    Cell(){};
    Cell(int x, int y){
        x = x;
        y = y;
        isVisited = false;
        up = true;
        down = true;
        left = true;
        right = true;
    }
};

void generate(int rows, int cols, int ID){
    vector<vector<Cell> > mazeMatrix(rows, vector<Cell>(cols));
    
    Stack<Cell> mazeStack;
}

void saveMaze(vector<vector<Cell> > maze, int num){
    string filename = "maze_" + to_string(num) + ".txt";
    
    ofstream out(filename); 
    out << maze[0].size() << " " << maze.size() << "\n";
    for (int j = 0; j < maze[0].size(); j++){
        for(int i = 0; i < maze.size(); i++){
            out << "x=" << maze[i][j].x << " ";
            out << "y=" << maze[i][j].y << " ";
            out << "u=" << maze[i][j].up << " ";
            out << "d=" << maze[i][j].down << " ";
            out << "l=" << maze[i][j].left << " ";
            out << "r=" << maze[i][j].right << " ";
        }
    }
    out.close();
}

void takeInput(int & count, int & rows, int & cols){
    cout << "Enter the number of mazes: ";
    cin >> count;
    cout << "Enter the number of rows and columns (M and N): ";
    cin >> rows >> cols;
}

int main(){
    int count, rows, cols;
    takeInput(count, rows, cols);
    
    
    
    return 0;
}
