#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <string>
#include <set>

using Coordinates = std::pair<int, int>;
std::vector<Coordinates> directions = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
using Griddata = std::vector<std::vector<std::pair<int, std::set<Coordinates>>>>;

void print_grid(Griddata &largest_reachable) {
    for (auto &line : largest_reachable){
        for (auto &[height, set] : line) {
            printf("{%d, %li} ", height, set.size());
        }
        printf("\n");
    }
    printf("\n");
}

void displaydata(std::vector<std::vector<std::pair<int, int>>> &largest_reachable) {
    for (auto &line : largest_reachable){
        for (auto &[height, count] : line) {
            printf("{%d, %d} ", height, count);
        }
        printf("\n");
    }
    printf("\n");
}

std::set<Coordinates> compute_largest_reachable(int i, int j, Griddata &largest_reachable) {
    //check grid bounds
    std::pair<int, std::set<Coordinates>> &current_pos = largest_reachable[i][j];
    if (current_pos.first == 9) {
        current_pos.second.insert(std::make_pair(i, j));
        return current_pos.second;
    }
    if (largest_reachable[i][j].second.size() > 0) {
        return largest_reachable[i][j].second;
    }
    std::set<Coordinates> compute = {};
    int current_height = largest_reachable[i][j].first;
    for (auto [rowdiff, coldiff] : directions){
        if (i + rowdiff< 0 || j + coldiff  < 0 || i + rowdiff >= largest_reachable.size() || j + coldiff >= largest_reachable[0].size()) {
            continue;
        }
        if (current_height + 1 == largest_reachable[i + rowdiff][j + coldiff].first) {
            compute = compute_largest_reachable(i + rowdiff, j + coldiff, largest_reachable);
            for (Coordinates coordinate: compute) {
                current_pos.second.insert(coordinate);
            }
        }
    }
    return current_pos.second;
}

int compute_largest_reachable_part2(int i, int j, std::vector<std::vector<std::pair<int, int>>> &largest_reachable) {
    std::pair<int, int> &current_pos = largest_reachable[i][j];
    if (current_pos.first == 9) {
        current_pos.second = 1;
        return 1;
    }
    if (largest_reachable[i][j].second != -1) {
        return largest_reachable[i][j].second;
    }
    int compute = 0;
    int current_height = largest_reachable[i][j].first;
    for (auto [rowdiff, coldiff]: directions) {
        if (i + rowdiff< 0 || j + coldiff  < 0 || i + rowdiff >= largest_reachable.size() || j + coldiff >= largest_reachable[0].size()) {
            continue;
        }

        if (current_height + 1 == largest_reachable[i + rowdiff][j + coldiff].first) {
            compute += compute_largest_reachable_part2(i + rowdiff, j + coldiff, largest_reachable);
        }
    }
    largest_reachable[i][j].second = compute;
    return compute;
}

int part1(std::vector<std::vector<int>> &grid) {
    int ans = 0;
    Griddata largest_reachable;

    for (auto row : grid) {
        std::vector<std::pair<int, std::set<Coordinates>>> vec;
        for (int col : row) {
            vec.push_back(std::make_pair(col, std::set<Coordinates>()));
        }
        largest_reachable.push_back(vec);
    }

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (largest_reachable[i][j].second.size() <= 0) {
                compute_largest_reachable(i, j ,largest_reachable);
            }
            if (largest_reachable[i][j].first == 0) {
                ans += largest_reachable[i][j].second.size();
            }
        }
    }
    return ans;
}

int part2(std::vector<std::vector<int>> &grid) {
    int ans = 0;
    std::vector<std::vector<std::pair<int, int>>> largest_reachable;

    for (auto row : grid) {
        std::vector<std::pair<int, int>> vec;
        for (int col : row) {
            vec.push_back(std::make_pair(col, -1));
        }
        largest_reachable.push_back(vec);
    }

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (largest_reachable[i][j].second <= 0) {
                compute_largest_reachable_part2(i, j ,largest_reachable);
            }
            if (largest_reachable[i][j].first == 0) {
                ans += largest_reachable[i][j].second;
            }
        }
    }

    return ans;
}

int main(void) {
    std::fstream inputstream("day10.in");

    std::string line;
    std::vector<std::vector<int>> grid;

    //initialise input
    while (inputstream >> line) {
        std::vector<int> vec;
        for (char c : line) {
            vec.push_back(c - '0');
        }
        grid.push_back(vec);
    }

    int part1ans = part1(grid);
    int part2ans = part2(grid);

    std::cout << part1ans << std::endl;
    std::cout << part2ans << std::endl;
}
