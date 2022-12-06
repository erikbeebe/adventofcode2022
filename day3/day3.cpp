#include <cstring>
#include <fstream>
#include <iostream>
#include <hash_map>
#include <locale>
#include <set>
#include <string>
#include <sstream>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

#define ll long long;

int get_priority(char &c);

int main() {
    string filename = "day3.txt";
    ifstream infile (filename);
    string line;

    vector<string> rucksacks;

    if (infile.is_open()) {
        while (getline(infile, line)) {
            rucksacks.push_back(line);
        }
    }

    int priority_sum = 0;

    for (string &pack : rucksacks) {
        unordered_set<char> charset;

        int items = pack.length() / 2;
        cout << pack.length() << endl;

        for (int i=0; i<pack.length()/2; i++) {
            charset.emplace(pack[i]);
        }
        for (int i=pack.length()/2; i<pack.length(); i++) {
            if (charset.count(pack[i]) > 0) {
                priority_sum += get_priority(pack[i]);
                break;
            }
        }
    }
    cout << "part1: " << priority_sum << endl;

    // part2
    int part2_prio = 0;
    for (int i = 0; i<rucksacks.size(); i += 3) {
        set<char> a, b, c, tmp, intersect;

        for (int j=0; j<rucksacks[i].size(); j++) a.emplace(rucksacks[i][j]);
        for (int j=0; j<rucksacks[i+1].size(); j++) b.emplace(rucksacks[i+1][j]);
        for (int j=0; j<rucksacks[i+2].size(); j++) c.emplace(rucksacks[i+2][j]);
        }

        set_intersection(a.begin(), a.end(),
                         b.begin(), b.end(),
                         std::inserter(tmp, tmp.begin()));
        set_intersection(tmp.begin(), tmp.end(),
                         c.begin(), c.end(),
                         std::inserter(intersect, intersect.begin()));
        for (char x : intersect) {
            part2_prio += get_priority(x);
        }
    }
    cout << "part2: " << part2_prio << endl;
};

int get_priority(char &c) {
    // Lowercase item types a through z have priorities 1 through 26.
    // Uppercase item types A through Z have priorities 27 through 52.

    int cval = (int) c;

    if (isupper(c)) {
        return cval - 38;
    } else {
        return cval - 96;
    }
}