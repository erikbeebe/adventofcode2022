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

class Filesystem {
    enum dentry_type {
        directory,
        file
    };

    // Filesystem inode-ish
    struct Node {
        // contains size of directory, and all subdirectories
        size_t size;
        // filename
        string name;
        dentry_type type;
        Node *parent_directory = nullptr;
        vector<Node *> directories;
        vector<Node *> files;
    };

    struct Node *root = new Node;
    struct Node *cwd;
    int total_size = 0;
    int target_delete_size = 0;
    const int TOTAL_FILESYSTEM_SIZE = 70000000;
    const int MINIMUM_SPACE_REQUIRED = 30000000;
    vector<Node *> visited;
    vector<int> eligable_directories;

    public:
        // Sum all directories <= 100k
        void dfsPart1(Node *n) {
            if (n->directories.size() == 0) {
                 // Reached a directory with no more children
                 if (n->size < 1e5) total_size += n->size;
                 return;
            }

            // Descend into child directories
            for (Node *file : n->directories) {
                if (!count(visited.begin(), visited.end(), file)) {
                    dfsPart1(file);
                }
                if (n->size < 1e5) total_size += n->size;
            }
        }

        // Find smallest directory that's at least minimum_delete_size large
        void dfsPart2(Node *n, int &minimum_delete_size) {
            if (n->directories.size() == 0) {
                 // Reached a directory with no more children
                 if (n->size > minimum_delete_size) eligable_directories.push_back(n->size);
                 return;
            }

            // Descend into child directories
            for (Node *file : n->directories) {
                if (!count(visited.begin(), visited.end(), file)) {
                    dfsPart2(file, minimum_delete_size);
                }
                if (n->size > minimum_delete_size) eligable_directories.push_back(n->size);
            }
        }

        void dfsPart1Runner() {
            dfsPart1(root);
            cout << "Part 1: " << total_size << endl;
        }

        void dfsPart2Runner() {
            int minimum_delete_size = MINIMUM_SPACE_REQUIRED - (TOTAL_FILESYSTEM_SIZE - root->size);
            dfsPart2(root, minimum_delete_size);
            sort(eligable_directories.begin(), eligable_directories.end());
            cout << "Part 2: " << eligable_directories[0] << endl;
        }

        int run() {
            string filename = "input.txt";
            //string filename = "sample.txt";
            ifstream infile (filename);
            string line;

            cwd = root;
            root->name = "/";

            if (! infile.is_open()) {
                throw runtime_error("File not open, this is not good.");
            }

            int linectr = 0;
            while (getline(infile, line)) {
                //cout << "LINE: " << line << " " << linectr << endl;
                linectr++;
                if (line.rfind("$ cd ", 0) == 0) {
                    // Change directory
                    string d = get_directory(line);
                    
                    change_directory(d);
                } else if (line.rfind("$ ls", 0) == 0) {
                    // NO OP
                } else if (line.rfind("dir", 0) == 0) {
                    // Directory entry
                    Node* d = new Node;
                    d->name = get_file_name(line);
                    d->size = 0;
                    d->parent_directory = cwd;

                    cwd->directories.push_back(d);
                } else if (isdigit(line[0])) {
                    // File
                    // Create a node for the file, and append it to cwd's files list
                    Node* f = new Node;

                    f->name = get_file_name(line);
                    f->size = get_file_size(line);
                    f->type = file;
                    cwd->files.push_back(f);

                    // Update size for all parents too
                    Node *parent = cwd;
                    while (parent != NULL) {
                        parent->size += f->size;
                        parent = parent->parent_directory;
                    }
                }
            }
            return 0;
        };

    private:
        void change_directory(string directory) {
            if (directory.compare("..") == 0) {
                // Up one level
                if (cwd->parent_directory != NULL) {
                    cwd = cwd->parent_directory;
                } else {
                    cout << "ALREADY AT TOP LEVEL" << endl;
                }
            } else if (directory.compare("/") == 0 ) {
                cwd = root;
            } else {
                for (auto &file : cwd->directories) {
                    if (file != NULL) {
                        //cout << "FILE: " << file->name << " SIZE: " << file->size << endl;
                        if (file->name.compare(directory) == 0) {
                            cwd = file;
                        }
                    }
                }
            }
        }

        string get_directory(string& line) {
            string cd_array[3];
            istringstream ss(line);
            int i=0;

            while (ss.good() && i<3) {
                ss >> cd_array[i];
                ++i;
            }
            
            return cd_array[2];
        }

        int get_file_size(string& line) {
            string size_array[2];
            istringstream ss(line);
            int i=0;

            while (ss.good() && i<2) {
                ss >> size_array[i];
                ++i;
            }
            
            return stoi(size_array[0]);
        }

        string get_file_name(string& line) {
            string file_array[2];
            istringstream ss(line);
            string junk;
            string name;
            
            ss >> junk >> name;
            return name;
        }

        string get_directory_stack(stack<string> &s, string &str) {
            if (s.empty()) {
                return "";
            }

            string tmp = s.top();

            str.append("/");
            str.append(tmp);
            s.pop();

            str.append(get_directory_stack(s, str));

            s.push(tmp);
        }

        void print_stack(stack<string> &s) {
            if (s.empty()) {
                cout << endl;
                return;
            }

            string tmp = s.top();
            s.pop();

            print_stack(s);

            cout << "ENTRY: " << tmp << " ";
            s.push(tmp);
        }
};

int main() {
    Filesystem f;
    f.run();
    f.dfsPart1Runner();
    f.dfsPart2Runner();
}