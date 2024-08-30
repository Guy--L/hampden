#include <iostream>
#include <vector>
#include <algorithm>

struct Person {
    int height;
    int weight;
};

// Comparator to sort people by height ascending and weight descending
bool compare(const Person &a, const Person &b) {
    if (a.height == b.height) {
        return a.weight > b.weight;  // Sort by descending weight for the same height
    }
    return a.height < b.height;
}

// Function to determine the largest possible number of people in the tower
int largestTower(std::vector<Person> &people) {
    int n = people.size();
    if (n == 0) return 0;

    // Sort people by height ascending and weight descending
    std::sort(people.begin(), people.end(), compare);

    // Vector to store the smallest ending weight of increasing subsequences of different lengths
    std::vector<int> dp;

    for (const auto &person : people) {
        int weight = person.weight;

        // Use binary search to find the location where weight should be placed
        auto it = std::lower_bound(dp.begin(), dp.end(), weight);

        if (it == dp.end()) {
            // If weight is larger than any element in dp, append it
            dp.push_back(weight);
        } else {
            // Otherwise, replace the first element in dp that is >= weight
            *it = weight;
        }
    }

    // The size of dp will be the maximum number of people in the tower
    return dp.size();
}

// Utility function to run tests
void runTests() {
    // Test case 1: General case with multiple people
    std::vector<Person> people1 = {{65, 100}, {70, 150}, {56, 90}, {75, 190}, {60, 95}, {68, 110}};
    std::cout << "Test 1 - Expected: 6, Got: " << largestTower(people1) << std::endl;

    // Test case 2: No people
    std::vector<Person> people2 = {};
    std::cout << "Test 2 - Expected: 0, Got: " << largestTower(people2) << std::endl;

    // Test case 3: All people have the same height and weight
    std::vector<Person> people3 = {{65, 100}, {65, 100}, {65, 100}};
    std::cout << "Test 3 - Expected: 1, Got: " << largestTower(people3) << std::endl;

    // Test case 4: Increasing height but decreasing weight
    std::vector<Person> people4 = {{56, 150}, {60, 140}, {65, 130}, {70, 120}};
    std::cout << "Test 4 - Expected: 1, Got: " << largestTower(people4) << std::endl;

    // Test case 5: Decreasing height and weight
    std::vector<Person> people5 = {{70, 190}, {68, 180}, {65, 170}, {60, 160}};
    std::cout << "Test 5 - Expected: 4, Got: " << largestTower(people5) << std::endl;

    // Test case 6: Increasing height and weight
    std::vector<Person> people6 = {{56, 90}, {60, 95}, {65, 100}, {70, 110}, {75, 120}};
    std::cout << "Test 6 - Expected: 5, Got: " << largestTower(people6) << std::endl;

    // Test case 7: Mixed heights and weights
    std::vector<Person> people7 = {{65, 100}, {70, 110}, {56, 95}, {75, 105}, {60, 85}, {68, 90}};
    std::cout << "Test 7 - Expected: 3, Got: " << largestTower(people7) << std::endl;
    
    // Test case 8: People with the same height but different weights
    std::vector<Person> people8 = {{65, 100}, {65, 90}, {70, 110}, {70, 95}, {75, 120}};
    std::cout << "Test 8 - Expected: 3, Got: " << largestTower(people8) << std::endl;
}

int main() {
    runTests();
    return 0;
}
