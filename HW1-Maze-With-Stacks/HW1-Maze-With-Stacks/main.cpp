#include <iostream>

using namespace std;

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
