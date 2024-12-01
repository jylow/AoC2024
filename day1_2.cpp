#include <unordered_map>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main(void) {
    std::unordered_map<int, int> map_a;
    std::unordered_map<int, int> map_b;

    std::ifstream inputFile("d1.in");
    std::string line;

    while (getline(inputFile, line)) {
        int pos = line.find(' ');
        int first = stoi(line.substr(0, pos));
        line.erase(0, pos + 1); //we get the second element
        int second = stoi(line);

        if (map_a.find(first) == map_a.end()) {
            map_a[first] = 1;
        } else {
            map_a[first] += 1;
        }
        if (map_b.find(second) == map_b.end()) {
            map_b[second] = 1;
        } else {
            map_b[second] += 1;
        }
    }

    long total = 0;
    for (auto &[key, value] : map_a) {
        int map_b_count = map_b[key];
        total += key * value * map_b_count;
    }

    std::cout << total << '\n';

    return 0;
}
