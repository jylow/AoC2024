#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>

int BLINKLIMIT = 75;

long long part1(std::unordered_map<std::string, long long> stonemap, int blink_count){
    std::unordered_map<std::string, long long> newmap;
    if (blink_count == BLINKLIMIT) {
        long long ans = 0;
        for (auto &[key, count]: stonemap) {
            ans += count;
        }
        return ans;
    }
    for (auto &[stone, count]: stonemap) {
        if (stone == "0") {
            newmap["1"] += count;
        } else if (stone.size() % 2 == 0) {
            std::string a = stone.substr(0, stone.size() / 2);
            std::string b = stone.substr(stone.size() / 2, stone.size() / 2);

            int c = 0;
            for (char letter : a) {
               if (letter == '0') {
                    c++;
                } else {
                    break;
                }
            }
            a.erase(0, std::min((int)a.size() - 1, c));
            c = 0;
            for (char letter : b) {
               if (letter == '0') {
                    c++;
                } else {
                    break;
                }
            }
            b.erase(0, std::min((int)b.size() - 1, c));

            newmap[a] += count;
            newmap[b] += count;
        } else {
            newmap[std::to_string(stoll(stone) * 2024)] += count;
        }
    }
    return part1(std::move(newmap), ++blink_count);
}

int main(void) {
    std::fstream inputstream("day11.in");
    int input;
    std::unordered_map<std::string, long long> stonemap;
    while (inputstream >> input){
        stonemap[std::to_string(input)]++;
    }

    long long part1ans = part1(stonemap, 0);
    std::cout << part1ans << std::endl;
}
