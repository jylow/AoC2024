#include <iostream>
#include <fstream>
#include <vector>

using Gardengrid = std::vector<std::vector<std::pair<char, bool>>>; //pair of grid character and isvisited
//
Gardengrid garden_grid;
std::vector<std::pair<int, int>> directions = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};

std::pair<int, int> calculatecost(int row, int col) {
    if (garden_grid[row][col].second == true) {
        return std::make_pair(0, 0);
    }
    garden_grid[row][col].second = true;
    int perimeter = 4;
    int area = 1;
    for (auto [rowdiff, coldiff]: directions) {
        int newrow = row + rowdiff;
        int newcol = col + coldiff;
        if (newrow < 0 || newrow >= garden_grid.size() || newcol < 0 || newcol >= garden_grid[0].size()){
            continue;
        }
        if (garden_grid[row][col].first == garden_grid[newrow][newcol].first) {
            //int p, a;
            perimeter--;
            auto [p, a] = calculatecost(newrow, newcol);
            perimeter += p;
            area += a;
        }
    }
    return std::make_pair(perimeter, area);
}

int part1(){
    int ans = 0;
    for (int i = 0; i < garden_grid.size(); i++) {
        for (int j = 0; j < garden_grid[0].size(); j++) {
            auto [perimeter, area] = calculatecost(i, j);
            ans += perimeter * area;
        }
    }
    return ans;
}

int main(void) {
    std::fstream inputstream("day12.in");
    std::string input;

    while (inputstream >> input) {
        std::vector<std::pair<char, bool>> vec;
        for (char c : input) {
            vec.push_back(std::make_pair(c, false));
        }
        garden_grid.push_back(vec);
    }

    int part1ans = part1();
    std::cout << part1ans << std::endl;
}
