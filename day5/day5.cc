#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <sstream>

int part1() {
    return 0;
}

std::unordered_map<int, std::unordered_set<int> > ordering_map;//contains map of undorderings

int main(void) {
    std::fstream input_stream("test.in");
    std::string input;
    int count = 0;

    //get ordering_map
    while (getline(input_stream, input)) {
        if (input == "") {
            break;
        }
        int first = stoi(input.substr(0, input.find('|')));
        int second = stoi(input.erase(0, input.find('|') + 1));
        ordering_map[second].insert(first);
    }


    while (getline(input_stream, input)) {
        std::stringstream line(input);
        std::vector<int> pages;
        std::string number;
        while(getline(line, number, ',')) {
            pages.push_back(stoi(number));
        }

        int is_in_order = true;
        for (int i = 0; i < pages.size() - 1; i++) {
            std::unordered_set<int> set = ordering_map[pages[i]];
            for (int j = i + 1; j < pages.size(); j++) {
                if (set.find(pages[j]) != set.end()) {
                    is_in_order = false;
                    break;
                }
            }

        }

        if (is_in_order) {
            int mid = pages[pages.size() / 2];
            count += mid;
        }
    }

    std::cout << count << '\n';
}
