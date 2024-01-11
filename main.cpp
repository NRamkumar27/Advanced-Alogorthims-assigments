#include <iostream>

// Returns a pair of indices in arr[0..n-1] with sum equal to 'K'
std::pair<int, int> getPairsCount(int arr[], int n, int K) {
    // Iterate through each pair of elements
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            // Check if the pair's sum is equal to the target
            if (arr[i] + arr[j] == K) {
                // Return the indices of the two numbers
                return {i, j};
            }
        }
    }

    // Return an empty pair if no solution is found
    return {-1, -1};
}

// Driver function to test the above function
int main() {
    int nums[] = {2, 11, 7, 15};
    int n = sizeof(nums) / sizeof(nums[0]);
    int target = 9;

    // Function Call
    auto result = getPairsCount(nums, n, target);

    // Display the result
    if (result.first != -1) {
        std::cout << "Indices: " << result.first << " and " << result.second << std::endl;
    } else {
        std::cout << "No pair found with the given sum." << std::endl;
    }

    return 0;
}
