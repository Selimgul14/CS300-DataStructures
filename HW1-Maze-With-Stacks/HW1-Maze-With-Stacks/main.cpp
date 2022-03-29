#include <iostream>
#include "stack.h"
#include "stack.cpp"
#include <vector>
#include <fstream>
#include <string>
#include "randgen.h"

using namespace std;

struct Cell {
    int x, y;
    bool up, down, left, right;
    bool isVisited;

    Cell() {};
    Cell(int x, int y) {
        this->x = x;
        this->y = y;
        isVisited = false;
        up = true;
        down = true;
        left = true;
        right = true;
    }
};

Stack<Cell> reverse(Stack<Cell>& stack) {

    Stack<Cell> reversed;
    while (!stack.isEmpty()) {
        reversed.push(stack.topAndPop());
    }
    return reversed;
}

void saveMaze(vector<vector<Cell> > maze, int num) {
    string filename = "maze_" + to_string(num) + ".txt";

    ofstream out(filename);
    out << maze[0].size() << " " << maze.size() << endl;
    for (int j = 0; j < maze[0].size(); j++) {
        for (int i = 0; i < maze.size(); i++) {
            out << "x=" << maze[i][j].x << " ";
            out << "y=" << maze[i][j].y << " ";
            out << "l=" << maze[i][j].left << " ";
            out << "r=" << maze[i][j].right << " ";
            out << "u=" << maze[i][j].up << " ";
            out << "d=" << maze[i][j].down << endl;
        }
    }
    out.close();
}

void generate(int rows, int cols, int ID) {
    vector<vector<Cell> > Matrix(rows, vector<Cell>(cols));
    RandGen rand;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Matrix[i][j] = Cell(i, j);
        }
    }
    Stack<Cell> mazeStack;

    Matrix[0][0].isVisited = true;
    mazeStack.push(Matrix[0][0]);
    Cell curr = mazeStack.top();
    int discovered = 1;
    int size = rows * cols;

    while (discovered < size) {
        int x = curr.x;
        int y = curr.y;
        vector<char> adjacent;
        if (y + 1 < cols && Matrix[x][y + 1].isVisited == false) {
            adjacent.push_back('U');								
        }
        if (y - 1 >= 0 && Matrix[x][y - 1].isVisited == false) {     
            adjacent.push_back('D');
        }
        if (x - 1 >= 0 && Matrix[x - 1][y].isVisited == false) {   
            adjacent.push_back('L');
        }
        if (x + 1 < rows && Matrix[x + 1][y].isVisited == false) {	
            adjacent.push_back('R');
        }
        if (adjacent.size() != 0) {
            int randomIndex = rand.RandInt(0, adjacent.size() - 1);

            if (adjacent[randomIndex] == 'U') {
                curr = Matrix[x][y + 1];
                Matrix[x][y].up = false;
                Matrix[x][y + 1].down = false;
                Matrix[x][y + 1].isVisited = true;
                mazeStack.push(curr);
                discovered++;
           }
            else if (adjacent[randomIndex] == 'D') {
                curr = Matrix[x][y - 1];
                Matrix[x][y].down = false;
                Matrix[x][y - 1].up = false;
                Matrix[x][y - 1].isVisited = true;
                mazeStack.push(curr);
                discovered++;

            }
            else if (adjacent[randomIndex] == 'L') {
                curr = Matrix[x - 1][y];
                Matrix[x][y].left = false;
                Matrix[x - 1][y].right = false;
                Matrix[x - 1][y].isVisited = true;
                mazeStack.push(curr);
                discovered++;

            }
            else if (adjacent[randomIndex] == 'R') {
                curr = Matrix[x + 1][y];
                Matrix[x][y].right = false;
                Matrix[x + 1][y].left = false;
                Matrix[x + 1][y].isVisited = true;
                mazeStack.push(curr);
                discovered++;
            }
        }
        else if (!mazeStack.isEmpty()) {
            mazeStack.pop();
            curr = mazeStack.top();
        }
    }
    saveMaze(Matrix, ID);
}


vector<vector<Cell> > readMaze(string filename) {
    ifstream input(filename);
    int rows, cols;
    input >> cols >> rows;
    vector<vector<Cell> > data(rows, vector<Cell>(cols));
    for (int i = 0; i < cols * rows; i++) {
        string x_coord, y_coord, up, down, left, right;
        input >> x_coord >> y_coord >> left >> right >> up >> down;
        int x_c = stoi(x_coord.substr(2));
        int y_c = stoi(y_coord.substr(2));
        data[x_c][y_c].x = x_c;
        data[x_c][y_c].y = y_c;
        data[x_c][y_c].up = stoi(up.substr(2));
        data[x_c][y_c].down = stoi(down.substr(2));
        data[x_c][y_c].left = stoi(left.substr(2));
        data[x_c][y_c].right = stoi(right.substr(2));
    }
    input.close();
    return data;
}

