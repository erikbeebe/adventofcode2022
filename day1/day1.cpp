#include <fstream>
#include <iostream>
#include <hash_map>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

#define ll long long;

int main() {
    string filename = "day1.txt";
    ifstream infile (filename);
    string line;
    int counter = 0;
    int max_value;

    if (infile.is_open()) {
        while (getline(infile, line)) {
            if (line.empty()) {
                max_value = max(max_value, counter);
                counter = 0;
            } else {
                counter += stoi(line);
            }
        }
        cout << "MAX: " << max_value << "\n";
    }
};