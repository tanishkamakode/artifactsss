#include <iostream>
using namespace std;

int n;
int board[10];

bool isSafe(int row, int col){
    for(int i = 0; i < row; i++){
        if(board[i] == col || abs(board[i] - col) == abs(i - row)){
            return false;
        }
    }
    return true;
}

bool solve(int row){
    if(row == n){
        return true;
    }

    for(int col = 0; col < n; col++){
        if(isSafe(row, col)){
            board[row] = col;

            if(solve(row + 1)){
                return true;
            }

            board[row] = -1;
        }
    }
    return false;
}

void printBoard(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(board[i] == j){
                cout << "Q ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
}

int main(){
    int firstRow, firstCol;

    cout << "Enter the number of queens: ";
    cin >> n;

    for(int i = 0; i < n; i++){
        board[i] = -1;
    }

    cout << "Enter the position of first queen: ";
    cin >> firstRow >> firstCol;

    firstRow--;
    firstCol--;

    board[firstRow] = firstCol;

    if(solve(firstRow + 1)){
        cout << "Solution found: " << endl;
        printBoard();
    } else {
        cout << "No solution found" << endl;
    }

    return 0;
}

// Time Complexity: O(n!)
// Space Complexity: O(n)