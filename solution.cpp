#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class PotionSynthesizer {
private:
    unordered_map<string, vector<string>> graph; // Dependency graph: potion -> ingredients
    unordered_map<string, int> memo; // Memoization for calculated steps
    
public:
    // DFS with memoization to calculate minimum synthesis steps
    int calculateSteps(const string& potion) {
        // If already calculated, return memoized result
        if (memo.count(potion)) {
            return memo[potion];
        }
        
        // If potion has no dependencies, it's a basic ingredient (0 steps)
        if (graph[potion].empty()) {
            return memo[potion] = 0;
        }
        
        // Calculate maximum steps among all ingredients
        int maxSteps = 0;
        for (const string& ingredient : graph[potion]) {
            maxSteps = max(maxSteps, calculateSteps(ingredient));
        }
        
        // This potion takes max(ingredient steps) + 1
        return memo[potion] = maxSteps + 1;
    }
    
    void addPotion(const string& name, const vector<string>& ingredients) {
        graph[name] = ingredients;
    }
    
    int solve(const string& target) {
        return calculateSteps(target);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    PotionSynthesizer synthesizer;
    
    // Build the dependency graph
    for (int i = 0; i < n; i++) {
        string potionName;
        int k;
        cin >> potionName >> k;
        
        vector<string> ingredients(k);
        for (int j = 0; j < k; j++) {
            cin >> ingredients[j];
        }
        
        synthesizer.addPotion(potionName, ingredients);
    }
    
    // Read target potion and solve
    string target;
    cin >> target;
    
    cout << synthesizer.solve(target) << endl;
    
    return 0;
}