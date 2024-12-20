#include <iostream>
#include <fstream>
#include <sstream>

using Button = std::pair<long long, long long>;
long long OFFSET = 10000000000000;

long long play_clawmachine(Button A, Button B, std::pair<long long, long long> location) {
    double pushA, pushB;

    double determinant = A.first * B.second - A.second * B.first;

    pushA = (B.second * location.first - B.first * location.second) / determinant;
    pushB = (A.first * location.second - A.second * location.first) / determinant;

    if((std::floor(pushA) == pushA) && (std::round(pushB) == pushB)) {
        return pushA * 3 + pushB;
    } else {
        return 0;
    }

}

int main(void) {
    std::fstream inputstream("day13.in");

    std::string input;
    long long ans = 0;

    while (getline(inputstream, input, '+')){
        Button A, B, location;
        std::stringstream line(input);
        std::string temp;
        inputstream >> A.first;
        getline(inputstream, temp, '+');
        inputstream >> A.second;
        getline(inputstream, temp, '+');
        inputstream >> B.first;
        getline(inputstream, temp, '+');
        inputstream >> B.second;
        getline(inputstream, temp, '=');
        inputstream >> location.first;
        location.first += OFFSET;
        getline(inputstream, temp, '=');
        inputstream >> location.second;
        location.second += OFFSET;

        ans += play_clawmachine(A, B,location);

    }
    std::cout << ans << std::endl;
}

