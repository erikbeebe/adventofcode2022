#include <cstring>
#include <deque>
#include <fstream>
#include <iostream>
#include <hash_map>
#include <locale>
#include <set>
#include <stack>
#include <string>
#include <sstream>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

#include "utils.h"

#define ll long long;

int main() {
    string filename = "input.txt";
    ifstream infile (filename);
    string line;

    int cols = 9;
    vector<deque<char>> vsc;

    for (int i=0; i<cols; i++) vsc.push_back(deque<char>());

    if (infile.is_open()) {
        while (getline(infile, line) && (line[0] != '\0')) {
            for (size_t i=1,j=0; i<line.length(); i+=4,j++) {
                if (line[i] != ' ' && !(isdigit(line[i]))) {
                    vsc[j].push_front(line[i]);
                }
            }
        }
    }

    while (getline(infile, line)) {
        string garbage, qty, from, to;
        istringstream ssin (line);
        ssin >> garbage;
        ssin >> qty;
        ssin >> garbage;
        ssin >> from;
        ssin >> garbage;
        ssin >> to;
    
        int q = stoi(qty);
        int f = stoi(from);
        int t = stoi(to);

        // move crates
        deque<char> s;
        for (int z=0; z<q; z++) {
            s.push_back(vsc[f-1].back());
            vsc[f-1].pop_back();
        }

        for (int z=0; z<q; z++) {
            vsc[t-1].push_back(s.back());
            s.pop_back();
        }
    }

    cout << "part2: ";
    for (int x=0; x<cols; x++) {
        cout << vsc[x].back();
    }
    cout << endl;
};