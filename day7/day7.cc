#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include<chrono>

std::vector<long long> parse_line(std::string line) {
    std::vector<long long> vec;
    long long val;

    //get first value
    long long head = stoll(line.substr(0, line.find(':')));
    vec.push_back(head);
    line.erase(0, line.find(':') + 2);

    std::stringstream sstream(line);
    while (sstream >> val) {
        vec.push_back(val);
    }
    return vec;
}

long long helper2(long long a, long long b, int val) {
    if (val == 0) {
        return a + b;
    } else if (val == 1) {
        return a * b;
    } else {
        std::string t = std::to_string(a) + std::to_string(b);
        return stoll(t);
    }
}

long long calibrate(std::vector<long long> &vec, int count) {
    long long bitmask = 0;
    long long target = vec[0];
    while (bitmask < std::pow(count, vec.size())) {
        long long total = vec[1];
        long long bm = bitmask;
        for (int i = 2; i < vec.size(); i++) {
            total = helper2(total, vec[i], bm % count);
            bm /= count;
        }
        if (total == target) return total;
        bitmask++;
    }
    return 0;
}

long long part1(std::vector<std::vector<long long>> &lines) {
    long long ans = 0;
    for (auto &line : lines){
       ans += calibrate(line, 2);
    }
    return ans;
}

long long part2(std::vector<std::vector<long long>> &lines) {
    long long ans = 0;
    for (auto &line : lines){
       ans += calibrate(line, 3);
    }
    return ans;
}


int main(void) {
    std::fstream inputstream("day7.in");
    std::vector<std::vector<long long>> lines;
    std::string line;

    while (getline(inputstream, line)) {
        lines.push_back(parse_line(line));
    }

    auto start = std::chrono::high_resolution_clock::now();
    long long part1ans = part1(lines);
    std::cout << part1ans << std::endl;
    auto t1 = std::chrono::high_resolution_clock::now();
    auto time1 = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - start);
    std::cout << time1.count() << std::endl;

    long long part2ans = part2(lines);
    std::cout << part2ans << std::endl;
    auto t2 = std::chrono::high_resolution_clock::now();
    auto time2 = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - start);
    std::cout << time2.count() << std::endl;

}
