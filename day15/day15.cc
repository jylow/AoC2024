#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using Position = std::pair<int, int>;

Position robot_position; //row, col
std::unordered_map<char, Position> directions = {{'^', {-1, 0}},
                                    {'>', {0, 1}},
                                    {'v', {1, 0}},
                                    {'<', {0, -1}}};

bool simulate(Position pos, Position dir, std::vector<std::string> &grid) {
    char c = grid[pos.first][pos.second];
    bool res;

    if (c == '@') {
        res = simulate(std::make_pair(pos.first + dir.first, pos.second + dir.second), dir, grid);
        if (res) {
            grid[pos.first][pos.second] = '.';
            //update robot position
            robot_position.first += dir.first;
            robot_position.second += dir.second;
        }
        return true;
    }
    if (c == '#') {
        return false;
    }

    if (c == '.') {
        grid[pos.first][pos.second] = grid[pos.first - dir.first][pos.second - dir.second];
        return true;
    }

    //c == 'O'
    res = simulate(std::make_pair(pos.first + dir.first, pos.second + dir.second), dir, grid);
    if (res) {
        grid[pos.first][pos.second] = grid[pos.first - dir.first][pos.second - dir.second];
    }
    return res;
}

int calculate(std::vector<std::string> &grid) {
    int sum = 0;
    for (int row = 1; row < grid.size(); row++) {
        for (int col = 1; col < grid[0].size(); col++) {
            if (grid[row][col] == 'O') {
                sum += row * 100 + col;
            }
        }
    }
    return sum;
}



int main(void) {
    std::fstream inputstream("day15.in");
    std::vector<std::string> grid;
    std::vector<char> moves;
    int startrow = 0;
    std::string line;

    while(getline(inputstream, line)) {
        if (line == "") {
            break;
        }

        for (int i = 0; i < line.size(); i++) {
            if (line[i] == '@') {
                robot_position.first = startrow;
                robot_position.second = i;
            }
        }
        grid.push_back(line);
        startrow++;
    }

    char c;
    while(inputstream >> c) {
        moves.push_back(c);
    }

    for (auto line : grid) {
        std::cout << line << std::endl;
    }
    //part1
    for (int i = 0; i < moves.size(); i++) {
        std::cout << moves[i] << std::endl;
        simulate(robot_position, directions[moves[i]], grid);
    }

    std::cout << calculate(grid) << std::endl;
}