void checkAdjacent(vector<char>& adjacent, vector<vector<Cell>> Matrix, Cell curr, int & x_coord, int & y_coord) {
    x_coord = curr.x;
    y_coord = curr.y;
    if (y_coord + 1 < Matrix[0].size() && Matrix[x_coord][y_coord + 1].isVisited == false && !curr.up) {
        adjacent.push_back('U');
    }
    if (y_coord - 1 >= 0 && Matrix[x_coord][y_coord - 1].isVisited == false && !curr.down) {
        adjacent.push_back('D');
    }
    if (x_coord - 1 >= 0 && Matrix[x_coord - 1][y_coord].isVisited == false && !curr.left) {
        adjacent.push_back('L');
    }
    if (x_coord + 1 < Matrix.size() && Matrix[x_coord][y_coord].isVisited == false && !curr.right) {
        adjacent.push_back('R');
    }
}

void savePath(Stack<Cell> mazeStack, string path) {
    Cell curr;
    ofstream output(path);
    while (!mazeStack.isEmpty()) {
        curr = mazeStack.topAndPop();
        output << curr.x << " " << curr.y << endl;
    }
    output.close();
}

void findPath(int x_entry, int y_entry, int x_exit, int y_exit, int ID) {
    string filename;
    filename += "maze_" + to_string(ID) + ".txt";
    vector<vector<Cell> > Matrix = readMaze(filename);
    Stack<Cell> mazeStack;
    RandGen rand;
    Matrix[x_entry][y_entry].isVisited = true;
    mazeStack.push(Matrix[x_entry][y_entry]);

    Cell curr = mazeStack.top();

    while ((curr.x != x_exit) && (curr.y != y_exit)) {
        int x_coord, y_coord;
        vector<char> adjacent;
        checkAdjacent(adjacent, Matrix, curr, x_coord, y_coord);
        
        if (adjacent.size() != 0) {
            int randomIndex = rand.RandInt(0, adjacent.size() - 1);
            if (adjacent[randomIndex] == 'U') {
                curr = Matrix[x_coord][y_coord + 1];
                curr.isVisited = true;
                mazeStack.push(curr);
            }
            else if (adjacent[randomIndex] == 'D') {
                curr = Matrix[x_coord][y_coord - 1];
                curr.isVisited = true;
                mazeStack.push(curr);
            }
            else if (adjacent[randomIndex] == 'L') {
                curr = Matrix[x_coord - 1][y_coord];
                curr.isVisited = true;
                mazeStack.push(curr);
            }
            else if (adjacent[randomIndex] == 'R') {
                curr = Matrix[x_coord + 1][y_coord];
                curr.isVisited = true;
                mazeStack.push(curr);
            }
        }
        else if (!mazeStack.isEmpty()) {
            mazeStack.pop();
            curr = mazeStack.top();
        }
    }
    string path;
    path = "maze_" + to_string(ID) + "_path_" + to_string(x_entry) + "_" + to_string(y_entry) + "_" + to_string(x_exit) + "_" + to_string(y_exit) + ".txt";
    savePath(reverse(mazeStack), path);
}

void takeInput(int& count, int& rows, int& cols) {
    cout << "Enter the number of mazes: ";
    cin >> count;
    cout << "Enter the number of rows and columns (M and N): ";
    cin >> rows >> cols;
}


int main() {
    int count, rows, cols;
    takeInput(count, rows, cols);
    for (int i = 1; i <= count; i++) {
        generate(rows, cols, i);
    }
    cout << "All mazes are generated.\n";
    
    int ID;
    cout << "Enter a maze ID between 1 to " << count << " inclusive to find a path: ";
    cin >> ID;

    int x_entry, x_exit, y_entry, y_exit;
    cout << "Enter x and y coordinates of the entry points (x, y) or (column, row): ";
    cin >> x_entry >> y_entry;
    cout << "Enter x and y coordinates of the expit points (x, y) or (column, row): ";
    cin >> x_exit >> y_exit;
    findPath(ID, x_entry, y_entry, x_entry, y_exit);

    return 0;
}