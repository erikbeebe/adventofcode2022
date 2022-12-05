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
vector<string> split(string strToSplit, char delimeter);
pair<int,int> splitToPair(string strToSplit);

int main() {
    string filename = "input.txt";
    ifstream infile (filename);
    string line;

    vector<vector<pair<int,int>>> assignments;

    if (infile.is_open()) {
        while (getline(infile, line)) {
            vector<string> splitted = split(line, ',');
            vector<pair<int,int>> vp;
            pair<int,int> lp = splitToPair(splitted[0]);
            pair<int,int> rp = splitToPair(splitted[1]);
            vp.push_back(lp);
            vp.push_back(rp);
            assignments.push_back(vp);
        }
    }

    // how many ranges entirely contain the other range
    int ranges = 0;

    for (vector<pair<int,int>> a : assignments) {
        // a[0]  a[1]
        // 2-4, 6-8
        if ((a[0].first <= a[1].first) && (a[0].second >= a[1].second)) {
            ranges += 1;
        } else if ((a[1].first <= a[0].first) && (a[1].second >= a[0].second)) {
            ranges += 1;
        }
    }

    // 571
    cout << "part1: " << ranges << endl;

    int rangesp2 = 0;

    // check for any overlap
    for (vector<pair<int,int>> a : assignments) {
        if ((a[0].first <= a[1].first) && (a[0].second >= a[1].first)) {
            rangesp2 += 1;
        } else if ((a[1].first <= a[0].first) && (a[1].second >= a[0].first)) {
            rangesp2 += 1;
        }
    }

    // 571
    cout << "part2: " << rangesp2 << endl;




};

vector<string> split(string strToSplit, char delimeter) {
    stringstream ss(strToSplit);
    string item;
    vector<string> splittedStrings;
    while (getline(ss, item, delimeter)) {
       splittedStrings.push_back(item);
    }

    return splittedStrings;
}

pair<int,int> splitToPair(string strToSplit) {
    string lstring;
    string rstring;

    stringstream ss(strToSplit);

    getline(ss, lstring, '-');
    getline(ss, rstring);

    return make_pair(stoi(lstring), stoi(rstring));
}