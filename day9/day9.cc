#include <fstream>
#include <vector>
#include <iostream>

long long part1(std::string input) {
    long long checksum = 0;
    int count = 0;
    int position = 0;

    for (int i = 0; i < input.size(); i++) {
        int num = input[i] - '0';
        if (i % 2 == 0) {
            float pos_total = 0.5 * num * (position + position + num - 1);
            std::cout << pos_total<< '\n';

            checksum += (int)pos_total * count;
            position += num;
            count++;
        } else {
            position += num;
        }
    }
/*
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[i] - '0'; j++) {
            if (i % 2 == 0) {
                vec.push_back(count);
            } else {
                vec.push_back(-1);
            }
        }
        if (i % 2 == 0) count++;
    }
    int pos = 0;
    int endpos = vec.size() - 1;

    while (pos <= endpos) {
        if (vec[pos] == -1) {
            checksum += vec[endpos] * pos;
            do {
                endpos--;
            } while (vec[endpos] == -1);
        } else {
            checksum += vec[pos] * pos;
        }
        pos++;
    }
*/
    return checksum;
}

long long part2(std::string input) {
    long long checksum = 0;
    std::vector<int> vec;
    std::vector<int> data;
    std::vector<int> spaces;
    int count = 0;
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[i] - '0'; j++) {
            if (i % 2 == 0) {
                vec.push_back(count);
            } else {
                vec.push_back(-1);
            }
        }
        if (i % 2 == 0) count++;
    }

    int p = vec.size() - 1;
    while (p > 0) {
        if (vec[p] == -1) {
            p--;
        } else {
            int c = 0;
            while (vec[p] == vec[p - c]) c++;
            //c is the number of conseq data
            int frontp = 0;

            //search for open space from the start
            bool found_space = false;
            while (frontp < p) {
                int space_count = 0;
                if (vec[frontp] == -1) {
                    while (vec[frontp] == vec[frontp + space_count]) space_count++;
                    if (space_count >= c) { //open space found
                        while (c > 0) {
                            vec[frontp] = vec[p];
                            vec[p] = -1;
                            c--;
                            frontp++;
                            p--;
                        }
                        found_space = true;
                        break;
                    } else {
                        frontp += space_count + 1;
                        space_count = 0;
                    }
                } else {
                    frontp++;
                }
            }
            if (!found_space) {
                int val = vec[p];
                while (vec[p] == val) p--;
            }
        }
    }

    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] > 0) {
            checksum += i * vec[i];
        }
    }



    return checksum;
}

int main (void) {
    std::fstream inputstream("test.in");

    std::string input;


    inputstream >> input;

    long long part1ans = part1(input);

    std::cout << part1ans << std::endl;
}
