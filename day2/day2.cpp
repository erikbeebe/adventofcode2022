#include <cstring>
#include <fstream>
#include <iostream>
#include <hash_map>
#include <string>
#include <sstream>
#include <string_view>
#include <unordered_map>
#include <vector>

using namespace std;

#define ll long long;

int main() {
    string filename = "day2.txt";
    ifstream infile (filename);
    string line;

    unordered_map<string, int> scores;
    scores["A"] = 1;
    scores["B"] = 2;
    scores["C"] = 3;
    scores["X"] = 1;
    scores["Y"] = 2;
    scores["Z"] = 3;

    unordered_map<string, string> rmap;
    rmap["A"] = "rock";
    rmap["B"] = "paper";
    rmap["C"] = "scissors";
    rmap["X"] = "rock";
    rmap["Y"] = "paper";
    rmap["Z"] = "scissors";

    unordered_map<string, string> lose;
    lose["B"] = "A";
    lose["C"] = "B";
    lose["A"] = "C";
    unordered_map<string, string> win;
    win["A"] = "B";
    win["B"] = "C";
    win["C"] = "A";

    // 0 == lost, 3 == draw, 6 == win
    // Then, a winner for that round is selected:
    // Rock defeats Scissors, Scissors defeats Paper,
    // and Paper defeats Rock. If both players choose the
    // same shape, the round instead ends in a draw.

    int score = 0;

    vector<pair<string, string>> plays;

    string them, us;
    if (infile.is_open()) {
        while (getline(infile, line)) {
            istringstream ssin (line);
            ssin >> them;
            ssin >> us;

            plays.push_back(make_pair(them, us));
        }
    }

    for (auto& play : plays) {
        them = play.first;
        us = play.second;
        score += scores[us];

        // determine winner
        if (them.compare("A") == 0 && us.compare("Y") == 0) {
            score += 6;
        } else if (them.compare("B") == 0 && us.compare("Z") == 0) {
            score += 6;
        } else if (them.compare("C") == 0 && us.compare("X") == 0) {
            score += 6;
        } else if (strcmp(rmap[them].c_str(), rmap[us].c_str()) == 0) {
            score += 3;
        } 
    }

    cout << "score1: " << score << endl;

    // part 2
    int score2 = 0;

    for (auto& play : plays) {
        them = play.first;
        us = play.second;

        // determine winner
        // "Anyway, the second column says how the round needs to end:
        // X means you need to lose, Y means you need to end the round
        // in a draw, and Z means you need to win.
        if (us.compare("Y") == 0) {
            // Should end in a draw, so pick same as them
            score2 += scores[them];
            score2 += 3;
        } else if (us.compare("X") == 0) {
            // lose, so if them is paper, we choose rock, 
            // if them is rock, we choose scissors, if them is 
            // scissors, we choose paper
            score2 += scores[lose[them]];
        } else if (us.compare("Z") == 0) {
            // win
            score2 += scores[win[them]];
            score2 += 6;
        }
    }

    cout << "score2: " << score2 << endl;

};