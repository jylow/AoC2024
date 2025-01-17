#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <utility>
#include <vector>
#include <unordered_map>

using Velocity = std::pair<int, int>;
using Position = std::pair<int, int>;

int STEPS = 100;
int WIDTH = 101;
int HEIGHT = 103;


std::unordered_map<int, int> quadrant;

int calculate_position(std::vector<std::pair<Position, Velocity>> &robots) {
    int ans = 0;
    for (auto &robot : robots) {
        //std::cout << robot.first.first << " " << robot.first.second << " " << robot.second.first << " " <<robot.second.second << std::endl;
        int finalx = (robot.first.first + robot.second.first * STEPS);
        int finaly = (robot.first.second + robot.second.second * STEPS);

        while (finalx < 0) finalx += WIDTH;
        while (finaly < 0) finaly += HEIGHT;

        finalx %= WIDTH;
        finaly %= HEIGHT;

        if (finalx == WIDTH / 2 || finaly == HEIGHT / 2) {
            continue;
        }

        int q = finalx * 2 / WIDTH + finaly * 2/ HEIGHT * 2;
        quadrant[q]+=1;
        std::cout << finalx << " " <<finaly << std::endl;
        std::cout << q << std::endl;
    }

    return ans;
}

void printgrid(std::vector<std::pair<Position, Velocity>> &robots) {
    int count = 0;

    while(true) {
        //std::vector<std::vector<char>> grid (HEIGHT, std::vector<char>(WIDTH, '.'));
        std::string str(WIDTH, '.');
        std::vector<std::string> grid (HEIGHT, str);
        count++;
        std::cout << count << std::endl;

        for (auto &robot : robots) {
            robot.first.first += robot.second.first;
            while (robot.first.first < 0) robot.first.first += WIDTH;
            robot.first.first %= WIDTH;
            robot.first.second += robot.second.second;
            while (robot.first.second < 0) robot.first.second += HEIGHT;
            robot.first.second %= HEIGHT;
            //std::cout << robot.first.first << " " << robot.first.second << std::endl;
            grid[robot.first.first][robot.first.second] = 'x';
        }

        bool toprint = false;
        for (auto &string: grid) {
            if (string.find("xxxxx") != std::string::npos) {
                toprint = true;
            }
        }
        if (toprint) {
            for (auto &string: grid) {
                std::cout << string << std::endl;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}

int main(void) {
    std::fstream inputstream("day14.in");

    std::vector<std::pair<Position, Velocity>> robots;

    int px, py, vx, vy;
    std::string input;

    while(getline(inputstream, input, '=')){
        inputstream >> px;
        getline(inputstream, input, ',');
        inputstream >> py;
        getline(inputstream, input, '=');
        inputstream >> vx;
        getline(inputstream, input, ',');
        inputstream >> vy;

        std::pair<Velocity, Position> r = std::make_pair(std::make_pair(px, py), std::make_pair(vx, vy));
        robots.push_back(r);
        getline(inputstream, input, 'p');
    }
    calculate_position(robots);

    long long part1ans = 1;
    for (auto &[key, value] : quadrant) {
        std::cout << "KEY " << key << " VALUE " << value << std::endl;
        part1ans = part1ans * value;
        std::cout << part1ans << std::endl;
    }
    std::cout << part1ans << std::endl;

    printgrid(robots);
}
