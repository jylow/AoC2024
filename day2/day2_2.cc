#include <iostream>
#include <fstream>
#include <vector>

bool is_safe_vector(std::vector<int> vec) {
    int is_safe = true;
    int isAsc = 0;

    isAsc = vec[0] < vec[1] ? 1 : -1;

    for (int i = 0; i < vec.size() - 1; i++) {
        int diff = (vec[i + 1] - vec[i]) * isAsc;
        if (diff > 3 || diff <= 0) {
            is_safe = false;
            break;
        }
    }

    return is_safe;
}

int main(void) {

    std::fstream inputstream("day2.in");

    int a, b;
    std::vector<int> vec;
    int count = 0;
    std::string input;

    while (getline(inputstream, input)) {

        std::string value;
        bool is_safe = false;
        while (input.find(' ') != std::string::npos){
            value = input.substr(0, input.find(' '));
            vec.push_back(stoi(value));
            input.erase(0, input.find(' ') + 1);
        }
        vec.push_back(stoi(input));

        for (int i = 0; i < vec.size(); i++) {
            std::vector<int> remove_elem_vec = vec;

            remove_elem_vec.erase(remove_elem_vec.begin() + i);

            if (is_safe_vector(remove_elem_vec)) {
                count++;
                break;
            }
        }
        vec.clear();

    }
    std::cout << count << '\n';
}

