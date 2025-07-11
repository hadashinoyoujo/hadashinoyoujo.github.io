#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

class Solution {
public:
    long long maxSum(std::vector<int>& nums, int m, int k) {
        int n = nums.size(), sum = 0, max = 0, count = 0;
        std::map<int, int> map;
        for(int i = 0, j = k - 1; j < n; ++i, ++j) {
            if(i == 0) {
                for(; i <= k - 1; ++i) {
                    sum += nums[i];

                    if(map.find(nums[i]) == map.end()) {
                        map[nums[i]] = 1;
                        ++count;
                    }
                    else {
                        if(map[nums[i]] == 1) {
                            --count;
                        }
                        ++map[nums[i]];
                    }
                }
                
                if(count >= m) {
                    max = std::max(max, sum);
                }
                i = 0;
            }
            else {
                sum = sum - nums[i - 1] + nums[j];

                --map[nums[i - 1]];
                if(map[nums[i - 1]] == 0) {
                    map.erase(nums[i - 1]);
                    --count;
                }
                else if(map[nums[i - 1] == 1]) {
                    ++count;
                }

                if(map.find(nums[j]) == map.end()) {
                    map[nums[j]] = 1;
                    ++count;
                }
                else {
                    if(map[nums[j]] == 1) {
                        --count;
                    }
                    ++map[nums[j]];
                }

                if(count >= m) {
                    max = std::max(max, sum);
                }
            }
        }
        return max;
    }
};

int main() {
    std::vector<int> nums = {1, 2, 1, 2, 1, 2, 1};
    std::cout << "Run the LeetCode Solution..." << "\n";
    Solution solution;
    long long result = solution.maxSum(nums, 3, 3);
    std::cout << "The maximum sum of the subarray is: " << result << std::endl;
    std::cout << "End the Solution..." << std::endl;
    return 0;
}
