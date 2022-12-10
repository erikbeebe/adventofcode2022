#include <algorithm>
#include <cstring>
#include <deque>
#include <fstream>
#include <iostream>
#include <hash_map>
#include <locale>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <sstream>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class RopePart1 {
    // Initial state == head is covering tail, same x/y coords
    // When moving the head, change direction and move x/y
    char direction;
    pair<int,int> head = make_pair(0,0);
    pair<int,int> tail = make_pair(0,0);
    // Initialize and include the default position so it's counted in the total
    set<pair<int,int>> visited = {make_pair(0,0)};

    public:
        void move(char type) {
            switch (type) {
                case 'U':
                    head.second--;
                    break;
                case 'D':
                    head.second++;
                    break;
                case 'L':
                    head.first--;
                    break;
                case 'R':
                    head.first++;
                    break;
            }

            this->move_tail();
        }

        pair<int,int> get_head() {
            return head;
        }

        pair<int,int> get_tail() {
            return tail;
        }

        size_t get_visited_count() {
            return visited.size();
        }

    private:
        int get_direction(int diff) {
            if (diff == 0) {
                return 0;
            } else if (diff > 0) {
                return 1;
            } else {
                return -1;
            }
        }
        void move_tail() {
            int x_diff = head.first - tail.first;
            int y_diff = head.second - tail.second;

            if (abs(x_diff) <= 1 && abs(y_diff) <= 1) {
                return;
            } else {
                tail.first += get_direction(x_diff);
                tail.second += get_direction(y_diff);
                visited.insert(make_pair(tail.first, tail.second));
            }
        }
};

class RopePart2 {
    // Initial state == head is covering tail, same x/y coords
    // When moving the head, change direction and move x/y
    char direction;
    // head == index 0
    pair<int,int> positions[10] = {make_pair(0,0)};
    
    // Initialize and include the default position so it's counted in the total
    set<pair<int,int>> visited = {make_pair(0,0)};

    public:
        void move(char type) {
            switch (type) {
                case 'U':
                    positions[0].second--;
                    break;
                case 'D':
                    positions[0].second++;
                    break;
                case 'L':
                    positions[0].first--;
                    break;
                case 'R':
                    positions[0].first++;
                    break;
            }

            for (int i=1; i<10; i++) {
                this->move_tail(i);
            }
        }

        pair<int,int> get_head() {
            return positions[0];
        }

        pair<int,int> get_tail() {
            return positions[9];
        }

        size_t get_visited_count() {
            return this->visited.size();
        }

    private:
        int get_direction(int diff) {
            if (diff == 0) {
                return 0;
            } else if (diff > 0) {
                return 1;
            } else {
                return -1;
            }
        }

        void move_tail(int idx) {
            int x_diff = positions[idx-1].first - positions[idx].first;
            int y_diff = positions[idx-1].second - positions[idx].second;

            if (abs(x_diff) <= 1 && abs(y_diff) <= 1) {
                return;
            } else {
                positions[idx].first += get_direction(x_diff);
                positions[idx].second += get_direction(y_diff);
                
                // record location if tail
                if (idx == 9) visited.insert(make_pair(positions[idx].first, positions[idx].second));
            }
        }
};

int main() {
    string filename = "input.txt";
    ifstream infile (filename);
    string line;

    vector<pair<char, int>> moves;

    while (getline(infile, line)) {
        istringstream ss(line);
        string direction;
        string count;

        ss >> direction;
        ss >> count;
        
        char idirection = direction[0];
        int icount = stoi(count);

        //cout << "LINE: " << direction << " " << icount << endl;
        moves.push_back(make_pair(idirection, icount));
    }

    RopePart1 rp1;
    for (auto &move : moves) {
        //cout << "MOVE: X=" << move.first << " Y=" << move.second << endl;

        for (int i=0; i<move.second; i++) {
            rp1.move(move.first);

            pair<int,int> h = rp1.get_head();
            pair<int,int> t = rp1.get_tail();
            //cout << "HEAD: X=" << h.first << " Y=" << h.second << " TAIL: X=" << t.first << " Y=" << t.second << endl;
        }
    }
    cout << "Part 1: " << rp1.get_visited_count() << endl;

    RopePart2 rp2;
    for (auto &move : moves) {
        //cout << "MOVE: X=" << move.first << " Y=" << move.second << endl;

        for (int i=0; i<move.second; i++) {
            rp2.move(move.first);

            pair<int,int> h = rp2.get_head();
            pair<int,int> t = rp2.get_tail();
            //cout << "HEAD: X=" << h.first << " Y=" << h.second << " TAIL: X=" << t.first << " Y=" << t.second << endl;
        }
    }
    cout << "Part 2: " << rp2.get_visited_count() << endl;
};
