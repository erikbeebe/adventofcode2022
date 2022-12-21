#include <bits/stdc++.h>

using namespace std;

const bool debug = false;
vector<vector<char>> route;

struct Node {
    int x, y;
    int distance = 0;
};

class HillClimb {
    pair<int, int> start;
    pair<int, int> end;
    queue<pair<int,int>> v;

public:
    void run() {
        start = find('S');
        route[start.first][start.second] = 'a';
        cout << "S: " << start.first << " " << start.second << endl;

        end = find('E');
        route[end.first][end.second] = 'z';
        cout << "E: " << end.first << " " << end.second << endl;

        int x = start.first;
        int y = start.second;
        Node start = {x, y, 0};

        cout << "Part 1: " << bfs(start) << endl;
        cout << "Part 2: " << part2() << endl;
    }

private:
    int part2() {
        vector<int> steps;
        for (auto a : find_all_a()) {
            int s = bfs(a);
            if (s > 0) steps.push_back(s);
        }
        sort(steps.begin(), steps.end());
        return steps[0];
    }

    vector<Node> find_all_a() {
        vector<Node> v;
        for (int i=0; i<route.size(); ++i) {
            for (int j=0; j<route[i].size(); ++j) {
                if (route[i][j] == 'a') {
                    Node n = {i, j, 0};
                    v.push_back(n);
                }
            }
        }
        return v;
    }

    bool is_valid_path(Node &cur, Node &target, set<pair<int,int>> &visited) {
        if (target.x < 0 || target.x > (route.size()-1) || target.y < 0 || (target.y > route[0].size()-1)) {
            //cout << "NOT VALID: " << target.x << "," << target.y << endl;
            return false;
        }

        if (std::find(visited.begin(), visited.end(), make_pair(target.x, target.y)) != visited.end()) {
            //cout << "Already visited: " << target.x << " " << target.y << endl;
            return false;
        }

        char current_char = route[cur.x][cur.y];
        char target_char = route[target.x][target.y];

        if (((int)target_char - (int)current_char) > 1) {
            return false;
        }


        return true;
    }

    // X == W,E   Y = N,S
    int bfs(Node &node) {
        queue<Node> q;
        //vector<pair<int,int>> visited;
        set<pair<int,int>> visited;

        q.push(node);
        visited.insert(make_pair(node.x, node.y));

        while (!q.empty()) {
            Node n = q.front();
            q.pop();
            
            if (n.x == end.first && n.y == end.second) {
                return n.distance;
            }

            // Possible paths
            Node N = {n.x-1, n.y, n.distance+1};
            Node S = {n.x+1, n.y, n.distance+1};
            Node W = {n.x, n.y-1, n.distance+1};
            Node E = {n.x, n.y+1, n.distance+1};

            vector<Node> valid_paths;

            // Valid paths from here
            if (is_valid_path(n, N, visited)) valid_paths.push_back(N);
            if (is_valid_path(n, S, visited)) valid_paths.push_back(S);
            if (is_valid_path(n, W, visited)) valid_paths.push_back(W);
            if (is_valid_path(n, E, visited)) valid_paths.push_back(E);

            for (auto &path : valid_paths) {
                q.push(path);
                visited.insert(make_pair(path.x, path.y));
            }
        }
        return -1;
    }

    pair<int, int> find(char target) {
        for (int i=0; i<route.size(); ++i) {
            for (int j=0; j<route[i].size(); ++j) {
                if (route[i][j] == target) {
                    return make_pair(i, j);
                }
            }
        }
        return make_pair(-1, -1);
    }
};

int main() {
    string filename = "input.txt";
    ifstream infile (filename);
    string line;

    // elevation, a = lowest, ..., z = highest
    // current location = S
    // best signal = E
    // move one square at a time, up/down/left/right, not diag
    while (getline(infile, line)) { 
        vector<char> v;
        for (int i=0; i<line.size(); ++i) {
            v.push_back(line[i]);
        };
        route.push_back(v);
    }

    HillClimb hc;
    hc.run();
}