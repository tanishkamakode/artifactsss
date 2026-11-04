#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int comparisons = 0;

int partition(int arr[], int low, int high){
    int pivot = arr[high];
    int idx = low - 1;

    for(int i = low; i < high; i++){
        comparisons++;

        if(arr[i] <= pivot){
            idx++;
            swap(arr[idx], arr[i]);
        }
    }

    idx++;
    swap(arr[idx], arr[high]);
    return idx;
}

void deterministicQuickSort(int arr[], int low, int high){
    if(low < high){
        int p = partition(arr, low, high);
        deterministicQuickSort(arr, low, p - 1);
        deterministicQuickSort(arr, p + 1, high);
    }
}

void randomizedQuickSort(int arr[], int low, int high){
    if (low < high){
        int randomIndex = low + rand() % (high - low + 1);
        swap(arr[randomIndex], arr[high]);

        int p = partition(arr, low, high);
        deterministicQuickSort(arr, low, p - 1);
        deterministicQuickSort(arr, p + 1, high);
    }
}

int main(){
    int n, op, flag = 1;
    int arr[10];

    while(flag == 1){
        cout << "\n1. Deterministic Quick Sort" << endl;
        cout << "2. Randomied Quick Sort" << endl;
        cout << "3. Exit" << endl;
        cout << "Choose an option: ";
        cin >> op;

        switch(op){
            case 1:
                cout << "\nEnter the number of terms: ";
                cin >> n;
                cout << "\nEnter the elements: ";
                for(int i = 0; i < n; i++){
                    cin >> arr[i];
                }

                comparisons = 0;
                deterministicQuickSort(arr, 0, n - 1);

                cout << "Deterministic Quick Sort: ";
                for(int i = 0; i < n; i++){
                    cout << arr[i] << " ";
                }

                cout << "\nComparisons: " << comparisons << endl;
                break;

            case 2:
                cout << "\nEnter the number of terms: ";
                cin >> n;
                cout << "\nEnter the elements: ";
                for(int i = 0; i < n; i++){
                    cin >> arr[i];
                }

                srand(time(0));
                comparisons = 0;
                randomizedQuickSort(arr, 0, n - 1);

                cout << "\nRandomized Quick Sort: ";
                for(int i = 0; i < n; i++){
                    cout << arr[i] << " ";
                }

                cout << "\nComparisons: " << comparisons << endl;
                break;

            case 3:
                cout << "Exiting the program..." << endl;
                flag = 0;
                break;

            default:
                cout << "Invalid option. Choose from 1 to 3" << endl;
                break;
        }
    }
    return 0;
}

// Time Complexity: O(n log n)/O(n ^ 2)
// Space Complexity: O(log n)/O(n)
