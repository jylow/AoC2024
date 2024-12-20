#include <climits>
#include <iostream>
#include <fstream>
#include <sstream>

using Button = std::pair<long long, long long>;
//long long OFFSET = 10000000000000;
long long OFFSET = 0;

long long play_clawmachine(Button A, Button B, std::pair<long long, long long> location) {
    long long cost = LONG_MAX;
    bool is_swapped = false;
    if (A.first < B.first) {
        std::swap(A, B);
        is_swapped = true;
    }
    long long Acount = std::floor(location.first / A.first);
    long long Bcount = 0;

    while (Acount > 0) {
        //std::cout << Acount << " " << Bcount << std::endl;
        long long x = Acount * A.first + Bcount * B.first;
        if (x > location.first) {
            Acount--;
            continue;
        } else if (x < location.first) {
            Bcount++;
            continue;
        }

        if ((Acount * A.second + Bcount * B.second) == location.second) {
            //std::cout << Acount << " " << Bcount << std::endl;
            if (is_swapped) {
                cost = std::min(cost, Bcount * 3 + Acount);
            } else {
                cost = std::min(cost, Acount * 3 + Bcount);
            }
            Acount--;
        }
        Acount--;
    }

    //std::cout << cost << std::endl;
    return cost == LONG_MAX ? 0 : cost;

}

int main(void) {
    std::fstream inputstream("test.in");

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

        ans += play_clawmachine(A, B, location);
        std::cout << ans << std::endl;
    }
    std::cout << ans << std::endl;
}
