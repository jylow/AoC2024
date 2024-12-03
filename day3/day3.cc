#include <cstdint>
#include <iterator>
#include <string>
#include <iostream>
#include <regex>
#include <fstream>



int part1(void) {
    std::fstream input_stream("day3.in");
    std::uint64_t total = 0;
    std::string line;

    while (getline(input_stream, line)) {
        std::regex mul_regex("mul[(][0-9]*,[0-9]*[)]");
        auto valid_sequences = std::sregex_iterator(line.begin(), line.end(), mul_regex);

        for (std::sregex_iterator i = valid_sequences; i != std::sregex_iterator(); i++){
            std::smatch match_word = *i;
            std::string sequence = match_word.str();
            sequence.erase(0, 4); // remove first 4 characters
            sequence.erase(sequence.size() - 1, 1);// remove last character

            //split the string by ,
            int first = stoi(sequence.substr(0, sequence.find(",")));
            int second = stoi(sequence.erase(0, sequence.find(",") + 1));
            total += first * second;
        }
    }
    return total;
}

int part2(void) {
    std::fstream input_stream("day3.in");
    std::uint64_t total = 0;
    std::string line;

    bool is_do = true;
    while (getline(input_stream, line)) {
        std::regex part2_regex("(mul[(][0-9]*,[0-9]*[)])|(do[(][)])|(don't[(][)])");
        auto valid_sequences = std::sregex_iterator(line.begin(), line.end(), part2_regex);

        for (std::sregex_iterator i = valid_sequences; i != std::sregex_iterator(); i++){
            std::smatch match_word = *i;
            std::string sequence = match_word.str();

            if (sequence == "do()") {
                is_do = true;
            } else if (sequence == "don't()") {
                is_do = false;
            } else if (is_do) {
                sequence.erase(0, 4); // remove first 4 characters
                sequence.erase(sequence.size() - 1, 1);// remove last character
                //split the string by ,
                int first = stoi(sequence.substr(0, sequence.find(",")));
                int second = stoi(sequence.erase(0, sequence.find(",") + 1));
                total += first * second;
            }
        }
    }
    return total;
}
int main(void) {
    uint64_t p1ans = part1();
    uint64_t p2ans = part2();


    std::cout << p1ans << '\n';
    std::cout << p2ans << '\n';
}
