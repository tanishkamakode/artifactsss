#include <iostream>
using namespace std;

void iterativeFibonacci(int n){
    int first = 0;
    int second = 1;
    int next;

    for(int i = 0; i < n; i++){
        cout << first << " ";
        next = first + second;
        first = second;
        second = next;
    }
}

int recursiveFibonacci(int n){
    if (n <= 1){
        return n;
    }

    return recursiveFibonacci(n - 1)+recursiveFibonacci(n - 2);
}

int main(){
    int flag = 1;
    int op, n;

    while(flag){
        cout << "\n1. Iterative Fibonacci" << endl;
        cout << "2. Recursive Fibonacci" << endl;
        cout << "3. Exit" << endl;
        cout << "Choose an option: ";
        cin >> op;

        switch(op){
            case 1:
                cout << "\nEnter the number of terms: ";
                cin >> n;
                iterativeFibonacci(n);
                break;
            
            case 2:
                cout << "\nEnter the number of terms: ";
                cin >> n;
                for(int i = 0; i < n; i++){
                    cout << recursiveFibonacci(i) << " ";
                }
                break;

            case 3:
                cout << "\nExiting the program..." << endl;
                flag = 0;
                break;

            default:
                cout << "\nInvalid option. Enter from 1 to 3" << endl;
                break;
        }
    }

    return 0;
}

// Time Complexity: O(n): Iterates n times & O(2^n): Grows exponentially in recursive calls
// Space Complexity: O(1): 3 variables only & O(n): n memory frames for n recursive calls