#include <iostream>
#include <unordered_set>
#include <queue>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// Function to check if two words differ by only one character
bool differByOne(const string &word1, const string &word2) {
    int count = 0;
    for (int i = 0; i < word1.size(); i++) {
        if (word1[i] != word2[i]) {
            count++;
        }
        if (count > 1) {
            return false;
        }
    }
    return count == 1;
}

// Function to transform one word to another word by changing only one letter at a time
vector<string> transformWord(string start, string end, unordered_set<string> &dictionary) {
    queue<vector<string>> q;  // Queue for BFS, containing paths as vectors of strings
    q.push({start});  // Initialize with the start word
    dictionary.erase(start);  // Remove start word from the dictionary

    while (!q.empty()) {
        vector<string> path = q.front();
        q.pop();
        string last = path.back();

        // Check each word in the dictionary to see if it differs by one letter
        for (auto it = dictionary.begin(); it != dictionary.end();) {
            if (differByOne(last, *it)) {
                vector<string> newPath = path;
                newPath.push_back(*it);

                if (*it == end) {
                    return newPath;  // Return the path if the end word is reached
                }

                q.push(newPath);  // Push the new path to the queue
                it = dictionary.erase(it);  // Erase the word from the dictionary
            } else {
                ++it;
            }
        }
    }

    return {};  // Return empty vector if no transformation is possible
}

int main() {
    // Define test cases with names
    vector<pair<string, string>> testCases = {
        {"DAMP", "LIKE"},  // Basic Case
        {"DAMP", "LIKE"},  // No Transformation Possible
        {"COLD", "CORD"},  // Direct Transformation
        {"COLD", "CORD"},  // Empty Dictionary
        {"HARD", "HARD"},  // Same Start and End Word
        {"FARM", "FIRM"},  // All Words in Dictionary are Identical
        {"HIT", "COG"},    // Multiple Possible Paths
        {"JUMP", "HUMP"},  // Dictionary with Non-Related Words
        {"FOUR", "FIVE"}   // Large Dictionary
    };

    // Names for test cases for better output
    vector<string> testCaseNames = {
        "Basic Case",
        "No Transformation Possible",
        "Direct Transformation",
        "Empty Dictionary",
        "Same Start and End Word",
        "All Words in Dictionary are Identical",
        "Multiple Possible Paths",
        "Dictionary with Non-Related Words",
        "Large Dictionary"
    };

    vector<unordered_set<string>> dictionaries = {
        {"DAMP", "LAMP", "LIMP", "LIME", "LIKE"},
        {"DAMP", "LAMP", "LIMP", "LIMB", "BIKE"},
        {"COLD", "CORD", "CARD", "WARD"},
        {},
        {"HARD", "HARDY", "HARDEN"},
        {"FIRM", "FIRM", "FIRM"},
        {"HOT", "DOT", "DOG", "LOT", "LOG", "COG", "HIT"},
        {"DUMP", "PUMP", "BUMP", "LUMP", "JUMP", "HUMP", "COLD", "CORD"},
        {"FOUR", "FORT", "FIRE", "FINE", "LINE", "LIVE", "FIVE"}
    };

    for (int i = 0; i < testCases.size(); ++i) {
        string start = testCases[i].first;
        string end = testCases[i].second;
        unordered_set<string> dictionary = dictionaries[i];

        vector<string> result = transformWord(start, end, dictionary);

        cout << "Test Case: " << testCaseNames[i] << "\n";
        if (!result.empty()) {
            cout << "Transformation sequence from " << start << " to " << end << ":\n";
            for (const string &word : result) {
                cout << word << " ";
            }
            cout << endl;
        } else {
            cout << "No transformation sequence found from " << start << " to " << end << "." << endl;
        }
        cout << "----------------------------------\n";
    }

    return 0;
}
