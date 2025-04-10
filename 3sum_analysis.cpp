#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        int n = nums.size();
        sort(nums.begin(), nums.end());
        
        for (int i = 0; i < n - 2; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            
            for (int j = i + 1; j < n - 1; j++) {
                if (j > i + 1 && nums[j] == nums[j - 1]) continue;
                
                for (int k = j + 1; k < n; k++) {
                    if (k > j + 1 && nums[k] == nums[k - 1]) continue;
                    
                    if (nums[i] + nums[j] + nums[k] == 0) {
                        result.push_back({nums[i], nums[j], nums[k]});
                    }
                }
            }
        }
        return result;
    }
};

vector<pair<int, vector<int>>> generate_test_cases() {
    vector<int> sizes = {100, 200, 400, 800, 1600, 4600, 8000};
    vector<pair<int, vector<int>>> test_cases;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(-5000, 5000);

    for (int size : sizes) {
        vector<int> nums;
        
        for (int i = 0; i < size * 0.9; ++i) {
            nums.push_back(dist(gen));
        }
        
        for (int i = 0; i < size * 0.1; ++i) {
            int a = dist(gen);
            int b = dist(gen);
            nums.push_back(a);
            nums.push_back(b);
            nums.push_back(-(a + b));
        }
        
        sort(nums.begin(), nums.end());
        nums.erase(unique(nums.begin(), nums.end()), nums.end());
        shuffle(nums.begin(), nums.end(), gen);
        
        test_cases.emplace_back(nums.size(), nums);
    }
    return test_cases;
}

int main() {
    Solution solver;
    auto test_cases = generate_test_cases();

    cout << "Benchmark Results:\n";
    cout << "Array Size\tExecution Time (ms)\n";
    cout << "---------------------------------\n";

    for (const auto& [size, nums] : test_cases) {
        vector<int> copy_nums = nums; 
        
        auto start = chrono::high_resolution_clock::now();
        auto result = solver.threeSum(copy_nums);
        auto end = chrono::high_resolution_clock::now();
        
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
        cout << size << "\t\t" << duration.count();
        cout << (result.empty() ? "\t(WARNING: No triplets)" : "") << endl;
        
        if (duration.count() > 50000) {
            cout << "\nStopping test: Execution time exceeds 50 seconds\n";
            break;
        }
    }

    return 0;
}
