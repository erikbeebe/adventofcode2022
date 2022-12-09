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

#include "utils.h"

int main() {
    string filename = "input.txt";
    ifstream infile (filename);
    string line;

    int trees[99][99];

    if (!infile.is_open()) {
        throw runtime_error("Can't read file.");
    }

    int line_count = 0;

    // Populate arrays
    while (getline(infile, line)) {
        for (int i=0; i<line.length(); i++) {
            // convert integer stored in char to integer value
            trees[line_count][i] = line[i] - '0';
        }       
        line_count++;
    }

    // Part 1
    int visible_tree_counter = 0;
    set<pair<int,int>> visible_trees;

    // all trees on the exterior are visible
    int elements = sizeof(trees[0])/4;
    int max_tree_height;
    visible_tree_counter += (elements*4)-4;

    // Walk columns
    for (int column=1; column < elements-1; ++column) {
        // All trees have to be shorter than this tree
        max_tree_height = trees[0][column];

        for (int row=1; row < elements-1; ++row) {
            if (trees[row][column] > max_tree_height) {
                visible_trees.insert(make_pair(row, column));
                max_tree_height = trees[row][column];
            }
        }

        max_tree_height = trees[elements-1][column];

        for (int row=elements-1; row > 0; --row) {
            if (trees[row][column] > max_tree_height) {
                visible_trees.insert(make_pair(row, column));
                max_tree_height = trees[row][column];
            }
        }
    }

    // Walk each row, from left and from right
    for (int row=1; row < elements-1; ++row) {
        max_tree_height = trees[row][0];
        for (int column=1; column < elements-1; ++column) {
            if (trees[row][column] > max_tree_height) {
                visible_trees.insert(make_pair(row, column));
                max_tree_height = trees[row][column];
            }
        }

        max_tree_height = trees[row][elements-1];
        for (int column=elements-1; column > 0; --column) {
            if (trees[row][column] > max_tree_height) {
                visible_trees.insert(make_pair(row, column));
                max_tree_height = trees[row][column];
            }
        }
    }

    /*
    for (auto it = visible_trees.begin(); it != visible_trees.end(); ++it) {
        pair<int,int> p = *it;
        cout << "TREE: " << p.first << "," << p.second << endl;
    }
    */
    visible_tree_counter += visible_trees.size();
    cout << "Part 1: " << visible_tree_counter << endl;

    // Part 2
    // Walk each row, then each column, then check for blockages
    // in all four directions
    // If we're on any edge, the direction of the edge is 0
    int up,down,left,right,max_score;
    for (int row=0; row < elements; ++row) {
        for (int column=0; column < elements; ++column) {
            up = 0;
            down = 0;
            left = 0;
            right = 0;
            int us = trees[row][column];
            // Move in all four directions, until the limit of either the min/max element count
            // or until we encounter a tree the same height or taller than ours
            // and sum each of the trees encountered, including the tree which blocks the view
            // UP
            for (int x=row-1; x>-1; x--) {
                if (trees[x][column] < us) {
                    up++;
                } else {
                    up++;
                    break;
                }
            }
            // DOWN
            for (int x=row+1; x<elements; x++) {
                if (trees[x][column] < us) {
                    down++;
                } else {
                    down++;
                    break;
                }
            }
            // LEFT
            for (int x=column-1; x>-1; x--) {
                if (trees[row][x] < us) {
                    left++;
                } else {
                    left++;
                    break;
                }
            }
            // RIGHT
            for (int x=column+1; x<elements; x++) {
                if (trees[row][x] < us) {
                    right++;
                } else {
                    right++;
                    break;
                }
            }
            max_score = max(max_score, up * down * left * right);
        }
    }
    cout << "Part 2: " << max_score << endl;
};