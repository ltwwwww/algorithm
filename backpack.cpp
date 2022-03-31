#include <iostream>
#include <vector>
using namespace std;

int backpack01(int room, vector<int> &cost, vector<int> &value) {
    vector<vector<int>> dp(cost.size(), vector<int>(room + 1, 0));
    // for (int i = 0;  i < cost.size(); ++i) {
    //     dp[i][0] = 0;
    // }

    for (int i = room; i >= cost[0]; --i) {
        dp[0][i] = value[0];
    }

    for (int i = 1; i < cost.size(); ++i) {
        for (int j = 0; j <= room; ++j) {
            if (cost[i] <= j)
                dp[i][j] = max(dp[i - 1][j - cost[i]] + value[i], dp[i - 1][j]);
            else 
                dp[i][j] = dp[i - 1][j];
        }
    }
 
    return dp[cost.size() - 1][room];
}

int backpackPro(int room, vector<int> &cost, vector<int> &value) {
    vector<int> dp(room + 1, 0);
    for (int i = 0; i < cost.size(); ++i) {
        for (int j = room; j >= cost[i]; --j) {
            dp[j] = max(dp[j], dp[j - cost[i]] + value[i]);
        }
    }
    return dp[room];
}

int main() {
    vector<int> cost = {1, 3, 4, 1, 4, 5};
    vector<int> value = {15, 20, 30, 30, 40, 90};
    cout << backpack01(5, cost, value) << endl;
    cout << backpackPro(5, cost, value) << endl;
    return 0;
}