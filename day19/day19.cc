#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

std::vector<std::string> towels;
std::vector<std::string> patterns;
std::vector<int> dp;
std::vector<long long> dp2;

int helper(std::string &str, int pos) {
    if (pos == -1) return 1;
    if (dp[pos] != 0) {
        return dp[pos];
    }
    int status = 0;
    for (auto towel : towels) {
        bool endsWith = true;
        if (towel.size() > pos + 1) {
            continue;
        }
        std::string ss = str.substr(pos - towel.size() + 1, towel.size());

        if (ss == towel) {
            int res = helper(str, pos - towel.size());
            if (dp[pos] != 1) {
                dp[pos] = res;
            }
            if (dp[pos] == 1) {
                status = 1;
            }
        }
    }
    if (status != 1) {
        dp[pos] = 2;
    }
    return dp[pos];
}

long long helper2(std::string &str, int pos) {
    dp2 = std::vector<long long>(str.size(), 0);
    for (int i = 0; i < str.size(); i++) {
        long long count = 0;
        for (auto towel : towels) {
            if (towel.size() > i + 1) {
                continue;
            }
            std::string ss = str.substr(i - towel.size() + 1, towel.size());
            if (ss == towel && i + 1 == towel.size()){
                count++;
            } else if (ss == towel) {
                count += dp2[i - towel.size()];
            }
        }
        dp2[i] = count;
    }
    return dp2[str.size() - 1];
}

int part1() {
    int ans = 0;
    for (std::string &pattern : patterns) {
        dp = std::vector<int>(pattern.size(), 0);
        helper(pattern, pattern.size() - 1);

        if (dp[pattern.size() - 1] == 1) {
            ans++;
        }
    }
    return ans;
}

long long part2() {
    long long ans = 0;
    for (std::string &pattern : patterns) {
        ans += helper2(pattern, pattern.size() - 1);
    }
    return ans;
}

int main(void) {
    std::string t;
    std::string input;

    std::fstream inputstream("day19.in");

    getline(inputstream, t);
    std::stringstream towelstream(t);
    while (getline(towelstream, input, ',')) {
        input.erase(std::remove_if(input.begin(), input.end(), ::isspace), input.end());
        towels.push_back(input);
    }
    getline(inputstream, input);
    while (getline(inputstream, input)) {
        patterns.push_back(input);
    }
    int part1ans = part1();
    std::cout << part1ans << std::endl;
    long long part2ans = part2();
    std::cout << part2ans << std::endl;
}
