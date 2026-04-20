#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main() {
    // Read first line with letters
    string line;
    getline(cin, line);
    
    // Remove spaces to get letters
    string letters;
    for (char c : line) {
        if (c != ' ') letters += c;
    }
    
    int k = letters.size();
    
    // Create map from char to index
    map<char, int> charToIndex;
    for (int i = 0; i < k; i++) {
        charToIndex[letters[i]] = i;
    }
    
    // Read cost matrix
    vector<vector<int>> cost(k, vector<int>(k));
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            cin >> cost[i][j];
        }
    }
    
    // Read number of queries
    int Q;
    cin >> Q;
    
    // Gap penalty
    const int GAP = -4;
    
    // Process each query
    for (int q = 0; q < Q; q++) {
        string s1, s2;
        cin >> s1 >> s2;
        
        int n = s1.length();
        int m = s2.length();
        
        // DP table
        vector<vector<int>> dp(n + 1, vector<int>(m + 1));
        
        // Initialize first row and column (gaps)
        dp[0][0] = 0;
        for (int i = 1; i <= n; i++) {
            dp[i][0] = dp[i-1][0] + GAP;
        }
        for (int j = 1; j <= m; j++) {
            dp[0][j] = dp[0][j-1] + GAP;
        }
        
        // Fill DP table
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                int match = dp[i-1][j-1] + cost[charToIndex[s1[i-1]]][charToIndex[s2[j-1]]];
                int gap1 = dp[i-1][j] + GAP;   // gap in s2 (star in s1)
                int gap2 = dp[i][j-1] + GAP;   // gap in s1 (star in s2)
                dp[i][j] = max({match, gap1, gap2});
            }
        }
        
        // Backtrack to reconstruct alignment
        string align1 = "", align2 = "";
        int i = n, j = m;
        
        while (i > 0 || j > 0) {
            if (i > 0 && j > 0 && dp[i][j] == dp[i-1][j-1] + cost[charToIndex[s1[i-1]]][charToIndex[s2[j-1]]]) {
                // Came from diagonal (match/mismatch)
                align1 = s1[i-1] + align1;
                align2 = s2[j-1] + align2;
                i--; j--;
            }
            else if (i > 0 && dp[i][j] == dp[i-1][j] + GAP) {
                // Came from up (gap in s2 → star in s1)
                align1 = s1[i-1] + align1;
                align2 = '*' + align2;
                i--;
            }
            else {
                // Came from left (gap in s1 → star in s2)
                align1 = '*' + align1;
                align2 = s2[j-1] + align2;
                j--;
            }
        }
        
        // Output result
        cout << align1 << " " << align2 << endl;
    }
    
    return 0;
}