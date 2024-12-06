#include <iostream>
#include <fstream>
#include <vector>

std::vector<std::string> map;
int x, y;
std::string DIR_ARROW = "^>v<";

int part1(int dir){
    int visited_count = 1;
    map[y][x] = 'X';
    int next_x = dir == 1 ? x + 1 : dir == 3 ? x - 1 : x;
    int next_y = dir == 0 ? y - 1 : dir == 2 ? y + 1 : y;
    while (next_x >= 0 && next_y >= 0 && next_x < map.size() && next_y < map[0].size()) {
        switch (map[next_y][next_x]) {
            case '.':
                map[next_y][next_x] = 'X';
                visited_count++;
                x = next_x;
                y = next_y;
            case 'X':
                x = next_x;
                y = next_y;
                break;
            case '#':
                dir = (dir + 1)%4;
                break;
        }
        next_x = dir == 1 ? x + 1 : dir == 3 ? x - 1 : x;
        next_y = dir == 0 ? y - 1 : dir == 2 ? y + 1 : y;

    }
    return visited_count;
}

int part2bruteforce (int dir) {
    int startingdir = dir;
    int ans = 0;
    for (int row = 0; row < map.size(); row++) {
        for (int col = 0; col < map[0].size(); col++) {
            if (map[row][col] == '.') {
                dir = startingdir;
                int cx = x;
                int cy = y;
                int checks = map.size() * map[0].size();
                std::vector<std::string> mapcopy(map);
                mapcopy[row][col] = '#';

                mapcopy[cy][cx] = 'X';
                int next_x = dir == 1 ? cx + 1 : dir == 3 ? cx - 1 : cx;
                int next_y = dir == 0 ? cy - 1 : dir == 2 ? cy + 1 : cy;
                while (checks > 0 && next_x >= 0 && next_y >= 0 && next_x < map.size() && next_y < map[0].size()) {
                    switch (mapcopy[next_y][next_x]) {
                        case '#':
                            dir = (dir + 1)%4;
                            break;
                        case '.':
                            mapcopy[next_y][next_x] = 'X';
                        case 'X':
                            cx = next_x;
                            cy = next_y;
                            checks--;
                            break;
                    }
                    next_x = dir == 1 ? cx + 1 : dir == 3 ? cx - 1 : cx;
                    next_y = dir == 0 ? cy - 1 : dir == 2 ? cy + 1 : cy;
                }
                if (checks == 0) ans++;
            }

        }

    }
    return ans;
}

bool check_loopable(int dir) {
    int tempx = x;
    int tempy = y;
    while (tempx >= 0 && tempy >= 0 && tempx < map.size() &&  tempy < map[0].size()) {
        int ntempx = dir == 1 ? tempx + 1 : dir == 3 ? tempx - 1 : tempx;
        int ntempy = dir == 0 ? tempy - 1 : dir == 2 ? tempy + 1 : tempy;

        if (map[ntempy][ntempx] == '#') {
            dir = (dir + 1)% 4;
        } else {
            int visit_bitmap = map[tempy][tempx] - '.';
            int bitmask = std::pow(2, dir);
            if ((visit_bitmap & bitmask) == bitmask) {
                return true;
            }
        }
    }
    return false;
}

int part2(int dir) {
    int block_count = 0;
    map[y][x] = '.';
    int next_x = dir == 1 ? x + 1 : dir == 3 ? x - 1 : x;
    int next_y = dir == 0 ? y - 1 : dir == 2 ? y + 1 : y;
    while (next_x >= 0 && next_y >= 0 && next_x < map.size() && next_y < map[0].size()) {
        char c;
        int visit_bitmap;
        switch (c = map[next_y][next_x]) {
            case '#':
                dir = (dir + 1)%4;
                break;
            default:
                int visit_bitmap = map[y][x] - '.';
                visit_bitmap ^= (int)std::pow(2, dir);
                map[y][x] = '.' + visit_bitmap;
                if (check_loopable((dir + 1) % 4)) block_count++;
                x = next_x;
                y = next_y;
                break;
        }
        next_x = dir == 1 ? x + 1 : dir == 3 ? x - 1 : x;
        next_y = dir == 0 ? y - 1 : dir == 2 ? y + 1 : y;

    }
    return block_count;

}

int main(void) {
    std::fstream input_stream("day6.in");
    std::string line;
    int count = 0;
    int dir;

    while (getline(input_stream, line)) {
        if (line.find_first_of("<>^v") != std::string::npos) {
            x = line.find_first_of("<>^v");
            switch(line.at(x)){
                case '^':
                    dir = 0;
                    break;
                case '>':
                    dir = 1;
                    break;
                case 'v':
                    dir = 2;
                    break;
                case '<':
                    dir = 3;
                    break;
            }
            y = count;
        }
        map.push_back(line);
        count++;
    }
    //int part1ans = part1(dir);
    //std::cout << part1ans << std::endl;
    int part2ans = part2bruteforce(dir);
    std::cout << part2ans << std::endl;

}
