#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

const long long BASE = 256;
const long long MOD = 1000000007;

// Stores the result and performance statistics
struct Result {
    vector<int> positions;
    long long charComparisons = 0;
    long long hashComparisons = 0;
    double timeTaken = 0.0;
};

// Naive String Matching Algorithm
Result naiveSearch(const string& text, const string& pattern) {
    Result result;

    int n = text.length();
    int m = pattern.length();

    auto start = high_resolution_clock::now();

    for (int i = 0; i <= n - m; i++) {
        int j = 0;

        while (j < m) {
            result.charComparisons++;

            if (text[i + j] != pattern[j])
                break;

            j++;
        }

        if (j == m)
            result.positions.push_back(i);
    }

    auto stop = high_resolution_clock::now();

    result.timeTaken =
        duration<double, milli>(stop - start).count();

    return result;
}

// Calculates the hash of a string
long long calculateHash(const string& str, int length) {
    long long hash = 0;

    for (int i = 0; i < length; i++) {
        hash = (hash * BASE +
                static_cast<unsigned char>(str[i]) + 1) % MOD;
    }

    return hash;
}

// Rabin-Karp String Matching Algorithm
Result rabinKarpSearch(const string& text,
                       const string& pattern) {
    Result result;

    int n = text.length();
    int m = pattern.length();

    auto start = high_resolution_clock::now();

    long long patternHash = calculateHash(pattern, m);
    long long windowHash = calculateHash(text, m);

    // BASE^(m-1) modulo MOD
    long long highestPower = 1;

    for (int i = 1; i < m; i++) {
        highestPower = (highestPower * BASE) % MOD;
    }

    for (int i = 0; i <= n - m; i++) {
        result.hashComparisons++;

        // Verify characters only when hashes match
        if (patternHash == windowHash) {
            int j = 0;

            while (j < m) {
                result.charComparisons++;

                if (text[i + j] != pattern[j])
                    break;

                j++;
            }

            if (j == m)
                result.positions.push_back(i);
        }

        // Calculate the next window's rolling hash
        if (i < n - m) {
            long long leading =
                (static_cast<unsigned char>(text[i]) + 1)
                * highestPower % MOD;

            windowHash =
                (windowHash - leading + MOD) % MOD;

            windowHash =
                (windowHash * BASE +
                 static_cast<unsigned char>(text[i + m]) + 1)
                % MOD;
        }
    }

    auto stop = high_resolution_clock::now();

    result.timeTaken =
        duration<double, milli>(stop - start).count();

    return result;
}

// Displays results and statistics
void displayResult(const string& algorithm,
                   const Result& result) {
    cout << "\n--- " << algorithm << " ---\n";

    if (result.positions.empty()) {
        cout << "Pattern not found.\n";
    } else {
        cout << "Pattern found at positions (0-based): ";

        for (int pos : result.positions)
            cout << pos << " ";

        cout << "\nPositions (1-based): ";

        for (int pos : result.positions)
            cout << pos + 1 << " ";

        cout << "\nTotal occurrences: "
             << result.positions.size() << "\n";
    }

    cout << "Character comparisons: "
         << result.charComparisons << "\n";

    if (algorithm == "Rabin-Karp")
        cout << "Hash comparisons: "
             << result.hashComparisons << "\n";

    cout << fixed << setprecision(6);
    cout << "Execution time: "
         << result.timeTaken << " ms\n";
}

int main() {
    string text, pattern;
    int choice;

    cout << "====================================\n";
    cout << "       STRING MATCHING PROJECT\n";
    cout << "====================================\n";

    cout << "\nEnter the text: ";
    getline(cin, text);

    cout << "Enter the pattern to search: ";
    getline(cin, pattern);

    if (pattern.empty()) {
        cout << "\nError: Pattern cannot be empty.\n";
        return 1;
    }

    if (pattern.length() > text.length()) {
        cout << "\nPattern is longer than the text.\n";
        cout << "No occurrences are possible.\n";
        return 0;
    }

    do {
        cout << "\n========== MENU ==========\n";
        cout << "1. Naive String Matching\n";
        cout << "2. Rabin-Karp Algorithm\n";
        cout << "3. Compare Both Algorithms\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number.\n";
            return 1;
        }

        switch (choice) {
            case 1: {
                Result naive = naiveSearch(text, pattern);
                displayResult("Naive String Matching", naive);
                break;
            }

            case 2: {
                Result rk = rabinKarpSearch(text, pattern);
                displayResult("Rabin-Karp", rk);
                break;
            }

            case 3: {
                Result naive = naiveSearch(text, pattern);
                Result rk = rabinKarpSearch(text, pattern);

                displayResult("Naive String Matching", naive);
                displayResult("Rabin-Karp", rk);

                cout << "\n========== COMPARISON ==========\n";

                if (naive.positions == rk.positions)
                    cout << "Both algorithms returned identical matches.\n";
                else
                    cout << "Warning: Results differ.\n";

                cout << "Naive character comparisons: "
                     << naive.charComparisons << "\n";

                cout << "Rabin-Karp character comparisons: "
                     << rk.charComparisons << "\n";

                cout << "Rabin-Karp hash comparisons: "
                     << rk.hashComparisons << "\n";

                cout << "Note: Execution times vary between runs.\n";
                break;
            }

            case 0:
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
