#include <iostream>
#include <algorithm>
using namespace std;

int knapsack(int n, int W, int wt[], int profit[]){
    int dp[101][101] = {0};

    for(int i = 1; i <= n; i++){
        for(int w = 1; w <= W; w++){
            if(wt[i] <= w){
                dp[i][w] = max(dp[i-1][w], dp[i-1][w-wt[i]] + profit[i]);
            } else {
                dp[i][w] = dp[i-1][w];
            }
        }
    }

    return dp[n][W];
}

int main(){
    int n, W;
    cout << "Enter the number of items: ";
    cin >> n;

    int wt[101], profit[101];

    cout << "Enter the weights: ";
    for(int i = 1; i <= n; i++){
        cin >> wt[i];
    }

    cout <<"Enter the profits: ";
    for(int i = 1; i <= n; i++){
        cin >> profit[i];
    }

    cout << "Enter the maximum knapsack capacity: ";
    cin >> W;

    cout << "Maximum profit: " << knapsack(n, W, wt, profit) << endl;

    return 0;
}

// Time Complexity: O(n * W)
// Space Complexity: O(n * W)