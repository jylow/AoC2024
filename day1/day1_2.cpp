#include <unordered_map>
#include <fstream>
#include <iostream>
#include <string>

int main(void) {
    std::unordered_map<int, int> map_a;
    std::unordered_map<int, int> map_b;

    std::ifstream inputFile("d1.in");
    std::string line;
    int first, second;

    while (inputFile >> first >> second) {
        map_a[first] += 1;
        map_b[second] += 1;
    }

    long total = 0;
    for (auto &[key, value] : map_a) {
        int map_b_count = map_b[key];
        total += key * value * map_b_count;
    }

    std::cout << total << '\n';

    return 0;
}
