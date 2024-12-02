#include <iostream>
#include <fstream>
#include <vector>

int main(void) {

    std::fstream inputstream("day2.in");

    int a, b;
    std::vector<int> vec;
    int count = 0;
    std::string input;

    while (getline(inputstream, input)) {

        std::string value;
        while (input.find(' ') != std::string::npos){
            value = input.substr(0, input.find(' '));
            vec.push_back(stoi(value));
            input.erase(0, input.find(' ') + 1);
        }
        vec.push_back(stoi(input));

        int isValid = true;
        int isAsc = 0;

        isAsc = vec[0] < vec[1] ? 1 : -1;

        for (int i = 0; i < vec.size() - 1; i++) {
            int diff = (vec[i + 1] - vec[i]) * isAsc;
            if (diff > 3 || diff <= 0) {
                isValid = false;
                break;
            }
        }

        if (isValid) count++;
        vec.clear();
    }
    std::cout << count << '\n';
}
