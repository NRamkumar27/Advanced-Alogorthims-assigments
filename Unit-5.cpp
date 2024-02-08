#include <iostream>
#include <vector>

// Function to find the longest common substring(s)
std::pair<int, std::vector<std::string>> longestCommonSubstrings(const std::string& str1, const std::string& str2) {
    int m = str1.length();
    int n = str2.length();

    // Create a 2D table to store lengths of longest common suffixes
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

    // To store the length of the longest common substring
    int maxLen = 0;

    // Fill the DP table and find the maximum length
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                maxLen = std::max(maxLen, dp[i][j]);
            }
        }
    }

    // Find all longest common substrings
    std::vector<std::string> result;
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (dp[i][j] == maxLen) {
                result.push_back(str1.substr(i - maxLen, maxLen));
            }
        }
    }

    return {maxLen, result};
}

int main() {
    std::string str1, str2;

    // Input two strings
    std::cout << "Enter the first string: ";
    std::cin >> str1;
    std::cout << "Enter the second string: ";
    std::cin >> str2;

    // Find the longest common substring(s) and its length
    auto result = longestCommonSubstrings(str1, str2);
    int longestLength = result.first;
    const std::vector<std::string>& longestSubstrings = result.second;

    // Output the length of the longest common substring(s)
    std::cout << "Length of Longest Common Substring(s): " << longestLength << std::endl;

    // Output the longest common substring(s)
    if (longestLength > 0) {
        std::cout << "Longest Common Substring(s): ";
        for (const auto& substring : longestSubstrings) {
            std::cout << substring << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
