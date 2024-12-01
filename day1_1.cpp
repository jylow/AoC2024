#include <fstream>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main(void) {
    std::vector<int> list_a;
    std::vector<int> list_b;

    std::ifstream inputFile("d1.in");
    std::string line;

    while (getline(inputFile, line)) {
        int pos = line.find(' ');
        std::string first = line.substr(0, pos);
        line.erase(0, pos + 1);
        list_a.push_back(std::stoi(first));
        list_b.push_back(std::stoi(line));
    }

    std::sort(list_a.begin(), list_a.end());
    std::sort(list_b.begin(), list_b.end());

    long diff = 0;
    for (int i = 0; i < list_a.size(); i++) {
        diff += abs(list_a[i] - list_b[i]);
    }

    std::cout << diff << '\n';

    return 0;
}
