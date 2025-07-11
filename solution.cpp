#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

unordered_map<string, vector<string>> dependencies;
unordered_map<string, int> memo;

int calculateSteps(const string& potion) {
    // If already calculated, return memoized result
    if (memo.find(potion) != memo.end()) {
        return memo[potion];
    }
    
    // If potion has no dependencies, it's a basic ingredient (0 steps)
    if (dependencies[potion].empty()) {
        memo[potion] = 0;
        return 0;
    }
    
    // Calculate maximum steps among all ingredients
    int maxSteps = 0;
    for (const string& ingredient : dependencies[potion]) {
        maxSteps = max(maxSteps, calculateSteps(ingredient));
    }
    
    // This potion takes max(ingredient steps) + 1
    memo[potion] = maxSteps + 1;
    return memo[potion];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    // Read potion definitions
    for (int i = 0; i < n; i++) {
        string potionName;
        int k;
        cin >> potionName >> k;
        
        vector<string> ingredients(k);
        for (int j = 0; j < k; j++) {
            cin >> ingredients[j];
        }
        
        dependencies[potionName] = ingredients;
    }
    
    // Read target potion
    string target;
    cin >> target;
    
    // Calculate and output the minimum steps
    cout << calculateSteps(target) << endl;
    
    return 0;
}