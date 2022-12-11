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

// Part 2
class OneRegComputer {
    typedef enum { addx, noop } VALID_INSTRUCTIONS;
    string INSTRUCTION_NAMES[2] = {"addx", "noop"};
    int CYCLES_REQUIRED[2] = {2, 1};

    struct instruction {
        VALID_INSTRUCTIONS op;
        int value;
    };
    
    // Enable debug output
    const bool debug = false;
    // Our one register, initialized to 1
    int x = 1;
    // Cycle begins at 1, not 0
    int cycle = 1;
    // Where to draw pixels
    int pixel_pos = 0;
    
    int next_check = 20;
    int signal_strength_sum;
    deque<instruction> instructions;

    const int arraySize = 240;
    vector<char> crt = vector<char>(arraySize, '.');

    public:
        void add_instruction(string op, int value) {
            VALID_INSTRUCTIONS e_op;
            if (op.compare("noop") == 0) {
                e_op = noop;
            } else if (op.compare("addx") == 0) {
                e_op = addx;
            }

            instructions.push_back({e_op, value});
        }

        void print_an_ins() {
            cout << instructions[0].op << " " << instructions[0].value << endl;
        }

        void run() {
            for (auto &ins : instructions) {
                if (debug) cout << "BEGINNING CYCLE: " << cycle << " X: " << x << endl;

                if (ins.op == noop) {
                    update_display();
                    cycle += 1;
                    check_signal_strength();

                } else if (ins.op == addx) {
                    update_display();
                    cycle += 1;
                    check_signal_strength();

                    update_display();
                    cycle += 1;
                    x += ins.value;
                    check_signal_strength();
                }
                if (debug) cout << "ENDING CYCLE: " << cycle << " op: " << INSTRUCTION_NAMES[ins.op] << " val: " << ins.value << " X: " << x << endl;
            }

            cout << "Part 1: " << signal_strength_sum << endl;
            cout << "Part 2: " << endl;
            show_display();
        }
    private:
        // Display is 40 x 6 pixels
        // Index starts at 0 (eg. 0-39 row 1)
        void update_display() {
            // If the sprite is positioned such that one of its three pixels is the pixel
            // currently being drawn, the screen produces a lit pixel (#); otherwise, the screen leaves the pixel dark (.).
            if ((abs(pixel_pos%40 - x)) < 2) {
                crt[cycle-1] = '#';
            } else {
                crt[cycle-1] = '.';
            }
            ++pixel_pos;
        }

        void show_display() {
            for (int i=0, j=1; i < crt.size(); ++i, ++j) {
                cout << crt[i];
                if ((j % 40) == 0) cout << endl;
            }
            cout << endl;
        }

        void check_signal_strength() {
            // Record strength at cycle 20, then cycle+=40 until 220
            if (cycle == next_check && next_check <= 220) {
                signal_strength_sum += cycle * x;
                next_check += 40;
            }
        }
};

int main() {
    string filename = "input.txt";
    ifstream infile (filename);
    string line;

    OneRegComputer c;

    while (getline(infile, line)) {
        istringstream ss(line);
        string instruction, value;
        ss >> instruction >> value;

        c.add_instruction(instruction, (!value.empty()) ? stoi(value) : -1);
    }

    c.run();
};