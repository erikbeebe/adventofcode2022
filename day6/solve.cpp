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

int find_distinct_chars(string &str, int num_chars);

int main() {
    string filename = "input.txt";
    ifstream infile (filename);
    string line;

    if (infile.is_open()) {
        getline(infile, line);
    }

    cout << "Part 1: " << find_distinct_chars(line, 4) << endl;
    cout << "Part 2: " << find_distinct_chars(line, 14) << endl;
};

int find_distinct_chars(string &str, int num_chars) {
    for (int i=0; i < str.length(); i++) {
        unordered_set<char> s;

        for (int j=i; j < i+num_chars; j++) {
            s.insert(str[j]);
        }

        if (s.size() == num_chars) {
            return i + num_chars;
            break;
        }
    }
}