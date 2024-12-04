#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<std::string> grid;
std::string XMAS = "XMAS";
std::vector<std::pair<int, int>> direction_change = {{-1,0}, {-1,1}, {-1,-1}, {0,1}, {0,-1}, {1,0}, {1,1}, {1,-1}};

int xmas_checker(int x, int y, int direction, int count) {
    if (count == 4) {
        return 1;
    }
    if (x < 0 || y < 0 || x >= grid.size() || y >= grid[0].size()) {
        return 0;
    }
    if (grid[x][y] == XMAS[count]) {
        return xmas_checker(x + direction_change[direction].first,
                            y + direction_change[direction].second,
                            direction,
                            count + 1);
    }
    return 0;
}

int part1() {
    int count = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == 'X') {
                for (int k = 0; k < 9; k++) {
                    count += xmas_checker(i + direction_change[k].first,
                                          j + direction_change[k].second,
                                          k,
                                          1);
                }
            }
        }
    }
    return count;
}

int x_mas_checker(int x, int y) {
    if (x > 0 && x < grid.size() - 1 && y > 0 && y < grid.size() - 1) {
        int m = 0;
        int s = 0;
        for (int a : {-1, 1}) {
            for (int b : {-1, 1}) {
                switch(grid[x+a][y+b]) {
                    case 'M':
                        m++;
                        break;
                    case 'S':
                        s++;
                        break;
                    default:
                        return false;
                }
            }
        }
        return ((m == 2) && (s == 2) && grid[x - 1][y - 1] != grid[x + 1][y + 1]);
    }
    return false;
}


int part2() {
    int count = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == 'A' && x_mas_checker(i, j)) {
                count++;
            }
        }
    }
    return count;

}

int main(void) {
    std::fstream inputstream("day4.in");
    std::string input;

    int count = 0;

    while (inputstream >> input) {
        grid.push_back(input);
    }

    int part1ans = part1();
    int part2ans = part2();

    std::cout << part1ans << '\n';
    std::cout << part2ans << '\n';

}
