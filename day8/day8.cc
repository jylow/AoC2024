#include <fstream>
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <set>

/*
struct Location {
    int x;
    int y;
};
*/
using Location = std::pair<int, int>;

std::set<Location> antinodes;
std::unordered_map<char, std::vector<Location>> antennae_map;

std::vector<std::string> citymap;

std::vector<Location>  get_antinode(Location a, Location b, int count){
    std::vector<Location> rv;
    for (int i = 0; i < 2; i++) {
        int c = count;
        Location t = std::make_pair(a.first, a.second);
        int dx = b.first - a.first;
        int dy = b.second - a.second;
        t.first -= dx;
        t.second -= dy;
        while (c > 0 && t.first >= 0 && t.first < citymap.size() && t.second >= 0 && t.second < citymap[0].size()) {
            rv.push_back(t);
            t.first -= dx;
            t.second -= dy;
            c--;
            //printf("x: %d, y: %d", t.first, t.second);
        }
        //std::cout << std::endl;
        std::swap(a, b);
    }

    return std::move(rv);
}

int solver(int count) {
    antinodes.clear();
    antennae_map.clear();

    int ans = 0;
    //Process the different locations of antennae
    for (int row = 0; row < citymap.size(); row++) {
        for (int col = 0; col < citymap.size(); col++) {
            char val = citymap[row][col];
            if (val != '.') {
                Location loc = std::make_pair(row, col);
                antennae_map[val].push_back(loc);
            }
        }
    }

    //calculate the antinodes;
    for (auto &[key, vec] : antennae_map) {
        for (int i = 0; i < vec.size() - 1; i++) {
            for (int j = i + 1; j < vec.size(); j++) {
                std::vector<Location> rv;
                rv = get_antinode(vec[i], vec[j], count);
                for (auto &location : rv) {
                    antinodes.insert(location);
                }
                if (count > 1) {
                    antinodes.insert(vec[i]);
                    antinodes.insert(vec[j]);
                }
            }
        }
    }

    return antinodes.size();
}

int main(void) {
    std::fstream inputstream("day8.in");

    std::string input;

    while (inputstream >> input) {
        citymap.push_back(input);
    }

    int part1ans = solver(1);
    std::cout << part1ans << std::endl;
    int part2ans = solver(INT_MAX);
    std::cout << part2ans << std::endl;
}
